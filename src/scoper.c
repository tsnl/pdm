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
typedef enum LookupContext LookupContext;

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
static ScopeStackFrame allocatedScopeStackFrames[MAX_NODE_COUNT];
static Scoper* newScoper(Scope* root);
static void pushScopeStackFrameToScoper(Scoper* scoper, Scope* scope, PushPurpose pushPurpose);
static ScopeStackFrame* popScopeStackFrameToScoper(Scoper* scoper);

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
    scoper->scopeStackTopP = NULL;
    scoper->currentModuleDefBegP = NULL;
    scoper->currentModuleDefEndP = NULL;
    return scoper;
}
void pushScopeStackFrameToScoper(Scoper* scoper, Scope* scope, PushPurpose pushPurpose) {
    // creating a new frame:
    ScopeStackFrame* newFrame = &allocatedScopeStackFrames[allocatedScopeStackFramesCount++];
    newFrame->linkP = scoper->scopeStackTopP;
    newFrame->purpose = pushPurpose;
    newFrame->scope = scope;

    // pushing the frame to the scoper:
    scoper->scopeStackTopP = newFrame;
}
ScopeStackFrame* popScopeStackFrameToScoper(Scoper* scoper) {
    ScopeStackFrame* poppedFrame = scoper->scopeStackTopP;
    if (scoper->scopeStackTopP) {
        scoper->scopeStackTopP = poppedFrame->linkP;
        return poppedFrame;
    } else {
        // Scoper popped from an empty stack
        return NULL;
    }
}
Scope* topScopeOfScoper(Scoper* scoper) {
    return scoper->scopeStackTopP->scope;
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

static int scopeAstNode(Scoper* scoper, AstNode* node);

int scopeAstNode(Scoper* scoper, AstNode* node) {
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
        case AST_TUPLE:
        {
            size_t tupleLength = GetAstTupleLength(node);
            for (size_t index = 0; index < tupleLength; index++) {
                AstNode* tupleItem = GetAstTupleItemAt(node, index);
                if (!scopeAstNode(scoper, tupleItem)) {
                    return 0;
                }
            }
            return 1;
        }
        case AST_STRUCT:
        {
            size_t structLength = GetAstTupleLength(node);
            for (size_t index = 0; index < structLength; index++) {
                AstNode* structField = GetAstStructFieldAt(node, index);
                AstNode* fieldRhs = GetAstFieldRhs(structField);
                if (!scopeAstNode(scoper, fieldRhs)) {
                    return 0;
                }
            }
            return 1;
        }
        case AST_CHAIN:
        {
            size_t chainLength = GetAstTupleLength(node);
            for (size_t index = 0; index < chainLength; index++) {
                AstNode* chainStmt = GetAstChainStmtAt(node, index);
                if (!scopeAstNode(scoper, chainStmt)) {
                    return 0;
                }
            }
            return 1;
        }
        case AST_ITE:
        {
            AstNode* cond = GetAstIteCond(node);
            AstNode* ifTrue = GetAstIteIfTrue(node);
            AstNode* ifFalse = GetAstIteIfFalse(node);
            if (cond) {
                if (!scopeAstNode(scoper, cond)) {
                    return 0;
                }
            }
            if (ifTrue) {
                if (!scopeAstNode(scoper, ifTrue)) {
                    return 0;
                }
            }
            if (ifFalse) {
                if (!scopeAstNode(scoper, ifFalse)) {
                    return 0;
                }
            }
            return 1;
        }
        case AST_LAMBDA:
        {
            // TODO
            return 0;
        }
        case AST_DOT_INDEX:
        {
            // TODO
            return 0;
        }
        case AST_DOT_NAME:
        {
            // TODO
            return 0;
        }
        case AST_STMT_BIND:
        {
            // TODO
            return 0;
        }
        case AST_STMT_CHECK:
        {
            return (
                scopeAstNode(scoper, GetAstCheckStmtChecked(node)) &&
                scopeAstNode(scoper, GetAstCheckStmtMessage(node))
            );
        }
        case AST_STMT_RETURN:
        {
            return scopeAstNode(scoper, GetAstReturnStmtValue(node));
        }
        case AST_TEMPLATE_CALL:
        {
            
        }
        case AST_VALUE_CALL:
        {
            // TODO
            return 0;
        }
        case AST_SQBRK_CALL:
        {

        }
        case AST_PATTERN:
        {

        }
        case AST_FIELD:
        {

        }
    }
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
        
    }
    return 0;
}

// After definition, IDs are looked up, map to type IDs.
// These type IDs can be stored in the AST.
