#include "ast.h"

#include <assert.h>

#include "useful.h"
#include "config.h"
#include "source.h"
#include "symbols.h"
#include "primer.h"

#include "stb/stretchy_buffer.h"

typedef struct AstModule            AstModule;
typedef struct AstID                AstID;
typedef union  AstInfo              AstInfo;
typedef struct AstNodeList          AstNodeList;
typedef struct AstCall              AstCall;
typedef struct AstCast              AstCast;
typedef struct AstField             AstField;
typedef enum   AstBinaryOperator    AstBinaryOperator;
typedef struct AstDotIndex          AstDotIndex;
typedef struct AstDotName           AstDotName;
typedef struct AstVLambda           AstVLambda;
typedef struct AstTLambda           AstTLambda;
typedef struct AstLet               AstLet;
typedef struct AstDef               AstDef;
typedef struct AstVal               AstVal;
typedef struct AstExtern            AstExtern;
typedef struct AstTypedef           AstTypedef;
typedef struct AstCheck             AstCheck;
typedef struct AstUnary             AstUnary;
typedef struct AstBinary            AstBinary;
typedef struct AstInt               AstInt;
typedef struct AstChain             AstChain;
typedef struct AstStruct            AstStruct;
typedef struct AstVCast             AstVCast;
typedef struct AstModuleStmt        AstModuleStmt;
typedef struct AstImportStmt        AstImportStmt;
typedef struct AstSetStmt           AstSetStmt;
typedef struct AstArray             AstArray;

struct AstNodeList {
    size_t count;
    AstNodeList* next;
    AstNode* items[MAX_AST_NODES_PER_LIST];
};

struct AstModule {
    SymbolID name;
    AstNodeList* items;
    AstNode* importHeader;
    AstNode* exportHeader;
};
struct AstID {
    SymbolID name;
    void* lookupScope;
    void* defnScope;
};
struct AstField {
    SymbolID name;
    AstNode* rhs;
    AstNode* parent;
    int index;
};
struct AstDotIndex {
    AstNode* lhs;
    size_t index;
};
struct AstDotName {
    AstNode* lhs;
    SymbolID symbol;
};
struct AstVLambda {
    AstNode* pattern;
    AstNode* body;
    Defn** capturesSB;
    Defn** localsSB;
};
struct AstTLambda {
    AstNode* pattern;
    AstNode* body;
    AstNodeList* callers;
    AstNodeList* copies;
};
struct AstLet {
    AstNode* lhs;
    AstNode* rhs;
};
struct AstDef {
    SymbolID lhs;
    AstNode* optTemplatePattern;
    AstNode* rhs;
};
struct AstVal {
    SymbolID lhs;
    AstNode* optTemplatePattern;
    AstNode* bodyPattern;
};
struct AstExtern {
    SymbolID name;
    AstNode* pattern;
    AstNode* typespec;
};
struct AstTypedef {
    SymbolID name;
    AstNode* optPattern;
    AstNode* rhs;
    // void* valueDefnType;
};
struct AstCheck {
    AstNode* checked;
};
struct AstCall {
    AstNode* lhs;
    AstNodeList* args;
    int isTemplateCall;
};
struct AstCast {
    AstNode* castTypespec;
    AstNode* rhs;
};
struct AstUnary {
    AstUnaryOperator operator;
    AstNode* operand;
};
struct AstBinary {
    AstBinaryOperator operator;
    AstNode* ltOperand;
    AstNode* rtOperand;
};
struct AstInt {
    size_t value;
    int base;
};
struct AstChain {
    AstNodeList* prefix;
    AstNode* result;
};
struct AstVCast {
    AstNode* toTypespecT2V;
    AstNode* fromExpr;
};
struct AstModuleStmt {
    SymbolID boundName;
    Utf8String from;
    Utf8String as;
};
struct AstImportStmt {
    SymbolID modName;
    SymbolID suffix;
    int glob;
};
struct AstSetStmt {
    AstNode* lhs;
    AstNode* rhs;
};
struct AstArray {
    AstNode* typespec;
    AstNode* count;
};

union AstInfo {
    AstModule           Module;
    AstID               ID;
    AstUnary            Unary;
    AstBinary           Binary;
    AstInt              Int;
    long double         Float;
    Utf8String          StringLiteral_utf8string;
    AstCall             Call;
    AstCast             Cast;
    AstNode*            CastTypespec;
    AstField            Field;
    AstDotIndex         DotIx;
    AstDotName          DotNm;
    AstVLambda          VLambda;
    AstTLambda          TLambda;
    AstLet              Let;
    AstDef              Def;
    AstVal              Val;
    AstExtern           Extern;
    AstTypedef          Typedef;
    AstCheck            Check;
    AstChain            Chain;
    AstNode*            Paren_item;
    AstVCast            VCast;
    AstNode*            T2V_typespec;
    AstNode*            V2T_expr;
    AstNode*            Ptr_pointee;
    AstModuleStmt       ModuleStmt;
    AstImportStmt       ImportStmt;
    AstSetStmt          SetStmt;
    AstNode*            DiscardStmt_discarded;
    AstNode*            SingletonPattern_field;
    AstNodeList*        GenericList_items;
    AstArray            Array;
};

struct AstNode {
    Span span;
    AstKind kind;
    AstInfo as;
    
    AstContext lookupContext;
    AstNode* parentFunc;

    void* typingExt_value;
    void* typingExt_type;
    
    void* constVal;

    void* llvmRepr;
};

//
// Constructor helpers:
//

static size_t allocatedNodeCount = 0;
static AstNode allocatedNodes[MAX_AST_LIST_COUNT];

static size_t allocatedListCount = 0;
static AstNodeList allocatedLists[MAX_AST_LIST_COUNT];

static AstNode* newNode(Span span, AstKind kind);
static AstNodeList* newNodeList(void);
static void pushListElement(AstNodeList* list, AstNode* node);
static int countList(AstNodeList* list);
static AstNode* listItemAt(AstNodeList* list, int index);

AstNode* newNode(Span span, AstKind kind) {
    AstNode* node = &allocatedNodes[allocatedNodeCount++];
    node->span = span;
    node->kind = kind;
    node->typingExt_value = NULL;
    node->typingExt_type = NULL;
    node->lookupContext = __ASTCTX_NONE;
    node->llvmRepr = NULL;
    node->parentFunc = NULL;
    node->constVal = NULL;
    return node;
}
AstNodeList* newNodeList(void) {
    AstNodeList* listP = &allocatedLists[allocatedListCount++];
    listP->count = 0;
    listP->next = NULL;
    return listP;
}
void pushListElement(AstNodeList* list, AstNode* node) {
    if (list->count == MAX_AST_NODES_PER_LIST) {
        if (!list->next) {
            list->next = newNodeList();
        }
        return pushListElement(list->next, node);
    } else {
        size_t index = list->count++;
        list->items[index] = node;
    }
}
int countList(AstNodeList* list) {
    int countSoFar = list->count;
    if (list->next) {
        return countSoFar + countList(list->next);
    } else {
        return countSoFar;
    }
}
AstNode* listItemAt(AstNodeList* list, int index) {
    if (DEBUG) {
        if (index < 0) {
            COMPILER_ERROR("listItemAt: invalid list index");
            return NULL;
        }
    }
    if (index >= MAX_AST_NODES_PER_LIST) {
        return listItemAt(list->next, index - MAX_AST_NODES_PER_LIST);
    } else {
        return list->items[index];
    }
}

//
// Constructor implementations:
//

static int isStmtKindModuleLevel(AstKind kind);
static int isIdKind(AstKind kind);
static int isCallKind(AstKind kind);
static AstNode* helpNewAstCall(Span span, AstKind kind, AstNode* lhs, AstNode* args[], int argsCount);

int isStmtKindModuleLevel(AstKind kind) {
    return (
        kind == AST_STMT_VDEF ||
        kind == AST_STMT_TDEF ||
        kind == AST_STMT_EXTERN ||
        0
    );
}
int isIdKind(AstKind kind) {
    return (
        kind == AST_TID ||
        kind == AST_VID ||
        0
    );
}
int isCallKind(AstKind kind) {
    return (
        kind == AST_TCALL ||
        kind == AST_VCALL ||
        0
    );
}
AstNode* helpNewAstCall(Span span, AstKind kind, AstNode* lhs, AstNode* args[], int argsCount) {
    AstNode* callNode = newNode(span,kind);
    callNode->as.Call.lhs = lhs;
    callNode->as.Call.args = newNodeList();
    for (int index = 0; index < argsCount; index++) {
        AstNode* arg = args[index];
        pushListElement(callNode->as.Call.args,arg);
    }
    return callNode;
}

AstNode* NewAstModule(Span span, SymbolID moduleID) {
    AstNode* node = newNode(span, AST_MODULE);
    node->as.Module.name = moduleID;
    node->as.Module.items = newNodeList();
    return node;
}
AstNode* NewAstModuleWithStmtSb(Span span, SymbolID moduleID, AstNode** mov_contentSb) {
    AstNode* node = NewAstModule(span, moduleID);

    int count = sb_count(mov_contentSb);
    for (int index = 0; index < count; index++) {
        AstNode* stmt = mov_contentSb[index];
        PushStmtToAstModule(node,stmt);
    }
    sb_free(mov_contentSb);

    return node;
}

void AttachToAstModule(AstNode* module, SymbolID boundName, char* from, char* as) {
    COMPILER_ERROR("NotImplemented: AttachToAstModule");
}
void PushStmtToAstModule(AstNode* module, AstNode* def) {
    COMPILER_ASSERT(def != NULL,"Cannot push NULL stmt to AstModule.");
    AstKind nodeKind = GetAstNodeKind(def);
    COMPILER_ASSERT(isStmtKindModuleLevel(nodeKind), "Cannot push non-def/extern to AstModule.");
    pushListElement(module->as.Module.items, def);
}

AstNode* NewAstVID(Span span, SymbolID symbolID) {
    AstNode* idNode = newNode(span, AST_VID);
    idNode->as.ID.name = symbolID;
    idNode->as.ID.lookupScope = NULL;
    idNode->as.ID.defnScope = NULL;
    return idNode;
}
AstNode* NewAstIntLiteral(Span span, size_t value, int base) {
    AstNode* intNode = newNode(span, AST_LITERAL_INT);
    intNode->as.Int.value = value;
    intNode->as.Int.base = base;
    return intNode;
}
AstNode* NewAstFloatLiteral(Span span, long double value) {
    AstNode* floatNode = newNode(span, AST_LITERAL_FLOAT);
    floatNode->as.Float = value;
    return floatNode;
}
AstNode* NewAstStringLiteral(Span span, Utf8String utf8string) {
    AstNode* stringNode = newNode(span, AST_LITERAL_STRING);
    stringNode->as.StringLiteral_utf8string = utf8string;
    return stringNode;
}
AstNode* NewAstVParen(Span span, AstNode* it) {
    AstNode* parenNode = newNode(span, AST_VPAREN);
    parenNode->as.Paren_item = it;
    return parenNode;
}
AstNode* NewAstVPtr(Span span, AstNode* pointee) {
    AstNode* ptrNode = newNode(span,AST_VPTR);
    ptrNode->as.Ptr_pointee = pointee;
    return ptrNode;
}
AstNode* NewAstUnit(Span span) {
    return newNode(span, AST_UNIT);
}

AstNode* NewAstField(Span span, SymbolID lhs, AstNode* rhs) {
    // new fields begin as ORPHANED.
    // this kind should be changed when parent and index are set according to the container.
    // see: PushFieldTo____

    AstNode* field = newNode(span, AST_ORPHANED_FIELD);
    field->as.Field.name = lhs;
    field->as.Field.rhs = rhs;
    
    // 'parent' and 'index' must be set by the PushField... functions.
    field->as.Field.parent = NULL;
    field->as.Field.index = -1;
    
    return field;
}
AstNode* NewAstVTuple(Span span) {
    AstNode* tupleNode = newNode(span, AST_VTUPLE);
    tupleNode->as.GenericList_items = newNodeList();
    return tupleNode;
}
AstNode* NewAstVTupleWithFieldsSb(Span span, AstNode** mov_fieldsSb) {
    AstNode* vtuple = NewAstVTuple(span);
    int fieldCount = sb_count(mov_fieldsSb);
    for (int index = 0; index < fieldCount; index++) {
        AstNode* field = mov_fieldsSb[index];
        PushFieldToAstVTuple(vtuple, field);
    }
    sb_free(mov_fieldsSb);
    return vtuple;
}
AstNode* NewAstVStruct(Span span) {
    AstNode* structNode = newNode(span, AST_VSTRUCT);
    structNode->as.GenericList_items = newNodeList();
    return structNode;
}
AstNode* NewAstVStructWithFieldsSb(Span span, AstNode** mov_fieldsSb) {
    AstNode* vstruct = NewAstVStruct(span);
    int fieldCount = sb_count(mov_fieldsSb);
    for (int index = 0; index < fieldCount; index++) {
        AstNode* field = mov_fieldsSb[index];
        PushFieldToAstVStruct(vstruct, field);
    }
    sb_free(mov_fieldsSb);
    return vstruct;
}
AstNode* NewAstTStruct(Span span) {
    AstNode* tstruct = newNode(span, AST_TSTRUCT);
    tstruct->as.GenericList_items = newNodeList();
    return tstruct;
}
AstNode* NewAstTStructWithFieldsSb(Span span, AstNode** mov_fieldsSb) {
    AstNode* tstruct = NewAstTStruct(span);
    int fieldCount = 0;
    for (int index = 0; index < fieldCount; index++) {
        AstNode* field = mov_fieldsSb[index];
        PushFieldToAstTStruct(tstruct, field);
    }
    sb_free(mov_fieldsSb);
    return tstruct;
}

AstNode* NewAstChain(Span span) {
    AstNode* chainNode = newNode(span, AST_CHAIN);
    chainNode->as.Chain.prefix = newNodeList();
    chainNode->as.Chain.result = NULL;
    return chainNode;
}
AstNode* NewAstChainWith(Span span, AstNode** mov_prefixSb, AstNode* result) {
    AstNode* chainNode = NewAstChain(span);
    
    int prefixCount = sb_count(mov_prefixSb);
    for (int index = 0; index < prefixCount; index++) {
        AstNode* prefixStmtNode = mov_prefixSb[index];
        PushStmtToAstChain(chainNode, prefixStmtNode);
    }

    if (result) {
        SetAstChainResult(chainNode, result);
    }
    return chainNode;
}

inline static AstNode* newAstPattern(Span span, AstKind kind) {
    AstNode* patternNode = newNode(span, kind);
    patternNode->as.GenericList_items = newNodeList();
    patternNode->as.GenericList_items->count = 0;
    return patternNode;
}
inline static AstNode* newAstPatternSingleton(Span span, AstKind singletonKind, AstNode* field) {
    AstNode* singletonPatternNode = newNode(span,singletonKind);
    singletonPatternNode->as.SingletonPattern_field = field;
    return singletonPatternNode;
}
AstNode* NewAstVPattern(Span span) { 
    return newAstPattern(span,AST_VPATTERN);
}
AstNode* NewAstVPatternSingleton(Span span, AstNode* field) {
    COMPILER_ASSERT(field->kind == AST_ORPHANED_FIELD, "vpattern cannot adopt non-orphan field.");
    AstNode* singleton = newAstPatternSingleton(span,AST_VPATTERN_SINGLETON,field);
    field->kind = AST_VPATTERN_SINGLETON_FIELD;
    field->as.Field.parent = singleton;
    field->as.Field.index = -1;
    return singleton;
}
AstNode* NewAstTPattern(Span span) { 
    return newAstPattern(span,AST_TPATTERN);
}
AstNode* NewAstTPatternSingleton(Span span, AstNode* field) {
    AstNode* singleton = newAstPatternSingleton(span,AST_TPATTERN_SINGLETON,field);
    field->kind = AST_TPATTERN_SINGLETON_FIELD;
    field->as.Field.parent = singleton;
    field->as.Field.index = -1;
    return singleton;
}
AstNode* NewAstVPatternWithFieldsSb(Span span, AstNode** mov_fieldsSb) {
    AstNode* pattern = NewAstVPattern(span);
    int fieldsCount = sb_count(mov_fieldsSb);
    for (int index = 0; index < fieldsCount; index++) {
        AstNode* field = mov_fieldsSb[index];
        PushFieldToAstVPattern(pattern,field);
    }
    sb_free(mov_fieldsSb);
    return pattern;
}
AstNode* NewAstTPatternWithFieldsSb(Span span, AstNode** mov_fieldsSb) {
    AstNode* pattern = NewAstTPattern(span);
    int fieldsCount = sb_count(mov_fieldsSb);
    for (int index = 0; index < fieldsCount; index++) {
        AstNode* field = mov_fieldsSb[index];
        PushFieldToAstTPattern(pattern,field);
    }
    sb_free(mov_fieldsSb);
    return pattern;
}

void PushFieldToAstTTuple(AstNode* ttuple, AstNode* field) {
    COMPILER_ASSERT(field->kind == AST_ORPHANED_FIELD, "Cannot push non-generic-field to ttuple.");
    pushListElement(ttuple->as.GenericList_items, field);
    field->kind = AST_TTUPLE_FIELD;
    field->as.Field.parent = ttuple;
    field->as.Field.index = countList(ttuple->as.GenericList_items);
}
void PushFieldToAstTStruct(AstNode* tstruct, AstNode* field) {
    COMPILER_ASSERT(field->kind == AST_ORPHANED_FIELD, "Cannot push non-generic-field to tstruct.");
    pushListElement(tstruct->as.GenericList_items, field);
    field->kind = AST_TSTRUCT_FIELD;
    field->as.Field.parent = tstruct;
    field->as.Field.index = countList(tstruct->as.GenericList_items);
}
void PushFieldToAstTPattern(AstNode* pattern, AstNode* field) {
    COMPILER_ASSERT(
        (field->kind == AST_ORPHANED_FIELD),
        "Cannot push non-generic-field with PushFieldToAstPattern."
    );
    COMPILER_ASSERT(
        (pattern->kind == AST_TPATTERN), 
        "Cannot push pattern field to a non-tpattern."
    );
    pushListElement(pattern->as.GenericList_items, field);
    field->kind = AST_TPATTERN_FIELD;
    field->as.Field.parent = pattern;
    field->as.Field.index = countList(pattern->as.GenericList_items);
}

void PushFieldToAstVTuple(AstNode* vtuple, AstNode* field) {
    COMPILER_ASSERT(field->kind == AST_ORPHANED_FIELD, "Cannot push non-generic field to tuple.");
    pushListElement(vtuple->as.GenericList_items, field);
    field->kind = AST_VTUPLE_FIELD;
    field->as.Field.parent = vtuple;
    field->as.Field.index = countList(vtuple->as.GenericList_items);
}
void PushFieldToAstVStruct(AstNode* vstruct, AstNode* field) {
    COMPILER_ASSERT(field->kind == AST_ORPHANED_FIELD, "Cannot push non-generic-field to vstruct.");
    pushListElement(vstruct->as.GenericList_items, field);
    field->kind = AST_VSTRUCT_FIELD;
    field->as.Field.parent = vstruct;
    field->as.Field.index = countList(vstruct->as.GenericList_items);
}
void PushFieldToAstVPattern(AstNode* pattern, AstNode* field) {
    COMPILER_ASSERT(
        (field->kind == AST_ORPHANED_FIELD),
        "Cannot push non-generic-field with PushFieldToAstPattern."
    );
    COMPILER_ASSERT(
        (pattern->kind == AST_VPATTERN), 
        "Cannot push pattern field to a non-vpattern."
    );
    pushListElement(pattern->as.GenericList_items, field);
    field->kind = AST_VPATTERN_FIELD;
    field->as.Field.parent = pattern;
    field->as.Field.index = countList(pattern->as.GenericList_items);
}

void PushFieldToAstVTupleFromRaw(Span span, AstNode* tuple, AstNode* value) {
    AstNode* field = newNode(span, AST_VTUPLE_FIELD);
    field->as.Field.name = SYM_NULL;
    field->as.Field.rhs = value;
    PushFieldToAstVTuple(tuple,field);
}
void PushFieldToAstVStructFromRaw(Span span, AstNode* vstruct, SymbolID name, AstNode* value) {
    AstNode* field = newNode(span, AST_VSTRUCT_FIELD);
    field->as.Field.name = name;
    field->as.Field.rhs = value;
    field->as.Field.parent = vstruct;
    field->as.Field.index = countList(vstruct->as.GenericList_items);
    PushFieldToAstVStruct(vstruct,field);
}
void PushFieldToAstVPatternFromRaw(Span span, AstNode* pattern, AstKind fieldKind, SymbolID name, AstNode* typespec) {
    COMPILER_ASSERT(
        (fieldKind == AST_TPATTERN_FIELD) || (fieldKind == AST_VPATTERN_FIELD), 
        "Cannot push non-field into a pattern"
    );
    COMPILER_ASSERT(
        (pattern->kind == AST_VPATTERN) || (pattern->kind == AST_TPATTERN),
        "Cannot push pattern field to non-pattern with 'PushFieldToAstPattern'"
    );
    AstNode* field = newNode(span, fieldKind);
    field->as.Field.name = name;
    field->as.Field.rhs = typespec;
    field->as.Field.index = countList(pattern->as.GenericList_items);
    field->as.Field.parent = pattern;
    PushFieldToAstVPattern(pattern,field);
}
void PushStmtToAstChain(AstNode* chain, AstNode* statement) {
    pushListElement(chain->as.Chain.prefix, statement);
}
void SetAstChainResult(AstNode* chain, AstNode* result) {
    chain->as.Chain.result = result;
}

AstNode* NewAstIte(Span span, AstNode* cond, AstNode* ifTrue, AstNode* ifFalse) {
    AstNode* iteNode = newNode(span, AST_ITE);
    iteNode->as.GenericList_items = newNodeList();
    pushListElement(iteNode->as.GenericList_items, cond);
    pushListElement(iteNode->as.GenericList_items, ifTrue);
    pushListElement(iteNode->as.GenericList_items, ifFalse);
    return iteNode;
}

AstNode* NewAstDotIndex(Span span, AstNode* lhs, size_t index) {
    AstNode* dotNode = newNode(span, AST_DOT_INDEX);
    dotNode->as.DotIx.lhs = lhs;
    dotNode->as.DotIx.index = index;
    return dotNode;
}

AstNode* NewAstDotName(Span span, AstNode* lhs, SymbolID rhs) {
    AstNode* dotNode = newNode(span, AST_DOT_NAME);
    dotNode->as.DotNm.lhs = lhs;
    dotNode->as.DotNm.symbol = rhs;
    return dotNode;
}

AstNode* NewAstVLambda(Span span, AstNode* pattern, AstNode* body) {
    AstNode* lambdaNode = newNode(span, AST_VLAMBDA);
    lambdaNode->as.VLambda.pattern = pattern;
    lambdaNode->as.VLambda.body = body;
    lambdaNode->as.VLambda.capturesSB = NULL;
    lambdaNode->as.VLambda.localsSB = NULL;
    return lambdaNode;
}
AstNode* NewAstTLambda(Span span, AstNode* pattern, AstNode* body) {
    AstNode* lambdaNode = newNode(span, AST_TLAMBDA);
    lambdaNode->as.TLambda.pattern = pattern;
    lambdaNode->as.TLambda.body = body;
    lambdaNode->as.TLambda.callers = newNodeList();
    lambdaNode->as.TLambda.copies = newNodeList();
    return lambdaNode;
}

AstNode* NewAstModuleStmt(Span span, SymbolID boundName, Utf8String fromStr, Utf8String asStr) {
    AstNode* stmt = newNode(span, AST_STMT_MODULE);
    stmt->as.ModuleStmt.boundName = boundName;
    stmt->as.ModuleStmt.from = fromStr;
    stmt->as.ModuleStmt.as = asStr;
    return stmt;
}
AstNode* NewAstImportStmt(Span span, SymbolID module, SymbolID suffix, int glob) {
    AstNode* stmt = newNode(span, AST_STMT_IMPORT);
    stmt->as.ImportStmt.modName = module;
    stmt->as.ImportStmt.suffix = suffix;
    stmt->as.ImportStmt.glob = glob;
    return stmt;
}

AstNode* NewAstLetStmt(Span span, AstNode* lhs, AstNode* rhs) {
    AstNode* letNode = newNode(span, AST_STMT_VLET);
    letNode->as.Let.lhs = lhs;
    letNode->as.Let.rhs = rhs;
    return letNode;
}
AstNode* NewAstDefStmt(Span span, SymbolID lhs, AstNode* optTemplatePattern, AstNode* pattern, AstNode* rhs) {
    AstNode* defNode = newNode(span, AST_STMT_VDEF);
    defNode->as.Def.lhs = lhs;
    defNode->as.Def.optTemplatePattern = optTemplatePattern;
    defNode->as.Def.rhs = NewAstVLambda(span,pattern,rhs);
    return defNode;
}
AstNode* NewAstTypedefStmt(Span span, SymbolID lhs, AstNode* optPattern, AstNode* rhs) {
    AstNode* td = newNode(span, AST_STMT_TDEF);
    td->as.Typedef.name = lhs;
    td->as.Typedef.optPattern = optPattern;
    td->as.Typedef.rhs = rhs;
    return td;
}
AstNode* NewAstTypedefEnumStmt(Span span, SymbolID lhs, AstNode* optPattern, AstNode* rhs) {
    AstNode* ed = newNode(span, AST_TDEF_ENUM);
    ed->as.Typedef.name = lhs;
    ed->as.Typedef.optPattern = optPattern;
    ed->as.Typedef.rhs = rhs;
    return ed;
}

AstNode* NewAstExternStmt(Span span, SymbolID lhs, AstNode* pattern, AstNode* typespec) {
    AstNode* defNode = newNode(span, AST_STMT_EXTERN);
    defNode->as.Extern.name = lhs;
    defNode->as.Extern.pattern = pattern;
    defNode->as.Extern.typespec = typespec;
    return defNode;
}

AstNode* NewAstDiscardStmt(Span span, AstNode* discarded) {
    AstNode* discard = newNode(span, AST_STMT_DISCARD);
    discard->as.DiscardStmt_discarded = discarded;
    return discard;
}
AstNode* NewAstAssertStmt(Span span, AstNode* checked) {
    AstNode* checkNode = newNode(span, AST_STMT_ASSERT);
    checkNode->as.Check.checked = checked;
    return checkNode;
}
AstNode* NewAstSetStmt(Span span, AstNode* lhs, AstNode* rhs) {
    AstNode* set = newNode(span, AST_STMT_SET);
    set->as.SetStmt.lhs = lhs;
    set->as.SetStmt.rhs = rhs;
    return set;
}

AstNode* NewAstVCall(Span span, AstNode* lhs, AstNode* args[], int argsCount) {
    return helpNewAstCall(span,AST_VCALL,lhs,args,argsCount);
}
AstNode* NewAstVCallWithArgsSb(Span span, AstNode* lhs, AstNode** mov_argsSb) {
    AstNode* vcall = NewAstVCall(span,lhs,mov_argsSb,sb_count(mov_argsSb));
    sb_free(mov_argsSb);
    return vcall;
}
AstNode* NewAstTCall(Span span, AstNode* lhs, AstNode* args[], int argsCount) {
    return helpNewAstCall(span,AST_TCALL,lhs,args,argsCount);
}
AstNode* NewAstTCallWithArgsSb(Span span, AstNode* lhs, AstNode** mov_argsSb) {
    AstNode* tcall = NewAstTCall(span,lhs,mov_argsSb,sb_count(mov_argsSb));
    sb_free(mov_argsSb);
    return tcall;
}
AstNode* NewAstUnary(Span span, AstUnaryOperator op, AstNode* arg) {
    AstNode* unaryNode = newNode(span, AST_UNARY);
    unaryNode->as.Unary.operator = op;
    unaryNode->as.Unary.operand = arg;
    return unaryNode;
}
AstNode* NewAstBinary(Span span, AstBinaryOperator op, AstNode* ltArg, AstNode* rtArg) {
    AstNode* binaryNode = newNode(span, AST_BINARY);
    binaryNode->as.Binary.operator = op;
    binaryNode->as.Binary.ltOperand = ltArg;
    binaryNode->as.Binary.rtOperand = rtArg;
    return binaryNode;
}

AstNode* NewAstTID(Span span, SymbolID symbolID) {
    AstNode* idNode = newNode(span, AST_TID);
    idNode->as.ID.name = symbolID;
    idNode->as.ID.lookupScope = NULL;
    idNode->as.ID.defnScope = NULL;
    return idNode;
}
AstNode* NewAstTTuple(Span span) {
    AstNode* tupleNode = newNode(span,AST_TTUPLE);
    tupleNode->as.GenericList_items = newNodeList();
    return tupleNode;
}
AstNode* NewAstTTupleWithFieldsSb(Span span, AstNode** mov_fieldsSb) {
    AstNode* ttuple = NewAstTTuple(span);
    int fieldsCount = sb_count(mov_fieldsSb);
    for (int index = 0; index < fieldsCount; index++) {
        AstNode* field = mov_fieldsSb[index];
        PushFieldToAstTTuple(ttuple,field);
    }
    sb_free(mov_fieldsSb);
    return ttuple;
}
AstNode* NewAstTArray(Span span, AstNode* typespec, AstNode* count) {
    AstNode* tarray = newNode(span,AST_TARRAY);
    tarray->as.Array.typespec = typespec;
    tarray->as.Array.count = count;
    return tarray;
}
AstNode* NewAstTParen(Span span, AstNode* it) {
    AstNode* parenNode = newNode(span,AST_TPAREN);
    parenNode->as.Paren_item = it;
    return parenNode;
}
AstNode* NewAstTPtr(Span span, AstNode* pointee) {
    AstNode* ptrNode = newNode(span,AST_TPTR);
    ptrNode->as.Ptr_pointee = pointee;
    return ptrNode;
}

AstNode* NewAstVCast(Span span, AstNode* toTypespecT2V, AstNode* fromExpr) {
    COMPILER_ASSERT(toTypespecT2V->kind == AST_TYPE2VAL, "VCast expects a T2V typespec.");
    AstNode* vcastNode = newNode(span,AST_VCAST);
    vcastNode->as.VCast.toTypespecT2V = toTypespecT2V;
    vcastNode->as.VCast.fromExpr = fromExpr;
    return vcastNode;
}
AstNode* NewAstType2Val(Span span, AstNode* toTypespec) {
    AstNode* t2v = newNode(span,AST_TYPE2VAL);
    t2v->as.T2V_typespec = toTypespec;
    return t2v;
}
AstNode* NewAstVal2Type(Span span, AstNode* valueExpr) {
    AstNode* v2t = newNode(span,AST_VAL2TYPE);
    v2t->as.V2T_expr = valueExpr;
    return v2t;
}

//
// Lambda capture registration:
//

void AddAstLambdaDefn(AstNode* lambda, void* rawDefn) {
    Defn* defn = rawDefn;
    sb_push(lambda->as.VLambda.localsSB,defn);
}
void ReqAstLambdaDefn(AstNode* lambda, void* rawDefn) {
    Defn* defn = rawDefn;
    int localCount = sb_count(lambda->as.VLambda.localsSB);
    for (int localIndex = 0; localIndex < localCount; localIndex++) {
        Defn* localDefn = lambda->as.VLambda.localsSB[localIndex];
        if (defn == localDefn) {
            // this defn was a local. returning early.
            return;
        }
    }

    // this defn was a capture.
    int captureCount = sb_count(lambda->as.VLambda.capturesSB);
    int pushReq = 1;
    for (int captureIndex = 0; captureIndex < captureCount; captureIndex++) {
        Defn* captureDefn = lambda->as.VLambda.capturesSB[captureIndex];
        if (defn == captureDefn) {
            // this defn was a capture that was already added. returning early.
            pushReq = 0;
            break;
        }
    }
    if (pushReq) {
        sb_push(lambda->as.VLambda.capturesSB,defn);
        if (lambda->parentFunc) {
            ReqAstLambdaDefn(lambda->parentFunc,defn);
        }
    }
}

//
// Getter implementation:
//

SymbolID GetAstModuleName(AstNode* module) {
    return module->as.Module.name;
}
int GetAstModuleLength(AstNode* module) {
    return countList(module->as.Module.items);
}
AstNode* GetAstModuleStmtAt(AstNode* module, int index) {
    return listItemAt(module->as.Module.items, index);
}

size_t GetAstNodeKey(AstNode* node) {
    return (size_t)(node - allocatedNodes);
}

Loc GetAstNodeLoc(AstNode* node) {
    return FirstLocOfSpan(node->span);
}
Span GetAstNodeSpan(AstNode* node) {
    return node->span;
}

AstKind GetAstNodeKind(AstNode* node) {
    return node->kind;
}

SymbolID GetAstIdName(AstNode* node) {
    if (DEBUG) {
        assert(isIdKind(node->kind));
    }
    return node->as.ID.name;
}

size_t GetAstIntLiteralValue(AstNode* node) {
    return node->as.Int.value;
}
int GetAstIntLiteralBase(AstNode* node) {
    return node->as.Int.base;
}
long double GetAstFloatLiteralValue(AstNode* node) {
    return node->as.Float;
}
Utf8String GetAstStringLiteralValue(AstNode* node) {
    return node->as.StringLiteral_utf8string;
}
AstNode* GetAstParenItem(AstNode* node) {
    if (DEBUG) {
        assert(node->kind == AST_VPAREN);
    }
    return node->as.Paren_item;
}

int GetAstPatternLength(AstNode* node) {
    COMPILER_ASSERT(node->kind == AST_TPATTERN || node->kind == AST_VPATTERN, "Expected multi-pattern AST nodes.");
    return countList(node->as.GenericList_items);
}
AstNode* GetAstPatternFieldAt(AstNode* node, int index) {
    COMPILER_ASSERT(node->kind == AST_TPATTERN || node->kind == AST_VPATTERN, "Expected multi-pattern AST nodes.");
    return listItemAt(node->as.GenericList_items, index);
}
AstNode* GetAstSingletonPatternField(AstNode* node) {
    COMPILER_ASSERT(
        (node->kind == AST_TPATTERN_SINGLETON) || 
        (node->kind == AST_VPATTERN_SINGLETON), 
        "Expected singleton-pattern AST node."
    );
    return node->as.SingletonPattern_field;
}

int GetAstTupleLength(AstNode* node) {
    return countList(node->as.GenericList_items);
}
int CountAstStructFields(AstNode* node) {
    return countList(node->as.GenericList_items);
}
int GetAstChainPrefixLength(AstNode* node) {
    return countList(node->as.Chain.prefix);
}
AstNode* GetAstChainResult(AstNode* node) {
    return node->as.Chain.result;
}

AstNode* GetAstTupleItemAt(AstNode* node, int index) {
    if (DEBUG) {
        assert(node->kind == AST_VTUPLE);
    }
    return listItemAt(node->as.GenericList_items, index);
}
AstNode* GetAstStructFieldAt(AstNode* node, int index) {
    if (DEBUG) {
        assert(node->kind == AST_VSTRUCT);
    }
    return listItemAt(node->as.GenericList_items, index);
}
AstNode* GetAstChainPrefixStmtAt(AstNode* node, int index) {
    if (DEBUG) {
        assert(node->kind == AST_CHAIN);
    }
    return listItemAt(node->as.Chain.prefix, index);
}

AstNode* GetAstIteCond(AstNode* ite) {
    if (DEBUG) {
        assert(ite->kind == AST_ITE);
    }
    return listItemAt(ite->as.GenericList_items, 0);
}
AstNode* GetAstIteIfTrue(AstNode* ite) {
    if (DEBUG) {
        assert(ite->kind == AST_ITE);
    }
    return listItemAt(ite->as.GenericList_items, 1);
}
AstNode* GetAstIteIfFalse(AstNode* ite) {
    if (DEBUG) {
        assert(ite->kind == AST_ITE);
    }
    return listItemAt(ite->as.GenericList_items, 2);
}

AstNode* GetAstDotIndexLhs(AstNode* dot) {
    if (DEBUG) {
        assert(dot->kind == AST_DOT_INDEX);
    }
    return dot->as.DotIx.lhs;
}
size_t GetAstDotIndexRhs(AstNode* dot) {
    if (DEBUG) {
        assert(dot->kind == AST_DOT_INDEX);
    }
    return dot->as.DotIx.index;
}

AstNode* GetAstDotNameLhs(AstNode* dot) {
    if (DEBUG) {
        assert(dot->kind == AST_DOT_NAME);
    }
    return dot->as.DotNm.lhs;
}
SymbolID GetAstDotNameRhs(AstNode* dot) {
    if (DEBUG) {
        assert(dot->kind == AST_DOT_NAME);
    }
    return dot->as.DotNm.symbol;
}

AstNode* GetAstLetStmtLhs(AstNode* bindStmt) {
    if (DEBUG) {
        assert(bindStmt->kind == AST_STMT_VLET);
    }
    return bindStmt->as.Let.lhs;
}
AstNode* GetAstLetStmtRhs(AstNode* bindStmt) {
    if (DEBUG) {
        assert(bindStmt->kind == AST_STMT_VLET);
    }
    return bindStmt->as.Let.rhs;
}

int CountAstLambdaCaptures(AstNode* lambda) {
    return sb_count(lambda->as.VLambda.capturesSB);
}
void* GetAstVLambdaCaptureAt(AstNode* lambda, int index) {
    return lambda->as.VLambda.capturesSB[index];
}
AstNode* GetAstVLambdaPattern(AstNode* node) {
    return node->as.VLambda.pattern;
}
AstNode* GetAstVLambdaBody(AstNode* node) {
    if (DEBUG) {
        assert(node->kind == AST_VLAMBDA);
    }
    return node->as.VLambda.body;
}
AstNode* GetAstTLambdaPattern(AstNode* node) {
    return node->as.TLambda.pattern;
}
AstNode* GetAstTLambdaBody(AstNode* node) {
    return node->as.TLambda.body;
}

AstNode* GetAstAssertStmtChecked(AstNode* checkStmt) {
    if (DEBUG) {
        assert(checkStmt->kind == AST_STMT_ASSERT);
    }
    return checkStmt->as.Check.checked;
}
AstNode* GetAstDiscardStmtDiscarded(AstNode* discardStmt) {
    return discardStmt->as.DiscardStmt_discarded;
}

AstNode* GetAstCallLhs(AstNode* call) {
    if (DEBUG) {
        assert(isCallKind(call->kind) && "GetAstCallLhs on non-call!");
    }
    return call->as.Call.lhs;
}
int GetAstCallArgCount(AstNode* call) {
    return countList(call->as.Call.args);
}
AstNode* GetAstCallArgAt(AstNode* call, int index) {
    return listItemAt(call->as.Call.args,index);
}
int IsAstCallTemplate(AstNode* call) {
    if (DEBUG) {
        assert(isCallKind(call->kind));
    }
    return call->kind == AST_TCALL;
}

SymbolID GetAstFieldName(AstNode* field) {
    COMPILER_ASSERT_VA(
        field->kind == AST_VPATTERN_FIELD ||
        field->kind == AST_VSTRUCT_FIELD ||
        field->kind == AST_TPATTERN_FIELD ||
        field->kind == AST_VTUPLE_FIELD ||
        field->kind == AST_TPATTERN_SINGLETON_FIELD ||
        field->kind == AST_VPATTERN_SINGLETON_FIELD,
        "GetAstFieldRhs inapplicable to non-field of kind %s", AstKindAsText(field->kind)
    );
    return field->as.Field.name;
}
AstNode* GetAstFieldRhs(AstNode* field) {
    COMPILER_ASSERT_VA(
        field->kind == AST_VPATTERN_FIELD ||
        field->kind == AST_VSTRUCT_FIELD ||
        field->kind == AST_TPATTERN_FIELD ||
        field->kind == AST_VTUPLE_FIELD ||
        field->kind == AST_TPATTERN_SINGLETON_FIELD ||
        field->kind == AST_VPATTERN_SINGLETON_FIELD,
        "GetAstFieldRhs inapplicable to non-field of kind %s", AstKindAsText(field->kind)
    );
    return field->as.Field.rhs;
}
int GetAstFieldIndex(AstNode* field) {
    return field->as.Field.index;
}
AstNode* GetAstFieldParent(AstNode* field) {
    return field->as.Field.parent;
}

AstUnaryOperator GetAstUnaryOperator(AstNode* unary) {
    if (DEBUG) {
        assert(unary->kind == AST_UNARY);
    }
    return unary->as.Unary.operator;
}
AstNode* GetAstUnaryOperand(AstNode* unary) {
    if (DEBUG) {
        assert(unary->kind == AST_UNARY);
    }
    return unary->as.Unary.operand;
}

AstBinaryOperator GetAstBinaryOperator(AstNode* binary) {
    if (DEBUG) {
        assert(binary->kind == AST_BINARY);
    }
    return binary->as.Binary.operator;
}
AstNode* GetAstBinaryLtOperand(AstNode* binary) {
    if (DEBUG) {
        assert(binary->kind == AST_BINARY);
    }
    return binary->as.Binary.ltOperand;
}
AstNode* GetAstBinaryRtOperand(AstNode* binary) {
    if (DEBUG) {
        assert(binary->kind == AST_BINARY);
    }
    return binary->as.Binary.rtOperand;
}

AstNode* GetAstDefValueStmtOptTemplatePattern(AstNode* def) {
    return def->as.Def.optTemplatePattern;
}
SymbolID GetAstDefValueStmtLhs(AstNode* def) {
    return def->as.Def.lhs;
}
AstNode* GetAstDefValueStmtRhs(AstNode* def) {
    return def->as.Def.rhs;
}

SymbolID GetAstValStmtLhs(AstNode* valStmt) {
    return valStmt->as.Val.lhs;
}
AstNode* GetAstValStmtOptTemplatePattern(AstNode* valStmt) {
    return valStmt->as.Val.optTemplatePattern;
}
AstNode* GetAstValStmtPattern(AstNode* valStmt) {
    return valStmt->as.Val.bodyPattern;
}

SymbolID GetAstExternStmtName(AstNode* externDef) {
    return externDef->as.Extern.name;
}
AstNode* GetAstExternPattern(AstNode* externDef) {
    return externDef->as.Extern.pattern;
}
AstNode* GetAstExternTypespec(AstNode* externDef) {
    return externDef->as.Extern.typespec;
}

SymbolID GetAstTypedefStmtName(AstNode* td) {
    return td->as.Typedef.name;
}
AstNode* GetAstTypedefStmtOptPattern(AstNode* td) {
    return td->as.Typedef.optPattern;
}
AstNode* GetAstTypedefStmtOptRhs(AstNode* td) {
    return td->as.Typedef.rhs;
}

AstNode* GetAstVCastTypespec(AstNode* vcast) {
    return vcast->as.VCast.toTypespecT2V;
}
AstNode* GetAstVCastRhs(AstNode* vcast) {
    return vcast->as.VCast.fromExpr;
}

AstNode* GetAstVPtrPointee(AstNode* vptr) {
    return vptr->as.Ptr_pointee;
}
AstNode* GetAstTPtrPointee(AstNode* tptr) {
    return tptr->as.Ptr_pointee;
}

AstNode* GetAstType2ValTypespec(AstNode* type2Val) {
    return type2Val->as.T2V_typespec;
}
AstNode* GetAstVal2TypeExpr(AstNode* val2type) {
    return val2type->as.V2T_expr;
}

//
// Scoper and typer storage:
//

void* GetAstNodeTypingExt_Value(AstNode* node) {
    return node->typingExt_value;
}
void* GetAstNodeTypingExt_Type(AstNode* node) {
    return node->typingExt_type;
}
void SetAstNodeTypingExt_Value(AstNode* node, void* type) {
    if (DEBUG) {
        COMPILER_ASSERT(type,"SetAstNodeTypingExt_Value: null arg set.");
    }
    node->typingExt_value = type;
}
void SetAstNodeTypingExt_Type(AstNode* node, void* type) {
    if (DEBUG) {
        COMPILER_ASSERT(type,"SetAstNodeTypingExt_Type: null arg set.");
    }
    node->typingExt_type = type;
}

// void SetAstTypedefStmtValueDefnType(AstNode* node, void* valueDefn) {
//     node->as.Typedef.valueDefnType = valueDefn;
// }
// void* GetAstTypedefStmtValueDefnType(AstNode* node) {
//     return node->as.Typedef.valueDefnType;
// }

AstNode* GetAstCastTypespec(AstNode* cast) {
    return cast->as.Cast.castTypespec->as.CastTypespec;
}
AstNode* GetAstCastRhs(AstNode* cast) {
    return cast->as.Cast.rhs;
}

AstNode* GetAstNodeParentFunc(AstNode* node) {
    return node->parentFunc;
}
void SetAstNodeParentFunc(AstNode* node, AstNode* parentFunc) {
    COMPILER_ASSERT_VA(
        parentFunc->kind == AST_VLAMBDA,
        "non-lambda parent func of kind '%s' in 'SetAstNodeParentFunc'", AstKindAsText(parentFunc->kind)
    );
    node->parentFunc = parentFunc;
}

AstContext GetAstNodeLookupContext(AstNode* node) {
    return node->lookupContext;
}
void SetAstNodeLookupContext(AstNode* node, AstContext context) {
    node->lookupContext = context;
}

void* GetAstIdLookupScope(AstNode* node) {
    return node->as.ID.lookupScope;
}
void SetAstIdLookupScope(AstNode* node, void* scopeP) {
    node->as.ID.lookupScope = scopeP;
}
void* GetAstIdDefn(AstNode* node) {
    return node->as.ID.defnScope;
}
void SetAstIdDefnScope(AstNode* node, void* defn) {
    node->as.ID.defnScope = defn;
}

//
// Visitor API:
//

inline static int recursivelyVisitChildren(void* context, AstNode* node, VisitorCb preVisitorCb, VisitorCb postVisitorCb) {
    AstKind nodeKind = GetAstNodeKind(node);
    switch (nodeKind) {
        case AST_UNIT:
        case AST_LITERAL_INT:
        case AST_LITERAL_FLOAT:
        case AST_LITERAL_STRING:
        case AST_VID:
        case AST_TID:
        {
            return 1;
        }
        case AST_VPAREN:
        case AST_TPAREN:
        {
            RecursivelyVisitAstNode(context, node->as.Paren_item, preVisitorCb, postVisitorCb);
            return 1;
        }
        case AST_ITE:
        {
            return (
                RecursivelyVisitAstNode(context, GetAstIteCond(node), preVisitorCb, postVisitorCb) &&
                RecursivelyVisitAstNode(context, GetAstIteIfTrue(node), preVisitorCb, postVisitorCb) &&
                RecursivelyVisitAstNode(context, GetAstIteIfFalse(node), preVisitorCb, postVisitorCb)
            );
        }
        case AST_TLAMBDA:
        {
            AstNode* lambda = node;

            // visiting arg pattern:
            if (!RecursivelyVisitAstNode(context,GetAstTLambdaPattern(lambda),preVisitorCb,postVisitorCb)) {
                return 0;
            }

            // visiting the body:
            if (!RecursivelyVisitAstNode(context,GetAstTLambdaBody(lambda),preVisitorCb,postVisitorCb)) {
                return 0;
            }

            return 1;
        }
        case AST_VLAMBDA:
        {
            AstNode* lambda = node;

            // visiting each arg pattern:
            if (!RecursivelyVisitAstNode(context,GetAstVLambdaPattern(lambda),preVisitorCb,postVisitorCb)) {
                return 0;
            }

            // visiting the body:
            if (!RecursivelyVisitAstNode(context,GetAstVLambdaBody(lambda),preVisitorCb,postVisitorCb)) {
                return 0;
            }

            // all ok!
            return 1;
        }
        case AST_DOT_INDEX:
        {
            return RecursivelyVisitAstNode(context, GetAstDotIndexLhs(node), preVisitorCb, postVisitorCb);
        }
        case AST_DOT_NAME:
        {
            return RecursivelyVisitAstNode(context, GetAstDotNameLhs(node), preVisitorCb, postVisitorCb);
        }
        case AST_UNARY:
        {
            return RecursivelyVisitAstNode(context, GetAstUnaryOperand(node), preVisitorCb, postVisitorCb);
        }
        case AST_BINARY:
        {
            return (
                RecursivelyVisitAstNode(context, GetAstBinaryLtOperand(node), preVisitorCb, postVisitorCb) &&
                RecursivelyVisitAstNode(context, GetAstBinaryRtOperand(node), preVisitorCb, postVisitorCb)
            );
        }
        case AST_STMT_VLET:
        {
            return (
                RecursivelyVisitAstNode(context, GetAstLetStmtLhs(node), preVisitorCb, postVisitorCb) &&
                RecursivelyVisitAstNode(context, GetAstLetStmtRhs(node), preVisitorCb, postVisitorCb)
            );
        }
        case AST_STMT_VDEF:
        {
            return RecursivelyVisitAstNode(context,GetAstDefValueStmtRhs(node),preVisitorCb,postVisitorCb);
        }
        case AST_STMT_ASSERT:
        {
            return RecursivelyVisitAstNode(context, GetAstAssertStmtChecked(node), preVisitorCb, postVisitorCb);
        }

        case AST_VCAST:
        {
            return (
                RecursivelyVisitAstNode(context, GetAstVCastTypespec(node), preVisitorCb, postVisitorCb) &&
                RecursivelyVisitAstNode(context, GetAstVCastRhs(node), preVisitorCb, postVisitorCb)
            );
        }
        case AST_VCALL:
        case AST_TCALL:
        {
            if (!RecursivelyVisitAstNode(context, GetAstCallLhs(node), preVisitorCb, postVisitorCb)) {
                return 0;
            }
            int argCount = GetAstCallArgCount(node);
            for (int argIndex = 0; argIndex < argCount; argIndex++) {
                AstNode* arg = GetAstCallArgAt(node,argIndex);
                if (!RecursivelyVisitAstNode(context, arg, preVisitorCb, postVisitorCb)) {
                    return 0;
                }
            }
            return 1;
        }
        case AST_TPATTERN:
        case AST_VPATTERN:
        {
            int patternLength = GetAstPatternLength(node);
            for (int i = 0; i < patternLength; i++) {
                AstNode* patternField = GetAstPatternFieldAt(node, i);
                if (!RecursivelyVisitAstNode(context, patternField, preVisitorCb, postVisitorCb)) {
                    return 0;
                }
            }
            return 1;
        }
        case AST_VPATTERN_SINGLETON:
        case AST_TPATTERN_SINGLETON:
        {
            AstNode* field = GetAstSingletonPatternField(node);
            return RecursivelyVisitAstNode(context,field,preVisitorCb,postVisitorCb);
        }
        case AST_VTUPLE:
        case AST_TTUPLE:
        {
            int tupleLength = GetAstTupleLength(node);
            for (int i = 0; i < tupleLength; i++) {
                AstNode* tupleField = GetAstTupleItemAt(node, i);
                if (!RecursivelyVisitAstNode(context, tupleField, preVisitorCb, postVisitorCb)) {
                    return 0;
                }
            }
            return 1;
        }
        case AST_VSTRUCT:
        {
            size_t structLength = GetAstTupleLength(node);
            for (size_t index = 0; index < structLength; index++) {
                AstNode* structField = GetAstStructFieldAt(node, index);
                if (!RecursivelyVisitAstNode(context, structField, preVisitorCb, postVisitorCb)) {
                    return 0;
                }
            }
            return 1;
        }
        case AST_CHAIN:
        {
            size_t chainLength = GetAstChainPrefixLength(node);
            for (size_t index = 0; index < chainLength; index++) {
                AstNode* chainStmt = GetAstChainPrefixStmtAt(node, index);
                if (!RecursivelyVisitAstNode(context, chainStmt, preVisitorCb, postVisitorCb)) {
                    return 0;
                }
            }
            AstNode* result = GetAstChainResult(node);
            if (result && !RecursivelyVisitAstNode(context, result, preVisitorCb, postVisitorCb)) {
                return 0;
            }
            return 1;
        }
        case AST_VPATTERN_FIELD:
        case AST_VSTRUCT_FIELD:
        case AST_TPATTERN_FIELD:
        case AST_VTUPLE_FIELD:
        case AST_VPATTERN_SINGLETON_FIELD:
        case AST_TPATTERN_SINGLETON_FIELD:
        {
            AstNode* rhs = GetAstFieldRhs(node);
            if (rhs && !RecursivelyVisitAstNode(context, rhs, preVisitorCb, postVisitorCb)) {
                return 0;
            }
            return 1;
        }
        case AST_MODULE:
        {
            int moduleLength = GetAstModuleLength(node);
            for (int i = 0; i < moduleLength; i++) {
                AstNode* moduleField = GetAstModuleStmtAt(node, i);
                if (!RecursivelyVisitAstNode(context, moduleField, preVisitorCb, postVisitorCb)) {
                    return 0;
                }
            }
            return 1;
        }
        case AST_STMT_EXTERN:
        {
            AstNode* pattern = GetAstExternPattern(node);
            AstNode* typespec = GetAstExternTypespec(node);
            return (
                RecursivelyVisitAstNode(context, pattern, preVisitorCb, postVisitorCb) &&
                RecursivelyVisitAstNode(context, typespec, preVisitorCb, postVisitorCb)
            );
        }
        case AST_STMT_TDEF:
        {
            AstNode* optPattern = GetAstTypedefStmtOptPattern(node);
            if (optPattern) {
                AstNode* pattern = optPattern;
                if (!RecursivelyVisitAstNode(context, pattern, preVisitorCb, postVisitorCb)) {
                    return 0;
                }
            }
            AstNode* optRhs = GetAstTypedefStmtOptRhs(node);
            if (optRhs) {
                AstNode* rhs = optRhs;
                if (!RecursivelyVisitAstNode(context, rhs, preVisitorCb, postVisitorCb)) {
                    return 0;
                }
            }
            return 1;
        }
        case AST_VPTR:
        {
            AstNode* pointee = GetAstVPtrPointee(node);
            return RecursivelyVisitAstNode(context,pointee,preVisitorCb,postVisitorCb);
        }
        case AST_TPTR:
        {
            AstNode* pointee = GetAstTPtrPointee(node);
            return RecursivelyVisitAstNode(context,pointee,preVisitorCb,postVisitorCb);
        }
        case AST_ORPHANED_FIELD:
        {
            COMPILER_ERROR_VA("Placeholder node of kind '%s' should never be visited", AstKindAsText(nodeKind));
            return 0;
        }
        case AST_TYPE2VAL:
        {
            return RecursivelyVisitAstNode(context,GetAstType2ValTypespec(node),preVisitorCb,postVisitorCb);
        }
        case AST_VAL2TYPE:
        {
            return RecursivelyVisitAstNode(context,GetAstVal2TypeExpr(node),preVisitorCb,postVisitorCb);
        }
        case AST_STMT_DISCARD:
        {
            return RecursivelyVisitAstNode(context,GetAstDiscardStmtDiscarded(node),preVisitorCb,postVisitorCb);
        }
        case AST_NULL:
        {
            COMPILER_ERROR("Cannot visit a NULL AST node.");
            return 0;
        }
        case AST_ERROR:
        {
            COMPILER_ERROR("Cannot visit an ERROR AST node.");
            return 0;
        }
        default:
        {
            COMPILER_ERROR_VA("Unsupported AST node in 'visit' of type %s.", AstKindAsText(nodeKind));
            return 0;
        }
    }
}

int RecursivelyVisitAstNode(void* context, AstNode* node, VisitorCb preVisitorCb, VisitorCb postVisitorCb) {
    if (preVisitorCb) {
        if (!preVisitorCb(context, node)) {
            return 0;
        }
    }
    if (!recursivelyVisitChildren(context, node, preVisitorCb, postVisitorCb)) {
        return 0;
    }
    if (postVisitorCb) {
        if (!postVisitorCb(context, node)) {
            return 0;
        }
    }
    return 1;
}

//
// Const evaluation:
//

int IsAstNodeConstEvaluable(AstNode* node) {
    switch (GetAstNodeKind(node))
    {
        case AST_LITERAL_INT:
        case AST_LITERAL_FLOAT:
        case AST_LITERAL_STRING:
        {
            return 1;
        }
        case AST_UNARY:
        {
            AstUnaryOperator operator = GetAstUnaryOperator(node);
            int isConstOperator = (
                operator != UOP_GETREF &&
                operator != UOP_DEREF
            );
            AstNode* operand = GetAstUnaryOperand(node);
            return isConstOperator && IsAstNodeConstEvaluable(operand);
        }
        case AST_BINARY:
        {
            AstNode* ltOperand = GetAstBinaryLtOperand(node);
            AstNode* rtOperand = GetAstBinaryRtOperand(node);
            return (
                IsAstNodeConstEvaluable(ltOperand) &&
                IsAstNodeConstEvaluable(rtOperand)
            );
        }
        case AST_TYPE2VAL:
        {
            return IsAstNodeConstEvaluable(GetAstType2ValTypespec(node));
        }
        case AST_VAL2TYPE:
        {
            return IsAstNodeConstEvaluable(GetAstVal2TypeExpr(node));
        }
        case AST_TID:
        {
            return 1;
        }
        case AST_VID:
        {
            // vid constant <=> defnNode constant
            Scope* defn = GetAstIdDefn(node);
            AstNode* defnNode = defn->defnAstNode;
            return IsAstNodeConstEvaluable(defnNode);
        }

        //
        // DefnNodes (for derived VIDs):
        //

        case AST_VPATTERN_FIELD:
        case AST_VPATTERN_SINGLETON_FIELD:
        {
            return 0;
        }
        case AST_TPATTERN_FIELD:
        case AST_TPATTERN_SINGLETON_FIELD:
        {
            return 1;
        }
        
        default:
        {
            return 0;
        }
    }
}

void* GetAstNodeConstValue(AstNode* node) {
    return node->constVal;
}
void SetAstNodeConstValue(AstNode* node, void* value) {
    node->constVal = value;
}

//
// LLVM representations
//

void SetAstNodeLlvmRepr(AstNode* node, void* repr) {
    node->llvmRepr = repr;
}

void* GetAstNodeLlvmRepr(AstNode* node) {
    return node->llvmRepr;
}

//
// Reflection:
//

char const unaryOperatorTextArray[__UOP_COUNT][2] = {
    [UOP_NOT] = "!",
    [UOP_GETREF] = "^",
    [UOP_DEREF] = "*"
};
char const binaryOperatorTextArray[__BOP_COUNT][4] = {
    [BOP_MUL] = "*",
    [BOP_DIV] = "/",
    [BOP_REM] = "%",
    [BOP_ADD] = "+",
    [BOP_SUBTRACT] = "-",
    [BOP_LTHAN] = "<", 
    [BOP_LETHAN] = "<=", 
    [BOP_GTHAN] = ">", 
    [BOP_GETHAN] = ">=",
    [BOP_EQUALS] = "==", 
    [BOP_NEQUALS] = "!=",
    [BOP_AND] = "and",
    [BOP_OR] = "or",
    [BOP_XOR] = "xor"
};

//
// Reflection:
//

char const* AstKindAsText(AstKind kind) {
    switch (kind) {
        case AST_MODULE: return "AST_MODULE";
        case AST_TID: return "AST_TID";
        case AST_VID: return "AST_VID";
        case AST_LITERAL_INT: return "AST_LITERAL_INT"; 
        case AST_LITERAL_FLOAT: return "AST_LITERAL_FLOAT"; 
        case AST_LITERAL_STRING: return "AST_LITERAL_STRING"; 
        case AST_UNIT: return "AST_UNIT"; 
        case AST_TPAREN: return "AST_TPAREN";
        case AST_VPAREN: return "AST_VPAREN"; 
        case AST_VTUPLE: return "AST_VTUPLE"; 
        case AST_VSTRUCT: return "AST_VSTRUCT"; 
        case AST_CHAIN: return "AST_CHAIN";
        case AST_VLAMBDA: return "AST_VLAMBDA";
        case AST_TLAMBDA: return "AST_TLAMBDA";
        case AST_ITE: return "AST_ITE";
        case AST_DOT_INDEX: return "AST_DOT_INDEX"; 
        case AST_DOT_NAME: return "AST_DOT_NAME";
        case AST_STMT_VLET: return "AST_STMT_VLET"; 
        case AST_STMT_VDEF: return "AST_STMT_VDEF";
        case AST_STMT_DISCARD: return "AST_STMT_DISCARD";
        case AST_STMT_TDEF: return "AST_STMT_TDEF";
        case AST_STMT_ASSERT: return "AST_STMT_ASSERT"; 
        case AST_STMT_RETURN: return "AST_STMT_RETURN";
        case AST_STMT_EXTERN: return "AST_STMT_EXTERN"; 
        case AST_VCALL: return "AST_VCALL";
        case AST_TCALL: return "AST_TCALL";
        case AST_UNARY: return "AST_UNARY"; 
        case AST_BINARY: return "AST_BINARY";
        case AST_TPATTERN: return "AST_TPATTERN";
        case AST_VPATTERN: return "AST_VPATTERN";
        case AST_TPATTERN_SINGLETON: return "AST_TPATTERN_SINGLETON";
        case AST_VPATTERN_SINGLETON: return "AST_VPATTERN_SINGLETON";
        case AST_TPATTERN_FIELD: return "AST_TPATTERN_FIELD";
        case AST_TSTRUCT_FIELD: return "AST_TSTRUCT_FIELD";
        case AST_VTUPLE_FIELD: return "AST_VTUPLE_FIELD";
        case AST_VSTRUCT_FIELD: return "AST_VSTRUCT_FIELD";
        case AST_VPATTERN_FIELD: return "AST_VPATTERN_FIELD";
        case AST_TPATTERN_SINGLETON_FIELD: return "AST_TPATTERN_SINGLETON_FIELD";
        case AST_VPATTERN_SINGLETON_FIELD: return "AST_VPATTERN_SINGLETON_FIELD";
        case AST_ORPHANED_FIELD: return "AST_ORPHANED_FIELD";
        case AST_VCAST: return "AST_VCAST";
        case AST_TYPE2VAL: return "AST_TYPE2VAL";
        case AST_VAL2TYPE: return "AST_VAL2TYPE";
        case AST_TPTR: return "AST_TPTR";
        case AST_VPTR: return "AST_VPTR";
        case AST_VDEF_BUILTIN: return "AST_VDEF_BUILTIN";
        default: return "AST_?";
    }
}

char const* AstUnaryOperatorAsText(AstUnaryOperator op) {
    return unaryOperatorTextArray[op];
};
char const* AstBinaryOperatorAsText(AstBinaryOperator op) {
    return binaryOperatorTextArray[op];
}
