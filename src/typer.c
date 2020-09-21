#include "typer.h"

#include <stddef.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>

#include "stb/stretchy_buffer.h"

#include "config.h"
#include "scoper.h"
#include "symbols.h"

typedef struct MetaInfo MetaInfo;
typedef struct FuncInfo FuncInfo;
typedef struct TypefuncInfo TypefuncInfo;

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
struct Type {
    TypeKind kind;
    union {
        IntWidth Int;
        FloatWidth Float;
        Type* Ptr_pointee;
        MetaInfo Meta;
        FuncInfo Func;
        TypefuncInfo Typefunc;
        AdtTrieNode* Compound_trieNode;
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
    TypeBuf structTypeBuf;
    TypeBuf unionTypeBuf;

    AdtTrieNode unitATN;
};

static TyperCfg createDefaultTyperCfg(void);
static Typer* createTyper(TyperCfg config);
static TypeBuf createTypeBuf(char const* name, size_t capacity);
static Type* tryPushTypeBuf(TypeBuf* buf);
static Type* pushTypeBuf(TypeBuf* buf);

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
    typer->floatType[FLOAT_32] = (Type) {T_FLOAT, {.Float = FLOAT_32}, NULL};
    typer->floatType[FLOAT_64] = (Type) {T_FLOAT, {.Float = FLOAT_64}, NULL};
    typer->intType[INT_8] = (Type) {T_INT, {.Int = INT_8}, NULL};
    typer->intType[INT_16] = (Type) {T_INT, {.Int = INT_16}, NULL};
    typer->intType[INT_32] = (Type) {T_INT, {.Int = INT_32}, NULL};
    typer->intType[INT_64] = (Type) {T_INT, {.Int = INT_64}, NULL};
    typer->intType[INT_64] = (Type) {T_INT, {.Int = INT_64}, NULL};
    
    typer->metaTypeBuf = createTypeBuf("metaTypeBuf", typer->backupCfg.maxMetavarCount);
    typer->ptrTypeBuf = createTypeBuf("ptrTypeBuf", typer->backupCfg.maxPtrCount);
    typer->funcTypeBuf = createTypeBuf("funcTypeBuf", typer->backupCfg.maxFuncCount);
    typer->typefuncTypeBuf = createTypeBuf("typefuncTypeBuf", typer->backupCfg.maxTypefuncCount);
    typer->moduleTypeBuf = createTypeBuf("moduleTypeBuf", typer->backupCfg.maxModuleCount);
    typer->structTypeBuf = createTypeBuf("structTypeBuf", typer->backupCfg.maxStructCount);
    typer->unionTypeBuf = createTypeBuf("unionTypeBuf", typer->backupCfg.maxUnionCount);
    
    typer->unitATN = (AdtTrieNode) {NULL,NULL,&typer->unitType};
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

static AdtTrieNode* createTrieNode(AdtTrieNode* parent, Type* owner);
static AdtTrieNode* getTrieNodeChild(AdtTrieNode* root, AdtOperator operator, InputTypeFieldNode const* inputFieldList, int noNewEdges);
static AdtTrieNode* getCommonSuperTrieNode(AdtTrieNode* a, AdtTrieNode* b);
static int isSubTrieNode(AdtTrieNode* sup, AdtTrieNode* sub);

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

AdtTrieNode* createTrieNode(AdtTrieNode* parent, Type* owner) {
    AdtTrieNode* trieNode = malloc(sizeof(AdtTrieNode));
    trieNode->edgesSb = NULL;
    trieNode->parent = parent;
    trieNode->owner = NULL;
    return trieNode;
}
AdtTrieNode* getTrieNodeChild(AdtTrieNode* parent, AdtOperator operator, InputTypeFieldNode const* inputField, int noNewEdges) {
    if (inputField == NULL) {
        return parent;
    } else {
        // searching children for an existing edge:
        int edgeCount = sb_count(parent->edgesSb);
        for (int i = 0; i < edgeCount; i++) {
            AdtTrieEdge edge = parent->edgesSb[i];
            int operatorMatch = (operator == edge.operator);
            int nameMatch = 1;
            if (inputField->name != SYM_NULL) {
                nameMatch = (inputField->name == edge.name);
            }
            int typeMatch = 1;
            if (inputField->type != NULL) {
                typeMatch = (inputField->type == edge.type);
            }
            if (operatorMatch && nameMatch && typeMatch) {
                return getTrieNodeChild(
                    edge.result,
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
            AdtTrieNode* infant = createTrieNode(parent, NULL);
            AdtTrieEdge edge = {operator, inputField->name, inputField->type, infant};
            sb_push(parent->edgesSb, edge);
            return infant;
        }
    }
}
AdtTrieNode* getCommonSuperTrieNode(AdtTrieNode* a, AdtTrieNode* b) {
    if (a == b) {
        return a;
    } else {
        return getCommonSuperTrieNode(
            getCommonSuperTrieNode(a->parent, b),
            getCommonSuperTrieNode(a, b->parent)
        );
    }
}
int isSubTrieNode(AdtTrieNode* sup, AdtTrieNode* sub) {
    return getCommonSuperTrieNode(sub,sup) == sup;
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
    return funcType;
}
Type* GetTypefuncType(Typer* typer, Type* arg, Type* body) {
    Type* typefuncType = pushTypeBuf(&typer->typefuncTypeBuf);
    typefuncType->as.Typefunc.arg = arg;
    typefuncType->as.Typefunc.body = body;
    return typefuncType;
}
Type* GetStruct(Typer* typer, InputTypeFieldList const* inputFieldList) {
    Type* structType = pushTypeBuf(&typer->structTypeBuf);
    structType->as.Compound_trieNode = getTrieNodeChild(&typer->unitATN, ADT_MUL, inputFieldList, 0);
    return structType;
}
Type* GetUnion(Typer* typer, InputTypeFieldList const* inputFieldList) {
    Type* unionType = pushTypeBuf(&typer->unionTypeBuf);
    unionType->as.Compound_trieNode = getTrieNodeChild(&typer->unitATN, ADT_MUL, inputFieldList, 0);
    return unionType;
}

Type* CreateMetatype(Typer* typer, char const* format, ...) {
    Type* metaTypeP = pushTypeBuf(&typer->metaTypeBuf);
    metaTypeP->kind = T_META;
    metaTypeP->requiredSubTypesSb = NULL;
    metaTypeP->as.Meta.id = typer->metaTypeBuf.count;   // using the buffer count as a unique ID.
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
        metaTypeP->as.Meta.name = strdup(nameBuffer);
    }
    return metaTypeP;
}

//
// Getters:
//

TypeKind GetTypeKind(Type* typeP) {
    return typeP->kind;
}
IntWidth GetIntTypeWidth(Type* typeP) {
    return typeP->as.Int;
}
FloatWidth GetFloatTypeWidth(Type* typeP) {
    return typeP->as.Float;
}
Type* GetPtrTypePointee(Type* typeP) {
    return typeP->as.Ptr_pointee;
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

int typeNodePostVisitor(void* rawTyper, AstNode* node) {
    Typer* typer = rawTyper;
    switch (GetAstNodeKind(node)) {
        case AST_UNIT:
        {
            SetAstNodeValueType(node, GetUnitType(typer));
            break;
        }
        case AST_LITERAL_FLOAT:
        {
            SetAstNodeValueType(node, GetFloatType(typer, FLOAT_64));
            break;
        }
        case AST_LITERAL_INT:
        {
            // TODO: automatically select width based on int value
            SetAstNodeValueType(node, GetIntType(typer, INT_64));
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
        case AST_TUPLE:
        {
            // todo: create a struct type here.
            // todo: add types of fields.
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
            SetAstNodeTypingType(node, CreateMetatype(typer, "template %s", GetSymbolText(GetAstFieldName(node))));
            
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
            // todo: prepare field types for parent
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

void TypeNode(Source* source, AstNode* node) {
    visit(source, node, NULL, typeNodePostVisitor);
}

int Typecheck(void) {
    // todo: check requirements for each non-metatype.
    // todo: synthesize solutions for each metatype.
    if (DEBUG) {
        printf("!!- Not implemented: `typecheck` for type kind <*>\n.");
    }
    return 0;
}