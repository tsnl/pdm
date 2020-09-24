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

typedef enum ConcreteFrom ConcreteFrom;

typedef enum AdtOperator AdtOperator;
typedef struct AdtTrieNode AdtTrieNode;
typedef struct AdtTrieEdge AdtTrieEdge;

typedef struct TypeSub TypeSub;
typedef struct TypeBuf TypeBuf;

typedef struct MetaInfo MetaInfo;
typedef struct FuncInfo FuncInfo;
typedef struct TypefuncInfo TypefuncInfo;
typedef struct ModuleInfo ModuleInfo;

typedef struct SubOrSupTypeRec SubOrSupTypeRec;

enum ConcreteFrom {
    CONCRETE_SUBTYPES,
    CONCRETE_SUPERTYPES
};

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
    char* name;
    SubOrSupTypeRec* subtypesSB;
    SubOrSupTypeRec* suptypesSB;
    Type* soln;
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
};

struct Typer {
    TyperCfg backupCfg;

    Type anyType;
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

    AdtTrieNode anyATN;
};

struct SubOrSupTypeRec {
    Loc loc;
    Type* ptr;
};

static TyperCfg createDefaultTyperCfg(void);
static Typer* createTyper(TyperCfg config);
static TypeBuf createTypeBuf(char const* name, size_t capacity);
static Type* tryPushTypeBuf(TypeBuf* buf);
static Type* pushTypeBuf(TypeBuf* buf);

static Type* substitution(Typer* typer, Type* arg, TypeSub* firstTypeSubP);

static AdtTrieNode* createATN(AdtTrieNode* parent, Type* owner);
static AdtTrieNode* getAtnChild(AdtTrieNode* root, AdtOperator operator, InputTypeFieldNode const* inputFieldList, int noNewEdges);
static AdtTrieNode* getCommonSuperATN(AdtTrieNode* a, AdtTrieNode* b);
static int isSubATN(AdtTrieNode* sup, AdtTrieNode* sub);

static int typerPostVisitor(void* rawTyper, AstNode* node);
typedef int(*CheckReqSubtypeCB)(Loc loc, Type* type, Type* reqSubtype);
static int requireSubtype(Loc loc, Type* sup, Type* sub);
static int requireSubtype_genericPush(Loc, Type* sup, Type* sub);
static int requireSubtype_intSup(Loc loc, Type* type, Type* reqSubtype);
static int requireSubtype_floatSup(Loc loc, Type* type, Type* reqSubtype);
static int requireSubtype_ptrSup(Loc loc, Type* type, Type* reqSubtype);
static int requireSubtype_typefuncSup(Loc loc, Type* type, Type* reqSubtype);
static int requireSubtype_funcSup(Loc loc, Type* type, Type* reqSubtype);
static int requireSubtype_moduleSup(Loc loc, Type* type, Type* reqSubtype);
static int requireSubtype_tupleSup(Loc loc, Type* type, Type* reqSubtype);
static int requireSubtype_unionSup(Loc loc, Type* type, Type* reqSubtype);
static int requireSubtype_metavarSup(Loc loc, Type* metatype, Type* subtype);
static int requireSupertype_metavarSub(Loc loc, Type* metatype, Type* supertype);

static Type** getConcreteTypesSB(Type* metavar, ConcreteFrom hypothesisFrom);
static void getConcreteTypesSB_impl(Type* metavar, ConcreteFrom hypothesisFrom, Type*** visitedSB, Type*** out);
static int checkConcreteSubtype(Loc loc, Type* concreteSup, Type* concreteSub);
static Type* getSupermostConcreteSubtype(Loc loc, Type* type);
static int checkSubtype(Loc loc, Type* sup, Type* sub);
static int checkMetavar(Type* metavar);

static void printTyper(Typer* typer);
static void printType(Typer* typer, Type* type);
static void printTypeLn(Typer* typer, Type* type);

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
    
    typer->anyType = (Type) {T_ANY, {}};
    typer->unitType = (Type) {T_UNIT, {}};
    typer->floatType[FLOAT_32] = (Type) {T_FLOAT, {.Float_width = FLOAT_32}};
    typer->floatType[FLOAT_64] = (Type) {T_FLOAT, {.Float_width = FLOAT_64}};
    typer->intType[INT_8] = (Type) {T_INT, {.Int_width = INT_8}};
    typer->intType[INT_16] = (Type) {T_INT, {.Int_width = INT_16}};
    typer->intType[INT_32] = (Type) {T_INT, {.Int_width = INT_32}};
    typer->intType[INT_64] = (Type) {T_INT, {.Int_width = INT_64}};
    typer->intType[INT_64] = (Type) {T_INT, {.Int_width = INT_64}};
    
    typer->metaTypeBuf = createTypeBuf("metaTypeBuf", typer->backupCfg.maxMetavarCount);
    typer->ptrTypeBuf = createTypeBuf("ptrTypeBuf", typer->backupCfg.maxPtrCount);
    typer->funcTypeBuf = createTypeBuf("funcTypeBuf", typer->backupCfg.maxFuncCount);
    typer->typefuncTypeBuf = createTypeBuf("typefuncTypeBuf", typer->backupCfg.maxTypefuncCount);
    typer->moduleTypeBuf = createTypeBuf("moduleTypeBuf", typer->backupCfg.maxModuleCount);
    typer->tupleTypeBuf = createTypeBuf("structTypeBuf", typer->backupCfg.maxStructCount);
    typer->unionTypeBuf = createTypeBuf("unionTypeBuf", typer->backupCfg.maxUnionCount);
    
    typer->anyATN = (AdtTrieNode) {NULL,NULL,&typer->anyType,-1,0};
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
    if (buf->count >= buf->capacity) {
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
AdtTrieNode* getAtnChild(AdtTrieNode* parent, AdtOperator operator, InputTypeFieldNode const* inputField, int noNewEdges) {
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
            int typeMatch = 0;
            if (inputField->type != NULL) {
                typeMatch = (inputField->type == edge.type);
            }
            if (operatorMatch && nameMatch && typeMatch) {
                return getAtnChild(
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
            return getAtnChild(
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
            // SetAstNodeTypingType(node,t);
            break;
        }
        case AST_LITERAL_INT:
        {
            // TODO: automatically select width based on int value
            Type* t = GetIntType(typer, INT_64);
            SetAstNodeValueType(node,t);
            // SetAstNodeTypingType(node,t);
            break;
        }
        case AST_ID:
        {
            Loc loc = GetAstNodeLoc(node);
            SymbolID name = GetAstIdName(node);
            Scope* scope = GetAstIdScopeP(node);
            AstContext lookupContext = GetAstIdLookupContext(node);
            Type* foundType = LookupSymbol(scope, name, lookupContext);
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
            Type* lhsValueType = GetAstNodeValueType(node);
            Type* lhsTypingType = GetAstNodeTypingType(node);
            Type* rhsType = GetAstNodeValueType(GetAstBindStmtRhs(node));
            if (rhsType) {
                if (lhsValueType) {
                    requireSubtype(GetAstNodeLoc(node), rhsType, lhsValueType);
                }
                if (lhsTypingType) {
                    requireSubtype(GetAstNodeLoc(node), rhsType, lhsTypingType);
                }
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
            // todo: make these types the results of Typefunc instances
            SetAstNodeValueType(node, GetAstNodeValueType(GetAstFieldRhs(node)));
            SetAstNodeTypingType(node, GetAstNodeTypingType(GetAstFieldRhs(node)));
            break;
        }
        case AST_FIELD__TEMPLATE_ITEM:
        case AST_FIELD__PATTERN_ITEM:
        {
            // metatypes created by scoper (since lexically scoped)
            // AstNodeTypingType and ValueType already set.
            
            // subtyping from RHS if present
            AstNode* rhs = GetAstFieldRhs(node);
            Type* fieldType = GetAstNodeValueType(node);
            if (rhs && fieldType) {
                Loc loc = GetAstNodeLoc(node);

                Type* rhsValueType = GetAstNodeValueType(rhs);
                if (rhsValueType) {
                    requireSubtype(loc, rhsValueType, fieldType);
                }

                Type* rhsTypingType = GetAstNodeTypingType(rhs);
                if (rhsTypingType) {
                    requireSubtype(loc, rhsTypingType, fieldType);
                }
            }
            break;
        }
        case AST_FIELD__STRUCT_ITEM:
        case AST_FIELD__TUPLE_ITEM:
        {
            AstNode* rhs = GetAstFieldRhs(node);
            Type* tv;
            Type* tt;
            if (rhs) {
                tv = GetAstNodeValueType(rhs);
                tt = GetAstNodeTypingType(rhs);
            } else {
                char const* nameText = GetSymbolText(GetAstFieldName(node));
                tv = CreateMetatype(typer, "field<v>%s", nameText);
                tt = CreateMetatype(typer, "field<t>%s", nameText);
            }
            SetAstNodeValueType(node,tv);
            SetAstNodeTypingType(node,tt);
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
                    GetAstNodeValueType(GetAstPatternFieldAt(node,0))
                );
            } else if (DEBUG) {
                // todo: create a tuple type here.
                printf("!!- Typing patterns of length > 1 not implemented.\n");
            } else {
                assert(0 && "typing patterns of length > 1 not implemented.");
            }
            break;
        }
        case AST_STRUCT:
        {
            int ignoreTypingContext = 1;
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
                    valueITF->next = inputValueFieldHead;
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
                Type* tuple = GetTupleType(typer, inputTypingFieldHead);
                SetAstNodeTypingType(node,tuple);
            }
            if (!ignoreValueContext) {
                Type* tuple = GetTupleType(typer, inputValueFieldHead);
                SetAstNodeValueType(node,tuple);
            }
            break;
        }
        case AST_TUPLE:
        {
            int ignoreTypingContext = 1;
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

int requireSubtype(Loc loc, Type* sup, Type* sub) {
    // selecting the right subtyping callback based on the type node's kind.
    // - for concrete types, we check and post feedback immediately.
    // - for metavars, we add subtypes and suptypes to lists and check them in `checkSubtype`
    CheckReqSubtypeCB callback = NULL;
    switch (sup->kind) {
        case T_INT:
        {
            callback = requireSubtype_intSup;
            break;
        }
        case T_FLOAT:
        {
            callback = requireSubtype_floatSup;
            break;
        }
        case T_PTR:
        {
            callback = requireSubtype_ptrSup;
            break;
        }
        case T_TYPEFUNC:
        {
            callback = requireSubtype_typefuncSup;
            break;
        }
        case T_FUNC:
        {
            callback = requireSubtype_funcSup;
            break;
        }
        case T_MODULE:
        {
            callback = requireSubtype_moduleSup;
            break;
        }
        case T_TUPLE:
        {
            callback = requireSubtype_tupleSup;
            break;
        }
        case T_UNION:
        {
            callback = requireSubtype_unionSup;
            break;
        }
        case T_META:
        {
            callback = requireSubtype_metavarSup;
            break;
        }
        default:
        {
            if (DEBUG) {
                printf("!!- Not implemented: typecheck for type kind <?>.\n");
            } else {
                assert(0 && "Not implemented: typecheck for type kind <?>.");
            }
            break;
        }
    }

    // running the chosen callback if found to further validate:
    if (callback) {
        return callback(loc, sup, sub);
    } else {
        return 0;
    }
}
int requireSubtype_intSup(Loc loc, Type* type, Type* reqSubtype) {
    int result = 1;
    switch (reqSubtype->kind) {
        case T_INT:
        {
            if (reqSubtype->as.Int_width < type->as.Int_width) {
                FeedbackNote* note = CreateFeedbackNote("in int type here...", loc, NULL);
                PostFeedback(FBK_ERROR, note, "Implicit integer truncation");
                result = 0;
            }
            break;
        }
        case T_FLOAT:
        {
            FeedbackNote* note = CreateFeedbackNote("in float type here...", loc, NULL);
            PostFeedback(FBK_ERROR, note, "Implicit float to integer conversion");
            result = 0;
            break;
        }
        case T_META:
        {
            result = requireSupertype_metavarSub(loc,reqSubtype,type) && result;
            break;
        }
        default:
        {
            // todo: implement TypeKindToText to make error reporting more descriptive (see here).
            FeedbackNote* note = CreateFeedbackNote("in subtype here...", loc, NULL);
            PostFeedback(FBK_ERROR, note, "Incompatible subtypes of different 'kinds': int and <?>.");
            result = 0;
            break;
        }
    }
    return result;
}
int requireSubtype_floatSup(Loc loc, Type* type, Type* reqSubtype) {
    int result = 1;
    switch (reqSubtype->kind) {
        case T_FLOAT:
        {
            if (reqSubtype->as.Float_width < type->as.Float_width) {
                // todo: while typechecking float type, get loc (here) to report type errors.
                PostFeedback(FBK_ERROR, NULL, "Implicit float to integer conversion");
                result = 0;
            }
            break;
        }
        case T_META:
        {
            result = requireSupertype_metavarSub(loc,reqSubtype,type) && result;
            break;
        }
        default:
        {
            // todo: implement TypeKindToText to make error reporting more descriptive (see here).
            // todo: while typechecking float type, get loc (here) to report type errors.
            PostFeedback(FBK_ERROR, NULL, "Incompatible subtypes of different 'kinds': float and <?>.");
            result = 0;
            break;
        }
    }
    return result;
}
int requireSubtype_ptrSup(Loc loc, Type* type, Type* reqSubtype) {
    int result = 1;
    switch (reqSubtype->kind) {
        case T_PTR:
        {
            result = requireSubtype(loc, type->as.Ptr_pointee, reqSubtype->as.Ptr_pointee) && result;
            break;
        }
        case T_META:
        {
            result = requireSupertype_metavarSub(loc,reqSubtype,type) && result;
            break;
        }
        default:
        {
            // todo: while typechecking float type, get loc (here) to report type errors.
            // todo: implement TypeKindToText to make error reporting more descriptive (see here).
            PostFeedback(FBK_ERROR, NULL, "Incompatible subtypes of different 'kinds': ptr and <?>.");
            result = 0;
            break;
        }
    }
    return result;
}
int requireSubtype_typefuncSup(Loc loc, Type* type, Type* reqSubtype) {
    if (DEBUG) {
        printf("!!- Not implemented: requireSubtype_typefunc\n");
    } else {
        assert(0 && "Not implemented: requireSubtype_typefunc");
    }
    return 0;
}
int requireSubtype_funcSup(Loc loc, Type* type, Type* reqSubtype) {
    if (DEBUG) {
        printf("!!- Not implemented: requireSubtype_func\n");
    } else {
        assert(0 && "Not implemented: requireSubtype_func");
    }
    return 0;
}
int requireSubtype_moduleSup(Loc loc, Type* type, Type* reqSubtype) {
    if (DEBUG) {
        printf("!!- Not implemented: requireSubtype_module\n");
    } else {
        assert(0 && "Not implemented: requireSubtype_module");
    }
    return 0;
}
int requireSubtype_tupleSup(Loc loc, Type* type, Type* reqSubtype) {
    if (DEBUG) {
        printf("!!- Not implemented: requireSubtype_tuple\n");
    } else {
        assert(0 && "Not implemented: requireSubtype_tuple");
    }
    return 0;
}
int requireSubtype_unionSup(Loc loc, Type* type, Type* reqSubtype) {
    if (DEBUG) {
        printf("!!- Not implemented: requireSubtype_union\n");
    } else {
        assert(0 && "Not implemented: requireSubtype_union");
    }
    return 0;
}
int requireSubtype_metavarSup(Loc loc, Type* metatype, Type* subtype) {
    int subtypeCount = sb_count(metatype->as.Meta.subtypesSB);
    for (int index = 0; index < subtypeCount; index++) {
        Type* oldSubtype = metatype->as.Meta.subtypesSB[index].ptr;
        if (subtype == oldSubtype) {
            return 1;
        }
    }
    SubOrSupTypeRec typing = {loc,subtype};
    sb_push(metatype->as.Meta.subtypesSB, typing);
    return 1;
}
int requireSupertype_metavarSub(Loc loc, Type* metatype, Type* supertype) {
    // adding 'type' as a supertype of this metatype. 
    // each real supertype is a possible solution.
    
    // searching for an existing supertype, returning early if found
    int count = sb_count(metatype->as.Meta.suptypesSB);
    for (int index = 0; index < count; index++) {
        if (metatype->as.Meta.suptypesSB[index].ptr == supertype) {
            return 1;
        }
    }
    SubOrSupTypeRec typing = {loc,supertype};
    sb_push(metatype->as.Meta.suptypesSB, typing);
    return 1;
}

Type** getConcreteTypesSB(Type* type, ConcreteFrom concreteFrom) {
    Type** outSB = NULL;
    Type** visitedSB = NULL;
    getConcreteTypesSB_impl(type, concreteFrom, &visitedSB, &outSB);
    sb_free(visitedSB);
    return outSB;
}
void getConcreteTypesSB_impl(Type* type, ConcreteFrom concreteFrom, Type*** visitedSB, Type*** outSB) {
    // todo: replace SBs in `getConcreteTypesSB` with pre-allocated LL nodes.
    
    // if 'type' is not a metavar, then it's a concrete type.
    if (type->kind != T_META) {
        sb_push((*outSB), type);
        return;
    }

    // if 'type' is a metavar we've visited before, we terminate immediately and do not add any more concrete types.
    // if not, we push 'type' to visitedSB to preempt any future visits.
    int visitedCount = sb_count((*visitedSB));
    for (int i = 0; i < visitedCount; i++) {
        if ((*visitedSB)[i] == type) {
            return;
        }
    }
    sb_push((*visitedSB),type);
    
    // selecting super or sub type lists for the metavar based on `concreteFrom`
    SubOrSupTypeRec* typingSB = NULL;
    if (concreteFrom == CONCRETE_SUBTYPES) {
        typingSB = type->as.Meta.subtypesSB;
    } else if (concreteFrom == CONCRETE_SUPERTYPES) {
        typingSB = type->as.Meta.suptypesSB;
    } else {
        if (DEBUG) {
            printf("!!- metavarHypothesisKind: unknown `metavarHypothesisKind` value.\n");
        } else {
            assert(0 && "!!- metavarHypothesisKind: unknown `metavarHypothesisKind` value.");
        }
        return;
    }
    
    if (typingSB) {
        // see: `requireSubtype/requireSuptype`
        // for each sub or sup type, recursively applying `getConcreteTypesSB`
        int count = sb_count(typingSB);
        for (int i = 0; i < count; i++) {
            getConcreteTypesSB_impl(typingSB[i].ptr,concreteFrom,visitedSB,outSB);
        }
    }
}
int checkConcreteSubtype(Loc loc, Type* concreteSup, Type* concreteSub) {
    if (DEBUG) {
        printf("!!- concreteSup not actually concrete.\n");
        printf("!!- concreteSub not actually concrete.\n");
    } else {
        assert(concreteSup->kind != T_META && "concreteSup not actually concrete.");
        assert(concreteSub->kind != T_META && "concreteSub not actually concrete.");
    }

    // checking for mismatched kinds:
    if (concreteSup->kind != concreteSub->kind) {
        FeedbackNote* note = CreateFeedbackNote("while adding this relation...", loc, NULL);
        PostFeedback(FBK_ERROR, note, "Kind-incompatible supertype and subtype.");
        return 0;
    }

    // updating the outPtr on a per-kind basis:
    TypeKind commonTypeKind = concreteSup->kind;
    switch (commonTypeKind) {
        case T_UNIT:
        {
            return 1;
        }
        case T_INT:
        {
            return concreteSup->as.Int_width <= concreteSub->as.Int_width;
        }
        case T_FLOAT:
        {
            return concreteSup->as.Float_width <= concreteSub->as.Float_width;
        }
        case T_TUPLE:
        case T_UNION:
        {
            return isSubATN(concreteSup->as.Compound_atn, concreteSub->as.Compound_atn);
        }
        case T_PTR:
        {
            return checkSubtype(loc, concreteSup->as.Ptr_pointee, concreteSub->as.Ptr_pointee);
        }
        case T_TYPEFUNC:
        {
            return (
                checkSubtype(loc, concreteSup->as.Typefunc.arg, concreteSub->as.Typefunc.arg) &&
                checkSubtype(loc, concreteSup->as.Typefunc.body, concreteSub->as.Typefunc.body)
            );
        }
        case T_MODULE:
        {
            // todo: checkConcreteSubtype for modules
            return 0;
        }
        default:
        {
            if (DEBUG) {
                printf("!!- Not implemented: checkConcreteSubtype for type kind <?>.\n");
            } else {
                assert(0 && "Not implemented: checkConcreteSubtype for type kind <?>.\n");
            }
            return 0;
        }
    }
}
Type* getSupermostConcreteSubtype(Loc loc, Type* type) {
    if (type->kind != T_META) {
        return type;
    } else {
        Type** concreteSubtypesSB = getConcreteTypesSB(type, CONCRETE_SUBTYPES);
        Type* chosenSupertype = NULL;
        int subtypesCount = sb_count(concreteSubtypesSB);
        for (int index = 0; index < subtypesCount; index++) {
            Type* concreteSubtype = concreteSubtypesSB[index];
            if (chosenSupertype == NULL) {
                chosenSupertype = concreteSubtype;
            } else {
                // todo: update outPtr with the supermost type in supermostConcreteSubtype
                if (checkSubtype(loc,concreteSubtype,chosenSupertype)) {
                    chosenSupertype = concreteSubtype;
                }
            }
        }

        sb_free(concreteSubtypesSB);
        return chosenSupertype;
    }
}
Type* getSubmostConcreteSupertype(Loc loc, Type* sup, Type* optSupermostConcreteSubtype) {
    Type* chosenSupertype = NULL;

    Type** concreteSupertypesSB = getConcreteTypesSB(sup, CONCRETE_SUPERTYPES);
    int superCount = sb_count(concreteSupertypesSB);
    for (int superIndex = 0; superIndex < superCount; superIndex++) {
        Type* supertype = concreteSupertypesSB[superIndex];
        if (optSupermostConcreteSubtype == NULL || checkSubtype(loc, supertype, optSupermostConcreteSubtype)) {
            // updating the chosenSupertype with the new supertype if required.
            int update = (
                (chosenSupertype == NULL) ||
                (checkSubtype(loc, supertype, chosenSupertype))
            );
            if (update) {
                chosenSupertype = supertype;
            }
        }
    }
    
    sb_free(concreteSupertypesSB);
    
    if (sup->kind == T_META) {
        // if sup is a metavar, updating its solution:
        Type* oldSoln = sup->as.Meta.soln;
        int update = (
            (chosenSupertype != NULL) &&
            ((sup->as.Meta.soln == NULL) ||
             (checkSubtype(loc,chosenSupertype,sup->as.Meta.soln)))
        );
        if (update) {
            sup->as.Meta.soln = chosenSupertype;
        }
    }

    return chosenSupertype;
}
int checkSubtype(Loc loc, Type* sup, Type* sub) {
    if (sup->kind == T_META || sub->kind == T_META) {
        Type* supermostConcreteSubtype = getSupermostConcreteSubtype(loc,sub);
        Type* chosenSupertype = getSubmostConcreteSupertype(loc,sup,supermostConcreteSubtype);
        return chosenSupertype != NULL;
    } else {
        return checkConcreteSubtype(loc, sup, sub);
    }
}
int checkMetavar(Type* metavar) {
    if (metavar->kind != T_META) {
        // not a metavar
        return 0;
    }
    if (metavar->as.Meta.soln) {
        return 1;
    }
    metavar->as.Meta.soln = getSubmostConcreteSupertype(NullLoc(), metavar, NULL);
    return metavar->as.Meta.soln != NULL;
}

void printTyper(Typer* typer) {
    printf("!!- Typer dump:\n");
    printTypeLn(typer, &typer->intType[INT_8]);
    printTypeLn(typer, &typer->intType[INT_16]);
    printTypeLn(typer, &typer->intType[INT_32]);
    printTypeLn(typer, &typer->intType[INT_64]);
    printTypeLn(typer, &typer->floatType[FLOAT_32]);
    printTypeLn(typer, &typer->floatType[FLOAT_64]);

    int it;
    for (it = 0; it < typer->ptrTypeBuf.count; it++) {
        printTypeLn(typer, &typer->ptrTypeBuf.ptr[it]);
    }
    for (it = 0; it < typer->typefuncTypeBuf.count; it++) {
        printTypeLn(typer, &typer->typefuncTypeBuf.ptr[it]);
    }
    for (it = 0; it < typer->funcTypeBuf.count; it++) {
        printTypeLn(typer, &typer->funcTypeBuf.ptr[it]);
    }
    for (it = 0; it < typer->moduleTypeBuf.count; it++) {
        printTypeLn(typer, &typer->moduleTypeBuf.ptr[it]);
    }
    for (it = 0; it < typer->tupleTypeBuf.count; it++) {
        printTypeLn(typer, &typer->tupleTypeBuf.ptr[it]);
    }
    for (it = 0; it < typer->unionTypeBuf.count; it++) {
        printTypeLn(typer, &typer->unionTypeBuf.ptr[it]);
    }

    for (it = 0; it < typer->metaTypeBuf.count; it++) {
        printTypeLn(typer, &typer->metaTypeBuf.ptr[it]);
    }
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
            printf("ptr ");
            printType(typer, type->as.Ptr_pointee);
            break;
        }
        case T_META:
        {
            printf("meta %s", type->as.Meta.name);
            if (type->as.Meta.soln) {
                printf(" = ");
                printType(typer, type->as.Meta.soln);
            }
            break;
        }
        case T_FUNC:
        {
            printf("func ");
            printType(typer, type->as.Func.domain);
            printf(" ");
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
void printTypeLn(Typer* typer, Type* type) {
    printType(typer, type);
    printf("\n");
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
    typefuncType->kind = T_TYPEFUNC;
    typefuncType->as.Typefunc.arg = arg;
    typefuncType->as.Typefunc.body = body;
    return typefuncType;
}
Type* GetTupleType(Typer* typer, InputTypeFieldList const* inputFieldList) {
    Type* tupleType = pushTypeBuf(&typer->tupleTypeBuf);
    tupleType->kind = T_TUPLE;
    tupleType->as.Compound_atn = getAtnChild(&typer->anyATN, ADT_MUL, inputFieldList, 0);
    tupleType->as.Compound_atn->owner = tupleType;
    return tupleType;
}
Type* GetUnionType(Typer* typer, InputTypeFieldList const* inputFieldList) {
    Type* unionType = pushTypeBuf(&typer->unionTypeBuf);
    unionType->kind = T_UNION;
    unionType->as.Compound_atn = getAtnChild(&typer->anyATN, ADT_SUM, inputFieldList, 0);
    unionType->as.Compound_atn->owner = unionType;
    return unionType;
}

Type* CreateMetatype(Typer* typer, char const* format, ...) {
    Type* metatype = pushTypeBuf(&typer->metaTypeBuf);
    metatype->kind = T_META;
    metatype->as.Meta.subtypesSB = NULL;
    metatype->as.Meta.suptypesSB = NULL;
    metatype->as.Meta.soln = NULL;
    metatype->as.Meta.name = NULL; { 
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

char const* GetMetatypeName(Type* typeP) {
    return typeP->as.Meta.name;
}

//
// Typer:
//

void TypeNode(Typer* typer, AstNode* node) {
    visit(typer, node, NULL, typerPostVisitor);
}

//
// Type checker:
//

int Typecheck(Typer* typer) {
    
    // note: typer has already been run, all constraints should have been applied to metatypes.
    // todo: in Typecheck, select a suitable solution supertype that fits subtyping constraints for each metatype.
    // todo: synthesize solutions for each metatype by first typechecking each candidate subtype, then selecting the most general solution.

    int res = 1;
    int failureCount = 0;
    for (int index = 0; index < typer->metaTypeBuf.count; index++) {
        Type* metatype = &typer->metaTypeBuf.ptr[index];        
        int metatypeRes = checkMetavar(metatype);
        if (!metatypeRes) {
            failureCount++;
        }
        res = res && metatypeRes;
    }

    if (DEBUG) {
        printf("!!- POST-TYPECHECK:\n");
        PrintTyper(typer);
        printf("!!- %d metavar failures.\n", failureCount);
    }

    return res;
}

//
// DEBUG:
//

void PrintTyper(Typer* typer) {
    printTyper(typer);
}


// FIXME: this premise is flipped; we must request supertypes and provide subtype solutions.
