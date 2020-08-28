#include "scoper.h"
#include "symbols.h"
#include "config.h"

// The scoper performs `Lexical Analysis`, which involves traversing the AST, building a tree of
// contexts from linked list node stored in stack frames, and using this tree to look up symbols'
// types.
// At the end of Lexical Analysis, we have a typeP for each typed expression, ready for 
// typing/unification after analysis.
// Crucially, each context contains at most *one* definition.

typedef struct Scoper Scoper;
typedef struct Scope Scope;

struct Scoper {
    Scope* root;

    // each module context tree starts forward declarations of [all] its symbols.
    // the below 'beg' and 'end' pointers let us iterate through them.
    // - import statements can use these pointers to map to another module.
    // - `beg` points to the first INCLUSIVE element
    // - `end` points to the last INCLUSIVE element
    Scope* currentModuleDefBegP;
    Scope* currentModuleDefEndP;
};

struct Scope {
    Scope* parent;
    SymbolID defnID;
    void* typeP;
};

static size_t allocatedScopeCount = 0;
static Scope allocatedScopes[MAX_NODE_COUNT];

// allocates a new Scope from the `scoper` memory manager.
inline static Scope* allocateScope(Scope* parent, SymbolID defnID, void* typeP);

// creates a new Scope defining the specified symbol.
static Scope* defineSymbol(Scope* parent, SymbolID defnID, void* typeP);

// looks up a symbol's typeP starting at the specified scope.
static void* lookupSymbol(Scope* scope, SymbolID lookupID);

// looks up a symbol's typeP starting at the specified scope, and ending at the specified scope.
static void* lookupSymbolUntil(Scope* scope, SymbolID lookupID, Scope* endScopeP);

inline Scope* allocateScope(Scope* parent, SymbolID defnID, void* typeP) {
    return &allocatedScopes[allocatedScopeCount++];
}

Scope* defineSymbol(Scope* parent, SymbolID defnID, void* typeP) {
    return (Scope*)allocateScope(defnID, typeP, parent);
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

//
// Implementation:
//

Scoper* CreateScoper(void) {
    return NULL;
}

int ScopeModule(Scoper* scoper, AstNode* module) {
    //
    // Step 1: 
    //
    
    size_t moduleStmtLength = GetAstModuleLength(module);
    for (size_t index = 0; index < moduleStmtLength; index++) {
        AstNode* stmt = GetAstModuleStmtAt(module, index);
    }
    return 0;
}

// After definition, IDs are looked up, map to type IDs.
// These type IDs can be stored in the AST.
