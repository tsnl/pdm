#include "scoper.h"

struct Scoper {

};

//
// Implementation:
//

Scoper* CreateScoper(void) {
    return NULL;
}

int ScopeModule(Scoper* scoper, AstNode* node) {
    return 0;
}

// The `ScopeModule` function recurses through `node` content, 
//   creating an in-stack linked-list of contexts.
// The sole exception: 
//   all module-level symbols are in sequence before any RHS.
//   all chains are in sequence (shadowing)
//   so module <> chain

// After definition, IDs are looked up, map to type IDs.
// These type IDs can be stored in the AST.