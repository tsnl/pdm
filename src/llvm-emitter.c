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
};
static Emitter newEmitter(Typer* typer, AstNode* astModule, char const* moduleName);
static LLVMTypeRef emitType(Typer* typer, Type* typerType);
static void buildLlvmField(Typer* typer, void* sb, SymbolID name, Type* type);
static int emitLlvmModule_preVisitor(void* emitter, AstNode* node);
static int emitLlvmModule_postVisitor(void* emitter, AstNode* node);

Emitter newEmitter(Typer* typer, AstNode* astModule, char const* moduleName) {
    Emitter emitter;
    emitter.typer = typer;
    emitter.astModule = astModule;
    emitter.llvmModule = LLVMModuleCreateWithName(moduleName);
    return emitter;
}
LLVMTypeRef emitType(Typer* typer, Type* typerType) {
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
int emitLlvmModule_preVisitor(void* emitter, AstNode* node) {
    // todo: implement 'emitLlvmModule_preVisitor' [using 'emitType']
    return 0;
}
int emitLlvmModule_postVisitor(void* emitter, AstNode* node) {
    // todo: implement 'emitLlvmModule_postVisitor' [using 'emitType']
    return 0;
}

//
// Implementation:
//

int EmitLlvmModule(Typer* typer, AstNode* module) {
    Emitter emitter = newEmitter(typer,module,"testmodule");
    int result = RecursivelyVisitAstNode(&emitter, module, emitLlvmModule_preVisitor, emitLlvmModule_postVisitor);
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
