#include "llvm-emitter.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>

#include "stb/stretchy_buffer.h"

#include "source.h"
#include "primer.h"
#include "typer.h"

// See Paul Smith's "How to Get Started with LLVM C API"
// - https://www.pauladamsmith.com/blog/2015/01/how-to-get-started-with-llvm-c-api.html

// See Eli Bendersky's Python implementation of the LLVM Kaleidoscope demo:
// - https://github.com/eliben/pykaleidoscope/blob/master/chapter3and4.py

typedef struct Emitter Emitter;
struct Emitter {
    Typer* typer;
    AstNode* astModule;
    LLVMModuleRef llvmModule;
    LLVMBuilderRef llvmBuilder;

    int currentLlvmFunctionStackCount;
    LLVMValueRef* currentLlvmFunctionStackSB;
};
static Emitter newEmitter(Typer* typer, AstNode* astModule, char const* moduleName);
static void pushLlvmFunctionToEmitterStack(Emitter* emitter, LLVMValueRef pushed);
static void popLlvmFunctionFromEmitterStack(Emitter* emitter);
static LLVMValueRef currentLlvmFunction(Emitter* emitter);
static LLVMTypeRef emitType(Typer* emitter, Type* typerType);
static LLVMTypeRef helpEmitType(Typer* emitter, Type* typerType);
static LLVMValueRef emitExpr(Emitter* emitter, AstNode* expr);
static LLVMValueRef helpEmitExpr(Emitter* emitter, AstNode* expr);
static void buildLlvmField(Typer* typer, void* sb, SymbolID name, Type* type);
static AstNode* getDefnRhsAstNode(Emitter* emitter, AstNode* defnNode);

Emitter newEmitter(Typer* typer, AstNode* astModule, char const* moduleName) {
    Emitter emitter;
    emitter.typer = typer;
    emitter.astModule = astModule;
    emitter.llvmModule = LLVMModuleCreateWithName(moduleName);
    emitter.llvmBuilder = LLVMCreateBuilder();
    emitter.currentLlvmFunctionStackCount = 0;
    emitter.currentLlvmFunctionStackSB = NULL;
    return emitter;
}
void pushLlvmFunctionToEmitterStack(Emitter* emitter, LLVMValueRef pushed) {
    int index = (emitter->currentLlvmFunctionStackCount++);
    int capacity = sb_count(emitter->currentLlvmFunctionStackSB);
    if (index >= capacity) {
        sb_push(emitter->currentLlvmFunctionStackSB,pushed);
        assert(index < sb_count(emitter->currentLlvmFunctionStackSB) && "SB overflow error.");
    } else {
        emitter->currentLlvmFunctionStackSB[index] = pushed;
    }
}
void popLlvmFunctionFromEmitterStack(Emitter* emitter) {
    if (emitter->currentLlvmFunctionStackCount > 0) {
        --emitter->currentLlvmFunctionStackCount;
    }
}
LLVMValueRef currentLlvmFunction(Emitter* emitter) {
    return emitter->currentLlvmFunctionStackSB[emitter->currentLlvmFunctionStackCount-1];
}
LLVMTypeRef emitType(Typer* typer, Type* typerType) {
    LLVMTypeRef llvmType;
    llvmType = GetTypeLlvmRepr(typerType);
    if (llvmType) {
        return llvmType;
    }
    llvmType = helpEmitType(typer,typerType);
    if (llvmType) {
        SetTypeLlvmRepr(typerType,llvmType);
    }
    return llvmType;
}
LLVMTypeRef helpEmitType(Typer* typer, Type* typerType) {
    Type* concrete = GetConcreteType(typerType);
    switch (GetTypeKind(concrete))
    {
        case T_UNIT:
        {
            return LLVMVoidType();
        }
        case T_INT:
        {
            IntWidth intWidth = GetIntTypeWidth(concrete);
            switch (intWidth)
            {
                case INT_1: return LLVMInt1Type();
                case INT_8: return LLVMInt8Type();
                case INT_16: return LLVMInt16Type();
                case INT_32: return LLVMInt32Type();
                case INT_64: return LLVMInt64Type();
                case INT_128: return LLVMInt128Type();
                default: return NULL;
            }
        }
        case T_FLOAT:
        {
            FloatWidth floatWidth = GetFloatTypeWidth(concrete);
            switch (floatWidth)
            {
                case FLOAT_32: return LLVMFloatType();
                case FLOAT_64: return LLVMDoubleType();
                default: return NULL;
            }
            break;
        }
        case T_FUNC:
        {
            LLVMTypeRef arg = emitType(typer,GetFuncTypeDomain(concrete));
            LLVMTypeRef ret = emitType(typer,GetFuncTypeDomain(concrete));
            return LLVMFunctionType(ret, &arg, 1, 0);
        }
        case T_PTR:
        {
            LLVMTypeRef pointeeType = emitType(typer,GetPtrTypePointee(concrete));
            return LLVMPointerType(pointeeType,0);
        }
        case T_TUPLE:
        {
            LLVMTypeRef* elementTypesSB = NULL;
            MapCompoundType(typer,concrete,buildLlvmField,&elementTypesSB);
            return LLVMStructType(elementTypesSB,sb_count(elementTypesSB),1);
        }
        case T_UNION:
        {
            if (DEBUG) {
                printf("!!- Not implemented: `emitType` for T_UNION.\n");
            } else {
                assert(0 && "Not implemented: `emitType` for T_UNION");
            }
            return NULL;
        }
        default:
        {
            if (DEBUG) {
                printf("!!- Not implemented: `emitType` for <?>.\n");
            } else {
                assert(0 && "Not implemented: `emitType` for <?>");
            }
            return NULL;
        }
    }
    return NULL;
}
void buildLlvmField(Typer* typer, void* rawSB, SymbolID name, Type* type) {
    LLVMTypeRef** sb = rawSB;
    LLVMTypeRef fieldTypeRef = emitType(typer,type);
    sb_push((*sb),fieldTypeRef);
}
AstNode* getDefnRhsAstNode(Emitter* emitter, AstNode* defnNode) {
    AstKind defnKind = GetAstNodeKind(defnNode);
    switch (defnKind)
    {
        case AST_STMT_BIND:
        {
            AstNode* rhs = GetAstBindStmtRhs(defnNode);
            return rhs;
        }
        case AST_FIELD__MODULE_ITEM:
        {
            AstNode* rhs = GetAstFieldRhs(defnNode);
            return rhs;
        }
        case AST_FIELD__PATTERN_ITEM:
        {
            // llvm repr (param) stored on the field in lambda definitions
            return defnNode;
        }
        default:
        {
            if (DEBUG) {
                printf("!!- getDefnRhs not implemented for defnNode of kind <?>.");
            } else {
                assert(0 && "getDefnRhs not implemented for defnNode of kind <?>.");
            }
            return NULL;
        }
    }
}
LLVMValueRef emitExpr(Emitter* emitter, AstNode* expr) {
    LLVMValueRef value;
    value = GetAstNodeLlvmRepr(expr);
    if (value) {
        return value;
    }
    value = helpEmitExpr(emitter,expr);
    if (value) {
        SetAstNodeLlvmRepr(expr,value);
    }
    return value;
}
LLVMValueRef helpEmitExpr(Emitter* emitter, AstNode* expr) {
    switch (GetAstNodeKind(expr))
    {
        case AST_ID:
        {
            if (GetAstNodeLookupContext(expr) == ASTCTX_VALUE) {
                Defn* defn = GetAstIdDefn(expr);
                AstNode* defnNode = GetDefnNode(defn);
                if (defnNode) {
                    AstNode* rhsNode = getDefnRhsAstNode(emitter,defnNode);
                    return emitExpr(emitter,rhsNode);
                } else {
                    if (DEBUG) {
                        printf("!!- WARNING: defnNode is NULL in `helpEmitExpr`.\n");
                    }
                }
            } 
            return NULL;
        }
        case AST_LITERAL_INT:
        {
            Type* type = GetAstNodeType(expr);
            size_t value = GetAstIntLiteralValue(expr);
            LLVMTypeRef llvmType = emitType(emitter->typer,type);
            return LLVMConstInt(llvmType,value,0);
        }
        case AST_LITERAL_FLOAT:
        {
            Type* type = GetAstNodeType(expr);
            LLVMTypeRef llvmType = emitType(emitter->typer,type);
            long double value = GetAstFloatLiteralValue(expr);
            return LLVMConstReal(llvmType,value);
        }
        case AST_LITERAL_STRING:
        {
            int const* chars = GetAstStringLiteralValue(expr);
            int length = 0;
            for (;chars[length];length++);
            char* charsSB = NULL;
            for (int index = 0; index < length; index++) {
                int ch_int = chars[index];
                char ch = ch_int;
                sb_push(charsSB, ch);
            }
            LLVMValueRef string = LLVMConstString(charsSB, sb_count(charsSB), 1);
            sb_free(charsSB);
            return string;
        }
        case AST_CALL:
        {
            // todo: pass captured arguments here
            // todo: destructure tuple types for function calls
            Type* callType = GetAstNodeType(expr);
            LLVMTypeRef callLlvmType = emitType(emitter->typer,callType);
            AstNode* lhs = GetAstCallLhs(expr);
            AstNode* rhs = GetAstCallRhs(expr);
            LLVMValueRef lhsLlvmValue = emitExpr(emitter,lhs);
            LLVMValueRef rhsLlvmValue = emitExpr(emitter,rhs);
            return LLVMBuildCall2(
                emitter->llvmBuilder,
                callLlvmType,
                lhsLlvmValue,
                &rhsLlvmValue,1,
                "call"
            );
        }
        case AST_UNARY:
        {
            // todo: emitExpr for AST_UNARY
            return NULL;
        }
        case AST_BINARY:
        {
            // todo: emitExpr for AST_BINARY
            return NULL;
        }
        case AST_PAREN:
        {
            return emitExpr(emitter,GetAstParenItem(expr));
        }
        case AST_CHAIN:
        {
            AstNode* exprResult = GetAstChainResult(expr);
            return emitExpr(emitter,exprResult);
        }
        case AST_LAMBDA:
        case AST_FIELD__PATTERN_ITEM:
        {
            // set by `emitLlvmModulePrefix_preVisitor`
            // we should not reach this point

            if (DEBUG) {
                printf("!!- error: should not evaluate node of kind <?> in `tryEmitExpr`\n");
            } else {
                assert(0 && "error: should not evaluate node of kind <?> in `tryEmitExpr`");
            }
            return NULL;
        }
        case AST_DOT_NAME:
        {
            if (DEBUG) {
                printf("!!- NotImplemented: AST_DOT_NAME in `emitExpr`\n");
            } else {
                assert(0 && "NotImplemented: AST_DOT_NAME in `emitExpr`");
            }
            return NULL;
        }
        case AST_DOT_INDEX:
        {
            if (DEBUG) {
                printf("!!- NotImplemented: AST_DOT_INDEX in `emitExpr`\n");
            } else {
                assert(0 && "NotImplemented: AST_DOT_INDEX in `emitExpr`");
            }
            return NULL;
        }
        case AST_MODULE:
        {
            // todo: store an integer ID mapping modules
            if (DEBUG) {
                printf("!!- NotImplemented: AST_MODULE in `emitExpr`\n");
            } else {
                assert(0 && "NotImplemented: AST_MODULE in `emitExpr`");
            }
            return NULL;
        }
        case AST_TUPLE:
        {
            // todo: store an integer ID mapping modules
            if (DEBUG) {
                printf("!!- NotImplemented: handler for AST_TUPLE in `emitExpr`\n");
            } else {
                assert(0 && "NotImplemented: handler for AST_TUPLE in `emitExpr`");
            }
            return NULL;
        }
        case AST_STRUCT:
        {
            // todo: store an integer ID mapping modules
            if (DEBUG) {
                printf("!!- NotImplemented: handler for AST_STRUCT in `emitExpr`\n");
            } else {
                assert(0 && "NotImplemented: handler for AST_STRUCT in `emitExpr`");
            }
            return NULL;
        }
        case AST_ITE:
        {
            // getting the ITE type:
            Type* iteType = GetAstNodeType(expr);
            LLVMTypeRef iteLlvmType = emitType(emitter->typer,iteType);
            
            // adding any basic blocks required:
            LLVMValueRef func = currentLlvmFunction(emitter);
            LLVMBasicBlockRef entryBlock = LLVMAppendBasicBlock(func, "ite-entry");
            LLVMBasicBlockRef trueBlock = LLVMAppendBasicBlock(func, "ite-true");
            LLVMBasicBlockRef falseBlock = LLVMAppendBasicBlock(func, "ite-false");
            LLVMBasicBlockRef landingBlock = LLVMAppendBasicBlock(func, "ite-landing");

            // computing cond, breaking in 'entry' to other blocks:
            LLVMPositionBuilderAtEnd(emitter->llvmBuilder,entryBlock);
            AstNode* cond = GetAstIteCond(expr);
            LLVMValueRef condLlvm = emitExpr(emitter,cond);
            LLVMBuildCondBr(emitter->llvmBuilder,condLlvm,trueBlock,falseBlock);
            
            // populating 'ite-true':
            LLVMPositionBuilderAtEnd(emitter->llvmBuilder,entryBlock);
            AstNode* ifTrue = GetAstIteIfTrue(expr);
            LLVMValueRef valueIfTrue = NULL;
            if (ifTrue) {
                valueIfTrue = emitExpr(emitter,ifTrue);
            }

            // populating 'ite-false':
            LLVMPositionBuilderAtEnd(emitter->llvmBuilder,falseBlock);
            AstNode* ifFalse = GetAstIteIfFalse(expr);
            LLVMValueRef valueIfFalse = NULL;
            if (ifFalse) {
                valueIfFalse = emitExpr(emitter,ifFalse);
            }

            // tying together these blocks with a 'phi' node and returning:
            LLVMPositionBuilderAtEnd(emitter->llvmBuilder,landingBlock);
            LLVMValueRef phi = LLVMBuildPhi(emitter->llvmBuilder, iteLlvmType, "ite-result");
            LLVMValueRef phi_values[] = {valueIfTrue, valueIfFalse};
            LLVMBasicBlockRef phi_blocks[] = {entryBlock, falseBlock};
            LLVMAddIncoming(phi, phi_values, phi_blocks, 2);
            return phi;
        }
        default:
        {
            if (DEBUG) {
                printf("!!- Invalid kind in `emitExpr`.\n");
            } else {
                assert(0 && "Invalid kind in `emitExpr`");
            }
            return NULL;
        }
    }
}

int emitLlvmModulePrefix_preVisitor(void* rawEmitter, AstNode* node) {
    Emitter* emitter = rawEmitter;
    AstKind nodeKind = GetAstNodeKind(node);
    switch (nodeKind) {
        case AST_LAMBDA:
        {
            // todo: add captured arguments.

            AstNode* pattern = GetAstLambdaPattern(node);
            AstNode* body = GetAstLambdaBody(node);
            int patternLength = GetAstPatternLength(pattern);

            Type* funcType = GetAstNodeType(node);
            Type* funcDomainType = GetFuncTypeDomain(funcType);
            Type* funcImageType = GetFuncTypeImage(funcType);

            LLVMTypeRef funcImageLlvmType = emitType(emitter->typer,funcImageType);

            LLVMTypeRef funcLlvmType = NULL;
            if (patternLength == 0) {
                funcLlvmType = LLVMFunctionType(funcImageLlvmType,NULL,0,0);
            } else if (patternLength == 1) {
                LLVMTypeRef funcDomainLlvmType = emitType(emitter->typer,funcDomainType);
                funcLlvmType = LLVMFunctionType(funcImageLlvmType,&funcDomainLlvmType,1,0);
            } else {
                // todo: destructure tuple arguments:
                // for (int index = 0; index < patternLength; index++) {
                //     AstNode* field = GetAstPatternFieldAt(pattern,index);
                // }
                if (DEBUG) {
                    printf("!!- NotImplemented: lambdas with patterns of length > 1\n");
                } else {
                    assert(0 && "NotImplemented: lambdas with patterns of length > 1");
                }
                funcLlvmType = NULL;
            }

            // adding the defined LLVM function reference:
            LLVMValueRef funcLlvmExpr = LLVMAddFunction(emitter->llvmModule,"__anonymous_function__",funcLlvmType);

            // pushing the LLVM function reference to the emitter stack:
            pushLlvmFunctionToEmitterStack(emitter,funcLlvmExpr);
            
            // storing formal argument references:
            for (int index = 0; index < patternLength; index++) {
                AstNode* patternArg = GetAstPatternFieldAt(pattern,index);
                LLVMValueRef llvmArg = LLVMGetParam(funcLlvmExpr,index);
                SetAstNodeLlvmRepr(patternArg,llvmArg);
            }

            // emitting the body or void:
            LLVMBasicBlockRef entry = LLVMAppendBasicBlock(funcLlvmExpr,"entry");
            LLVMPositionBuilderAtEnd(emitter->llvmBuilder,entry);
            if (GetTypeKind(GetAstNodeType(body)) == T_UNIT) {
                LLVMBuildRet(emitter->llvmBuilder,NULL);
            } else {
                LLVMValueRef bodyLlvmExpr = emitExpr(emitter,body);
                LLVMBuildRet(emitter->llvmBuilder,bodyLlvmExpr);
            }
            
            // storing the LLVM function reference on the Lambda:
            SetAstNodeLlvmRepr(node,funcLlvmExpr);

            break;
        }
        default:
        {
            break;
        }
    }
    return 1;
}
int emitLlvmModulePrefix_postVisitor(void* rawEmitter, AstNode* node) {
    Emitter* emitter = rawEmitter;
    switch (GetAstNodeKind(node)) {
        case AST_LAMBDA:
        {
            // popping the LLVM function reference from the emitter stack:
            popLlvmFunctionFromEmitterStack(emitter);
            break;
        }
        default:
        {
            // do nothing.
            break;
        }
    }
    return 1;
}
int emitLlvmModule_preVisitor(void* rawEmitter, AstNode* node) {
    Emitter* emitter = rawEmitter;
    AstKind nodeKind = GetAstNodeKind(node);
    switch (nodeKind) {
        case AST_FIELD__MODULE_ITEM:
        {
            AstNode* rhs = GetAstFieldRhs(node);
            SetAstNodeLlvmRepr(node,emitExpr(emitter,rhs));
            break;
        }
        case AST_UNIT:
        case AST_LITERAL_FLOAT:
        case AST_LITERAL_INT:
        case AST_LITERAL_STRING:
        case AST_LAMBDA:
        case AST_STRUCT:
        case AST_TUPLE:
        case AST_UNARY:
        case AST_BINARY:
        case AST_CALL:
        case AST_PAREN:
        {
            AstNode* expr = node;
            LLVMValueRef llvmExpr = emitExpr(emitter,expr);

            if (nodeKind == AST_LAMBDA) {
                // pushing the LLVM function reference to the emitter stack:
                pushLlvmFunctionToEmitterStack(emitter,llvmExpr);
            }
        }
        default:
        {
            // do nothing.
            break;
        }
    }
    return 1;
}
int emitLlvmModule_postVisitor(void* rawEmitter, AstNode* node) {
    Emitter* emitter = rawEmitter;
    AstKind nodeKind = GetAstNodeKind(node);
    switch (nodeKind) {
        case AST_LAMBDA:
        {
            // popping the LLVM function reference from the emitter stack:
            popLlvmFunctionFromEmitterStack(emitter);
            break;
        }
        default:
        {
            // do nothing.
            break;
        }
    }
    return 1;
}

//
// Implementation:
//

int EmitLlvmModule(Typer* typer, AstNode* module) {
    Emitter emitter = newEmitter(typer,module,"testmodule");

    // we run 2 emitter passes:
    int result = 1;
    result = RecursivelyVisitAstNode(&emitter, module, emitLlvmModulePrefix_preVisitor, emitLlvmModulePrefix_postVisitor) && result;
    result = RecursivelyVisitAstNode(&emitter, module, emitLlvmModule_preVisitor, emitLlvmModule_postVisitor) && result;
    if (!result) {
        if (DEBUG) {
            printf("!!- Emission visitor failed.\n");
        }
        return 0;
    }

    LLVMVerifierFailureAction failureAction = (DEBUG ? LLVMPrintMessageAction : LLVMReturnStatusAction);
    char* errorMessage = NULL;
    result = !LLVMVerifyModule(emitter.llvmModule,failureAction,&errorMessage) && result;
    if (result) {
        SetAstNodeLlvmRepr(module,emitter.llvmModule);

        // todo: PostFeedback from LLVMVerifyModule
        LLVMDisposeBuilder(emitter.llvmBuilder);
    }

    if (DEBUG) {
        char* text = LLVMPrintModuleToString(emitter.llvmModule);
        printf("!!- LLVMVerifyModule %s with message: '%s'\n\n%s", (result ? "succeeded":"failed"), errorMessage,text);
        LLVMDisposeMessage(text);
    }

    return result;
}


// debug

// int cgen_main(int argc, char const *argv[]) {
//     LLVMModuleRef mod = LLVMModuleCreateWithName("my_module");

//     LLVMTypeRef param_types[] = { LLVMInt32Type(), LLVMInt32Type() };
//     LLVMTypeRef ret_type = LLVMFunctionType(LLVMInt32Type(), param_types, 2, 0);
//     LLVMValueRef sum = LLVMAddFunction(mod, "sum", ret_type);

//     LLVMBasicBlockRef entry = LLVMAppendBasicBlock(sum, "entry");

//     LLVMBuilderRef builder = LLVMCreateBuilder();
//     LLVMPositionBuilderAtEnd(builder, entry);
//     LLVMValueRef tmp = LLVMBuildAdd(builder, LLVMGetParam(sum, 0), LLVMGetParam(sum, 1), "tmp");
//     LLVMBuildRet(builder, tmp);

//     char *error = NULL;
//     LLVMVerifyModule(mod, LLVMAbortProcessAction, &error);
//     LLVMDisposeMessage(error);

//     LLVMExecutionEngineRef engine;
//     error = NULL;
//     LLVMLinkInMCJIT();
//     LLVMInitializeNativeTarget();
//     if (LLVMCreateExecutionEngineForModule(&engine, mod, &error) != 0) {
//         fprintf(stderr, "failed to create execution engine\n");
//         abort();
//     }
//     if (error) {
//         fprintf(stderr, "error: %s\n", error);
//         LLVMDisposeMessage(error);
//         exit(EXIT_FAILURE);
//     }

//     if (argc < 3) {
//         fprintf(stderr, "usage: %s x y\n", argv[0]);
//         exit(EXIT_FAILURE);
//     }
//     long long x = strtoll(argv[1], NULL, 10);
//     long long y = strtoll(argv[2], NULL, 10);

//     LLVMGenericValueRef args[] = {
//         LLVMCreateGenericValueOfInt(LLVMInt32Type(), x, 0),
//         LLVMCreateGenericValueOfInt(LLVMInt32Type(), y, 0)
//     };
//     LLVMGenericValueRef res = LLVMRunFunction(engine, sum, 2, args);
//     printf("%d\n", (int)LLVMGenericValueToInt(res, 0));

//     // Write out bitcode to file
//     if (LLVMWriteBitcodeToFile(mod, "sum.bc") != 0) {
//         fprintf(stderr, "error writing bitcode to file, skipping\n");
//     }

//     LLVMDisposeBuilder(builder);
//     LLVMDisposeExecutionEngine(engine);


// }

// todo: implement a lambda-only visitor to define lambdas and map them to calls
// todo: implement constructors for ad-hoc struct and union literals?
// todo: implement a final emitter that...
//  - uses previously emitted definitions
//  - writes definitions in a 1:1 form from our source code.