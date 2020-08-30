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
typedef enum Breadcrumb Breadcrumb;
typedef struct BreadcrumbFrame BreadcrumbFrame;
typedef enum LookupContext LookupContext;

struct Scoper {
    Scope* root;

    // stackBegP and stackEndP track scopes for chains and functions that can be pushed or popped.
    Scope* currentScopeP;
    BreadcrumbFrame* breadcrumbStackTopP;

    // each module context tree starts forward declarations of [all] its symbols.
    // the below 'beg' and 'end' pointers let us iterate through them.
    // - import statements can use these pointers to map to another module.
    // - `beg` points to the first INCLUSIVE element
    // - `end` points to the last INCLUSIVE element
    Scope* currentModuleDefBegP;
    Scope* currentModuleDefEndP;
};

enum Breadcrumb {
    PP_INTERNAL,
    PP_TYPE_CLOSURE,
    PP_VALUE_CLOSURE,
    PP_CHAIN,
    PP_STRUCT,
    PP_PATTERN,
};

struct BreadcrumbFrame {
    BreadcrumbFrame* linkP;
    Scope* preScopeP;
    Breadcrumb breadcrumb;
};

struct Scope {
    Scope* parent;
    SymbolID defnID;
    void* valueTypeP;
    void* typingTypeP;
};

enum LookupContext {
    LOOKUP_TYPING,
    LOOKUP_VALUE
};

size_t allocatedScopersCount = 0;
Scoper allocatedScopers[MAX_SCOPER_COUNT];
static size_t allocatedScopeStackFramesCount = 0;
static BreadcrumbFrame allocatedScopeStackFrames[MAX_NODE_COUNT];
static Scoper* newScoper(Scope* root);
static void pushBreadcrumb(Scoper* scoper, Breadcrumb breadcrumb);
static void popBreadcrumb(Scoper* scoper);

static size_t allocatedScopeCount = 0;
static Scope allocatedScopes[MAX_NODE_COUNT];
inline static Scope* newScope(Scope* parent, SymbolID defnID, void* valueTypeP, void* typingTypeP);
static Scope* defineSymbol(Scope* parent, SymbolID defnID, void* valueTypeP, void* typingTypeP);
static void* lookupSymbol(Scope* scope, SymbolID lookupID, LookupContext context);
static void* lookupSymbolUntil(Scope* scope, SymbolID lookupID, Scope* endScopeP, LookupContext context);

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
    scoper->currentScopeP = NULL;
    scoper->currentModuleDefBegP = NULL;
    scoper->currentModuleDefEndP = NULL;
    return scoper;
}
void pushBreadcrumb(Scoper* scoper, Breadcrumb breadcrumb) {
    // allocating a new frame:
    BreadcrumbFrame* newFrame = &allocatedScopeStackFrames[allocatedScopeStackFramesCount++];
    
    // populating:
    newFrame->linkP = scoper->breadcrumbStackTopP;
    newFrame->breadcrumb = breadcrumb;
    newFrame->preScopeP = topScopeOfScoper(scoper);

    // pushing the frame to the scoper:
    scoper->breadcrumbStackTopP = newFrame;
}
void popBreadcrumb(Scoper* scoper) {
    BreadcrumbFrame* poppedFrame = scoper->breadcrumbStackTopP;
    if (poppedFrame) {
        scoper->breadcrumbStackTopP = poppedFrame->linkP;
        return poppedFrame;
    } else {
        // Scoper popped from an empty stack
        return NULL;
    }
}
Breadcrumb topBreadcrumb(Scoper* scoper) {
    return scoper->breadcrumbStackTopP->breadcrumb;
}

Scope* topScopeOfScoper(Scoper* scoper) {
    return scoper->currentScopeP;
}

inline Scope* newScope(Scope* parent, SymbolID defnID, void* valueTypeP, void* typingTypeP) {
    Scope* scopeP = &allocatedScopes[allocatedScopeCount++];
    scopeP->parent = parent;
    scopeP->defnID = defnID;
    scopeP->valueTypeP = valueTypeP;
    scopeP->typingTypeP = typingTypeP;
    return scopeP;
}
Scope* defineSymbol(Scope* parent, SymbolID defnID, void* valueTypeP, void* typingTypeP) {
    return (Scope*)newScope(defnID, valueTypeP, typingTypeP, parent);
}
void* lookupSymbol(Scope* scope, SymbolID lookupID, LookupContext context) {
    return lookupSymbolUntil(scope, lookupID, NULL, context);
}
void* lookupSymbolUntil(Scope* scope, SymbolID lookupID, Scope* endScopeP, LookupContext context) {
    if (scope->defnID == lookupID) {
        return scope->valueTypeP;
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
        return lookupSymbolUntil(scope->parent, lookupID, endScopeP, context);
    }
}

static int preScopeAstNode(Scoper* scoper, AstNode* node);
static int postScopeAstNode(Scoper* scoper, AstNode* node);

int preScopeAstNode(Scoper* scoper, AstNode* node) {
    AstKind kind = GetAstNodeKind(node);
    switch (kind) {
        case AST_ID:
        {
            SetAstIDScopeP(node, GetTopScopeP(scoper));
            break;
        }
        case AST_STRUCT:
        {
            pushBreadcrumb(scoper, PP_STRUCT);
            break;
        }
        case AST_CHAIN:
        {
            pushBreadcrumb(scoper, PP_CHAIN);
            break;
        }
        case AST_LAMBDA:
        {
            pushBreadcrumb(scoper, PP_VALUE_CLOSURE);
            break;
        }
        case AST_STMT_BIND:
        {
            pushBreadcrumb(scoper, PP_TYPE_CLOSURE);
            break;
        }
        case AST_PATTERN:
        {
            pushBreadcrumb(scoper, PP_PATTERN);
            break;
        }
        case AST_FIELD:
        {
            switch (topBreadcrumb(scoper)) {
                case PP_PATTERN:
                case PP_STRUCT:
                case PP_VALUE_CLOSURE:
                case PP_TYPE_CLOSURE:
                {
                    // TODO: define
                    break;
                }
            }
            break;
        }
        default:
        {
            break;
        }
    }
    return 1;
}

int postScopeAstNode(Scoper* scoper, AstNode* node) {
    AstKind kind = GetAstNodeKind(node);
    switch (kind) {
        case AST_STRUCT:
        case AST_CHAIN:
        case AST_LAMBDA:
        case AST_PATTERN:
        case AST_STMT_BIND:
        {
            popBreadcrumb(scoper);
            break;
        }
        default:
        {
            break;
        }
    }
    return 1;
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
        // TODO: define the symbol from a bind statement here.
    }
    // visiting the AST:
    if (!visit(scoperP, module, preScopeAstNode, postScopeAstNode)) {
        return 0;
    }
    return 1;
}

// TODO: lookup symbols.

// After definition, IDs are looked up, map to type IDs.
// These type IDs can be stored in the AST.
