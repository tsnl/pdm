#include "scoper.h"
#include "symbols.h"
#include "config.h"

// The scoper performs `Lexical Analysis`, which involves traversing the AST, building a tree of
// contexts from linked list node stored in stack frames, and using this tree to look up symbols'
// types.
// At the end of Lexical Analysis, we have a typeP for each typed expression, ready for 
// typing/unification after analysis.
// Crucially, each context contains at most *one* definition.

typedef struct Scope Scope;
typedef struct Scoper Scoper;
typedef enum PushPurpose PushPurpose;
typedef struct ScopeStackFrame ScopeStackFrame;

struct Scoper {
    Scope* root;

    // stackBegP and stackEndP track scopes for chains and functions that can be pushed or popped.
    ScopeStackFrame* scopeStackTopP;

    // each module context tree starts forward declarations of [all] its symbols.
    // the below 'beg' and 'end' pointers let us iterate through them.
    // - import statements can use these pointers to map to another module.
    // - `beg` points to the first INCLUSIVE element
    // - `end` points to the last INCLUSIVE element
    Scope* currentModuleDefBegP;
    Scope* currentModuleDefEndP;
};

enum PushPurpose {
    PP_INTERNAL,
    PP_CLOSURE
};

struct ScopeStackFrame {
    ScopeStackFrame* linkP;
    Scope* scope;
    PushPurpose purpose;
};

struct Scope {
    Scope* parent;
    SymbolID defnID;
    void* typeP;
};


size_t allocatedScopersCount = 0;
Scoper allocatedScopers[MAX_SCOPER_COUNT];
static size_t allocatedScopeStackFrames = 0;
static ScopeStackFrame allocatedScopeStackFrames[MAX_NODE_COUNT];
static Scoper* newScoper(Scope* root);
static void pushScopeStackFrameToScoper(Scoper* scoper, Scope* scope, PushPurpose pushPurpose);
static ScopeStackFrame* popScopeStackFrameToScoper(Scoper* scoper);

static size_t allocatedScopeCount = 0;
static Scope allocatedScopes[MAX_NODE_COUNT];
inline static Scope* newScope(Scope* parent, SymbolID defnID, void* typeP);
static Scope* defineSymbol(Scope* parent, SymbolID defnID, void* typeP);
static void* lookupSymbol(Scope* scope, SymbolID lookupID);
static void* lookupSymbolUntil(Scope* scope, SymbolID lookupID, Scope* endScopeP);

//
// Static implementation:
//

Scoper* newScoper(Scope* root) {
    Scoper* scoper = NULL;
    if (allocatedScopersCount < MAX_SCOPER_COUNT) {
        scoper = &allocatedScopers[allocatedScopersCount++];
    } else {
        return NULL;
    }
    scoper->scopeStackTopP = NULL;
    scoper->currentModuleDefBegP = NULL;
    scoper->currentModuleDefEndP = NULL;
    return scoper;
}

void pushScopeStackFrameToScoper(Scoper* scoper, Scope* scope, PushPurpose pushPurpose) {
    // todo: continue from here.
}

ScopeStackFrame* popScopeStackFrameToScoper(Scoper* scoper) {

}

inline Scope* newScope(Scope* parent, SymbolID defnID, void* typeP) {
    return &allocatedScopes[allocatedScopeCount++];
}

Scope* defineSymbol(Scope* parent, SymbolID defnID, void* typeP) {
    return (Scope*)newScope(defnID, typeP, parent);
}
void* lookupSymbolUntil(Scope* scope, SymbolID lookupID, Scope* endScopeP) {
    if (scope->defnID == lookupID) {
        return scope->typeP;
    }
    if (scope == endScopeP) {
        // this is the last scope
        // we haven't found the symbol
        // return NULL => not found.
        return NULL;
    } else {
        // try repeating on parent
        if (DEBUG && scope->parent) {
            return NULL;
        }
        return lookupSymbolUntil(scope->parent, lookupID, endScopeP);
    }
}
void pushScope(Scoper* scoper, Scope* scope, PushPurpose purpose) {
    if (scoper->scopeStackTopP) {
        scoper->scopeStackTopP
    }
}
Scope* popScope(void) {

}

//
// Implementation:
//

Scoper* CreateScoper(void) {
    return NULL;
}

int ScopeModule(Scoper* scoperP, AstNode* module) {
    // building scoperP->currentModuleDef{Beg -> End}P
    size_t moduleStmtLength = GetAstModuleLength(module);
    for (size_t index = 0; index < moduleStmtLength; index++) {
        AstNode* stmt = GetAstModuleStmtAt(module, index);
        GetAstNodeKind(stmt);
    }
    return 0;
}

int RunScoper(Scoper* scoper, AstNode* node) {
    AstKind kind = GetAstNodeKind(node);
    switch (kind) {
        case AST_LITERAL_INT:
        case AST_LITERAL_FLOAT:
        case AST_LITERAL_STRING:
        {
            return 1;
        }
        case AST_ID:
        {
            SetAstIDScopeP(node, GetTopScopeP(scoper));
            return 1;
        }
    }
}

// After definition, IDs are looked up, map to type IDs.
// These type IDs can be stored in the AST.
