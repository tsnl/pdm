#include "interp.h"

#include <assert.h>
#include <stdio.h>

#include "stb/stretchy_buffer.h"

#include "config.h"
#include "lexer.h"
#include "parser.h"
#include "primer.h"
#include "typer.h"
#include "code-printer.h"
#include "llvm-emitter.h"

typedef struct LoadedSource LoadedSource;

struct LoadedSource {
    Source* source;
    AstNode* scriptAstNode;
};

struct Interp {
    LoadedSource* loadedSourceSb;
    Manager* typer;
    Primer* primer;
};

static int lookupLoadedSource(Interp* interp, Source* source) {
    for (int i = 0; i < sb_count(interp->loadedSourceSb); i++) {
        if (interp->loadedSourceSb[i].source == source) {
            return i;
        }
    }
    return -1;
}
static LoadedSource loadedSource(Interp* interp, int index) {
    return interp->loadedSourceSb[index];
}

//
// Implementation:
//

Interp* CreateInterp(void) {
    InitSymbols();
    InitLexer();

    Interp* interp = malloc(sizeof(Interp));
    interp->loadedSourceSb = NULL;
    interp->typer = NewManager(NewDefaultManagerCfg());
    interp->primer = CreatePrimer(interp->typer);
    return interp;
}
void DestroyInterp(Interp* interp) {
    free(interp);
    DeInitSymbols();
    DeInitLexer();
}
int InterpLoadModuleSource(Interp* interp, Source* scriptSource) {
    int alreadyLoadedSourceIndex = lookupLoadedSource(interp, scriptSource);
    if (alreadyLoadedSourceIndex >= 0) {
        // Already loaded, returning OK.
        return 1;
    } else {
        {   // DEBUG: lex and exit
            // Do not try to parse after debug lex, since the stream is single-use.
            // DebugLexer(scriptSource);
            // return 0;
        }

        LoadedSource loadedSource;
        
        loadedSource.source = scriptSource;
        loadedSource.scriptAstNode = ParseScript(scriptSource);
        if (!loadedSource.scriptAstNode) {
            return 0;
        }

        if (DEBUG && DEBUG__PRINT_LOADED_MODULES) {
            // DEBUG: module dump
            printf("Loaded module '%s':\n", scriptSource->path);
            CodePrinter printer = CreateCodePrinter(stdout, 0);
            PrintNode(&printer, loadedSource.scriptAstNode);
            printf("\nEnd of Module dump.\n");
        }

        if (!PrimeScript(interp->primer, loadedSource.scriptAstNode)) {
            return 0;
        }
        if (GetErrorPosted()) {
            return 0;
        }

        // All ok! Pushing and returning OK.
        sb_push(interp->loadedSourceSb, loadedSource);
        return 1;
    }
}

int InterpTypecheckModules(Interp* interp) {
    // todo: rather than just type each module sequentially, do so on-demand.
    int loadedSourceCount = sb_count(interp->loadedSourceSb);
    for (int i = 0; i < loadedSourceCount; i++) {
        LoadedSource loadedSource = interp->loadedSourceSb[i];
        TypeNode(interp->typer, loadedSource.scriptAstNode);
    }

    // typechecking the whole system:
    int result = SolveAndCheckManager(interp->typer);

    // post typer dump:
    if (DEBUG) {
        PrintManager(interp->typer);
    }

    return result;
}
int InterpCompile(Interp* interp) {
    int result = 1;
    int loadedSourceCount = sb_count(interp->loadedSourceSb);
    for (int i = 0; i < loadedSourceCount; i++) {
        LoadedSource loadedSource = interp->loadedSourceSb[i];
        result = EmitLlvmModule(interp->typer, loadedSource.scriptAstNode) && result;
    }
    return result;
}
int InterpExecute(Interp* interp, Source* entryScriptSource, SymbolID entryFieldName) {
    int index = lookupLoadedSource(interp,entryScriptSource);
    LoadedSource loaded = loadedSource(interp,index);
    AstNode* scriptAstNode = loaded.scriptAstNode;
    AstNode* entryPointField = NULL;
    int fieldCount = AstModuleStmt_GetLength(scriptAstNode);
    for (int fieldIndex = 0; fieldIndex < fieldCount; fieldIndex++) {
        AstNode* field = AstModuleStmt_GetStmtAt(scriptAstNode,fieldIndex);
        if (GetAstFieldName(field) == entryFieldName) {
            entryPointField = field;
            break;
        }
    }
    if (entryPointField) {
        // todo: typecheck the entryPointField here.
        void* llvmValueRef = GetAstNodeLlvmRepr(entryPointField);
        if (!llvmValueRef) {
            if (DEBUG) {
                printf("!!- InterpExecute cannot run a NULL llvm repr (have you run InterpCompile first?)\n");
            } else {
                assert(0 && "InterpExecute cannot run a NULL llvm repr (have you run InterpCompile first?)");
            }
        }
        // todo: evaluate this function in InterpExecute
    } else {
        PostFeedback(FBK_ERROR,NULL,"ababa");
        return 0;
    }
    // todo: execute code from the interpreter
    // todo: see if 'Compile' was called before 'Execute' to provide JIT functionality unless in debug mode.
    return 0;
}
int InterpExecuteWithArgList(Interp* interp, Source* entryModule, SymbolID entryFieldName, int argc, char const* argv[]) {
    if (DEBUG) {
        printf("!!- NotImplemented: InterpExecuteWithArgList\n");
    } else {
        assert(0 && "NotImplemented: InterpExecuteWithArgList");
    }
    return 0;
}

Source* GetLoadedModuleSourceAt(Interp* interp, int index) {
    return interp->loadedSourceSb[index].source;
}
AstNode* GetLoadedModuleAstNodeAt(Interp* interp, int index) {
    return interp->loadedSourceSb[index].scriptAstNode;
}
