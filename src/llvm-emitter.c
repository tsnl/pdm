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
    switch (GetAstNodeKind(node)) {
        case AST_LAMBDA:
        {
            ExportedValue* syntheticFunctionExportedValue = GetAstNodeLlvmRepr(node);
            LLVMValueRef syntheticFunction = syntheticFunctionExportedValue->llvm;

            LLVMBasicBlockRef entryBB = LLVMAppendBasicBlock(syntheticFunction,"entry");
            // todo: destructure arguments, store somewhere?
            // todo: emit RHS here
            // ExportedValue returnValue = exportValue(emitter,GetAstLambdaBody(node));
            break;
        }
        case AST_VDEF:
        {
            SymbolID lhs = GetAstDefValueStmtLhs(node);
            AstNode* rhsNode = GetAstDefValueStmtRhs(node);
            ExportedValue exportedRhs = exportValue(emitter,rhsNode);
            LLVMSetValueName(exportedRhs.llvm,GetSymbolText(lhs));
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
        switch (GetTypeKind(exportedType.native)) {
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
    exportedValue.type = exportType(emitter->typer,GetAstNodeTypingExt_Value(exprNode));
    exportedValue.llvm = NULL;
    if (GetTypeKind(exportedValue.type.native) != T_FUNC) {
        int typeSizeInBytes = GetTypeSizeInBytes(typer,exportedValue.type.native);
        if (typeSizeInBytes) {
            exportedValue.llvm = LLVMBuildAlloca(emitter->builder,exportedValue.type.llvm,NULL);
        }
    }

    if (exportedValue.native) {
        switch (GetAstNodeKind(exportedValue.native)) {
            
            //
            // ID,FUNC: just fetch the stored EValue from the symbol table.
            //

            case AST_LAMBDA:
            {
                ExportedValue* lambdaSynthetic = GetAstNodeLlvmRepr(exportedValue.native);
                exportedValue.llvm = lambdaSynthetic->llvm;
                break;
            }

            //
            // UNIT: represented by a NULL llvm
            //

            case AST_UNIT:
            {
                break;
            }

            //
            // INT,FLOAT: llvmValueRef is the value.
            //

            case AST_LITERAL_INT:
            {
                size_t intValue = GetAstIntLiteralValue(exportedValue.native);
                LLVMValueRef stored = LLVMConstInt(exportedValue.type.llvm,intValue,0);
                LLVMBuildStore(emitter->builder,stored,exportedValue.llvm);
                break;
            }
            case AST_LITERAL_FLOAT:
            {
                long double floatValue = GetAstFloatLiteralValue(exportedValue.native);
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
                // LLVMConstStruct();
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
