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
static int exportModuleHeaderVisitor_post(void* emitter, AstNode* node);
static int exportModule(Emitter* emitter, AstNode* moduleNode);
static int exportModuleVisitor_pre(void* emitter, AstNode* node);
static ExportedType exportType(Typer* typer, Type* type);
static ExportedValue exportValue(Emitter* emitter, AstNode* exprNode);
static AstBuiltinVDefKind selectBuiltinUnaryVDefKind(Emitter* emitter, AstNode* expr);
static AstBuiltinVDefKind selectBuiltinBinaryVDefKind(Emitter* emitter, AstNode* expr);
static ExportedValue helpExportUnaryBuiltinVDefCall(Emitter* emitter, AstBuiltinVDefKind builtinVDefKind, ExportedValue arg);
static ExportedValue helpExportBinaryBuiltinVDefCall(Emitter* emitter, AstBuiltinVDefKind builtinVDefKind, ExportedValue ltArg, ExportedValue rtArg);

//
// WIP: copy to appropriate section later.
//

static AstBuiltinVDefKind selectBuiltinUnaryVDefKind(Emitter* emitter, AstNode* expr) {
    AstUnaryOperator op = GetAstUnaryOperator(expr);
    AstNode* argNode = GetAstUnaryOperand(expr);
    ExportedValue arg = exportValue(emitter,argNode);

    TypeKind argTypeKind = GetTypeKind(arg.type.native);
    if (op == UOP_PLUS) {
        switch (argTypeKind) {
            case T_INT: 
            {
                if (GetIntTypeIsSigned(arg.type.native)) {
                    // signed...
                    switch (GetIntTypeWidth(arg.type.native)) {
                        case INT_8:   return AST_BUILTIN_POS_S8;
                        case INT_16:  return AST_BUILTIN_POS_S16;
                        case INT_32:  return AST_BUILTIN_POS_S32;
                        case INT_64:  return AST_BUILTIN_POS_S64;
                        case INT_128: return AST_BUILTIN_POS_S128;
                        default: goto failure;
                    }
                } else {
                    // unsigned...
                    switch (GetIntTypeWidth(arg.type.native)) {
                        case INT_1:   return AST_BUILTIN_POS_U1;
                        case INT_8:   return AST_BUILTIN_POS_U8;
                        case INT_16:  return AST_BUILTIN_POS_U16;
                        case INT_32:  return AST_BUILTIN_POS_U32;
                        case INT_64:  return AST_BUILTIN_POS_U64;
                        case INT_128: return AST_BUILTIN_POS_U128;
                        default: goto failure;
                    }
                }
            }
            case T_FLOAT:
            {
                switch (GetFloatTypeWidth(arg.type.native)) {
                    case FLOAT_32: return AST_BUILTIN_POS_F32;
                    case FLOAT_64: return AST_BUILTIN_POS_F64;
                    default: goto failure;
                }
            }
            default:
            {
                goto failure;
            }
        }
    }
    if (op == UOP_MINUS) {
        switch (argTypeKind) {
            case T_INT: 
            {
                if (GetIntTypeIsSigned(arg.type.native)) {
                    // signed...
                    switch (GetIntTypeWidth(arg.type.native)) {
                        case INT_8:   return AST_BUILTIN_NEG_S8;
                        case INT_16:  return AST_BUILTIN_NEG_S16;
                        case INT_32:  return AST_BUILTIN_NEG_S32;
                        case INT_64:  return AST_BUILTIN_NEG_S64;
                        case INT_128: return AST_BUILTIN_NEG_S128;
                        default: goto failure;
                    }
                }
            }
            case T_FLOAT:
            {
                switch (GetFloatTypeWidth(arg.type.native)) {
                    case FLOAT_32: return AST_BUILTIN_NEG_F32;
                    case FLOAT_64: return AST_BUILTIN_NEG_F64;
                    default: goto failure;
                }
            }
            default:
            {
                goto failure;
            }
        }
    }
    if (op == UOP_NOT) {
        switch (argTypeKind) {
            case T_INT:
            {
                if (!GetIntTypeIsSigned(arg.type.native)) {
                    // unsigned only
                    switch (GetIntTypeWidth(arg.type.native)) {
                        case INT_1:   return AST_BUILTIN_NOT_U1;
                        case INT_8:   return AST_BUILTIN_NOT_U8;
                        case INT_16:  return AST_BUILTIN_NOT_U16;
                        case INT_32:  return AST_BUILTIN_NOT_U32;
                        case INT_64:  return AST_BUILTIN_NOT_U64;
                        case INT_128: return AST_BUILTIN_NOT_U128;
                        default: goto failure;
                    }
                }
                break;
            }
            default:
            {
                goto failure;
            }
        }
    }
    
    // if we arrive at this point in control flow without returning, it means we've failed.
    failure: {
        COMPILER_ERROR_VA("NotImplemented: 'selectBuiltinUnaryVDefKind' for %s (%s)", AstUnaryOperatorAsText(op), TypeKindAsText(argTypeKind));
        return AST_BUILTIN_NULL;
    }
}
AstBuiltinVDefKind selectBuiltinBinaryVDefKind(Emitter* emitter, AstNode* expr) {
    ExportedValue ltArg = exportValue(emitter,GetAstBinaryLtOperand(expr));
    ExportedValue rtArg = exportValue(emitter,GetAstBinaryRtOperand(expr));
    TypeKind ltArgTypeKind = GetTypeKind(ltArg.type.native);
    TypeKind rtArgTypeKind = GetTypeKind(rtArg.type.native);

    AstBinaryOperator op = GetAstBinaryOperator(expr);

    if (op == BOP_MUL) {
        if (ltArgTypeKind == rtArgTypeKind) {
            if (ltArgTypeKind == T_INT) {
                if (GetIntTypeIsSigned(ltArg.type.native)) {
                    switch (GetIntTypeWidthInBits(ltArg.type.native)) {
                        case 1:   return AST_BUILTIN_MUL_U1;
                        case 8:   return AST_BUILTIN_MUL_U8;
                        case 16:  return AST_BUILTIN_MUL_U16;
                        case 32:  return AST_BUILTIN_MUL_U32;
                        case 64:  return AST_BUILTIN_MUL_U64;
                        case 128: return AST_BUILTIN_MUL_U128;
                        default: break;
                    }
                } else {
                    switch (GetIntTypeWidthInBits(ltArg.type.native)) {
                        case 8:   return AST_BUILTIN_MUL_S8;
                        case 16:  return AST_BUILTIN_MUL_S16;
                        case 32:  return AST_BUILTIN_MUL_S32;
                        case 64:  return AST_BUILTIN_MUL_S64;
                        case 128: return AST_BUILTIN_MUL_S128;
                        default: break;
                    }
                }
            } else if (ltArgTypeKind == T_FLOAT) {
                switch (GetFloatTypeWidthInBits(ltArg.type.native)) {
                    case 32: return AST_BUILTIN_MUL_F32;
                    case 64: return AST_BUILTIN_MUL_F64;
                }
            }
        }
    }
    if (op == BOP_DIV) {
        if (ltArgTypeKind == rtArgTypeKind) {
            if (ltArgTypeKind == T_INT) {
                if (GetIntTypeIsSigned(ltArg.type.native)) {
                    switch (GetIntTypeWidthInBits(ltArg.type.native)) {
                        case 1:   return AST_BUILTIN_QUO_U1;
                        case 8:   return AST_BUILTIN_QUO_U8;
                        case 16:  return AST_BUILTIN_QUO_U16;
                        case 32:  return AST_BUILTIN_QUO_U32;
                        case 64:  return AST_BUILTIN_QUO_U64;
                        case 128: return AST_BUILTIN_QUO_U128;
                        default: break;
                    }
                } else {
                    switch (GetIntTypeWidthInBits(ltArg.type.native)) {
                        case 8:   return AST_BUILTIN_QUO_S8;
                        case 16:  return AST_BUILTIN_QUO_S16;
                        case 32:  return AST_BUILTIN_QUO_S32;
                        case 64:  return AST_BUILTIN_QUO_S64;
                        case 128: return AST_BUILTIN_QUO_S128;
                        default: break;
                    }
                }
            } else if (ltArgTypeKind == T_FLOAT) {
                switch (GetFloatTypeWidthInBits(ltArg.type.native)) {
                    case 32: return AST_BUILTIN_DIV_F32;
                    case 64: return AST_BUILTIN_DIV_F64;
                }
            }
        }
    }
    if (op == BOP_REM) {
        if (ltArgTypeKind == rtArgTypeKind) {
            if (ltArgTypeKind == T_INT) {
                if (GetIntTypeIsSigned(ltArg.type.native)) {
                    switch (GetIntTypeWidthInBits(ltArg.type.native)) {
                        case 1:   return AST_BUILTIN_REM_U1;
                        case 8:   return AST_BUILTIN_REM_U8;
                        case 16:  return AST_BUILTIN_REM_U16;
                        case 32:  return AST_BUILTIN_REM_U32;
                        case 64:  return AST_BUILTIN_REM_U64;
                        case 128: return AST_BUILTIN_REM_U128;
                        default: break;
                    }
                } else {
                    switch (GetIntTypeWidthInBits(ltArg.type.native)) {
                        case 8:   return AST_BUILTIN_REM_S8;
                        case 16:  return AST_BUILTIN_REM_S16;
                        case 32:  return AST_BUILTIN_REM_S32;
                        case 64:  return AST_BUILTIN_REM_S64;
                        case 128: return AST_BUILTIN_REM_S128;
                        default: break;
                    }
                }
            }
        }
    }

    if (op == BOP_ADD) {
        if (ltArgTypeKind == rtArgTypeKind) {
            if (ltArgTypeKind == T_INT) {
                if (GetIntTypeIsSigned(ltArg.type.native)) {
                    switch (GetIntTypeWidthInBits(ltArg.type.native)) {
                        case 1:   return AST_BUILTIN_ADD_U1;
                        case 8:   return AST_BUILTIN_ADD_U8;
                        case 16:  return AST_BUILTIN_ADD_U16;
                        case 32:  return AST_BUILTIN_ADD_U32;
                        case 64:  return AST_BUILTIN_ADD_U64;
                        case 128: return AST_BUILTIN_ADD_U128;
                        default: break;
                    }
                } else {
                    switch (GetIntTypeWidthInBits(ltArg.type.native)) {
                        case 8:   return AST_BUILTIN_ADD_S8;
                        case 16:  return AST_BUILTIN_ADD_S16;
                        case 32:  return AST_BUILTIN_ADD_S32;
                        case 64:  return AST_BUILTIN_ADD_S64;
                        case 128: return AST_BUILTIN_ADD_S128;
                        default: break;
                    }
                }
            } else if (ltArgTypeKind == T_FLOAT) {
                switch (GetFloatTypeWidthInBits(ltArg.type.native)) {
                    case 32: return AST_BUILTIN_ADD_F32;
                    case 64: return AST_BUILTIN_ADD_F64;
                }
            }
        }
    }
    if (op == BOP_SUBTRACT) {
        if (ltArgTypeKind == rtArgTypeKind) {
            if (ltArgTypeKind == T_INT) {
                if (GetIntTypeIsSigned(ltArg.type.native)) {
                    switch (GetIntTypeWidthInBits(ltArg.type.native)) {
                        case 1:   return AST_BUILTIN_SUBTRACT_U1;
                        case 8:   return AST_BUILTIN_SUBTRACT_U8;
                        case 16:  return AST_BUILTIN_SUBTRACT_U16;
                        case 32:  return AST_BUILTIN_SUBTRACT_U32;
                        case 64:  return AST_BUILTIN_SUBTRACT_U64;
                        case 128: return AST_BUILTIN_SUBTRACT_U128;
                        default: break;
                    }
                } else {
                    switch (GetIntTypeWidthInBits(ltArg.type.native)) {
                        case 8:   return AST_BUILTIN_SUBTRACT_S8;
                        case 16:  return AST_BUILTIN_SUBTRACT_S16;
                        case 32:  return AST_BUILTIN_SUBTRACT_S32;
                        case 64:  return AST_BUILTIN_SUBTRACT_S64;
                        case 128: return AST_BUILTIN_SUBTRACT_S128;
                        default: break;
                    }
                }
            } else if (ltArgTypeKind == T_FLOAT) {
                switch (GetFloatTypeWidthInBits(ltArg.type.native)) {
                    case 32: return AST_BUILTIN_SUBTRACT_F32;
                    case 64: return AST_BUILTIN_SUBTRACT_F64;
                }
            }
        }
    }
    // ...

    // if we arrive at this point in control flow without returning, it means we've failed.
    failure: {
        COMPILER_ERROR_VA("NotImplemented: selectBuiltinBinaryVDefKind for %s (%s,%s)", AstBinaryOperatorAsText(op), TypeKindAsText(ltArgTypeKind),TypeKindAsText(rtArgTypeKind));
        return AST_BUILTIN_NULL;
    }
}
ExportedValue helpExportUnaryBuiltinVDefCall(Emitter* emitter, AstBuiltinVDefKind builtinVDefKind, ExportedValue arg) {
    // ASSUMING the actual arg has already been converted to the expected type, and that 'arg.llvm' stores a ptr to that value, emits inline instructions to perform the specified op.
    // this is okay for unary builtins, but binary builtins may require one arg to be converted before invocation. e.g., 2+3.0
    // this should be done in AST_VCALL.

    // todo: create an exported value
    // todo: return the exported value

    LLVMValueRef loadedArg = LLVMBuildLoad(emitter->builder,arg.llvm,"loaded_for_builtin_uop");
    LLVMValueRef loadedResult = NULL;

    switch (builtinVDefKind)
    {
        case AST_BUILTIN_POS_F64:
        case AST_BUILTIN_POS_F32:
        case AST_BUILTIN_POS_S128:
        case AST_BUILTIN_POS_S64:
        case AST_BUILTIN_POS_S32:
        case AST_BUILTIN_POS_S16:
        case AST_BUILTIN_POS_S8:
        case AST_BUILTIN_POS_U128:
        case AST_BUILTIN_POS_U64:
        case AST_BUILTIN_POS_U32:
        case AST_BUILTIN_POS_U16:
        case AST_BUILTIN_POS_U8:
        case AST_BUILTIN_POS_U1:
        {
            // identity
            return arg;
        }

        case AST_BUILTIN_NEG_F64:
        case AST_BUILTIN_NEG_F32:
        {
            loadedResult = LLVMBuildFNeg(emitter->builder,loadedArg,"loaded_fneg");
            break;
        }
        case AST_BUILTIN_NEG_S128:
        case AST_BUILTIN_NEG_S64:
        case AST_BUILTIN_NEG_S32:
        case AST_BUILTIN_NEG_S16:
        case AST_BUILTIN_NEG_S8:
        {
            // -x = ~x + 1
            loadedResult = LLVMBuildNeg(emitter->builder,loadedArg,"loaded_neg");
            break;
        }
        

        default:
        {
            COMPILER_ERROR("NotImplemented: helpExportUnaryBuiltinVDefCall for AST_BUILTIN_?");
            break;
        }
    }

    if (loadedResult) {
        LLVMValueRef builtinUOpResult = LLVMBuildAlloca(emitter->builder,arg.type.llvm,"builtin_uop_out");
        LLVMBuildStore(emitter->builder,loadedResult,builtinUOpResult);
        // LLVMBuildStore(emitter->builder,llvmParam,llvmParamMem);
    }

    COMPILER_ERROR("NotImplemented: helpExportUnaryBuiltinVDefCall");
    ExportedValue dummy;
    return dummy;
}
ExportedValue helpExportBinaryBuiltinVDefCall(Emitter* emitter, AstBuiltinVDefKind builtinVDefKind, ExportedValue ltArg, ExportedValue rtArg) {
    COMPILER_ERROR("NotImplemented: helpExportBinaryBuiltinVDefCall");
}

//
//
// End of WIP
//
//

static void buildLlvmField(Typer* typer, void* sb, SymbolID name, Type* type);

int exportModuleHeaders(Emitter* emitter, AstNode* moduleNode) {
    return RecursivelyVisitAstNode(emitter,moduleNode,NULL,exportModuleHeaderVisitor_post);
}
int exportModuleHeaderVisitor_post(void* rawEmitter, AstNode* node) {
    Emitter* emitter = rawEmitter;
    
    AstKind nodeKind = GetAstNodeKind(node);
    if (nodeKind == AST_LAMBDA) {
        Type* funcType = GetAstNodeTypingExt_Value(node);
        ExportedType exportedFuncType = exportType(emitter->typer,funcType);
        ExportedValue* funcValue = malloc(sizeof(ExportedValue));
        funcValue->native = node;
        funcValue->type = exportedFuncType;
        funcValue->llvm = LLVMAddFunction(emitter->module,"synthetic-function",exportedFuncType.llvm);
        LLVMSetFunctionCallConv(funcValue->llvm,LLVMCCallConv);
        SetAstNodeLlvmRepr(node,funcValue);
    } else if (nodeKind == AST_VDEF) {
        AstNode* vdef = node;

        SymbolID lhs = GetAstDefValueStmtLhs(vdef);
        AstNode* rhsNode = GetAstDefValueStmtRhs(vdef);
        ExportedValue exportedRhs = exportValue(emitter,rhsNode);
        LLVMSetValueName(exportedRhs.llvm,GetSymbolText(lhs));
        
        ExportedValue* llvmRepr = malloc(sizeof(ExportedValue));
        *llvmRepr = exportedRhs;
        SetAstNodeLlvmRepr(vdef,llvmRepr);
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
            
            AstNode* lambda = syntheticFunctionExportedValue->native;
            int argCount = CountAstLambdaPatterns(lambda);
            int postElisionArgCount = 0;
            for (int argIndex = 0; argIndex < argCount; argIndex++) {
                AstNode* argPattern = GetAstLambdaPatternAt(lambda,argIndex);
                AstKind patternKind = GetAstNodeKind(argPattern);

                ExportedValue* exportedPatternValue = malloc(sizeof(ExportedValue));
                exportedPatternValue->native = argPattern;
                exportedPatternValue->type = exportType(emitter->typer,GetAstNodeTypingExt_Value(argPattern));
                exportedPatternValue->llvm = NULL;
                SetAstNodeLlvmRepr(argPattern,exportedPatternValue);

                if (GetTypeKind(exportedPatternValue->type.native) != T_UNIT) {
                    LLVMValueRef llvmParam = LLVMGetParam(syntheticFunctionExportedValue->llvm,postElisionArgCount++);
                    
                    char* fmtArgName = fmt("arg:%d-%s",argIndex,GetSymbolText(GetAstSingletonPatternName(argPattern)));
                    LLVMValueRef llvmParamMem = LLVMBuildAlloca(emitter->builder,exportedPatternValue->type.llvm,fmtArgName);
                    free(fmtArgName);

                    if (patternKind == AST_VPATTERN_SINGLETON) {
                        exportedPatternValue->llvm = llvmParamMem;
                        LLVMBuildStore(emitter->builder,llvmParam,llvmParamMem);
                    } else {
                        COMPILER_ERROR_VA(
                            "NotImplemented: argument definition for pattern %d/%d of kind %s",
                            1+argIndex,argCount,TypeKindAsText(patternKind)
                        );
                    }
                }
            }

            ExportedValue returnValue = exportValue(emitter,GetAstLambdaBody(node));
            LLVMValueRef returnValueLlvm = returnValue.llvm;
            switch (GetTypeKind(returnValue.type.native)) {
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
                // FIXME: void type elision
                // exportedType.llvm = LLVMVoidType();
                exportedType.llvm = LLVMInt32Type();
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
                LLVMValueRef outValuePtr = NULL;

                // allocaing a result:
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
                ExportedValue exportedResult = exportValue(emitter,result);

                // load & store if we allocated memory:
                if (outValuePtr) {
                    exportedValue.llvm = outValuePtr;
                    LLVMValueRef loadedForChainYield = LLVMBuildLoad(emitter->builder,exportedResult.llvm,"chain_result_loaded");
                    LLVMBuildStore(emitter->builder,exportedValue.llvm,loadedForChainYield);
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
                    
                    char* fmtname = fmt("let:%s",GetSymbolText(symbolID));
                    LLVMSetValueName(exportedRhs->llvm,fmtname);
                    free(fmtname);

                    SetAstNodeLlvmRepr(lhsNode,exportedRhs);
                    exportedValue.llvm = exportedRhs->llvm;
                } else {
                    COMPILER_ERROR("NotImplemented: let statements with destructured, non singleton, LHS vpatterns.");
                }
                break;
            }
            case AST_VCALL:
            {
                ExportedType callReturnType = exportType(typer,GetAstNodeTypingExt_Value(exportedValue.native));
                exportedValue.llvm = LLVMBuildAlloca(emitter->builder,callReturnType.llvm,"call_alloca");

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
                    COMPILER_ERROR(
                        // exportedActual.type.native == exportedFormal_type_native,
                        "NotImplemented: implicit type conversions from subtype to supertype in AST_VCALL"
                    );

                    if (exportedActual_typeKind != T_UNIT) {
                        // allocating a new args buffer on demand:
                        if (elidedLlvmArgs == NULL) {
                            elidedLlvmArgs = malloc(argCount * sizeof(LLVMValueRef));
                        }

                        // pushing arg into existing buffer:
                        elidedLlvmArgs[elidedLlvmArgCount++] = exportedActual.llvm;
                    }
                }
                
                LLVMValueRef callValue = NULL;
                if (elidedLlvmArgCount) {
                    callValue = LLVMBuildCall(emitter->builder,lhsValue.llvm,elidedLlvmArgs,argCount,"call_value");
                } else {
                    callValue = LLVMBuildCall(emitter->builder,lhsValue.llvm,NULL,0,"call_value");
                }
                if (callValue) {
                    LLVMBuildStore(emitter->builder,callValue,exportedValue.llvm);
                }
                break;
            }

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

                    if ((toKind == T_FLOAT) && (fromKind == T_FLOAT)) {
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
                        
                        if (toIsSigned != fromIsSigned) {
                            COMPILER_ERROR("NotImplemented: signed/unsigned or unsigned/signed type conversion.");
                        } else {
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
            // Unary and binary operators:
            //

            // todo: painstakingly implement each of these functions, but not as binary operators, but callable functions.
            // todo: implement operator overloading to bridge functions with operator invocation.

            case AST_UNARY:
            {
                AstNode* expr = exportedValue.native;
                AstBuiltinVDefKind builtinVDefKind = selectBuiltinUnaryVDefKind(emitter,expr);
                if (COMPILER_ASSERT(builtinVDefKind != AST_BUILTIN_NULL,"Selected NULL builtinVDefKind while exporting AST_UNARY")) {
                    // todo: emit code based on the builtin vdef kind.
                }
                COMPILER_ERROR("NotImplemented: exportValue for AST_UNARY");
                break;
            }
            case AST_BINARY:
            {
                AstNode* expr = exportedValue.native;
                AstBuiltinVDefKind builtinVDefKind = selectBuiltinBinaryVDefKind(emitter,expr);
                if (COMPILER_ASSERT(builtinVDefKind != AST_BUILTIN_NULL,"Selected NULL builtinVDefKind while exporting AST_BINARY")) {
                    // todo: emit code based on the builtin vdef kind.
                }
                COMPILER_ERROR("NotImplemented: exportValue for AST_BINARY");
                break;
            }
            // case AST_BINARY:
            // {
            //     // todo: binary operators only support integers for now.
            //     AstBinaryOperator op = GetAstBinaryOperator(expr);
            //     AstNode* ltArg = GetAstBinaryLtOperand(expr);
            //     AstNode* rtArg = GetAstBinaryRtOperand(expr);
            //     LLVMValueRef llvmLtArg = emitExpr(emitter,ltArg);
            //     LLVMValueRef llvmRtArg = emitExpr(emitter,rtArg);
                
            //     switch (op)
            //     {
            //         case BOP_MUL:
            //         {
            //             return LLVMBuildMul(emitter->llvmBuilder,llvmLtArg,llvmRtArg,"mul");
            //         }
            //         case BOP_DIV:
            //         {
            //             return LLVMBuildUDiv(emitter->llvmBuilder,llvmLtArg,llvmRtArg,"div");
            //         }
            //         case BOP_REM:
            //         {
            //             return LLVMBuildURem(emitter->llvmBuilder,llvmLtArg,llvmRtArg,"rem");
            //         }
            //         case BOP_ADD:
            //         {
            //             return LLVMBuildAdd(emitter->llvmBuilder,llvmLtArg,llvmRtArg,"sum");
            //         }
            //         case BOP_SUB:
            //         {
            //             return LLVMBuildSub(emitter->llvmBuilder,llvmLtArg,llvmRtArg,"sub");
            //         }
            //         case BOP_AND:
            //         {
            //             return LLVMBuildAnd(emitter->llvmBuilder,llvmLtArg,llvmRtArg,"and");
            //         }
            //         case BOP_XOR:
            //         {
            //             return LLVMBuildXor(emitter->llvmBuilder,llvmLtArg,llvmRtArg,"xor");
            //         }
            //         case BOP_OR:
            //         {
            //             return LLVMBuildOr(emitter->llvmBuilder,llvmLtArg,llvmRtArg,"or");
            //         }
            //         case BOP_LTHAN:
            //         {
            //             LLVMValueRef rawValue = LLVMBuildICmp(emitter->llvmBuilder,LLVMIntULT,llvmLtArg,llvmRtArg,"lt");
            //             return LLVMBuildIntCast(emitter->llvmBuilder,rawValue,LLVMInt1Type(),NULL);
            //         }
            //         case BOP_GTHAN:
            //         {
            //             LLVMValueRef rawValue = LLVMBuildICmp(emitter->llvmBuilder,LLVMIntUGT,llvmLtArg,llvmRtArg,"gt");
            //             // return LLVMBuildIntCast(emitter->llvmBuilder,rawValue,LLVMInt1Type(),NULL);
            //             return rawValue;
            //         }
            //         case BOP_LETHAN:
            //         {
            //             LLVMValueRef rawValue = LLVMBuildICmp(emitter->llvmBuilder,LLVMIntULE,llvmLtArg,llvmRtArg,"le");
            //             // return LLVMBuildIntCast(emitter->llvmBuilder,rawValue,LLVMInt1Type(),NULL);
            //             return rawValue;
            //         }
            //         case BOP_GETHAN:
            //         {
            //             LLVMValueRef rawValue = LLVMBuildICmp(emitter->llvmBuilder,LLVMIntUGE,llvmLtArg,llvmRtArg,"ge");
            //             return LLVMBuildIntCast(emitter->llvmBuilder,rawValue,LLVMInt1Type(),NULL);
            //         }
            //         case BOP_EQUALS:
            //         {
            //             // LLVMValueRef rawValue = LLVMBuildFCmp(emitter->llvmBuilder,LLVMRealOEQ,llvmLtArg,llvmRtArg,"eq");
            //             LLVMValueRef rawValue = LLVMBuildICmp(emitter->llvmBuilder,LLVMIntEQ,llvmLtArg,llvmRtArg,"eq");
            //             // return LLVMBuildIntCast(emitter->llvmBuilder,rawValue,LLVMInt1Type(),NULL);
            //             return rawValue;
            //         }
            //         case BOP_NEQUALS:
            //         {
            //             // LLVMValueRef rawValue = LLVMBuildFCmp(emitter->llvmBuilder,LLVMRealONE,llvmLtArg,llvmRtArg,"eq");
            //             LLVMValueRef rawValue = LLVMBuildICmp(emitter->llvmBuilder,LLVMIntNE,llvmLtArg,llvmRtArg,"neq");
            //             // return LLVMBuildIntCast(emitter->llvmBuilder,rawValue,LLVMInt1Type(),NULL);
            //             return rawValue;
            //         }
            //         default:
            //         {
            //             if (DEBUG) {
            //                 printf("!!- NotImplemented: AST_BINARY in helpEmitExpr for BOP_?\n");
            //             } else {
            //                 assert(0 && "NotImplemented: AST_BINARY in helpEmitExpr for BOP_?");
            //             }
            //             return NULL;
            //         }
            //     }
            // }

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

    int debugPrintLlvmLL = 1;
    if (DEBUG && debugPrintLlvmLL) {
        printf("!!- LLVM Module Dump:\n");
        LLVMDumpModule(emitter.module);
    }

    return result;
}
