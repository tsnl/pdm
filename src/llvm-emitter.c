// EMITTER: generates LLVM IR from a typed, solved AST.
// - requires AST correctness
// - requires each type to have a concrete soln

// TWO PASSES: exportModuleHeaders & exportModule
// * goal: export each 'def' statement.
// - headers: forward declarations
//   - each anonymous function has a 'synthetic' function definition inserted at module-level.
//     - synthetic functions are defined in exportModuleHeaderVisitor
//     - synthetic functions can be renamed by 'def' statements.
//   - rename synthetic functions for 'def' statements
//   - only declared, never defined
// - module: writing synthetic functions' bodies
//   - exportvalue & return each lambda body


// Have you configured LLVM IR Autocompletion?
// The CMake config should spit out LLVM header paths you can use.

// See `github.com/f0rki`'s "Mapping High Level Constructs to LLVM IR"
// - https://github.com/f0rki/mapping-high-level-constructs-to-llvm-ir
// - https://mapping-high-level-constructs-to-llvm-ir.readthedocs.io/en/latest/README.html

// See Paul Smith's "How to Get Started with LLVM C API"
// - https://www.pauladamsmith.com/blog/2015/01/how-to-get-started-with-llvm-c-api.html

// See Eli Bendersky's Python implementation of the LLVM Kaleidoscope demo:
// - https://github.com/eliben/pykaleidoscope/blob/master/chapter3and4.py

// See wickedchicken's GitHub examples:
// - https://github.com/wickedchicken/llvm-c-example/blob/master/fac.c


#include "llvm-emitter.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "stb/stretchy_buffer.h"

#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>

#include "useful.h"
#include "primer.h"
#include "unicoder.h"

typedef struct Emitter Emitter;
struct Emitter {
    Typer* typer;
    LLVMValueRef currentLlvmFunction;
    LLVMModuleRef module;
    LLVMBuilderRef builder;
};
static Emitter newEmitter(Typer* typer, char const* moduleName);

Emitter newEmitter(Typer* typer, char const* moduleName) {
    Emitter emitter;
    emitter.typer = typer;
    emitter.builder = LLVMCreateBuilder();
    emitter.module = LLVMModuleCreateWithName(moduleName);
    emitter.currentLlvmFunction = NULL;
    return emitter;
}

typedef struct ExportedType ExportedType;
typedef struct ExportedValue ExportedValue;

struct ExportedType {
    Type* native;
    LLVMTypeRef llvm;
};
struct ExportedValue {
    AstNode* native;
    LLVMValueRef llvm;
    ExportedType type;
};
static int exportModuleHeaders(Emitter* emitter, AstNode* moduleNode);
static int exportModule(Emitter* emitter, AstNode* moduleNode);
static int exportModuleHeaders_postVisitor(void* emitter, AstNode* node);
static int exportModule_preVisitor(void* emitter, AstNode* node);
static ExportedType exportType(Typer* typer, Type* type);
static ExportedValue exportValue(Emitter* emitter, AstNode* exprNode);

//
//
// End of WIP
//
//

static void buildLlvmField(Typer* typer, void* sb, SymbolID name, Type* type);

int exportModuleHeaders(Emitter* emitter, AstNode* moduleNode) {
    return RecursivelyVisitAstNode(emitter,moduleNode,NULL,exportModuleHeaders_postVisitor);
}
int exportModule(Emitter* emitter, AstNode* moduleNode) {
    return RecursivelyVisitAstNode(emitter,moduleNode,exportModule_preVisitor,NULL);
}
int exportModuleHeaders_postVisitor(void* rawEmitter, AstNode* node) {
    Emitter* emitter = rawEmitter;
    
    AstKind nodeKind = GetAstNodeKind(node);
    if (nodeKind == AST_VLAMBDA) {
        // adding a synthetic function, setting as node's LlvmRepr
        Type* funcType = GetAstNodeTypingExt_Value(node);
        ExportedType exportedFuncType = exportType(emitter->typer,funcType);
        ExportedValue* funcValue = malloc(sizeof(ExportedValue));
        funcValue->native = node;
        funcValue->type = exportedFuncType;
        funcValue->llvm = LLVMAddFunction(emitter->module,"synthetic-function",exportedFuncType.llvm);
        LLVMSetFunctionCallConv(funcValue->llvm,LLVMCCallConv);

        SetAstNodeLlvmRepr(node,funcValue);
    } 
    else if (nodeKind == AST_STMT_EXTERN) {
        // similar to lambda:
        AstNode* externNode = node;
        char const* nameStr = GetSymbolText(GetAstExternStmtName(externNode));
        Type* funcType = GetAstNodeTypingExt_Value(externNode);
        ExportedType exportedFuncType = exportType(emitter->typer,funcType);
        ExportedValue* externValue = malloc(sizeof(ExportedValue));
        externValue->native = externNode;
        externValue->type = exportedFuncType;
        externValue->llvm = LLVMAddFunction(emitter->module,nameStr,exportedFuncType.llvm);
        LLVMSetFunctionCallConv(externValue->llvm,LLVMCCallConv);
        
        SetAstNodeLlvmRepr(externNode,externValue);
    }
    else if (nodeKind == AST_STMT_VDEF) {
        AstNode* vdef = node;

        // note: exportValue(RHS) = the synthetic for this function.
        SymbolID lhs = GetAstDefValueStmtLhs(vdef);
        AstNode* rhsNode = GetAstDefValueStmtRhs(vdef);
        ExportedValue exportedRhs = exportValue(emitter,rhsNode);
        LLVMSetValueName(exportedRhs.llvm,GetSymbolText(lhs));
        
        ExportedValue* llvmRepr = malloc(sizeof(ExportedValue));
        *llvmRepr = exportedRhs;

        SetAstNodeLlvmRepr(vdef,llvmRepr);
    }
    else if (nodeKind == AST_LITERAL_STRING) {
        AstNode* literalString = node;
        Utf8String utf8string = GetAstStringLiteralValue(literalString);
        LLVMValueRef llvm_utf8string = LLVMConstString((char const*)utf8string.buf,utf8string.count,1);

        Type* stringType = GetAstNodeTypingExt_Value(literalString);

        ExportedValue* expVal = malloc(sizeof(ExportedValue));
        expVal->native = node;
        expVal->type = exportType(emitter->typer,stringType);
        expVal->llvm = LLVMAddGlobal(emitter->module,LLVMTypeOf(llvm_utf8string),"literal_string");
        LLVMSetInitializer(expVal->llvm,llvm_utf8string);
        LLVMSetLinkage(expVal->llvm, LLVMInternalLinkage);
        LLVMSetGlobalConstant(expVal->llvm,1);

        SetAstNodeLlvmRepr(literalString, expVal);
    }
    return 1;
}
int exportModule_preVisitor(void* rawEmitter, AstNode* node) {
    Emitter* emitter = rawEmitter;
    AstKind nodeKind = GetAstNodeKind(node);
    
    if (nodeKind == AST_VLAMBDA) {
        // acquiring synthetic:
        ExportedValue* syntheticFunctionExportedValue = GetAstNodeLlvmRepr(node);
        LLVMValueRef syntheticFunction = syntheticFunctionExportedValue->llvm;

        // setting the current function for emission (must be unset before end of block):
        COMPILER_ASSERT(emitter->currentLlvmFunction == NULL, "Accidentally clobbering emitted func <=> dirty state.");
        emitter->currentLlvmFunction = syntheticFunction;

        // adding an entry BB:
        LLVMBasicBlockRef entryBlock = LLVMAppendBasicBlock(emitter->currentLlvmFunction,"entry");
        LLVMPositionBuilderAtEnd(emitter->builder,entryBlock);
        
        // adding arguments to the entry BB:
        AstNode* lambda = node;
        AstNode* pattern = GetAstVLambdaPattern(lambda);
        int argCount = GetAstPatternLength(pattern);
        for (int index = 0; index < argCount; index++) {
            AstNode* argField = GetAstPatternFieldAt(pattern,index);
            LLVMValueRef llvmArg = LLVMGetParam(emitter->currentLlvmFunction,index);

            ExportedType argExpType = exportType(emitter->typer,GetAstNodeTypingExt_Value(argField));

            LLVMValueRef llvmArgMem; {
                char* argExpName = fmt("arg:%d-%s",index,GetSymbolText(GetAstFieldName(argField)));
                llvmArgMem = LLVMBuildAlloca(emitter->builder,argExpType.llvm,argExpName);
                free(argExpName);
            }

            LLVMBuildStore(emitter->builder,llvmArg,llvmArgMem);
            
            ExportedValue* argExpVal = malloc(sizeof(ExportedValue));
            argExpVal->native = argField;
            argExpVal->type = argExpType;
            argExpVal->llvm = llvmArgMem;
            SetAstNodeLlvmRepr(argField,argExpVal);
        }

        // exporting the body:
        ExportedValue returnValue = exportValue(emitter,GetAstVLambdaBody(node));
        
        // returning the body's value:
        // - most datatypes store references to the stack. These references must be loaded before return.
        // - sniff test: is it mutable? if so, it must be loaded from the stack!
        LLVMValueRef returnValueLlvm = returnValue.llvm;
        switch (GetTypeKind(returnValue.type.native)) {
            case T_UNIT:
            {
                returnValueLlvm = NULL;
                break;
            }
            case T_INT:
            case T_FLOAT:
            {
                returnValueLlvm = LLVMBuildLoad(emitter->builder,returnValueLlvm,"loaded_for_return");
                break;
            }
            default:
            {
                TypeKind typeKind = GetTypeKind(returnValue.type.native);
                COMPILER_ERROR_VA("NotImplemented: return for typekind %s", TypeKindAsText(typeKind));
                break;
            }
        }
        LLVMBuildRet(emitter->builder,returnValueLlvm);

        // un-setting the current function for emission:
        emitter->currentLlvmFunction = NULL;
    }
    return 1;
}

ExportedType exportType(Typer* typer, Type* type) {
    // converts a compiler 'Type' into an LLVM Type.
    // 1:1 conversion wherever possible, no magic.

    ExportedType exportedType;
    exportedType.native = GetTypeSoln(typer,type);
    exportedType.llvm = NULL;

    if (exportedType.native) {
        AstKind nodeKind = GetTypeKind(exportedType.native);
        switch (nodeKind) {
            case T_UNIT:
            {
                exportedType.llvm = LLVMVoidType();
                break;
            }
            case T_STRING:
            {
                exportedType.llvm = LLVMPointerType(LLVMInt8Type(),0);
                break;
            }
            case T_INT:
            {
                int numBits = GetIntTypeWidthInBits(exportedType.native);
                if (GetIntTypeIsSigned(exportedType.native)) {
                    COMPILER_ASSERT(numBits >= 2, "Cannot make a signed int of length < 2; 1 for sign bit, N-1 for mantissa");
                    exportedType.llvm = LLVMIntType(numBits);
                }
                // llvm uses the same type for signed and unsigned integers.
                exportedType.llvm = LLVMIntType(numBits);
                break;
            }
            case T_FLOAT:
            {
                int numBits = GetFloatTypeWidthInBits(exportedType.native);
                if (numBits == 16) {
                    exportedType.llvm = LLVMHalfType();
                } else if (numBits == 32) {
                    exportedType.llvm = LLVMFloatType();
                } else if (numBits == 64) {
                    exportedType.llvm = LLVMDoubleType();
                } else {
                    if (DEBUG) {
                        printf("!!- emitter: Unsupported float bit count: %d\n", numBits);
                    } else {
                        assert(0 && "Unsupported float bit count");
                    }
                }
                break;
            }
            case T_PTR:
            {
                Type* pointeeType = GetPtrTypePointee(exportedType.native);
                ExportedType pointeeEType = exportType(typer,pointeeType);
                exportedType.llvm = LLVMPointerType(pointeeEType.llvm,0);
                break;
            }
            case T_TUPLE:
            {
                ExportedType* exportFieldsSB = NULL;
                MapCompoundType(typer,type,buildLlvmField,&exportFieldsSB);
                
                int fieldCount = sb_count(exportFieldsSB);
                LLVMTypeRef* fieldLlvmTypes = malloc(fieldCount*sizeof(LLVMTypeRef));
                for (int i = 0; i < fieldCount; i++) {
                    ExportedType exportedField = exportFieldsSB[i];
                    fieldLlvmTypes[i] = exportedField.llvm;
                }
                sb_free(exportFieldsSB);

                exportedType.llvm = LLVMStructType(fieldLlvmTypes,fieldCount,0);
                free(fieldLlvmTypes);
                break;
            }
            case T_UNION:
            {
                // todo: create a tag/union pair
                int sizeInBytes = GetTypeSizeInBytes(typer,exportedType.native);
                exportedType.llvm = LLVMArrayType(LLVMIntType(8),sizeInBytes);
                break;
            }
            case T_FUNC:
            {
                // for now, all functions and calls are unary
                int argCount = GetFuncTypeArgCount(exportedType.native);
                int argCountPostElision = 0;
                LLVMTypeRef* llvmArgTypeArrayPostElision = NULL;
                for (int index = 0; index < argCount; index++) {
                    Type* argType = GetFuncTypeArgAt(exportedType.native,index);
                    ExportedType exportedType = exportType(typer,argType);
                    if (GetTypeKind(argType) != T_UNIT) {
                        // lazily initializing the array if required:
                        if (llvmArgTypeArrayPostElision == NULL) {
                            llvmArgTypeArrayPostElision = malloc(argCount*sizeof(LLVMTypeRef));
                        }
                        // pushing to the array with a non-void argument:
                        llvmArgTypeArrayPostElision[argCountPostElision++] = exportedType.llvm;
                    }
                }
                
                ExportedType exportRetType = exportType(typer,GetFuncTypeImage(exportedType.native));
                if (exportRetType.llvm) {
                    exportedType.llvm = LLVMFunctionType(
                        exportRetType.llvm,
                        llvmArgTypeArrayPostElision,argCountPostElision,
                        0
                    );
                } else {
                    if (DEBUG) {
                        printf("!!- Skipping exportType for T_FUNC due to an error.\n");
                    } else {
                        assert(0 && "Skipping exportType for T_FUNC due to an error.");
                    }
                }

                if (llvmArgTypeArrayPostElision) {
                    free(llvmArgTypeArrayPostElision); 
                    llvmArgTypeArrayPostElision = NULL;
                }

                break;
            }
            
            // todo: add support for T_SLICE, whose LLVM type is just a ptr

            default:
            {
                if (DEBUG) {
                    printf("!!- NotImplemented: exportType for unsupported type kind %s.\n",TypeKindAsText(GetTypeKind(exportedType.native)));
                } else {
                    assert(0 && "NotImplemented: exportType for unsupported type kind.");
                }
                break;
            }
        }
    }

    if (DEBUG) {
        if (exportedType.native && !exportedType.llvm) {
            printf("!!- Failed to export type of kind %s (exportedType.llvm = NULL).\n", TypeKindAsText(GetTypeKind(exportedType.native)));
        }
    }
    return exportedType;
}
ExportedValue exportValue(Emitter* emitter, AstNode* exprNode) {
    // converts a compiler expression into an LLVM expression, building as required.
    Typer* typer = emitter->typer;

    // alloca-ing some memory for each value, relying on LLVM's mem2reg pass to optimize where unnecessary:
    ExportedValue exportedValue;
    exportedValue.native = exprNode;
    exportedValue.type.llvm = NULL;
    exportedValue.type.native = NULL;
    exportedValue.llvm = NULL;

    // filling type:
    Type* abstractType = GetAstNodeTypingExt_Value(exprNode);
    if (abstractType) {
        exportedValue.type = exportType(emitter->typer,abstractType);
    }

    // filling value:
    if (exportedValue.native) {
        AstKind nodeKind = GetAstNodeKind(exportedValue.native);
        switch (nodeKind) {
            
            //
            // ID,FUNC: just fetch the stored EValue from the symbol table.
            //
            
            case AST_VID:
            {
                DefnScope* defn = GetAstIdDefn(exportedValue.native);
                AstNode* defnNode = GetDefnNode(defn);
                ExportedValue* defnPtrExportedValue = GetAstNodeLlvmRepr(defnNode);
                exportedValue = *defnPtrExportedValue;
                break;
            }
            case AST_VLAMBDA:
            {
                ExportedValue* lambdaSynthetic = GetAstNodeLlvmRepr(exportedValue.native);
                exportedValue.llvm = lambdaSynthetic->llvm;
                break;
            }

            //
            // UNIT: represented by a NULL LLVMvalue ptr
            //

            case AST_UNIT:
            {
                exportedValue.llvm = LLVMGetUndef(LLVMVoidType());
                break;
            }

            //
            // INT,FLOAT:
            //

            case AST_LITERAL_INT:
            {
                size_t intValue = GetAstIntLiteralValue(exportedValue.native);
                LLVMValueRef stored = LLVMConstInt(exportedValue.type.llvm,intValue,0);
                exportedValue.llvm = LLVMBuildAlloca(emitter->builder,exportedValue.type.llvm,"intl");
                LLVMBuildStore(emitter->builder,stored,exportedValue.llvm);
                break;
            }
            case AST_LITERAL_FLOAT:
            {
                long double floatValue = GetAstFloatLiteralValue(exportedValue.native);
                exportedValue.llvm = LLVMBuildAlloca(emitter->builder,exportedValue.type.llvm,"floatl");
                LLVMValueRef stored = LLVMConstReal(exportedValue.type.llvm,floatValue);
                LLVMBuildStore(emitter->builder,stored,exportedValue.llvm);
                break;
            }

            //
            // STRINGs:
            //

            case AST_LITERAL_STRING:
            {
                // see: https://mapping-high-level-constructs-to-llvm-ir.readthedocs.io/en/latest/appendix-a-how-to-implement-a-string-type-in-llvm/
                
                LLVMTypeRef llvmStringPtrType = exportedValue.type.llvm;
                LLVMValueRef llvmStringPtr; {
                    // all strings are allocated as global variables AOT
                    // cf https://llvm.org/docs/LangRef.html#module-structure
                    // "Global values are represented by a pointer to a memory location (in
                    //  this case, a pointer to an array of char, and a pointer to a function), 
                    //  and have one of the following linkage types."

                    // rather than use gep as in the above example, we can also just bitcast the array ptr
                    // cf https://stackoverflow.com/questions/37901866/get-pointer-to-first-element-of-array-in-llvm-ir

                    ExportedValue* llvmStringGlobal = GetAstNodeLlvmRepr(exportedValue.native);
                    
                    LLVMValueRef indices[] = {
                        LLVMConstInt(LLVMInt32Type(),0,0),
                        LLVMConstInt(LLVMInt64Type(),0,0)
                    };
                    llvmStringPtr = LLVMBuildGEP(emitter->builder, llvmStringGlobal->llvm, indices,2, "stringconst_ptr_loaded");
                    // llvmStringPtr = LLVMBuildBitCast(emitter->builder, llvmStringGlobal->llvm, llvmStringPtrType, "stringliteral_loaded");
                };
                
                // alloca, store ptr to static string literal.
                // the default memory manager should ignore pointers in the data segment.
                // note that 'String' is a general, read-only byte container.
                // converting a String to a slice is explicit, and permits mutation.
                exportedValue.llvm = LLVMBuildAlloca(emitter->builder,llvmStringPtrType,"stringliteral");
                LLVMBuildStore(emitter->builder,llvmStringPtr,exportedValue.llvm);
                break;
            }

            //
            // STRUCT,TUPLE,UNION,ARRAY: llvmValueRef is a pointer to the value.
            //

            case AST_VTUPLE:
            case AST_VSTRUCT:
            {
                int tupleNotStruct = ((nodeKind == AST_VTUPLE) || (nodeKind == AST_VSTRUCT));

                exportedValue.llvm = LLVMBuildAlloca(emitter->builder,exportedValue.type.llvm,NULL);
                int isPacked = 0;
                int fieldCount = CountAstStructFields(exportedValue.native);
                LLVMValueRef* fieldArray = malloc(sizeof(LLVMValueRef)*fieldCount);
                for (int fieldIndex = 0; fieldIndex < fieldCount; fieldIndex++) {
                    AstNode* fieldNode = (
                        tupleNotStruct ?
                        GetAstTupleItemAt(exportedValue.native,fieldIndex) :
                        GetAstStructFieldAt(exportedValue.native,fieldIndex)
                    );
                    ExportedValue exportedFieldValue = exportValue(emitter,fieldNode);
                    fieldArray[fieldIndex] = exportedFieldValue.llvm;
                }
                LLVMValueRef stored = LLVMConstStruct(fieldArray,fieldCount,isPacked);
                exportedValue.llvm = LLVMBuildAlloca(emitter->builder,exportedValue.type.llvm,"anonymous_struct");
                LLVMBuildStore(emitter->builder,stored,exportedValue.llvm);
                break;
            }

            //
            // Paren,Chain: evaluate each item and store in result
            //
            
            case AST_VPAREN:
            {
                AstNode* vparen = exportedValue.native;
                exportedValue.llvm = exportValue(emitter,GetAstParenItem(vparen)).llvm;
                break;
            }
            case AST_CHAIN:
            {
                // allocaing a result if non-void return type:
                LLVMValueRef outValuePtr = NULL;
                int sizeInBytes = GetTypeSizeInBytes(emitter->typer,exportedValue.type.native);
                if (sizeInBytes > 0) {
                    outValuePtr = LLVMBuildAlloca(emitter->builder,exportedValue.type.llvm,"chain_result");
                }

                // computing content with all side-effects:
                int prefixLength = GetAstChainPrefixLength(exportedValue.native);
                for (int prefixIndex = 0; prefixIndex < prefixLength; prefixIndex++) {
                    AstNode* prefixStmt = GetAstChainPrefixStmtAt(exportedValue.native,prefixIndex);
                    exportValue(emitter,prefixStmt);
                }
                AstNode* result = GetAstChainResult(exportedValue.native);
                if (result) {
                    ExportedValue exportedResult = exportValue(emitter,result);
                
                    // load & store if we allocated memory:
                    if (outValuePtr) {
                        exportedValue.llvm = outValuePtr;
                        LLVMValueRef loadedForChainYield = LLVMBuildLoad(emitter->builder,exportedResult.llvm,"chain_result_loaded");
                        LLVMBuildStore(emitter->builder,loadedForChainYield,exportedValue.llvm);
                    }
                }
                break;
            }

            //
            // Let statements:
            //

            case AST_STMT_VLET:
            {
                // exporting the RHS:
                AstNode* rhsNode = GetAstLetStmtRhs(exportedValue.native);
                ExportedValue* exportedRhs = malloc(sizeof(ExportedValue));
                *exportedRhs = exportValue(emitter,rhsNode);

                // binding RHS to LHS lpattern:
                AstNode* lhsNode = GetAstLetStmtLhs(exportedValue.native);
                if (GetAstNodeKind(lhsNode) == AST_VPATTERN_SINGLETON) {
                    AstNode* lhsField = GetAstSingletonPatternField(lhsNode);
                    SymbolID symbolID = GetAstFieldName(lhsField);
                    
                    char* fmtname = fmt("let:%s",GetSymbolText(symbolID));
                    LLVMSetValueName(exportedRhs->llvm,fmtname);
                    free(fmtname);

                    SetAstNodeLlvmRepr(lhsField,exportedRhs);
                    exportedValue.llvm = NULL;
                } else {
                    COMPILER_ERROR("NotImplemented: let statements with destructured, non singleton, LHS vpatterns.");
                }
                break;
            }

            //
            // Set statements:
            // TODO: implement these.
            //

            //
            // Discard statements:
            //

            case AST_STMT_DISCARD:
            {
                AstNode* discardedNode = GetAstDiscardStmtDiscarded(exportedValue.native);
                ExportedValue discardedExpVal = exportValue(emitter,discardedNode);
                exportedValue.llvm = NULL;
                break;
            }

            //
            // VCall:
            //

            case AST_VCALL:
            {
                Type* returnedType = exportedValue.type.native;
                if (returnedType != GetUnitType(emitter->typer)) {
                    exportedValue.llvm = LLVMBuildAlloca(emitter->builder,exportedValue.type.llvm,"call_res");
                }

                ExportedValue lhsValue = exportValue(emitter,GetAstCallLhs(exportedValue.native));
                
                // of the supplied actual args, we elide those of 'unit' type since LLVM does not support pure 'void' args.
                // - (formal & actual args still paired correctly) since the formal and actual function have typechecked, we know parallel empty args will be elided on the defn and call side.
                // - (even if empty) even in the degenerate case where all patterns are unit and elided, 0-args are understood by LLVM as a 0-ary function.
                int argCount = GetAstCallArgCount(exportedValue.native);
                LLVMValueRef* elidedLlvmArgs = NULL;
                int elidedLlvmArgCount = 0;
                for (int argIndex = 0; argIndex < argCount; argIndex++) {
                    AstNode* arg = GetAstCallArgAt(exportedValue.native,argIndex);
                    ExportedValue exportedActual = exportValue(emitter,arg);
                    TypeKind exportedActual_typeKind = GetTypeKind(exportedActual.type.native);
                    
                    // TODO: implement conversion from subtype to supertype 
                    // o i32 -> i64
                    // o (i32,i32) -> (i64,i64)
                    // - sub->super is all that is required, very predictable
                    // - in the future, when we add classes, sub->super gets more complex, but stays fixed in compiler-world.
                    // - if we introduce overloadable type conversions, overload resolution complexity balloons; high cost, low payoff.
                    // COMPILER_ERROR(
                    //     // exportedActual.type.native == exportedFormal_type_native,
                    //     "NotImplemented: implicit type conversions from subtype to supertype in AST_VCALL"
                    // );

                    if (exportedActual_typeKind != T_UNIT) {
                        // allocating a new args buffer on demand:
                        if (elidedLlvmArgs == NULL) {
                            elidedLlvmArgs = malloc(argCount * sizeof(LLVMValueRef));
                        }

                        char* loadedForCallName = fmt("actual_%d_%d_loaded", argIndex, elidedLlvmArgCount);
                        LLVMValueRef loadedForCall = LLVMBuildLoad2(emitter->builder,exportedActual.type.llvm,exportedActual.llvm,loadedForCallName);
                        free(loadedForCallName); loadedForCallName = NULL;

                        // pushing arg into existing buffer:
                        elidedLlvmArgs[elidedLlvmArgCount++] = loadedForCall;
                    }
                }
                
                LLVMValueRef callValue = NULL;
                char const* name = NULL;
                if (exportedValue.llvm) {
                    // non-unit return type => result is named.
                    name = "call_value";
                } else {
                    // void return type cannot accept a named result.
                    // from https://msm.runhello.com/p/1013
                    //      ... since printFactors returns void, the name passed to LLVMBuildCall() MUST be "", 
                    //          exactly the value "" and no other, or the program crashes.
                    name = "";
                }
                if (elidedLlvmArgCount) {
                    callValue = LLVMBuildCall2(emitter->builder,lhsValue.type.llvm,lhsValue.llvm,elidedLlvmArgs,argCount,name);
                } else {
                    callValue = LLVMBuildCall2(emitter->builder,lhsValue.type.llvm,lhsValue.llvm,NULL,0,name);
                }
                if (exportedValue.llvm) {
                    // non-unit return type => result can be stored.
                    LLVMBuildStore(emitter->builder,callValue,exportedValue.llvm);
                }
                break;
            }

            //
            // Unary and binary operators:
            //

            case AST_UNARY:
            {
                AstNode* expr = exportedValue.native;
                
                AstUnaryOperator uop = GetAstUnaryOperator(expr);
                
                AstNode* exprArg = GetAstUnaryOperand(expr);
                ExportedValue exprArgExportedValue = exportValue(emitter,exprArg);

                exportedValue.llvm = LLVMBuildAlloca(emitter->builder,exportedValue.type.llvm,"uop_res");
                switch (uop)
                {
                    case UOP_GETREF:
                    {
                        // exportedValue.llvm usually tracks a pointer to an alloca-ed block.
                        // just store this pointer.
                        LLVMBuildStore(emitter->builder, exprArgExportedValue.llvm, exportedValue.llvm);
                        break;
                    }
                    case UOP_DEREF:
                    {
                        // first load the pointer to deref:
                        LLVMValueRef loadedArg = LLVMBuildLoad2(emitter->builder, exprArgExportedValue.type.llvm, exprArgExportedValue.llvm, "uop_deref_arg_loaded");
                        
                        // then load from that ptr for the result:
                        LLVMValueRef loadedRes = LLVMBuildLoad2(emitter->builder, exportedValue.type.llvm, loadedArg, "uop_deref_res_loaded");

                        // store result in alloca-ed space:
                        LLVMBuildStore(emitter->builder, loadedRes, exportedValue.llvm);
                        break;
                    }
                    case UOP_PLUS:
                    {
                        // identity
                        LLVMValueRef loadedArg = LLVMBuildLoad2(emitter->builder, exprArgExportedValue.type.llvm, exprArgExportedValue.llvm, "uop_plus_arg_loaded");
                        LLVMBuildStore(emitter->builder, loadedArg, exportedValue.llvm);
                        break;
                    }
                    case UOP_MINUS:
                    {
                        LLVMValueRef loadedArg = LLVMBuildLoad2(emitter->builder, exprArgExportedValue.type.llvm, exprArgExportedValue.llvm, "uop_minus_arg_loaded");
                        TypeKind uopTKind = GetTypeKind(exportedValue.type.native);
                        LLVMValueRef loadedRes = NULL;
                        if (uopTKind == T_INT) {
                            loadedRes = LLVMBuildNeg(emitter->builder, loadedArg, "uop_minus_res_loaded");
                        } else if (uopTKind == T_FLOAT) {
                            loadedRes = LLVMBuildFNeg(emitter->builder, loadedArg, "uop_minus_res_loaded");
                        } else {
                            COMPILER_ERROR("NotImplemented: exportValue for AST_UNARY/UOP_MINUS");
                        }
                        if (loadedRes) {
                            LLVMBuildStore(emitter->builder, loadedRes, exportedValue.llvm);
                        }
                        break;
                    }
                    case UOP_NOT:
                    {
                        LLVMValueRef loadedArg = LLVMBuildLoad2(emitter->builder, exprArgExportedValue.type.llvm, exprArgExportedValue.llvm, "uop_not_arg_loaded");
                        LLVMValueRef loadedRes = LLVMBuildNot(emitter->builder, loadedArg, "uop_not_res_loaded");
                        LLVMBuildStore(emitter->builder, loadedRes, exportedValue.llvm);
                        break;
                    }
                    default:
                    {
                        COMPILER_ERROR_VA("NotImplemented: exportValue for AST_UNARY with uop=%s", AstUnaryOperatorAsText(uop));
                        break;
                    }
                }
                break;
            }
            case AST_BINARY:
            {
                AstNode* exprNode = exportedValue.native;

                AstBinaryOperator bop = GetAstBinaryOperator(exprNode);
                
                AstNode* ltArgNode = GetAstBinaryLtOperand(exprNode);
                AstNode* rtArgNode = GetAstBinaryRtOperand(exprNode);
                ExportedValue ltArgExpVal = exportValue(emitter,ltArgNode);
                ExportedValue rtArgExpVal = exportValue(emitter,rtArgNode);
                LLVMValueRef llvmLtArg = LLVMBuildLoad2(emitter->builder, ltArgExpVal.type.llvm, ltArgExpVal.llvm, "bop_ltarg_loaded");
                LLVMValueRef llvmRtArg = LLVMBuildLoad2(emitter->builder, rtArgExpVal.type.llvm, rtArgExpVal.llvm, "bop_rtarg_loaded");

                // TODO: CAST/CONVERT args IF REQD while exporting AST_BINARY
                int isIntBop = (GetTypeKind(exportedValue.type.native) == T_INT);
                int isFpBop = (GetTypeKind(exportedValue.type.native) == T_FLOAT);

                exportedValue.llvm = LLVMBuildAlloca(emitter->builder,exportedValue.type.llvm,"bop_res");
                LLVMValueRef loadedRes = NULL;
                if (isIntBop) {
                    if (GetIntTypeIsSigned(exportedValue.type.native)) {
                        // signed-int
                        switch (bop) 
                        {
                            case BOP_MUL:
                            {
                                loadedRes = LLVMBuildMul(emitter->builder,llvmLtArg,llvmRtArg,"bop_smul_loaded");
                                break;
                            }
                            case BOP_DIV:
                            {
                                loadedRes = LLVMBuildSDiv(emitter->builder,llvmLtArg,llvmRtArg,"bop_sdiv_loaded");
                                break;
                            }
                            case BOP_REM:
                            {
                                loadedRes = LLVMBuildSRem(emitter->builder,llvmLtArg,llvmRtArg,"bop_srem_loaded");
                                break;
                            }
                            case BOP_ADD:
                            {
                                loadedRes = LLVMBuildAdd(emitter->builder,llvmLtArg,llvmRtArg,"bop_sadd_loaded");
                                break;
                            }
                            case BOP_SUBTRACT:
                            {
                                loadedRes = LLVMBuildSub(emitter->builder,llvmLtArg,llvmRtArg,"bop_ssubtract_loaded");
                                break;
                            }
                            case BOP_LTHAN:
                            {
                                LLVMValueRef rawValue = LLVMBuildICmp(emitter->builder,LLVMIntSLT,llvmLtArg,llvmRtArg,"bop_slt_loaded");
                                loadedRes = LLVMBuildIntCast(emitter->builder,rawValue,LLVMInt1Type(),NULL);
                                break;
                            }
                            case BOP_GTHAN:
                            {
                                LLVMValueRef rawValue = LLVMBuildICmp(emitter->builder,LLVMIntSGT,llvmLtArg,llvmRtArg,"bop_sgt_loaded");
                                // return LLVMBuildIntCast(emitter->llvmBuilder,rawValue,LLVMInt1Type(),NULL);
                                loadedRes = rawValue;
                                break;
                            }
                            case BOP_LETHAN:
                            {
                                LLVMValueRef rawValue = LLVMBuildICmp(emitter->builder,LLVMIntSLE,llvmLtArg,llvmRtArg,"bop_sle_loaded");
                                // return LLVMBuildIntCast(emitter->llvmBuilder,rawValue,LLVMInt1Type(),NULL);
                                loadedRes = rawValue;
                                break;
                            }
                            case BOP_GETHAN:
                            {
                                LLVMValueRef rawValue = LLVMBuildICmp(emitter->builder,LLVMIntSGE,llvmLtArg,llvmRtArg,"bop_sge_loaded");
                                loadedRes = LLVMBuildIntCast(emitter->builder,rawValue,LLVMInt1Type(),NULL);
                                break;
                            }
                            case BOP_EQUALS:
                            {
                                // LLVMValueRef rawValue = LLVMBuildFCmp(emitter->llvmBuilder,LLVMRealOEQ,llvmLtArg,llvmRtArg,"eq");
                                LLVMValueRef rawValue = LLVMBuildICmp(emitter->builder,LLVMIntEQ,llvmLtArg,llvmRtArg,"bop_seq_loaded");
                                // return LLVMBuildIntCast(emitter->llvmBuilder,rawValue,LLVMInt1Type(),NULL);
                                loadedRes = rawValue;
                                break;
                            }
                            case BOP_NEQUALS:
                            {
                                // LLVMValueRef rawValue = LLVMBuildFCmp(emitter->llvmBuilder,LLVMRealONE,llvmLtArg,llvmRtArg,"eq");
                                LLVMValueRef rawValue = LLVMBuildICmp(emitter->builder,LLVMIntNE,llvmLtArg,llvmRtArg,"bop_sneq_loaded");
                                // return LLVMBuildIntCast(emitter->llvmBuilder,rawValue,LLVMInt1Type(),NULL);
                                loadedRes = rawValue;
                                break;
                            }
                            default:
                            {
                                COMPILER_ERROR_VA("Unsupported sint-bop: %s", AstBinaryOperatorAsText(bop));
                                break;
                            }
                        }
                    } else {
                        // unsigned-int
                        switch (bop) 
                        {
                            case BOP_MUL:
                            {
                                loadedRes = LLVMBuildMul(emitter->builder,llvmLtArg,llvmRtArg,"bop_umul_loaded");
                                break;
                            }
                            case BOP_DIV:
                            {
                                loadedRes = LLVMBuildUDiv(emitter->builder,llvmLtArg,llvmRtArg,"bop_udiv_loaded");
                                break;
                            }
                            case BOP_REM:
                            {
                                loadedRes = LLVMBuildURem(emitter->builder,llvmLtArg,llvmRtArg,"bop_urem_loaded");
                                break;
                            }
                            case BOP_ADD:
                            {
                                loadedRes = LLVMBuildAdd(emitter->builder,llvmLtArg,llvmRtArg,"bop_uadd_loaded");
                                break;
                            }
                            case BOP_SUBTRACT:
                            {
                                loadedRes = LLVMBuildSub(emitter->builder,llvmLtArg,llvmRtArg,"bop_usubtract_loaded");
                                break;
                            }
                            case BOP_AND:
                            {
                                loadedRes = LLVMBuildAnd(emitter->builder,llvmLtArg,llvmRtArg,"bop_uand_loaded");
                                break;
                            }
                            case BOP_XOR:
                            {
                                loadedRes = LLVMBuildXor(emitter->builder,llvmLtArg,llvmRtArg,"bop_uxor_loaded");
                                break;
                            }
                            case BOP_OR:
                            {
                                loadedRes = LLVMBuildOr(emitter->builder,llvmLtArg,llvmRtArg,"bop_uor_loaded");
                                break;
                            }
                            case BOP_LTHAN:
                            {
                                LLVMValueRef rawValue = LLVMBuildICmp(emitter->builder,LLVMIntULT,llvmLtArg,llvmRtArg,"bop_ult_loaded");
                                // loadedRes = LLVMBuildIntCast2(emitter->builder,rawValue,LLVMInt1Type(),0,);
                                loadedRes = rawValue;
                                break;
                            }
                            case BOP_GTHAN:
                            {
                                LLVMValueRef rawValue = LLVMBuildICmp(emitter->builder,LLVMIntUGT,llvmLtArg,llvmRtArg,"bop_ugt_loaded");
                                // return LLVMBuildIntCast(emitter->llvmBuilder,rawValue,LLVMInt1Type(),NULL);
                                loadedRes = rawValue;
                                break;
                            }
                            case BOP_LETHAN:
                            {
                                LLVMValueRef rawValue = LLVMBuildICmp(emitter->builder,LLVMIntULE,llvmLtArg,llvmRtArg,"bop_ule_loaded");
                                // return LLVMBuildIntCast(emitter->llvmBuilder,rawValue,LLVMInt1Type(),NULL);
                                loadedRes = rawValue;
                                break;
                            }
                            case BOP_GETHAN:
                            {
                                LLVMValueRef rawValue = LLVMBuildICmp(emitter->builder,LLVMIntUGE,llvmLtArg,llvmRtArg,"bop_uge_loaded");
                                // loadedRes = LLVMBuildIntCast(emitter->builder,rawValue,LLVMInt1Type(),NULL);
                                loadedRes = rawValue;
                                break;
                            }
                            case BOP_EQUALS:
                            {
                                // LLVMValueRef rawValue = LLVMBuildFCmp(emitter->llvmBuilder,LLVMRealOEQ,llvmLtArg,llvmRtArg,"eq");
                                LLVMValueRef rawValue = LLVMBuildICmp(emitter->builder,LLVMIntEQ,llvmLtArg,llvmRtArg,"bop_ueq_loaded");
                                // return LLVMBuildIntCast(emitter->llvmBuilder,rawValue,LLVMInt1Type(),NULL);
                                loadedRes = rawValue;
                                break;
                            }
                            case BOP_NEQUALS:
                            {
                                // LLVMValueRef rawValue = LLVMBuildFCmp(emitter->llvmBuilder,LLVMRealONE,llvmLtArg,llvmRtArg,"eq");
                                LLVMValueRef rawValue = LLVMBuildICmp(emitter->builder,LLVMIntNE,llvmLtArg,llvmRtArg,"bop_uneq_loaded");
                                // return LLVMBuildIntCast(emitter->llvmBuilder,rawValue,LLVMInt1Type(),NULL);
                                loadedRes = rawValue;
                                break;
                            }
                            default:
                            {
                                COMPILER_ERROR_VA("Unsupported uint-bop: %s", AstBinaryOperatorAsText(bop));
                                break;
                            }
                        }
                    }
                }
                else if (isFpBop) {
                    // floating point:
                    switch (bop) 
                    {
                        case BOP_MUL:
                        {
                            loadedRes = LLVMBuildFMul(emitter->builder,llvmLtArg,llvmRtArg,"bop_fmul_loaded");
                            break;
                        }
                        case BOP_DIV:
                        {
                            loadedRes = LLVMBuildFDiv(emitter->builder,llvmLtArg,llvmRtArg,"bop_fdiv_loaded");
                            break;
                        }
                        case BOP_REM:
                        {
                            loadedRes = LLVMBuildFRem(emitter->builder,llvmLtArg,llvmRtArg,"bop_frem_loaded");
                            break;
                        }
                        case BOP_ADD:
                        {
                            loadedRes = LLVMBuildFAdd(emitter->builder,llvmLtArg,llvmRtArg,"bop_fadd_loaded");
                            break;
                        }
                        case BOP_SUBTRACT:
                        {
                            loadedRes = LLVMBuildFSub(emitter->builder,llvmLtArg,llvmRtArg,"bop_fsubtract_loaded");
                            break;
                        }
                        case BOP_LTHAN:
                        {
                            LLVMValueRef rawValue = LLVMBuildFCmp(emitter->builder,LLVMRealOLT,llvmLtArg,llvmRtArg,"bop_flt_loaded");
                            loadedRes = LLVMBuildIntCast(emitter->builder,rawValue,LLVMInt1Type(),NULL);
                            break;
                        }
                        case BOP_GTHAN:
                        {
                            LLVMValueRef rawValue = LLVMBuildFCmp(emitter->builder,LLVMRealOGT,llvmLtArg,llvmRtArg,"bop_fgt_loaded");
                            // return LLVMBuildIntCast(emitter->llvmBuilder,rawValue,LLVMInt1Type(),NULL);
                            loadedRes = rawValue;
                            break;
                        }
                        case BOP_LETHAN:
                        {
                            LLVMValueRef rawValue = LLVMBuildFCmp(emitter->builder,LLVMRealOLE,llvmLtArg,llvmRtArg,"bop_fle_loaded");
                            // return LLVMBuildIntCast(emitter->llvmBuilder,rawValue,LLVMInt1Type(),NULL);
                            loadedRes = rawValue;
                            break;
                        }
                        case BOP_GETHAN:
                        {
                            LLVMValueRef rawValue = LLVMBuildFCmp(emitter->builder,LLVMRealOGE,llvmLtArg,llvmRtArg,"bop_fge_loaded");
                            // loadedRes = LLVMBuildIntCast(emitter->builder,rawValue,LLVMInt1Type(),NULL);
                            loadedRes = rawValue;
                            break;
                        }
                        case BOP_EQUALS:
                        {
                            LLVMValueRef rawValue = LLVMBuildFCmp(emitter->builder,LLVMRealOEQ,llvmLtArg,llvmRtArg,"bop_feq_loaded");
                            // return LLVMBuildIntCast(emitter->llvmBuilder,rawValue,LLVMInt1Type(),NULL);
                            loadedRes = rawValue;
                            break;
                        }
                        case BOP_NEQUALS:
                        {
                            LLVMValueRef rawValue = LLVMBuildFCmp(emitter->builder,LLVMRealONE,llvmLtArg,llvmRtArg,"bop_fneq_loaded");
                            // return LLVMBuildIntCast(emitter->llvmBuilder,rawValue,LLVMInt1Type(),NULL);
                            loadedRes = rawValue;
                            break;
                        }
                        default:
                        {
                            COMPILER_ERROR_VA("Unsupported fp-bop: %s", AstBinaryOperatorAsText(bop));
                        }
                    }
                }

                LLVMBuildStore(emitter->builder, loadedRes, exportedValue.llvm);
                break;
            }
            
            // todo: emitExpr for tuples:
            // - always returns a pointer to a tuple.

            //
            // ITEs:
            //

            case AST_ITE:
            {
                // getting the basic block and func we start in, to return to after computing the result:
                LLVMValueRef currentFunction = emitter->currentLlvmFunction;
                LLVMBasicBlockRef predecessorBlock = LLVMGetInsertBlock(emitter->builder);
                COMPILER_ASSERT(predecessorBlock, "unexpected NULL predecessor block in ITE");
                
                // getting the ITE type:
                AstNode* iteNode = exportedValue.native;
                Type* iteType = exportedValue.type.native;
                LLVMTypeRef iteLlvmType = exportedValue.type.llvm;
                
                // adding any basic blocks required:
                LLVMValueRef func = currentFunction;
                LLVMBasicBlockRef entryBlock = LLVMAppendBasicBlock(func, "ite_entry_bb");
                LLVMBasicBlockRef trueBlock = LLVMAppendBasicBlock(func, "ite_true_bb");
                LLVMBasicBlockRef falseBlock = LLVMAppendBasicBlock(func, "ite_false_bb");
                LLVMBasicBlockRef landingBlock = LLVMAppendBasicBlock(func, "ite_landing_bb");
                
                // breaking to the entry block:
                LLVMBuildBr(emitter->builder,entryBlock);
                
                // computing cond, breaking to other blocks:
                LLVMPositionBuilderAtEnd(emitter->builder,entryBlock);
                AstNode* condNode = GetAstIteCond(iteNode);
                ExportedValue condExpVal = exportValue(emitter,condNode);
                LLVMValueRef condExpVal_loaded = LLVMBuildLoad2(emitter->builder,condExpVal.type.llvm,condExpVal.llvm,"ite_cond_loaded");
                // LLVMPositionBuilderAtEnd(emitter->llvmBuilder,entryBlock);
                LLVMBuildCondBr(emitter->builder,condExpVal_loaded,trueBlock,falseBlock);
                
                // populating 'ite-true':
                LLVMPositionBuilderAtEnd(emitter->builder,trueBlock);
                AstNode* ifTrueNode = GetAstIteIfTrue(iteNode);
                ExportedValue ifTrueExpVal = exportValue(emitter,ifTrueNode);
                LLVMValueRef ifTrueExpVal_loaded = NULL;
                if (ifTrueExpVal.type.native != GetUnitType(typer)) {
                    ifTrueExpVal_loaded = LLVMBuildLoad2(emitter->builder,ifTrueExpVal.type.llvm,ifTrueExpVal.llvm,"if_true_loaded");
                }
                LLVMBasicBlockRef predTrueBlock = LLVMGetInsertBlock(emitter->builder);
                LLVMBuildBr(emitter->builder,landingBlock);

                // populating 'ite-false':
                LLVMPositionBuilderAtEnd(emitter->builder,falseBlock);
                AstNode* ifFalseNode = GetAstIteIfFalse(iteNode);
                LLVMValueRef ifFalseExpVal_loaded = NULL;
                if (ifFalseNode) {
                    ExportedValue ifFalseExpVal = exportValue(emitter,ifFalseNode);
                    if (ifFalseExpVal.type.native != GetUnitType(typer)) {
                        ifFalseExpVal_loaded = LLVMBuildLoad2(emitter->builder,ifFalseExpVal.type.llvm,ifFalseExpVal.llvm,"if_false_loaded");
                    }
                }
                LLVMBasicBlockRef predFalseBlock = LLVMGetInsertBlock(emitter->builder);
                LLVMBuildBr(emitter->builder,landingBlock);

                // finally, converging to return a value:
                LLVMPositionBuilderAtEnd(emitter->builder,landingBlock);

                int phiRequired = (iteType != GetUnitType(emitter->typer));
                if (phiRequired) {
                    // building a phi node:
                    LLVMValueRef phi_loaded = LLVMBuildPhi(emitter->builder, iteLlvmType, "ite_result_loaded");
                    LLVMValueRef phi_values[] = {ifTrueExpVal_loaded, ifFalseExpVal_loaded};
                    LLVMBasicBlockRef phi_blocks[] = {predTrueBlock, predFalseBlock};
                    LLVMAddIncoming(phi_loaded, phi_values, phi_blocks, 2);

                    // storing the phi value result if non-unit:
                    COMPILER_ASSERT(ifFalseNode != NULL, "ITE cannot return non-unit type with no false branch.");
                    exportedValue.llvm = LLVMBuildAlloca(emitter->builder,iteLlvmType,"ite_result");
                    LLVMBuildStore(emitter->builder,phi_loaded,exportedValue.llvm);
                }  else {
                    exportedValue.llvm = NULL;
                }
                break;
            }

            //
            // Cast expressions:
            //

            case AST_VCAST:
            {
                // see: https://mapping-high-level-constructs-to-llvm-ir.readthedocs.io/en/latest/basic-constructs/casts.html

                AstNode* vcast = exportedValue.native;
                Type* concreteTo = exportedValue.type.native;

                ExportedValue exportedRhs = exportValue(emitter,GetAstVCastRhs(vcast));
                Type* concreteFrom = exportedRhs.type.native;
                int inputTypesOk = (
                    COMPILER_ASSERT(concreteTo,"exportValue: NULL concrete to-type in AST_VCAST") &&
                    COMPILER_ASSERT(concreteFrom,"exportValue: NULL concrete from-type in AST_VCAST")
                );
                if (inputTypesOk) {
                    TypeKind toKind = GetTypeKind(concreteTo);
                    TypeKind fromKind = GetTypeKind(concreteFrom);

                    if ((toKind == T_UNIT) && (fromKind == T_UNIT)) {
                        exportedValue.llvm = LLVMGetUndef(LLVMVoidType());
                    }
                    else if ((toKind == T_FLOAT) && (fromKind == T_FLOAT)) {
                        exportedValue.llvm = LLVMBuildAlloca(emitter->builder,exportedValue.type.llvm,"cast_fp");
                        LLVMValueRef loadedInputLlvmValue = LLVMBuildLoad(emitter->builder,exportedRhs.llvm,"cast_fp_input_loaded");

                        int toWidth = GetTypeSizeInBytes(typer,concreteTo);
                        int fromWidth = GetTypeSizeInBytes(typer,concreteFrom);
                        if (toWidth < fromWidth) {
                            // fp truncating cast:
                            LLVMBuildStore(
                                emitter->builder,
                                LLVMBuildFPTrunc(emitter->builder,loadedInputLlvmValue,exportedValue.type.llvm,"cast_fptrunc_eval"),
                                exportedValue.llvm
                            );
                        } else if (toWidth > fromWidth) {
                            // fp extending cast:
                            LLVMBuildStore(
                                emitter->builder,
                                LLVMBuildFPExt(emitter->builder,loadedInputLlvmValue,exportedValue.type.llvm,"cast_fpext_eval"),
                                exportedValue.llvm
                            );
                        } else {
                            // identity
                            LLVMBuildStore(emitter->builder,loadedInputLlvmValue,exportedValue.llvm);
                        }
                    }
                    else if ((GetTypeKind(concreteTo) == T_INT) && (GetTypeKind(concreteFrom) == T_INT)) {
                        int toIsSigned = GetIntTypeIsSigned(concreteTo);
                        int fromIsSigned = GetIntTypeIsSigned(concreteFrom);
                        int toWidth = GetTypeSizeInBytes(typer,concreteTo);
                        int fromWidth = GetTypeSizeInBytes(typer,concreteFrom);
                        
                        // NOTE: mixed signed/unsigned arithmetic is not ideal, should we forbid some actions?
                        // if (toIsSigned != fromIsSigned) {
                        //      
                        // } else {
                        
                        if (1) {
                            if (toIsSigned) {
                                exportedValue.llvm = LLVMBuildAlloca(emitter->builder,exportedValue.type.llvm,"cast_si");
                                LLVMValueRef loadedInputLlvmValue = LLVMBuildLoad(emitter->builder,exportedRhs.llvm,"cast_si_input_loaded");

                                if (toWidth < fromWidth) {
                                    // signed truncation
                                    LLVMBuildStore(
                                        emitter->builder,
                                        LLVMBuildTrunc(emitter->builder,loadedInputLlvmValue,exportedValue.type.llvm,"cast_strunc_eval"),
                                        exportedValue.llvm
                                    );
                                } else if (toWidth > fromWidth) {
                                    // signed extension
                                    LLVMBuildStore(
                                        emitter->builder,
                                        LLVMBuildSExt(emitter->builder,loadedInputLlvmValue,exportedValue.type.llvm,"cast_sext"),
                                        exportedValue.llvm
                                    );
                                } else {
                                    // (signed) identity
                                    LLVMBuildStore(emitter->builder,loadedInputLlvmValue,exportedValue.llvm);
                                }
                            } else {
                                exportedValue.llvm = LLVMBuildAlloca(emitter->builder,exportedValue.type.llvm,"cast_ui");
                                LLVMValueRef loadedInputLlvmValue = LLVMBuildLoad(emitter->builder,exportedRhs.llvm,"cast_ui_input_loaded");
                                
                                if (toWidth < fromWidth) {
                                    // unsigned truncation
                                    LLVMBuildStore(
                                        emitter->builder,
                                        LLVMBuildTrunc(emitter->builder,loadedInputLlvmValue,exportedValue.type.llvm,"cast_utrunc"),
                                        exportedValue.llvm
                                    );
                                } else if (toWidth > fromWidth) {
                                    // unsigned extension
                                    LLVMBuildStore(
                                        emitter->builder,
                                        LLVMBuildZExt(emitter->builder,loadedInputLlvmValue,exportedValue.type.llvm,"cast_uext"),
                                        exportedValue.llvm
                                    );
                                } else {
                                    // (unsigned) identity
                                    exportedValue.llvm = exportedRhs.llvm;
                                }
                            }
                        }
                    }
                    else {
                        // default: alloca, zero, and use a bitwise cast.
                        COMPILER_ERROR("NotImplemented: generic extend+bitwise cast.");
                    }
                }
                break;
            }

            //
            // Colon-expressions: static lookup
            //
            
            case AST_COLON_NAME:
            {
                AstNode* colonNode = exportedValue.native;
                DefnScope* refedDefnScope = GetAstColonNameRefedDefnScope(colonNode);
                AstNode* refedDefnNode = GetDefnNode(refedDefnScope);

                // HACK: if the defined node is a 'def' statement, obtain the RHS instead
                if (GetAstNodeKind(refedDefnNode) == AST_STMT_VDEF) {
                    refedDefnNode = GetAstDefValueStmtRhs(refedDefnNode);
                }

                ExportedValue exportedRefedValue = exportValue(emitter, refedDefnNode);
                exportedValue.llvm = exportedRefedValue.llvm;
                break;
            }

            default:
            {
                AstKind nodeKind = GetAstNodeKind(exportedValue.native);
                COMPILER_ERROR_VA("NotImplemented: 'exportValue' for AST node of kind '%s'",AstKindAsText(nodeKind));
                break;
            }
        }
    }
    
    return exportedValue;
}

void buildLlvmField(Typer* typer, void* rawSBP, SymbolID name, Type* type) {
    ExportedType** sbp = rawSBP;
    ExportedType fieldTypeRef = exportType(typer,type);
    sb_push((*sbp),fieldTypeRef);
}

//
// Interface:
//

int EmitLlvmModule(Typer* typer, AstNode* module) {
    Emitter emitter = newEmitter(typer,"hub-test");
    int result = 1;
    result = exportModuleHeaders(&emitter,module) && result;
    result = exportModule(&emitter,module) && result;

    char* verifyMsg = NULL;

    int broken = LLVMVerifyModule(emitter.module,LLVMReturnStatusAction,&verifyMsg);
    if (broken) {
        COMPILER_ERROR_VA("LLVMVerifyModule failed with message(s):\n%s", verifyMsg);
        result = 0;
    } else {
        SetAstNodeLlvmRepr(module,emitter.module);

        if (DEBUG) {
            printf("!!- LLVM verify msg:\n<msg>\n%s</msg>\n", verifyMsg);
        }
    }
    LLVMDisposeMessage(verifyMsg); verifyMsg = NULL;

    int debugPrintLlvmLL = 1;
    if (DEBUG && debugPrintLlvmLL) {
        printf("!!- LLVM Module Dump:\n");
        LLVMDumpModule(emitter.module);
    }

    LLVMDisposeBuilder(emitter.builder);
    return result;
}
