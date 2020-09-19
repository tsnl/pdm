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
typedef struct TypeList TypeList;

typedef enum AdtOperator AdtOperator;
typedef struct AdtTrieNode AdtTrieNode;
typedef struct AdtTrieEdge AdtTrieEdge;

//
// Types
//

struct MetaInfo {
    size_t id;
    char* name;
};
struct FuncInfo {
    Type* domain;
    Type* image;
};
struct Type {
    TypeKind kind;
    union {
        IntWidth Int;
        FloatWidth Float;
        Type* Ptr;
        MetaInfo Meta;
        FuncInfo Func;
        AdtTrieNode* AdtTrieNode;
    } as;
    Type** supTypesSb;
};

static Type builtinUnitType = {T_UNIT, {}, NULL};
static Type builtinIntTypeBuffer[] = {
    {T_INT, {.Int = INT8}, NULL},
    {T_INT, {.Int = INT16}, NULL},
    {T_INT, {.Int = INT32}, NULL},
    {T_INT, {.Int = INT64}, NULL}
};
static Type builtinFloatTypeBuffer[] = {
    {T_FLOAT, {.Float = FLOAT32}, NULL},
    {T_FLOAT, {.Float = FLOAT64}, NULL}
};

static const size_t MAX_METAVAR_COUNT = MAX_AST_NODE_COUNT;
static const size_t MAX_PTR_COUNT = MAX_AST_NODE_COUNT / 3;
static const size_t MAX_FUNC_COUNT = MAX_AST_NODE_COUNT / 2;
static const size_t MAX_MODULE_COUNT = MAX_AST_NODE_COUNT / 2;
static const size_t MAX_STRUCT_COUNT = MAX_AST_NODE_COUNT / 2;
static const size_t MAX_UNION_COUNT = MAX_AST_NODE_COUNT / 2;

static size_t ptrTypeBufferCount = 0;
static Type ptrTypeBuffer[MAX_PTR_COUNT];

static size_t metaTypeBufferCount = 0;
static Type metaTypeBuffer[MAX_METAVAR_COUNT];

static size_t funcTypeBufferCount = 0;
static Type funcTypeBuffer[MAX_FUNC_COUNT];

static size_t moduleTypeBufferCount = 0;
static Type moduleTypeBuffer[MAX_MODULE_COUNT];

static size_t structTypeBufferCount = 0;
static Type structTypeBuffer[MAX_STRUCT_COUNT];

static size_t unionTypeBufferCount = 0;
static Type unionTypeBuffer[MAX_UNION_COUNT];

static void assertSubtypes(Type* sup, Type* sub) {
    int count = sb_count(sub->supTypesSb);
    for (int i = 0; i < count; i++) {
        if (sub->supTypesSb[i] == sup) {
            return;
        }
    }
    sb_push(sub->supTypesSb, sup);
}

//
// ADT type tries
//

enum AdtOperator {
    ADT_MUL,
    ADT_SUM
};
struct AdtTrieNode {
    AdtTrieEdge* edgesSb;
    Type* owner;
};
struct AdtTrieEdge {
    AdtOperator operator;
    SymbolID name;
    Type* type;
    AdtTrieNode* result;
};

static AdtTrieNode unitTTN = {NULL, &builtinUnitType};

static AdtTrieNode* createTrieNode(Type* owner);
static AdtTrieNode* getTrieNodeChild(AdtTrieNode* root, AdtOperator operator, InputTypeFieldNode const* inputFieldList, int noNewEdges);
static AdtTrieNode* createTrieNode(Type* owner) {
    AdtTrieNode* trieNode = malloc(sizeof(AdtTrieNode));
    trieNode->edgesSb = NULL;
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
            AdtTrieNode* infant = createTrieNode(NULL);
            AdtTrieEdge edge = {operator, inputField->name, inputField->type, infant};
            sb_push(parent->edgesSb, edge);
            return infant;
        }
    }
}



//
// API:
//

Type* GetUnitType(void) {
    return &builtinUnitType;
}
Type* GetIntType(IntWidth width) {
    return &builtinIntTypeBuffer[width];
}
Type* GetFloatType(FloatWidth width) {
    return &builtinFloatTypeBuffer[width];
}
Type* GetPtrType(Type* pointee) {
    // searching for an existing, structurally equivalent type:
    for (size_t index = 0; index < ptrTypeBufferCount; index++) {
        if (ptrTypeBuffer[index].as.Ptr == pointee) {
            return ptrTypeBuffer + index;
        }
    }
    // allocating and a new type:
    Type* ptrTypeP = &ptrTypeBuffer[ptrTypeBufferCount++];
    ptrTypeP->kind = T_PTR;
    ptrTypeP->as.Ptr = pointee;
    return ptrTypeP;
}
Type* GetFuncType(Type* domain, Type* image) {
    // searching for an existing, structurally equivalent type:
    for (size_t index = 0; index < funcTypeBufferCount; index++) {
        if (funcTypeBuffer[index].as.Func.domain == domain && funcTypeBuffer[index].as.Func.image == image) {
            return ptrTypeBuffer + index;
        }
    }
    // allocating and a new type:
    Type* ptrTypeP = &ptrTypeBuffer[ptrTypeBufferCount++];
    ptrTypeP->kind = T_FUNC;
    ptrTypeP->as.Func.domain = domain;
    ptrTypeP->as.Func.image = image;
    return ptrTypeP;
}
Type* CreateMetatype(char const* format, ...) {
    Type* metaTypeP = &metaTypeBuffer[metaTypeBufferCount++];
    metaTypeP->kind = T_META;
    metaTypeP->supTypesSb = NULL;
    metaTypeP->as.Meta.id = metaTypeBufferCount;   // using the buffer count as a unique ID.
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
Type* GetStruct(InputTypeFieldList const* inputFieldList) {
    Type* structType = &structTypeBuffer[structTypeBufferCount++];
    structType->as.AdtTrieNode = getTrieNodeChild(&unitTTN, ADT_MUL, inputFieldList, 0);
    return structType;
}
Type* GetUnion(InputTypeFieldList const* inputFieldList) {
    Type* unionType = &unionTypeBuffer[unionTypeBufferCount++];
    unionType->as.AdtTrieNode = getTrieNodeChild(&unitTTN, ADT_MUL, inputFieldList, 0);
    return unionType;
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
    return typeP->as.Ptr;
}
size_t GetMetatypeID(Type* typeP) {
    return typeP->as.Meta.id;
}
char const* GetMetatypeName(Type* typeP) {
    return typeP->as.Meta.name;
}

//
// Substitutions:
//

Type* TypeSubstitution(Type* arg, TypeSub* firstTypeSubP) {
    switch (arg->kind) {
        case T_INT:
        case T_FLOAT:
        case T_UNIT:
        {
            return arg;
        }
        case T_PTR:
        {
            return GetPtrType(TypeSubstitution(arg->as.Ptr, firstTypeSubP));
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

int typeNodePostVisitor(void* source, AstNode* node) {
    switch (GetAstNodeKind(node)) {
        case AST_UNIT:
        {
            SetAstNodeValueType(node, GetUnitType());
            break;
        }
        case AST_LITERAL_FLOAT:
        {
            SetAstNodeValueType(node, GetFloatType(FLOAT64));
            break;
        }
        case AST_LITERAL_INT:
        {
            // TODO: automatically select width based on int value
            SetAstNodeValueType(node, GetIntType(INT64));
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
                FeedbackNote* note = CreateFeedbackNote("here...", source, loc, NULL);
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
                assertSubtypes(lhsType, rhsType);
            }
            break;
        }
        case AST_LAMBDA:
        {
            void* lhsType = GetAstNodeTypingType(GetAstLambdaPattern(node));
            void* rhsType = GetAstNodeValueType(GetAstLambdaBody(node));
            if (lhsType && rhsType) {
                SetAstNodeValueType(node, GetFuncType(lhsType, rhsType));
            }
            break;
        }
        case AST_PATTERN:
        {
            int patternCount = GetAstPatternLength(node);
            if (patternCount == 0) {
                SetAstNodeTypingType(node, GetUnitType());
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
            // modules can be used in value and typing contexts
            SetAstNodeValueType(node, GetAstNodeValueType(GetAstFieldRhs(node)));
            SetAstNodeTypingType(node, GetAstNodeTypingType(GetAstFieldRhs(node)));
            break;
        }
        case AST_FIELD__TEMPLATE_ITEM:
        {
            // templates can be used in typing contexts only
            SetAstNodeTypingType(node, CreateMetatype("template %s", GetSymbolText(GetAstFieldName(node))));
            
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
                SetAstNodeValueType(node, GetUnitType());
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

