#include "typer.h"

#include <stddef.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "stb/stretchy_buffer.h"

#include "config.h"
#include "scoper.h"
#include "symbols.h"

typedef struct MetaInfo MetaInfo;
typedef struct FuncInfo FuncInfo;
typedef struct TypefuncInfo TypefuncInfo;
typedef struct ModuleInfo ModuleInfo;

typedef struct TypeSub TypeSub;
typedef struct TypeBuf TypeBuf;

typedef enum AdtOperator AdtOperator;
typedef struct AdtTrieNode AdtTrieNode;
typedef struct AdtTrieEdge AdtTrieEdge;

enum AdtOperator {
    ADT_MUL,
    ADT_SUM
};
struct AdtTrieNode {
    AdtTrieEdge* edgesSb;
    AdtTrieNode* parent;
    Type* owner;
    int parentEdgeIndex;
    int depth;
};
struct AdtTrieEdge {
    AdtOperator operator;
    SymbolID name;
    Type* type;
    AdtTrieNode* result;
};

struct TypeSub {
    Type* old;
    Type* new;
    TypeSub* next;
};
struct TypeBuf {
    char const* name;
    size_t capacity;
    size_t count;
    Type* ptr;
};

struct MetaInfo {
    size_t id;
    char* name;
};
struct FuncInfo {
    Type* domain;
    Type* image;
};
struct TypefuncInfo {
    Type* arg;
    Type* body;
};
struct ModuleInfo {
    // todo: implement type ModuleInfo
};
struct Type {
    TypeKind kind;
    union {
        IntWidth Int_width;
        FloatWidth Float_width;
        Type* Ptr_pointee;
        MetaInfo Meta;
        FuncInfo Func;
        TypefuncInfo Typefunc;
        ModuleInfo Module;
        AdtTrieNode* Compound_atn;
    } as;
    Type** requiredSubTypesSb;
};

struct Typer {
    TyperCfg backupCfg;

    Type unitType;
    Type intType[__INT_COUNT];
    Type floatType[__FLOAT_COUNT];
    
    TypeBuf metaTypeBuf;
    TypeBuf ptrTypeBuf;
    TypeBuf typefuncTypeBuf;
    TypeBuf funcTypeBuf;
    TypeBuf moduleTypeBuf;
    TypeBuf tupleTypeBuf;
    TypeBuf unionTypeBuf;

    AdtTrieNode unitATN;
};

static TyperCfg createDefaultTyperCfg(void);
static Typer* createTyper(TyperCfg config);
static TypeBuf createTypeBuf(char const* name, size_t capacity);
static Type* tryPushTypeBuf(TypeBuf* buf);
static Type* pushTypeBuf(TypeBuf* buf);

static int typerPostVisitor(void* rawTyper, AstNode* node);
static int typecheckSingle(Typer* typer, Type* type);
static void printType(Typer* typer, Type* type);

TyperCfg createDefaultTyperCfg(void) {
    return (TyperCfg) {
        .maxMetavarCount = MAX_AST_NODE_COUNT,
        .maxPtrCount = MAX_AST_NODE_COUNT,
        .maxTypefuncCount = MAX_AST_NODE_COUNT,
        .maxFuncCount = MAX_AST_NODE_COUNT,
        .maxModuleCount = MAX_AST_NODE_COUNT,
        .maxStructCount = MAX_AST_NODE_COUNT,
        .maxUnionCount = MAX_AST_NODE_COUNT
    };
}
Typer* createTyper(TyperCfg config) {
    Typer* typer = malloc(sizeof(Typer));
    
    typer->backupCfg = config;
    
    typer->unitType = (Type) {T_UNIT, {}, NULL};
    typer->floatType[FLOAT_32] = (Type) {T_FLOAT, {.Float_width = FLOAT_32}, NULL};
    typer->floatType[FLOAT_64] = (Type) {T_FLOAT, {.Float_width = FLOAT_64}, NULL};
    typer->intType[INT_8] = (Type) {T_INT, {.Int_width = INT_8}, NULL};
    typer->intType[INT_16] = (Type) {T_INT, {.Int_width = INT_16}, NULL};
    typer->intType[INT_32] = (Type) {T_INT, {.Int_width = INT_32}, NULL};
    typer->intType[INT_64] = (Type) {T_INT, {.Int_width = INT_64}, NULL};
    typer->intType[INT_64] = (Type) {T_INT, {.Int_width = INT_64}, NULL};
    
    typer->metaTypeBuf = createTypeBuf("metaTypeBuf", typer->backupCfg.maxMetavarCount);
    typer->ptrTypeBuf = createTypeBuf("ptrTypeBuf", typer->backupCfg.maxPtrCount);
    typer->funcTypeBuf = createTypeBuf("funcTypeBuf", typer->backupCfg.maxFuncCount);
    typer->typefuncTypeBuf = createTypeBuf("typefuncTypeBuf", typer->backupCfg.maxTypefuncCount);
    typer->moduleTypeBuf = createTypeBuf("moduleTypeBuf", typer->backupCfg.maxModuleCount);
    typer->tupleTypeBuf = createTypeBuf("structTypeBuf", typer->backupCfg.maxStructCount);
    typer->unionTypeBuf = createTypeBuf("unionTypeBuf", typer->backupCfg.maxUnionCount);
    
    typer->unitATN = (AdtTrieNode) {NULL,NULL,&typer->unitType,-1,0};
    // todo: singleton structs and tuples / unions == identity operation (!!)
    // todo: integer promotion must be implemented somehow
    return typer;
}
TypeBuf createTypeBuf(char const* name, size_t capacity) {
    return (TypeBuf) {
        name,
        capacity, 0,
        malloc(capacity * sizeof(Type))
    };
}
Type* tryPushTypeBuf(TypeBuf* buf) {
    if (buf->count == buf->capacity) {
        return NULL;
    } else {
        return &buf->ptr[buf->count++];
    }
}
Type* pushTypeBuf(TypeBuf* buf) {
    Type* type = tryPushTypeBuf(buf);
    if (type) {
        return type;
    } else {
        if (DEBUG) {
            printf("!!- Overflow in TypeBuf '%s': at capacity (%zu)", buf->name, buf->capacity);
        } else {
            assert(0 && "Overflow in TypeBuf");
        }
        return NULL;
    }
}

static void requireSubtyping(Type* sup, Type* sub);
static Type* substitution(Typer* typer, Type* arg, TypeSub* firstTypeSubP);

static AdtTrieNode* createATN(AdtTrieNode* parent, Type* owner);
static AdtTrieNode* getATN(AdtTrieNode* root, AdtOperator operator, InputTypeFieldNode const* inputFieldList, int noNewEdges);
static AdtTrieNode* getCommonSuperATN(AdtTrieNode* a, AdtTrieNode* b);
static int isSubATN(AdtTrieNode* sup, AdtTrieNode* sub);

void requireSubtyping(Type* sup, Type* sub) {
    int count = sb_count(sup->requiredSubTypesSb);
    for (int i = 0; i < count; i++) {
        if (sup->requiredSubTypesSb[i] == sub) {
            return;
        }
    }
    sb_push(sup->requiredSubTypesSb, sub);
}
Type* substitution(Typer* typer, Type* arg, TypeSub* firstTypeSubP) {
    switch (arg->kind) {
        case T_INT:
        case T_FLOAT:
        case T_UNIT:
        {
            return arg;
        }
        case T_PTR:
        {
            return GetPtrType(typer, substitution(typer, arg->as.Ptr_pointee, firstTypeSubP));
        }
        case T_META:
        {
            for (TypeSub* typeSubP = firstTypeSubP; typeSubP; typeSubP = typeSubP->next) {
                if (DEBUG) {
                    assert(typeSubP->old->kind == T_META);
                }
                if (typeSubP->old == arg) {
                    return typeSubP->new;
                }
            }
            return arg;
        }
        default:
        {
            if (DEBUG) {
                printf("!!- NotImplemented: ApplySubstitution for X type kind.\n");
            } else {
                assert(0 && "!!- NotImplemented: ApplySubstitution for X type kind.");
            }
            return NULL;
        }
    }
}

AdtTrieNode* createATN(AdtTrieNode* parent, Type* owner) {
    AdtTrieNode* trieNode = malloc(sizeof(AdtTrieNode));
    trieNode->edgesSb = NULL;
    trieNode->parent = parent;
    trieNode->owner = NULL;
    if (trieNode->parent) {
        trieNode->depth = 1+trieNode->parent->depth;
        trieNode->parentEdgeIndex = sb_count(parent->edgesSb);
    } else {
        trieNode->depth = -1;
        trieNode->parentEdgeIndex = -1;
    }
    return trieNode;
}
AdtTrieNode* getATN(AdtTrieNode* parent, AdtOperator operator, InputTypeFieldNode const* inputField, int noNewEdges) {
    if (inputField == NULL) {
        return parent;
    } else {
        if (DEBUG) {
            if (!parent) {
                printf("!!- cannot `getATN` from a NULL parent.\n");
            }
        } else {
            assert(parent && "cannot `getATN` from a NULL parent... give us something...");
        }

        // searching children for an existing edge:
        int edgeCount = sb_count(parent->edgesSb);
        for (int i = 0; i < edgeCount; i++) {
            AdtTrieEdge edge = parent->edgesSb[i];
            AdtTrieNode* child = edge.result;
            if (DEBUG) {
                if (child->parentEdgeIndex != i) {
                    printf("!!- ATN Tree property violated: a child's parent edge index does not match the found index.\n");
                }
            } else {
                assert(child->parentEdgeIndex == i);
            }
                
            int operatorMatch = (operator == edge.operator);
            int nameMatch = (inputField->name == edge.name);
            int typeMatch = 1;
            if (inputField->type != NULL) {
                typeMatch = (inputField->type == edge.type);
            }
            if (operatorMatch && nameMatch && typeMatch) {
                return getATN(
                    child,
                    operator,
                    inputField->next,
                    noNewEdges
                );
            }
        }
        // trying to insert a new edge since one could not be found in a child.
        if (noNewEdges) {
            return NULL;
        } else {
            AdtTrieNode* infant = createATN(parent, NULL);
            AdtTrieEdge edge = {operator, inputField->name, inputField->type, infant};
            sb_push(parent->edgesSb, edge);
            return getATN(
                infant,
                operator,
                inputField->next,
                noNewEdges
            );
        }
    }
}
AdtTrieNode* getCommonSuperATN(AdtTrieNode* a, AdtTrieNode* b) {
    if (a == b) {
        return a;
    } else {
        return getCommonSuperATN(
            getCommonSuperATN(a->parent, b),
            getCommonSuperATN(a, b->parent)
        );
    }
}
int isSubATN(AdtTrieNode* sup, AdtTrieNode* sub) {
    return getCommonSuperATN(sub,sup) == sup;
}

//
// API:
//

TyperCfg CreateDefaultTyperCfg(void) {
    return createDefaultTyperCfg();
}

Typer* CreateTyper(TyperCfg config) {
    return createTyper(config);
}

Type* GetUnitType(Typer* typer) {
    return &typer->unitType;
}
Type* GetIntType(Typer* typer, IntWidth width) {
    return &typer->intType[width];
}
Type* GetFloatType(Typer* typer, FloatWidth width) {
    return &typer->floatType[width];
}
Type* GetPtrType(Typer* typer, Type* pointee) {
    // searching for an existing, structurally equivalent type:
    for (size_t index = 0; index < typer->ptrTypeBuf.count; index++) {
        Type* cmpType = &typer->ptrTypeBuf.ptr[index];
        if (cmpType->as.Ptr_pointee == pointee) {
            return cmpType;
        }
    }
    // allocating and a new type:
    Type* ptrType = pushTypeBuf(&typer->ptrTypeBuf);
    ptrType->kind = T_PTR;
    ptrType->as.Ptr_pointee = pointee;
    ptrType->requiredSubTypesSb = NULL;
    return ptrType;
}
Type* GetFuncType(Typer* typer, Type* domain, Type* image) {
    // searching for an existing, structurally equivalent type:
    TypeBuf funcTypeBuf = typer->funcTypeBuf;
    for (size_t index = 0; index < funcTypeBuf.count; index++) {
        FuncInfo itemInfo = funcTypeBuf.ptr[index].as.Func;
        if (itemInfo.domain == domain && itemInfo.image == image) {
            return &funcTypeBuf.ptr[index];
        }
    }
    // allocating and a new type:
    Type* funcType = pushTypeBuf(&typer->ptrTypeBuf);
    funcType->kind = T_FUNC;
    funcType->as.Func.domain = domain;
    funcType->as.Func.image = image;
    funcType->requiredSubTypesSb = NULL;
    return funcType;
}
Type* GetTypefuncType(Typer* typer, Type* arg, Type* body) {
    Type* typefuncType = pushTypeBuf(&typer->typefuncTypeBuf);
    typefuncType->kind = T_TYPEFUNC;
    typefuncType->as.Typefunc.arg = arg;
    typefuncType->as.Typefunc.body = body;
    typefuncType->requiredSubTypesSb = NULL;
    return typefuncType;
}
Type* GetTupleType(Typer* typer, InputTypeFieldList const* inputFieldList) {
    Type* tupleType = pushTypeBuf(&typer->tupleTypeBuf);
    tupleType->kind = T_TUPLE;
    tupleType->as.Compound_atn = getATN(&typer->unitATN, ADT_MUL, inputFieldList, 0);
    tupleType->as.Compound_atn->owner = tupleType;
    tupleType->requiredSubTypesSb = NULL;
    return tupleType;
}
Type* GetUnionType(Typer* typer, InputTypeFieldList const* inputFieldList) {
    Type* unionType = pushTypeBuf(&typer->unionTypeBuf);
    unionType->kind = T_UNION;
    unionType->as.Compound_atn = getATN(&typer->unitATN, ADT_SUM, inputFieldList, 0);
    unionType->as.Compound_atn->owner = unionType;
    unionType->requiredSubTypesSb = NULL;
    return unionType;
}

Type* CreateMetatype(Typer* typer, char const* format, ...) {
    Type* metatype = pushTypeBuf(&typer->metaTypeBuf);
    metatype->kind = T_META;
    metatype->requiredSubTypesSb = NULL;
    metatype->as.Meta.id = typer->metaTypeBuf.count;   // using the buffer count as a unique ID.
    {  // metaTypeP->as.Meta.name
        char nameBuffer[1024];
        va_list args;
        va_start(args, format);
        int writeCount = vsnprintf(nameBuffer, 1024, format, args);
        if (writeCount > 1024) {
            if (DEBUG) {
                printf("!!- Metatype name too long! Greater than maximum length 1024.\n");
            } else {
                assert(0 && "Metatype name too long");
            }
        }
        va_end(args);
        metatype->as.Meta.name = strdup(nameBuffer);
    }
    metatype->requiredSubTypesSb = NULL;
    return metatype;
}

//
// Getters:
//

TypeKind GetTypeKind(Type* typeP) {
    return typeP->kind;
}
IntWidth GetIntTypeWidth(Type* typeP) {
    return typeP->as.Int_width;
}
FloatWidth GetFloatTypeWidth(Type* typeP) {
    return typeP->as.Float_width;
}
Type* GetPtrTypePointee(Type* typeP) {
    return typeP->as.Ptr_pointee;
}
int GetTupleTypeLength(Type* type) {
    return type->as.Compound_atn->depth;
}
int GetUnionTypeLength(Type* type) {
    return type->as.Compound_atn->depth;
}

size_t GetMetatypeID(Type* typeP) {
    return typeP->as.Meta.id;
}
char const* GetMetatypeName(Type* typeP) {
    return typeP->as.Meta.name;
}

//
// Typer visitor:
//

int typerPostVisitor(void* rawTyper, AstNode* node) {
    Typer* typer = rawTyper;
    switch (GetAstNodeKind(node)) {
        case AST_UNIT:
        {
            Type* t = GetUnitType(typer);
            SetAstNodeValueType(node,t);
            SetAstNodeTypingType(node,t);
            break;
        }
        case AST_LITERAL_FLOAT:
        {
            Type* t = GetFloatType(typer, FLOAT_64);
            SetAstNodeValueType(node,t);
            SetAstNodeTypingType(node,t);
            break;
        }
        case AST_LITERAL_INT:
        {
            // TODO: automatically select width based on int value
            Type* t = GetIntType(typer, INT_64);
            SetAstNodeValueType(node,t);
            SetAstNodeTypingType(node,t);
            break;
        }
        case AST_ID:
        {
            Loc loc = GetAstNodeLoc(node);
            SymbolID name = GetAstIdName(node);
            Scope* scope = GetAstIdScopeP(node);
            AstContext lookupContext = GetAstIdLookupContext(node);
            void* foundType = LookupSymbol(scope, name, lookupContext);
            if (!foundType) {
                FeedbackNote* note = CreateFeedbackNote("here...", loc, NULL);
                PostFeedback(
                    FBK_ERROR, note,
                    "Symbol '%s' not defined in this %s context",
                    GetSymbolText(name), (lookupContext == ASTCTX_TYPING ? "typing" : "value")
                );
            }
            if (lookupContext == ASTCTX_TYPING) {
                SetAstNodeTypingType(node, foundType);
                SetAstNodeValueType(node, NULL);
            } else if (lookupContext == ASTCTX_VALUE) {
                SetAstNodeValueType(node, foundType);
                SetAstNodeTypingType(node, NULL);
            } else if (DEBUG) {
                printf("!!- Invalid ID lookupContext in typeNodePostVisitor\n");
            } else {
                assert(0 && "Invalid ID lookupContext in typeNodePostVisitor\n");
            }
            break;
        }
        case AST_MODULE:
        {
            // TODO: type a module
            break;
        }
        case AST_STMT_BIND:
        {
            void* lhsType = GetAstNodeValueType(node);
            void* rhsType = GetAstNodeValueType(node);
            if (lhsType && rhsType) {
                requireSubtyping(lhsType, rhsType);
            }
            break;
        }
        case AST_LAMBDA:
        {
            void* lhsType = GetAstNodeTypingType(GetAstLambdaPattern(node));
            void* rhsType = GetAstNodeValueType(GetAstLambdaBody(node));
            if (lhsType && rhsType) {
                SetAstNodeValueType(node, GetFuncType(typer, lhsType, rhsType));
            }
            break;
        }

        case AST_FIELD__MODULE_ITEM:
        {
            // module items can be used in value and typing contexts
            // todo: make these types the results of type functions
            SetAstNodeValueType(node, GetAstNodeValueType(GetAstFieldRhs(node)));
            SetAstNodeTypingType(node, GetAstNodeTypingType(GetAstFieldRhs(node)));
            break;
        }
        case AST_FIELD__TEMPLATE_ITEM:
        {
            // templates can be used in typing contexts only
            SetAstNodeTypingType(node, GetAstNodeTypingType(node));
            
            // todo: and should give type reflection/actual template arg in value contexts
            SetAstNodeValueType(node, NULL);
            break;
        }
        case AST_FIELD__PATTERN_ITEM:
        {
            // pattern items (in lambdas, match expressions) can only be used in value contexts
            SetAstNodeValueType(node, GetAstNodeTypingType(GetAstFieldRhs(node)));
            break;
        }
        case AST_FIELD__STRUCT_ITEM:
        case AST_FIELD__TUPLE_ITEM:
        {
            AstNode* field = GetAstFieldRhs(node);
            SetAstNodeTypingType(node, GetAstNodeTypingType(field));
            SetAstNodeValueType(node, GetAstNodeValueType(field));
            break;
        }
        case AST_PATTERN:
        {
            int patternCount = GetAstPatternLength(node);
            if (patternCount == 0) {
                SetAstNodeTypingType(node, GetUnitType(typer));
            } else if (patternCount == 1) {
                SetAstNodeTypingType(
                    node,
                    GetAstNodeTypingType(GetAstPatternFieldAt(node,0))
                );
            } else if (DEBUG) {
                // todo: create a struct type here.
                printf("!!- Typing patterns of length > 1 not implemented.\n");
            } else {
                assert(0 && "typing patterns of length > 1 not implemented.");
            }
            break;
        }
        case AST_STRUCT:
        {
            int ignoreTypingContext = 0;
            int ignoreValueContext = 0;
            InputTypeFieldNode* inputTypingFieldHead = NULL;
            InputTypeFieldNode* inputValueFieldHead = NULL;
            for (int index = GetAstStructLength(node)-1; index >= 0; --index) {
                AstNode* field = GetAstStructFieldAt(node, index);
                SymbolID fieldName = GetAstFieldName(field);
                
                // creating a new input type field node, updating the list:
                if (!ignoreValueContext) {
                    InputTypeFieldNode* valueITF = malloc(sizeof(InputTypeFieldNode));
                    valueITF->name = fieldName;
                    valueITF->type = GetAstNodeValueType(field);
                    valueITF->next = inputTypingFieldHead;
                    inputValueFieldHead = valueITF;
                }
                
                if (!ignoreTypingContext) {
                    InputTypeFieldNode* typingITF = malloc(sizeof(InputTypeFieldNode));
                    typingITF->name = fieldName;
                    typingITF->type = GetAstNodeTypingType(field);
                    typingITF->next = inputTypingFieldHead;
                    inputTypingFieldHead = typingITF;
                }
            }
            if (!ignoreTypingContext) {
                SetAstNodeTypingType(node, GetTupleType(typer, inputTypingFieldHead));
            }
            if (!ignoreValueContext) {
                SetAstNodeValueType(node, GetTupleType(typer, inputValueFieldHead));
            }
            break;
        }
        case AST_TUPLE:
        {
            int ignoreTypingContext = 0;
            int ignoreValueContext = 0;
            InputTypeFieldNode* inputTypingFieldHead = NULL;
            InputTypeFieldNode* inputValueFieldHead = NULL;
            int tupleCount = GetAstTupleLength(node);
            for (int index = tupleCount-1; index >= 0; index--) {
                AstNode* field = GetAstTupleItemAt(node, index);
                SymbolID fieldName = GetAstFieldName(field);
                
                // creating a new input type field node, updating the list:
                if (!ignoreValueContext) {
                    InputTypeFieldNode* valueITF = malloc(sizeof(InputTypeFieldNode));
                    valueITF->name = fieldName;
                    valueITF->type = GetAstNodeValueType(field);
                    valueITF->next = inputTypingFieldHead;
                    inputValueFieldHead = valueITF;
                }
                
                if (!ignoreTypingContext) {
                    InputTypeFieldNode* typingITF = malloc(sizeof(InputTypeFieldNode));
                    typingITF->name = fieldName;
                    typingITF->type = GetAstNodeTypingType(field);
                    typingITF->next = inputTypingFieldHead;
                    inputTypingFieldHead = typingITF;
                }
            }
            if (!ignoreTypingContext) {
                SetAstNodeTypingType(node, GetTupleType(typer, inputTypingFieldHead));
            }
            if (!ignoreValueContext) {
                SetAstNodeValueType(node, GetTupleType(typer, inputValueFieldHead));
            }
            break;
        }
        case AST_CHAIN:
        {
            AstNode* result = GetAstChainResult(node);
            if (result) {
                SetAstNodeValueType(node, GetAstNodeValueType(result));
            } else {
                SetAstNodeValueType(node, GetUnitType(typer));
            }
            break;
        }
        case AST_UNARY:
        {
            // todo: TypeNode for unary function call
            break;
        }
        case AST_BINARY:
        {
            // todo: TypeNode for binary function call
            break;
        }
        case AST_CALL:
        {
            // todo: TypeNode for postfix function call
            break;
        }
        default:
        {
            if (DEBUG) {
                // TODO: replace with assertion for production
                if (DEBUG) {
                    printf("!!- Not implemented: TypeNode for AST node kind <?>\n");
                } else {
                    assert(0 && "Not implemented: TypeNode for AST node kind <?>");
                }
            }
            break;
        }
    }
    return 1;
}
void TypeNode(Typer* typer, AstNode* node) {
    visit(typer, node, NULL, typerPostVisitor);
}

int typecheckSingle(Typer* typer, Type* type) {
    if (DEBUG) {
        printf("!!- Not actually typechecking type in `typecheckSingle`... \n\t");
        printType(typer, type);
        printf("\n");
    } else {
        assert(0 && "Not implemented: typecheckSingle for any type.");
    }
    return 1;
}
void printType(Typer* typer, Type* type) {
    // prints an s-expression: (<kind> <args...>)
    printf("(");
    switch (type->kind)
    {
        case T_UNIT:
        {
            printf("unit");
            break;
        }
        case T_INT:
        {
            IntWidth width = type->as.Int_width;
            if (width == INT_8) {
                printf("int 8");
            } else if (width == INT_16) {
                printf("int 16");
            } else if (width == INT_32) {
                printf("int 32");
            } else if (width == INT_64) {
                printf("int 64");
            } else {
                printf("int ?");
            }
            break;
        }
        case T_FLOAT:
        {
            FloatWidth width = type->as.Float_width;
            if (width == FLOAT_32) {
                printf("float 32");
            } else if (width == FLOAT_64) {
                printf("float 64");
            } else {
                printf("float ?");
            }
            break;
        }
        case T_PTR:
        {
            puts("ptr ");
            printType(typer, type->as.Ptr_pointee);
            break;
        }
        case T_META:
        {
            printf("meta %zu %s", type->as.Meta.id, type->as.Meta.name);
            break;
        }
        case T_FUNC:
        {
            puts("func ");
            printType(typer, type->as.Func.domain);
            puts(" ");
            printType(typer, type->as.Func.image);
            break;
        }
        case T_MODULE:
        {
            // todo: implement printType for T_MODULE.
            break;
        }
        case T_TUPLE:
        {
            int atnDepth = GetTupleTypeLength(type);
            printf("tuple (%d)", atnDepth);
            for (AdtTrieNode* atn = type->as.Compound_atn; atn && atn->parentEdgeIndex >= 0; atn = atn->parent) {
                AdtTrieEdge edge = atn->parent->edgesSb[atn->parentEdgeIndex];
                printf(" (");
                if (edge.name != SYM_NULL) {
                    printf("%s:", GetSymbolText(edge.name));
                }
                if (edge.type) {
                    printType(typer, edge.type);
                } else {
                    printf("?");
                }
                printf(")");
            }
            break;
        }
        case T_UNION:
        {
            int atnDepth = GetTupleTypeLength(type);
            printf("union (count:%d)", atnDepth);
            break;
        }
        default:
        {
            break;
        }
    }
    printf(")");
}
int Typecheck(Typer* typer) {
    // todo: check requirements for each non-metatype.
    // todo: synthesize solutions for each metatype by first typechecking each candidate subtype, then selecting the most general solution.

    int it;
    int res = 1;

    res = typecheckSingle(typer, &typer->intType[INT_8]) && res;
    res = typecheckSingle(typer, &typer->intType[INT_16]) && res;
    res = typecheckSingle(typer, &typer->intType[INT_32]) && res;
    res = typecheckSingle(typer, &typer->intType[INT_64]) && res;
    res = typecheckSingle(typer, &typer->floatType[FLOAT_32]) && res;
    res = typecheckSingle(typer, &typer->floatType[FLOAT_64]) && res;

    for (it = 0; it < typer->ptrTypeBuf.count; it++) {
        res = typecheckSingle(typer, &typer->ptrTypeBuf.ptr[it]) && res;
    }
    for (it = 0; it < typer->typefuncTypeBuf.count; it++) {
        res = typecheckSingle(typer, &typer->ptrTypeBuf.ptr[it]) && res;
    }
    for (it = 0; it < typer->funcTypeBuf.count; it++) {
        res = typecheckSingle(typer, &typer->funcTypeBuf.ptr[it]) && res;
    }
    for (it = 0; it < typer->moduleTypeBuf.count; it++) {
        res = typecheckSingle(typer, &typer->moduleTypeBuf.ptr[it]) && res;
    }
    for (it = 0; it < typer->tupleTypeBuf.count; it++) {
        res = typecheckSingle(typer, &typer->tupleTypeBuf.ptr[it]) && res;
    }
    for (it = 0; it < typer->unionTypeBuf.count; it++) {
        res = typecheckSingle(typer, &typer->unionTypeBuf.ptr[it]) && res;
    }

    for (it = 0; it < typer->metaTypeBuf.count; it++) {
        res = typecheckSingle(typer, &typer->metaTypeBuf.ptr[it]) && res;
    }

    return res;
}
