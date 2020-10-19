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

// See Paul Smith's "How to Get Started with LLVM C API"
// - https://www.pauladamsmith.com/blog/2015/01/how-to-get-started-with-llvm-c-api.html

// See Eli Bendersky's Python implementation of the LLVM Kaleidoscope demo:
// - https://github.com/eliben/pykaleidoscope/blob/master/chapter3and4.py

// See wickedchicken's GitHub examples:
// - https://github.com/wickedchicken/llvm-c-example/blob/master/fac.c

typedef struct Emitter Emitter;
struct Emitter {
    Typer* typer;
    LLVMModuleRef module;
    LLVMBuilderRef builder;
};
static Emitter newEmitter(Typer* typer, char const* moduleName);

Emitter newEmitter(Typer* typer, char const* moduleName) {
    Emitter emitter;
    emitter.typer = typer;
    emitter.builder = LLVMCreateBuilder();
    emitter.module = LLVMModuleCreateWithName(moduleName);
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
static int exportModuleHeaderVisitor_pre(void* emitter, AstNode* node);
static int exportModule(Emitter* emitter, AstNode* moduleNode);
static int exportModuleVisitor_pre(void* emitter, AstNode* node);
static ExportedType exportType(Typer* typer, Type* type);
static ExportedValue exportValue(Emitter* emitter, AstNode* exprNode);
// static ExportedValue emitPtrToValue(Typer* typer, ExportedValue pointee);

static void buildLlvmField(Typer* typer, void* sb, SymbolID name, Type* type);

int exportModuleHeaders(Emitter* emitter, AstNode* moduleNode) {
    return RecursivelyVisitAstNode(emitter,moduleNode,exportModuleHeaderVisitor_pre,NULL);
}
int exportModuleHeaderVisitor_pre(void* rawEmitter, AstNode* node) {
    Emitter* emitter = rawEmitter;
    if (GetAstNodeKind(node) == AST_LAMBDA) {
        Type* funcType = GetAstNodeTypingExt_Value(node);
        ExportedType exportedFuncType = exportType(emitter->typer,funcType);
        ExportedValue* funcValue = malloc(sizeof(ExportedValue));
        funcValue->native = node;
        funcValue->type = exportedFuncType;
        funcValue->llvm = LLVMAddFunction(emitter->module,"synthetic-function",exportedFuncType.llvm);
        LLVMSetFunctionCallConv(funcValue->llvm,LLVMCCallConv);
        SetAstNodeLlvmRepr(node,funcValue);
    }
    return 1;
}
int exportModule(Emitter* emitter, AstNode* moduleNode) {
    return RecursivelyVisitAstNode(emitter,moduleNode,exportModuleVisitor_pre,NULL);
}
int exportModuleVisitor_pre(void* rawEmitter, AstNode* node) {
    Emitter* emitter = rawEmitter;
    AstKind nodeKind = GetAstNodeKind(node);
    switch (nodeKind) {
        case AST_LAMBDA:
        {
            ExportedValue* syntheticFunctionExportedValue = GetAstNodeLlvmRepr(node);
            LLVMValueRef syntheticFunction = syntheticFunctionExportedValue->llvm;

            LLVMBasicBlockRef entryBlock = LLVMAppendBasicBlock(syntheticFunction,"entry");

            LLVMPositionBuilderAtEnd(emitter->builder,entryBlock);
            ExportedValue returnValue = exportValue(emitter,GetAstLambdaBody(node));
            LLVMValueRef returnValueLlvm = returnValue.llvm;
            switch (GetTypeKind(returnValue.type.native)) {
                case T_INT:
                case T_FLOAT:
                {
                    returnValueLlvm = LLVMBuildLoad(emitter->builder,returnValueLlvm,"loaded_for_return");
                }
                default:
                {
                    break;
                }
            }
            LLVMBuildRet(emitter->builder,returnValueLlvm);
            break;
        }
        case AST_VDEF:
        {
            SymbolID lhs = GetAstDefValueStmtLhs(node);
            AstNode* rhsNode = GetAstDefValueStmtRhs(node);
            ExportedValue exportedRhs = exportValue(emitter,rhsNode);
            LLVMSetValueName(exportedRhs.llvm,GetSymbolText(lhs));
            
            ExportedValue* llvmRepr = malloc(sizeof(ExportedValue));
            *llvmRepr = exportedRhs;

            SetAstNodeLlvmRepr(node,llvmRepr);

            break;
        }
        case AST_EXTERN:
        {
            // todo: add support for 'extern' value definitions; values with external linkage.
            COMPILER_ERROR("NotImplemented: AST_EXTERN");
            break;
        }
        default:
        {
            // do nothing
            break;
        }
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
            case T_INT:
            {
                int numBits = GetIntTypeWidthInBits(exportedType.native);
                // todo: subtract 1 bit, add a sign-extension bit for signed.
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
                LLVMTypeRef* llvmArgTypeArray = NULL;
                if (argCount) {
                    llvmArgTypeArray = malloc(argCount*sizeof(LLVMTypeRef));
                    for (int index = 0; index < argCount; index++) {
                        llvmArgTypeArray[index] = exportType(typer,GetFuncTypeArgAt(exportedType.native,index)).llvm;
                    }
                }

                ExportedType exportRetType = exportType(typer,GetFuncTypeImage(exportedType.native));
                if (exportRetType.llvm) {
                    exportedType.llvm = LLVMFunctionType(
                        exportRetType.llvm,
                        llvmArgTypeArray,argCount,
                        0
                    );
                } else {
                    if (DEBUG) {
                        printf("!!- Skipping exportType for T_FUNC due to an error.\n");
                    } else {
                        assert(0 && "Skipping exportType for T_FUNC due to an error.");
                    }
                }

                if (llvmArgTypeArray) {
                    free(llvmArgTypeArray); 
                    llvmArgTypeArray = NULL;
                }

                break;
            }
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
                Defn* defn = GetAstIdDefn(exportedValue.native);
                AstNode* defnNode = GetDefnNode(defn);
                ExportedValue* defnPtrExportedValue = GetAstNodeLlvmRepr(defnNode);
                exportedValue = *defnPtrExportedValue;
                break;
            }
            case AST_LAMBDA:
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
            // INT,FLOAT: llvmValueRef is the value.
            //

            case AST_LITERAL_INT:
            {
                size_t intValue = GetAstIntLiteralValue(exportedValue.native);
                LLVMValueRef stored = LLVMConstInt(exportedValue.type.llvm,intValue,0);
                exportedValue.llvm = LLVMBuildAlloca(emitter->builder,exportedValue.type.llvm,"stack");
                LLVMBuildStore(emitter->builder,stored,exportedValue.llvm);
                break;
            }
            case AST_LITERAL_FLOAT:
            {
                long double floatValue = GetAstFloatLiteralValue(exportedValue.native);
                exportedValue.llvm = LLVMBuildAlloca(emitter->builder,exportedValue.type.llvm,NULL);
                LLVMValueRef stored = LLVMConstReal(exportedValue.type.llvm,floatValue);
                LLVMBuildStore(emitter->builder,stored,exportedValue.llvm);
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
            // Chain: evaluate each item and store in result
            //
            
            case AST_CHAIN:
            {
                LLVMValueRef outValuePtr = NULL;

                // allocaing a result:
                int sizeInBytes = GetTypeSizeInBytes(emitter,exportedValue.type.native);
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
                ExportedValue exportedResult = exportValue(emitter,result);

                // store:
                if (outValuePtr) {
                    LLVMBuildStore(emitter->builder,exportedResult.llvm,outValuePtr);
                    exportedValue.llvm = outValuePtr;
                }
                break;
            }

            //
            // Let statements:
            //

            case AST_VLET:
            {
                AstNode* lhsNode = GetAstLetStmtLhs(exportedValue.native);
                if (GetAstNodeKind(lhsNode) == AST_VPATTERN_SINGLETON) {
                    AstNode* rhsNode = GetAstLetStmtRhs(exportedValue.native);
                    ExportedValue* exportedRhs = malloc(sizeof(ExportedValue));
                    *exportedRhs = exportValue(emitter,rhsNode);
                    SymbolID symbolID = GetAstSingletonPatternName(lhsNode);
                    LLVMSetValueName(exportedRhs->llvm,GetSymbolText(symbolID));
                    SetAstNodeLlvmRepr(lhsNode,exportedRhs);
                    exportedValue.llvm = exportedRhs->llvm;
                } else {
                    COMPILER_ERROR("NotImplemented: let statements with destructured, non singleton, LHS vpatterns.");
                }
                break;
            }
            case AST_VCALL:
            {
                ExportedValue lhsValue = exportValue(emitter,GetAstCallLhs(exportedValue.native));
                
                int argCount = GetAstCallArgCount(exportedValue.native);
                LLVMValueRef* llvmArgs = malloc(argCount * sizeof(LLVMValueRef));
                if (llvmArgs) {
                    for (int argIndex = 0; argIndex < argCount; argIndex++) {
                        AstNode* arg = GetAstCallArgAt(exportedValue.native,argIndex);
                        llvmArgs[argIndex] = exportValue(emitter,arg).llvm;
                    }
                    exportedValue.llvm = LLVMBuildCall(emitter->builder,lhsValue.llvm,llvmArgs,argCount,"call");
                } else {
                    LLVMValueRef voidValue = LLVMGetUndef(LLVMVoidType());
                    exportedValue.llvm = LLVMBuildCall(emitter->builder,lhsValue.llvm,&voidValue,1,"call");
                }
                break;
            }

            //
            // STRING: data stored C-style, pointer to first byte returned.
            // todo: store string length
            //

            // case AST_LITERAL_STRING:
            // {
            //     char const* strValue = GetAstStringLiteralValue(value.exprNode);
            //     size_t len = strlen(strValue);
            //     value.llvmValueRef = LLVMConstString(strValue,len,0);
            //     break;
            // }
            
            // todo: emitExpr for tuples:
            // - always returns a pointer to a tuple.

            default:
            {
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

    int debugPrintLlvmLL = 1;
    if (DEBUG && debugPrintLlvmLL) {
        printf("!!- LLVM Module Dump:\n");
        LLVMDumpModule(emitter.module);
    }

    return result;
}
