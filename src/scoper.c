#include "scoper.h"

#include <assert.h>

#include "symbols.h"
#include "config.h"
#include "typer.h"

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

// Breadcrumbs are used to determine AST_FIELD usage.
enum Breadcrumb {
    CRUMB_MODULE_FIELDS,
    CRUMB_MODULE_FIELD_PATTERN,
    CRUMB_PATTERN,
    CRUMB_STRUCT
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
    LOOKUP_NONE = 0,
    LOOKUP_TYPING,
    LOOKUP_VALUE
};

size_t allocatedScopersCount = 0;
Scoper allocatedScopers[MAX_SCOPER_COUNT];
static size_t allocatedScopeStackFramesCount = 0;
static BreadcrumbFrame allocatedScopeStackFrames[MAX_AST_NODE_COUNT];
static Scoper* createScoper();
static void pushBreadcrumb(Scoper* scoper, Breadcrumb breadcrumb);
static void popBreadcrumb(Scoper* scoper);

static size_t allocatedScopeCount = 0;
static Scope allocatedScopes[MAX_AST_NODE_COUNT];
inline static Scope* newScope(Scope* parent, SymbolID defnID, void* valueTypeP, void* typingTypeP);
static Scope* defineSymbol(Scope* parent, SymbolID defnID, void* valueTypeP, void* typingTypeP);
static void* lookupSymbol(Scope* scope, SymbolID lookupID, LookupContext context);
static void* lookupSymbolUntil(Scope* scope, SymbolID lookupID, Scope* endScopeP, LookupContext context);

//
// Static implementation:
//

Scoper* createScoper() {
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
    newFrame->preScopeP = scoper->currentScopeP;

    // pushing the frame to the scoper:
    scoper->breadcrumbStackTopP = newFrame;
}
void popBreadcrumb(Scoper* scoper) {
    BreadcrumbFrame* poppedFrame = scoper->breadcrumbStackTopP;
    if (poppedFrame) {
        scoper->breadcrumbStackTopP = poppedFrame->linkP;
    } else {
        if (DEBUG) {
            assert(0 && "Scoper popped from an empty stack");
        }
    }
}
Breadcrumb topBreadcrumb(Scoper* scoper) {
    return scoper->breadcrumbStackTopP->breadcrumb;
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
    return (Scope*)newScope(parent, defnID, valueTypeP, typingTypeP);
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
        if (scope->parent) {
            return lookupSymbolUntil(scope->parent, lookupID, endScopeP, context);
        } else {
            return NULL;
        }
    }
}

//
// Implementation:
//

static int scoper_pre(void* scoper, AstNode* node);
static int scoper_post(void* scoper, AstNode* node);

int scoper_pre(void* rawScoper, AstNode* node) {
    Scoper* scoper = rawScoper;
    AstKind kind = GetAstNodeKind(node);
    switch (kind) {
        case AST_ID:
        {
            SetAstIdScopeP(node, scoper->currentScopeP);
            if (topBreadcrumb(scoper) == CRUMB_PATTERN) {
                SetAstIdLookupContext(node, LOOKUP_TYPING);
            } else {
                SetAstIdLookupContext(node, LOOKUP_VALUE);
            }
            break;
        }
        case AST_STMT_BIND:
        {
            SymbolID defnID = GetAstBindStmtLhs(node);
            void* valueTypeP = CreateMetatype("let %s", GetSymbolText(defnID));
            void* typingTypeP = CreateMetatype("let %s", GetSymbolText(defnID));
            scoper->currentScopeP = defineSymbol(scoper->currentScopeP, defnID, valueTypeP, typingTypeP);
            SetAstBindStmtValueTypeP(node, valueTypeP);
            SetAstBindStmtTypingTypeP(node, typingTypeP);
            break;
        }
        case AST_STRUCT:
        {
            pushBreadcrumb(scoper, CRUMB_STRUCT);
            break;
        }
        case AST_PATTERN:
        {
            pushBreadcrumb(scoper, CRUMB_PATTERN);
            break;
        }
        case AST_FIELD:
        {
            switch (topBreadcrumb(scoper)) {
                case CRUMB_MODULE_FIELDS:
                {
                    // symbol already defined ahead of time.

                    if (GetAstFieldPattern(node)) {
                        pushBreadcrumb(scoper, CRUMB_MODULE_FIELD_PATTERN);
                    }
                    break;
                }
                case CRUMB_MODULE_FIELD_PATTERN:
                {
                    SymbolID defnID = GetAstFieldName(node);
                    void* valueTypeP = CreateMetatype("template %s", GetSymbolText(defnID));
                    void* typingTypeP = CreateMetatype("template %s", GetSymbolText(defnID));
                    scoper->currentScopeP = defineSymbol(scoper->currentScopeP, defnID, valueTypeP, typingTypeP);
                    break;
                }
                case CRUMB_PATTERN:
                {
                    SymbolID defnID = GetAstFieldName(node);
                    void* valueTypeP = CreateMetatype("pattern %s", GetSymbolText(defnID));
                    void* typingTypeP = CreateMetatype("pattern %s", GetSymbolText(defnID));
                    scoper->currentScopeP = defineSymbol(scoper->currentScopeP, defnID, valueTypeP, typingTypeP);
                    break;
                }
                case CRUMB_STRUCT:
                {
                    // TODO: define a symbol chain similar to modules.
                    break;
                }
                default:
                {
                    // TODO: raise an error, 
                    assert(0 && "field in invalid context");
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

int scoper_post(void* rawScoper, AstNode* node) {
    Scoper* scoper = rawScoper;
    AstKind kind = GetAstNodeKind(node);
    switch (kind) {
        case AST_STRUCT:
        case AST_PATTERN:
        {
            popBreadcrumb(scoper);
            break;
        }
        case AST_FIELD:
        {
            if (GetAstFieldPattern(node)) {
                popBreadcrumb(scoper);
            }
        }
        default:
        {
            break;
        }
    }
    return 1;
}

Scoper* CreateScoper(void) {
    return createScoper();
}

int ScopeModule(Scoper* scoperP, AstNode* module) {
    if (DEBUG) {
        assert(GetAstNodeKind(module) == AST_MODULE);
    }

    // defining all module-symbols in one binding group
    // building scoperP->currentModuleDef{Beg -> End}P before visiting
    size_t moduleStmtLength = GetAstModuleLength(module);
    for (size_t index = 0; index < moduleStmtLength; index++) {
        AstNode* field = GetAstModuleFieldAt(module, index);
        void* valueTypeP = CreateMetatype("define %s", GetSymbolText(GetAstFieldName(field)));
        void* typingTypeP = CreateMetatype("define %s", GetSymbolText(GetAstFieldName(field)));
        scoperP->currentScopeP = defineSymbol(scoperP->currentScopeP, GetAstFieldName(field), valueTypeP, typingTypeP);
        scoperP->currentModuleDefEndP = scoperP->currentScopeP;
        if (scoperP->currentModuleDefBegP == NULL) {
            scoperP->currentModuleDefBegP = scoperP->currentScopeP;
        }
    }

    // visiting the AST:
    pushBreadcrumb(scoperP, CRUMB_MODULE_FIELDS);
    if (!visit(scoperP, module, scoper_pre, scoper_post)) {
        return 0;
    }
    popBreadcrumb(scoperP);
    return 1;
}

static int resolver_pre(void* source, AstNode* node);

static int resolver_pre(void* source, AstNode* node) {
    if (GetAstNodeKind(node) == AST_ID) {
        Loc loc = GetAstNodeLoc(node);
        SymbolID name = GetAstIdName(node);
        Scope* scope = GetAstIdScopeP(node);
        LookupContext lookupContext = GetAstIdLookupContext(node);
        void* typeP = lookupSymbol(scope, name, lookupContext);
        if (!typeP) {
            FeedbackNote* note = CreateFeedbackNote("here...", source, loc, NULL);
            PostFeedback(
                FBK_ERROR, note,
                "Symbol '%s' not defined in this context",
                GetSymbolText(name)
            );
        }
        SetAstNodeTypeP(node, typeP);
    }
    return 1;
}

int ResolveScopedModule(Source* source, AstNode* module) {
    visit(source, module, resolver_pre, NULL);
    if (GetErrorPosted()) {
        return 0;
    }

    return 1;
}

// After definition, IDs are looked up, map to type IDs.
// These type IDs can be stored in the AST.
