#include "llvm-emitter.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include <llvm-c/Core.h>
#include "stb/stretchy_buffer.h"

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
    AstNode* exprNode;
    LLVMValueRef llvmValueRef;
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
        ExportedType exportedFuncType = exportType(emitter->typer,GetAstNodeValueType(node));
        ExportedValue* funcValue = malloc(sizeof(ExportedValue));
        funcValue->exprNode = node;
        funcValue->type = exportedFuncType;
        funcValue->llvmValueRef = LLVMAddFunction(emitter->module,"synthetic-function",exportedFuncType.llvm);
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
        case AST_DEF:
        {
            AstNode* desugaredRhsNode = GetAstDefStmtDesugaredRhs(node);
            ExportedType exportedType = exportType(emitter->typer,GetAstNodeValueType(desugaredRhsNode));
            
            // todo: append a basic block here.

            ExportedValue exportedDesugaredRhsValue = exportValue(emitter,desugaredRhsNode);
            
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
    exportedType.native = GetConcreteType(typer,type);
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
                ExportedType* exportFields = NULL;
                MapCompoundType(typer,type,buildLlvmField,&exportFields);
                
                int fieldCount = sb_count(exportFields);
                LLVMTypeRef* fieldLlvmTypes = malloc(fieldCount*sizeof(LLVMTypeRef));
                for (int i = 0; i < fieldCount; i++) {
                    ExportedType eField = exportFields[i];
                    fieldLlvmTypes[i] = eField.llvm;
                }
                sb_free(exportFields);

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
                // todo: implement tuple destructuring for improved call performance.
                // for now, all functions and calls are unary
                ExportedType exportArgType = exportType(typer,GetFuncTypeDomain(exportedType.native));
                ExportedType exportRetType = exportType(typer,GetFuncTypeImage(exportedType.native));
                if (exportArgType.llvm && exportRetType.llvm) {
                    exportedType.llvm = LLVMFunctionType(
                        exportRetType.llvm,
                        &exportRetType.llvm,1,
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

    ExportedValue exportedValue;
    
    Type* valueType = GetAstNodeValueType(exprNode);
    Type* concreteType = GetConcreteType(typer,valueType);

    exportedValue.exprNode = exprNode;
    exportedValue.llvmValueRef = NULL;
    exportedValue.type = exportType(emitter->typer,concreteType);

    if (exportedValue.exprNode) {
        switch (GetAstNodeKind(exportedValue.exprNode)) {
            
            //
            // ID,FUNC: just fetch the stored EValue from the symbol table.
            //

            case AST_LAMBDA:
            {
                ExportedValue* lambdaSynthetic = GetAstNodeLlvmRepr(exportedValue.exprNode);
                exportedValue.llvmValueRef = lambdaSynthetic->llvmValueRef;
                break;
            }

            //
            // UNIT: represented by a NULL llvmValueRef
            //

            case AST_UNIT:
            {
                exportedValue.llvmValueRef = NULL;
                break;
            }

            //
            // INT,FLOAT: llvmValueRef is the value.
            //

            case AST_LITERAL_INT:
            {
                size_t intValue = GetAstIntLiteralValue(exportedValue.exprNode);
                exportedValue.llvmValueRef = LLVMConstInt(exportedValue.type.llvm,intValue,0);
                break;
            }
            case AST_LITERAL_FLOAT:
            {
                long double floatValue = GetAstFloatLiteralValue(exportedValue.exprNode);
                exportedValue.llvmValueRef = LLVMConstReal(exportedValue.type.llvm,floatValue);
                break;
            }

            //
            // TUPLE,UNION,ARRAY: llvmValueRef is a pointer to the value.
            //

            case AST_TUPLE:
            {
                exportedValue.llvmValueRef = LLVMBuildAlloca(emitter->builder,exportedValue.type.llvm,"tuple");
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
    return result;
}
