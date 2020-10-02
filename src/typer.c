#include "typer.h"

#include <stddef.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "stb/stretchy_buffer.h"

#include "config.h"
#include "primer.h"
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
typedef struct IntrinsicInfo IntrinsicInfo;
typedef struct PhiInfo PhiInfo;

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
    int size;
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
    Loc loc;
    char* name;
    SubOrSupTypeRec* subtypesSB;
    SubOrSupTypeRec* supertypesSB;
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
struct IntrinsicInfo {
    int operator;
    Type* t1;
    Type* t2;
};
struct PhiInfo {
    Type* cond;
    Type* ifTrue;
    Type* ifFalse;
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
        IntrinsicInfo Intrinsic;
        PhiInfo Phi;
        AdtTrieNode* Compound_atn;
    } as;
    void* llvmRepr;
};

struct Typer {
    TyperCfg backupCfg;

    Type anyType;
    Type unitType;
    Type intType[__INT_COUNT];
    Type floatType[__FLOAT_COUNT];
    
    TypeBuf metatypeBuf;
    TypeBuf ptrTypeBuf;
    TypeBuf typefuncTypeBuf;
    TypeBuf funcTypeBuf;
    TypeBuf moduleTypeBuf;
    TypeBuf tupleTypeBuf;
    TypeBuf unionTypeBuf;
    TypeBuf unaryIntrinsicTypeBuf;
    TypeBuf binaryIntrinsicTypeBuf;
    TypeBuf phiTypeBuf;

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

// static Type* substitution(Typer* typer, Type* arg, TypeSub* firstTypeSubP);

static AdtTrieNode* newATN(AdtTrieNode* parent, Type* owner);
static AdtTrieNode* getAtnChild(AdtTrieNode* root, AdtOperator operator, InputTypeFieldNode const* inputFieldList, int noNewEdges);
static AdtTrieNode* getCommonSuperATN(AdtTrieNode* a, AdtTrieNode* b);
static int isSubATN(AdtTrieNode* sup, AdtTrieNode* sub);

static int typer_post(void* rawTyper, AstNode* node);
typedef int(*CheckReqSubtypeCB)(Loc loc, Type* type, Type* reqSubtype);
static int requireSubtype(Loc loc, Type* sup, Type* sub);
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
static int requireSubtype_metavarSup_half(Loc loc, Type* metatype, Type* subtype);
static int requireSupertype_metavarSub_half(Loc loc, Type* metatype, Type* supertype);

static Type** getConcreteTypesSB(Type* metavar, ConcreteFrom hypothesisFrom);
static void getConcreteTypesSB_impl(Type* metavar, ConcreteFrom hypothesisFrom, Type*** visitedSB, Type*** out);
static int checkConcreteSubtype(Loc loc, Type* concreteSup, Type* concreteSub);
static Type* getSupermostConcreteSubtype(Loc loc, Type* type);
static int checkSubtype(Loc loc, Type* sup, Type* sub);
static int checkMetavar(Type* metavar);

static void mapCompoundType(Typer* typer, AdtTrieNode* compound, FieldCB cb, void* sb);

static void accumulateCompoundFieldSizeSum(Typer* typer, void* sumP, SymbolID name, Type* type);
static void accumulateCompoundFieldSizeMax(Typer* typer, void* maxP, SymbolID name, Type* type);

static void printTyper(Typer* typer);
static void printType(Typer* typer, Type* type);
static void printTypeLn(Typer* typer, Type* type);

TyperCfg createDefaultTyperCfg(void) {
    int const chunkSize = MAX_AST_NODE_COUNT / 8;
    return (TyperCfg) {
        .maxMetavarCount = chunkSize,
        .maxPtrCount = chunkSize,
        .maxTypefuncCount = chunkSize,
        .maxFuncCount = chunkSize,
        .maxModuleCount = chunkSize,
        .maxStructCount = chunkSize,
        .maxUnionCount = chunkSize,
        .maxUnaryIntrinsicCount = chunkSize,
        .maxBinaryIntrinsicCount = chunkSize,
        .maxPhiCount = chunkSize
    };
}
Typer* createTyper(TyperCfg config) {
    Typer* typer = malloc(sizeof(Typer));
    
    typer->backupCfg = config;
    
    typer->anyType = (Type) {T_ANY, {}, NULL};
    typer->unitType = (Type) {T_UNIT, {}, NULL};
    typer->floatType[FLOAT_32] = (Type) {T_FLOAT, {.Float_width = FLOAT_32}, NULL};
    typer->floatType[FLOAT_64] = (Type) {T_FLOAT, {.Float_width = FLOAT_64}, NULL};
    typer->intType[INT_1] = (Type) {T_INT, {.Int_width = INT_1}, NULL};
    typer->intType[INT_8] = (Type) {T_INT, {.Int_width = INT_8}, NULL};
    typer->intType[INT_16] = (Type) {T_INT, {.Int_width = INT_16}, NULL};
    typer->intType[INT_32] = (Type) {T_INT, {.Int_width = INT_32}, NULL};
    typer->intType[INT_64] = (Type) {T_INT, {.Int_width = INT_64}, NULL};
    typer->intType[INT_64] = (Type) {T_INT, {.Int_width = INT_64}, NULL};
    typer->intType[INT_128] = (Type) {T_INT, {.Int_width = INT_128}, NULL};
    
    // todo: establish subtyping chain between primitive numbers

    typer->metatypeBuf = createTypeBuf("metatypeBuf", typer->backupCfg.maxMetavarCount);
    typer->ptrTypeBuf = createTypeBuf("ptrTypeBuf", typer->backupCfg.maxPtrCount);
    typer->funcTypeBuf = createTypeBuf("funcTypeBuf", typer->backupCfg.maxFuncCount);
    typer->typefuncTypeBuf = createTypeBuf("typefuncTypeBuf", typer->backupCfg.maxTypefuncCount);
    typer->moduleTypeBuf = createTypeBuf("moduleTypeBuf", typer->backupCfg.maxModuleCount);
    typer->tupleTypeBuf = createTypeBuf("structTypeBuf", typer->backupCfg.maxStructCount);
    typer->unionTypeBuf = createTypeBuf("unionTypeBuf", typer->backupCfg.maxUnionCount);
    typer->unaryIntrinsicTypeBuf = createTypeBuf("unaryIntrinsicTypeBuf", typer->backupCfg.maxUnaryIntrinsicCount);
    typer->binaryIntrinsicTypeBuf = createTypeBuf("binaryIntrinsicTypeBuf", typer->backupCfg.maxBinaryIntrinsicCount);
    typer->phiTypeBuf = createTypeBuf("phiTypeBuf", typer->backupCfg.maxPhiCount);
    
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

// Type* substitution(Typer* typer, Type* arg, TypeSub* firstTypeSubP) {
//     switch (arg->kind) {
//         case T_INT:
//         case T_FLOAT:
//         case T_UNIT:
//         {
//             return arg;
//         }
//         case T_PTR:
//         {
//             return GetPtrType(typer, substitution(typer, arg->as.Ptr_pointee, firstTypeSubP));
//         }
//         case T_META:
//         {
//             for (TypeSub* typeSubP = firstTypeSubP; typeSubP; typeSubP = typeSubP->next) {
//                 if (DEBUG) {
//                     assert(typeSubP->old->kind == T_META);
//                 }
//                 if (typeSubP->old == arg) {
//                     return typeSubP->new;
//                 }
//             }
//             return arg;
//         }
//         default:
//         {
//             if (DEBUG) {
//                 printf("!!- NotImplemented: ApplySubstitution for X type kind.\n");
//             } else {
//                 assert(0 && "!!- NotImplemented: ApplySubstitution for X type kind.");
//             }
//             return NULL;
//         }
//     }
// }

AdtTrieNode* newATN(AdtTrieNode* parent, Type* owner) {
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
            AdtTrieNode* infant = newATN(parent, NULL);
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
    } else if (a == NULL) {
        return NULL;
    } else if (b == NULL) {
        return NULL;
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

int typer_post(void* rawTyper, AstNode* node) {
    Typer* typer = rawTyper;
    Loc nodeLoc = GetAstNodeLoc(node);
    AstKind nodeKind = GetAstNodeKind(node);
    switch (nodeKind) {
        case AST_UNIT:
        {
            Type* t = GetUnitType(typer);
            SetAstNodeValueType(node,t);
            break;
        }
        case AST_LITERAL_INT:
        {
            // TODO: automatically select width based on int value
            Type* t = GetIntType(typer, INT_64);
            SetAstNodeValueType(node,t);
            break;
        }
        case AST_LITERAL_FLOAT:
        {
            Type* t = GetFloatType(typer, FLOAT_64);
            SetAstNodeValueType(node,t);
            break;
        }
        case AST_ID:
        {
            Loc loc = GetAstNodeLoc(node);
            SymbolID name = GetAstIdName(node);
            Scope* scope = GetAstIdLookupScope(node);
            AstContext lookupContext = GetAstNodeLookupContext(node);
            Defn* foundDefn = LookupSymbol(scope, name, lookupContext);
            if (!foundDefn) {
                FeedbackNote* note = CreateFeedbackNote("here...", loc, NULL);
                PostFeedback(
                    FBK_ERROR, note,
                    "Symbol '%s' not defined in this %s context",
                    GetSymbolText(name), (lookupContext == ASTCTX_TYPING ? "typing" : "value")
                );
            }
            Type* foundType = GetDefnType(foundDefn);
            SetAstIdDefn(node,foundDefn);
            if (lookupContext == ASTCTX_TYPING) {
                SetAstNodeTypingType(node,foundType);
            } else if (lookupContext == ASTCTX_VALUE) {
                SetAstNodeValueType(node,foundType);
            } else {
                if (DEBUG) {
                    printf("!!- Invalid lookup context while typing AST_ID.\n");
                } else {
                    assert(0 && "Invalid lookup context while typing in AST_ID.\n");
                }
                break;
            }

            // tracking closures
            // ReqAstLambdaDefn(GetAstNodeParentFunc(node),foundDefn);
            break;
        }
        case AST_MODULE:
        {
            // TODO: type a module
            break;
        }
        case AST_LET:
        {
            Type* lhsValueType = GetAstNodeValueType(node);
            Type* rhsType = GetAstNodeValueType(GetAstLetStmtRhs(node));
            if (lhsValueType && rhsType) {
                requireSubtype(GetAstNodeLoc(node), rhsType, lhsValueType);
            }
            break;
        }
        case AST_LAMBDA:
        {
            Type* lhsType = GetAstNodeValueType(GetAstLambdaPattern(node));
            Type* rhsType = GetAstNodeValueType(GetAstLambdaBody(node));
            if (lhsType && rhsType) {
                SetAstNodeValueType(node, GetFuncType(typer, lhsType, rhsType));
            }
            break;
        }
        case AST_DEF:
        {
            // module items can be used in value and typing contexts
            // todo: make these types the results of Typefunc instances
            Loc loc = GetAstNodeLoc(node);
            Type* definedValueType = GetAstNodeValueType(node);
            Type* definedTypingType = GetAstNodeTypingType(node);
            
            AstNode* desugaredRhs = GetAstDefStmtFinalRhs(node);
            Type* desugaredRhsType = GetAstNodeValueType(desugaredRhs);

            AstNode* rhs = GetAstDefStmtRhs(node);
            Type* rhsType = GetAstNodeValueType(rhs);

            if (desugaredRhsType && rhsType && definedValueType) {
                requireSubtype(loc, desugaredRhsType, definedValueType);
                requireSubtype(loc, rhsType, definedTypingType);
            } else {
                if (DEBUG) {
                    printf("!!- Skipping `define` subtyping\n");
                } else {
                    assert(0 && "Skipping 'define' subtyping.");
                }
            }
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
            Loc loc = GetAstNodeLoc(node);
            AstNode* rhs = GetAstFieldRhs(node);
            Type* tv;
            if (rhs) {
                tv = GetAstNodeValueType(rhs);
            } else {
                SymbolID name = GetAstFieldName(node);
                char const* nameText = GetSymbolText(name);
                tv = CreateMetatype(loc, typer, "field:%s", nameText);
            }
            SetAstNodeValueType(node,tv);
            break;
        }
        case AST_T_PATTERN:
        case AST_V_PATTERN:
        {
            int patternCount = GetAstPatternLength(node);
            Type* type = NULL;
            if (patternCount == 0) {
                type = GetUnitType(typer);
            } else if (patternCount == 1) {
                type = GetAstNodeValueType(GetAstPatternFieldAt(node,0));
            } else {
                InputTypeFieldList* lastInputFieldList = NULL;
                for (int index = patternCount-1; index >= 0; index--) {
                    AstNode* field = GetAstPatternFieldAt(node,index);
                    
                    InputTypeFieldNode* node = malloc(sizeof(InputTypeFieldNode));
                    node->name = GetAstFieldName(field);
                    node->next = lastInputFieldList;
                    node->type = GetAstNodeTypingType(GetAstFieldRhs(field));
                    lastInputFieldList = node;
                }
                InputTypeFieldList* firstITF = lastInputFieldList;
                type = GetTupleType(typer,lastInputFieldList);

                // todo: de-allocate ITF list.
            }

            int typeNotValueContext = (nodeKind == AST_T_PATTERN);
            if (typeNotValueContext) {
                SetAstNodeTypingType(node, type);
            } else {
                SetAstNodeValueType(node, type);
            }
            break;
        }
        case AST_STRUCT:
        {
            InputTypeFieldNode* inputTypeFieldHead = NULL;
            for (int index = GetAstStructLength(node)-1; index >= 0; --index) {
                AstNode* field = GetAstStructFieldAt(node, index);
                SymbolID fieldName = GetAstFieldName(field);
                
                InputTypeFieldNode* typingITF = malloc(sizeof(InputTypeFieldNode));
                typingITF->name = fieldName;
                typingITF->type = GetAstNodeValueType(field);
                typingITF->next = inputTypeFieldHead;
                inputTypeFieldHead = typingITF;
            }
            Type* tuple = GetTupleType(typer, inputTypeFieldHead);
            SetAstNodeValueType(node,tuple);
            break;
        }
        case AST_TUPLE:
        {
            InputTypeFieldNode* inputTypeFieldHead = NULL;
            int tupleCount = GetAstTupleLength(node);
            for (int index = tupleCount-1; index >= 0; index--) {
                AstNode* field = GetAstTupleItemAt(node, index);
                SymbolID fieldName = GetAstFieldName(field);
                InputTypeFieldNode* typingITF = malloc(sizeof(InputTypeFieldNode));
                typingITF->name = fieldName;
                typingITF->type = GetAstNodeValueType(field);
                typingITF->next = inputTypeFieldHead;
                inputTypeFieldHead = typingITF;
            }
            SetAstNodeValueType(node, GetTupleType(typer, inputTypeFieldHead));
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
            AstUnaryOperator operator = GetAstUnaryOperator(node);
            AstNode* arg = GetAstUnaryOperand(node);
            Type* argType = GetAstNodeValueType(arg);
            Type* type = GetUnaryIntrinsicType(typer,nodeLoc,operator,argType);
            SetAstNodeValueType(node,type);
            break;
        }
        case AST_BINARY:
        {
            AstBinaryOperator binop = GetAstBinaryOperator(node);
            AstNode* ltArg = GetAstBinaryLtOperand(node);
            AstNode* rtArg = GetAstBinaryRtOperand(node);
            Type* ltArgType = GetAstNodeValueType(ltArg);
            Type* rtArgType = GetAstNodeValueType(rtArg);
            Type* type = GetBinaryIntrinsicType(typer,nodeLoc,binop,ltArgType,rtArgType);
            SetAstNodeValueType(node,type);
            break;
        }
        case AST_ITE:
        {
            AstNode* cond = GetAstIteCond(node);
            AstNode* ifTrue = GetAstIteIfTrue(node);
            AstNode* ifFalse = GetAstIteIfFalse(node);
            Type* condType = GetAstNodeValueType(cond);
            Type* ifTrueType = GetAstNodeValueType(ifTrue);
            Type* ifFalseType = ifFalse ? GetAstNodeValueType(ifFalse) : GetUnitType(typer);
            Type* type = GetPhiType(typer,nodeLoc,condType,ifTrueType,ifFalseType);
            SetAstNodeValueType(node,type);
            break;
        }
        case AST_CALL:
        {
            Loc loc = GetAstNodeLoc(node);
            AstNode* lhs = GetAstCallLhs(node);
            AstNode* rhs = GetAstCallRhs(node);
            Type* ret = CreateMetatype(loc, typer, "in-ret");
            
            Type* actualFuncType = GetFuncType(typer, GetAstNodeValueType(rhs), ret);
            requireSubtype(loc, GetAstNodeValueType(lhs), actualFuncType);
            
            SetAstNodeValueType(node,ret);
            break;
        }
        case AST_PAREN:
        {
            AstNode* itNode = GetAstParenItem(node);
            Type* itType = GetAstNodeValueType(itNode);
            SetAstNodeValueType(node,itType);
            break;
        }
        case AST_TYPEDEF:
        {
            Loc loc = GetAstNodeLoc(node);
            AstNode* optRhs = GetAstTypedefStmtOptRhs(node);
            if (optRhs) {
                AstNode* rhs = optRhs;
                Type* rhsType = GetAstNodeTypingType(rhs);
                Type* metavarType = GetAstNodeTypingType(node);

                // filling rhsType as a solution for the typing metavar:
                if (rhsType && metavarType) {
                    requireSubtype(loc,rhsType,metavarType);
                } else {
                    printf("!!- Skipping `typedef` subtyping.\n");
                }
            }
            break;
        }
        case AST_EXTERN:
        {
            Loc loc = GetAstNodeLoc(node);

            AstNode* typespec = GetAstExternTypespec(node);
            Type* typespecType = GetAstNodeTypingType(typespec);
            
            Type* defType = GetAstNodeValueType(node);

            if (defType && typespecType) {
                // filling typespecType as a solution (supertype) for defType
                requireSubtype(loc,typespecType,defType);
            }

            break;
        }
        default:
        {
            if (DEBUG) {
                // TODO: replace with assertion for production
                if (DEBUG) {
                    printf("!!- Not implemented: TypeNode for AST node kind %s\n", AstKindAsText(nodeKind));
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
    if (sup == NULL) {
        if (DEBUG) {
            printf("!!- ERROR: requireSubtype on null `sup`\n");
        } else {
            assert(0 && "requireSubtype on null `sup`");
        }
        return 0;
    }
    if (sub == NULL) {
        if (DEBUG) {
            printf("!!- ERROR: requireSubtype on null `sub`\n");
        } else {
            assert(0 && "requireSubtype on null `sub`");
        }
        return 0;
    }
    
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
                printf("!!- Not implemented: requireSubtype for type kind %s.\n", TypeKindAsText(sup->kind));
            } else {
                assert(0 && "Not implemented: requireSubtype for type kind <?>.");
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
            PostFeedback(FBK_ERROR, note, "Incompatible subtypes of different kinds: int and %s.", TypeKindAsText(reqSubtype->kind));
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
            FeedbackNote* note = CreateFeedbackNote("here...",loc,NULL);
            PostFeedback(FBK_ERROR, note, "Incompatible subtypes of different kinds: float and %s.", TypeKindAsText(reqSubtype->kind));
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
            PostFeedback(FBK_ERROR, NULL, "Incompatible subtypes of different kinds: ptr and %s.", TypeKindAsText(reqSubtype->kind));
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
    int result = 1;
    switch (reqSubtype->kind)
    {
        case T_FUNC:
        {
            result = requireSubtype(loc,type->as.Func.domain,reqSubtype->as.Func.domain) && result;
            result = requireSubtype(loc,type->as.Func.image,reqSubtype->as.Func.image) && result;
            break;
        }
        case T_META:
        {
            requireSupertype_metavarSub(loc,reqSubtype,type);
            break;
        }
        default:
        {
            // todo: while typechecking func types, get loc (here) to report type errors.
            // todo: implement TypeKindToText to make error reporting more descriptive (see here).
            PostFeedback(FBK_ERROR, NULL, "Incompatible subtypes of different kinds: func and %s.", TypeKindAsText(reqSubtype->kind));
            result = 0;
            break;
        }
    }
    return result;
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
    int result = 1;
    switch (reqSubtype->kind) {
        case T_TUPLE:
        {
            // comparing ATNs
            result = isSubATN(type->as.Compound_atn,reqSubtype->as.Compound_atn) && result;
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
            FeedbackNote* note = CreateFeedbackNote("here...",loc,NULL);
            PostFeedback(FBK_ERROR, note, "Incompatible subtypes of different kinds: tuple and %s.", TypeKindAsText(reqSubtype->kind));
            result = 0;
            break;
        }
    }
    return result;
}
int requireSubtype_unionSup(Loc loc, Type* type, Type* reqSubtype) {
    if (DEBUG) {
        printf("!!- Not implemented: requireSubtype_union\n");
    } else {
        assert(0 && "Not implemented: requireSubtype_union");
    }
    return 0;
}
int requireSubtype_metavarSup(Loc loc, Type* sup, Type* sub) {
    int result = 1;
    if (sup->kind == T_META) {
        result = requireSubtype_metavarSup_half(loc,sup,sub) && result;
    }
    if (sub->kind == T_META) {
        result = requireSupertype_metavarSub_half(loc,sub,sup) && result;
    }
    return result;
}
int requireSupertype_metavarSub(Loc loc, Type* sub, Type* sup) {
    return requireSubtype_metavarSup(loc,sup,sub);
}
int requireSubtype_metavarSup_half(Loc loc, Type* metatype, Type* subtype) {
    if (metatype == NULL) {
        if (DEBUG) {
            printf("!!- ERROR: requireSubtype_metavarSup_half on null `metatype`\n");
        } else {
            assert(0 && "requireSubtype_metavarSup_half on null `metatype`");
        }
        return 0;
    }
    if (subtype == NULL) {
        if (DEBUG) {
            printf("!!- ERROR: requireSubtype_metavarSup_half on null `subtype`\n");
        } else {
            assert(0 && "requireSubtype_metavarSup_half on null `subtype`");
        }
        return 0;
    }
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
int requireSupertype_metavarSub_half(Loc loc, Type* metatype, Type* supertype) {
    // adding 'type' as a supertype of this metatype. 
    // each real supertype is a possible solution.
    
    // searching for an existing supertype, returning early if found
    int count = sb_count(metatype->as.Meta.supertypesSB);
    for (int index = 0; index < count; index++) {
        if (metatype->as.Meta.supertypesSB[index].ptr == supertype) {
            return 1;
        }
    }
    SubOrSupTypeRec typing = {loc,supertype};
    sb_push(metatype->as.Meta.supertypesSB, typing);

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
        typingSB = type->as.Meta.supertypesSB;
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
    if (concreteSup->kind == T_META) {
        if (DEBUG) {
            printf("!!- concreteSup not actually concrete.\n");
        } else {
            assert(concreteSup->kind != T_META && "concreteSup not actually concrete.");
        }
        return 0;
    }
    if (concreteSub->kind == T_META) {
        if (DEBUG) {
            printf("!!- concreteSub not actually concrete.\n");
        } else {
            assert(concreteSub->kind != T_META && "concreteSub not actually concrete.");
        }
        return 0;
    }

    // checking for mismatched kinds:
    if (concreteSup->kind != concreteSub->kind) {
        FeedbackNote* note = CreateFeedbackNote("while adding this relation...", loc, NULL);
        PostFeedback(FBK_ERROR, note, "Kind-incompatible supertype and subtype: sup:%s and sub:%s", TypeKindAsText(concreteSup->kind), TypeKindAsText(concreteSub->kind));
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
        case T_FUNC:
        {
            return (
                checkSubtype(loc, concreteSup->as.Func.domain, concreteSub->as.Func.domain) &&
                checkSubtype(loc, concreteSup->as.Func.image, concreteSub->as.Func.image)
            );
        }
        default:
        {
            if (DEBUG) {
                printf("!!- Not implemented: checkConcreteSubtype for shared type kind %s.\n", TypeKindAsText(commonTypeKind));
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
            ((oldSoln == NULL) ||
             (checkSubtype(loc,chosenSupertype,oldSoln)))
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
    int useCachedSoln = 0;

    if (metavar->kind != T_META) {
        // not a metavar
        return 0;
    }
    if (useCachedSoln && metavar->as.Meta.soln) {
        return 1;
    }
    Type* soln = metavar->as.Meta.soln = getSubmostConcreteSupertype(metavar->as.Meta.loc, metavar, NULL);
    if (soln) {
        // as soon as we've solved a metavar, we want to propagate information about it to other metavars:
        int subtypeCount = sb_count(metavar->as.Meta.subtypesSB);
        for (int subtypeIndex = 0; subtypeIndex < subtypeCount; subtypeIndex++) {
            SubOrSupTypeRec subtypeRec = metavar->as.Meta.subtypesSB[subtypeIndex];
            requireSubtype(subtypeRec.loc, soln, subtypeRec.ptr);
        }
        int supertypeCount = sb_count(metavar->as.Meta.supertypesSB);
        for (int supertypeIndex = 0; supertypeIndex < supertypeCount; supertypeIndex++) {
            SubOrSupTypeRec supertypeRec = metavar->as.Meta.supertypesSB[supertypeIndex];
            requireSubtype(supertypeRec.loc, supertypeRec.ptr, soln);
        }
    }
    return soln != NULL;
}

void mapCompoundType(Typer* typer, AdtTrieNode* compoundATN, FieldCB cb, void* context) {
    if (compoundATN != NULL && compoundATN != &typer->anyATN) {
        mapCompoundType(typer, compoundATN->parent, cb, context);
        AdtTrieNode* node = compoundATN;
        AdtTrieEdge* edge = &node->parent->edgesSb[node->parentEdgeIndex];
        cb(typer,context,edge->name,edge->type);
    }
}

char const* TypeKindAsText(TypeKind typeKind) {
    switch (typeKind) {
        case T_ANY: 
        {
            return "any";
        }
        case T_UNIT: 
        {
            return "unit";
        }
        case T_INT: 
        {
            return "int";
        }
        case T_FLOAT: 
        {
            return "float";
        }
        case T_PTR: 
        {
            return "ptr";
        }
        case T_FUNC: 
        {
            return "func";
        }
        case T_TUPLE:  
        {
            return "tuple";
        }
        case T_UNION: 
        {
            return "union";
        }
        case T_TYPEFUNC: 
        {
            return "typefunc";
        }
        case T_MODULE: 
        {
            return "module";
        }
        default:
        {
            return "<error>";
        }
    }

}

void printTyper(Typer* typer) {
    printf("!!- Typer dump:\n");
    printTypeLn(typer, &typer->intType[INT_1]);
    printTypeLn(typer, &typer->intType[INT_8]);
    printTypeLn(typer, &typer->intType[INT_16]);
    printTypeLn(typer, &typer->intType[INT_32]);
    printTypeLn(typer, &typer->intType[INT_64]);
    printTypeLn(typer, &typer->intType[INT_128]);
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

    for (it = 0; it < typer->metatypeBuf.count; it++) {
        printTypeLn(typer, &typer->metatypeBuf.ptr[it]);
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
            printf("int %d", GetIntTypeWidthInBits(type));
            break;
        }
        case T_FLOAT:
        {
            printf("float %d", GetFloatTypeWidthInBits(type));
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
            int printSupAndSubTypeCount = 0;
            if (printSupAndSubTypeCount) {
                printf("meta %s[%d,%d]", type->as.Meta.name, sb_count(type->as.Meta.supertypesSB), sb_count(type->as.Meta.subtypesSB));
            } else {
                printf("meta %s", type->as.Meta.name);
            }
            if (type->as.Meta.soln) {
                printf(" soln:");
                printType(typer, type->as.Meta.soln);
            } else {
                printf(" soln:NULL");
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
    ptrType->llvmRepr = NULL;
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
    funcType->llvmRepr = NULL;
    return funcType;
}
Type* GetTypefuncType(Typer* typer, Type* arg, Type* body) {
    Type* typefuncType = pushTypeBuf(&typer->typefuncTypeBuf);
    typefuncType->kind = T_TYPEFUNC;
    typefuncType->as.Typefunc.arg = arg;
    typefuncType->as.Typefunc.body = body;
    typefuncType->llvmRepr = NULL;
    return typefuncType;
}
Type* GetTupleType(Typer* typer, InputTypeFieldList const* inputFieldList) {
    Type* tupleType = pushTypeBuf(&typer->tupleTypeBuf);
    tupleType->kind = T_TUPLE;
    tupleType->as.Compound_atn = getAtnChild(&typer->anyATN, ADT_MUL, inputFieldList, 0);
    tupleType->as.Compound_atn->owner = tupleType;
    tupleType->llvmRepr = NULL;
    return tupleType;
}
Type* GetUnionType(Typer* typer, InputTypeFieldList const* inputFieldList) {
    Type* unionType = pushTypeBuf(&typer->unionTypeBuf);
    unionType->kind = T_UNION;
    unionType->as.Compound_atn = getAtnChild(&typer->anyATN, ADT_SUM, inputFieldList, 0);
    unionType->as.Compound_atn->owner = unionType;
    unionType->llvmRepr = NULL;
    return unionType;
}
Type* GetUnaryIntrinsicType(Typer* typer, Loc loc, AstUnaryOperator op, Type* arg) {
    switch (op)
    {
        case UOP_GETREF:
        {
            return GetPtrType(typer,arg);
        }
        case UOP_DEREF:
        {
            Type* pointee = CreateMetatype(loc,typer, "deref-pointee");
            Type* derefedType = GetPtrType(typer,pointee);
            if (requireSubtype(loc,arg,derefedType)) {
                return derefedType;
            } else {
                return NULL;
            }
        }
        case UOP_PLUS:
        case UOP_MINUS:
        {
            // todo: check if int **or float**
            if (requireSubtype(loc,GetIntType(typer,INT_128),arg)) {
                return arg;
            } else {
                PostFeedback(FBK_ERROR, NULL, "Unary operator '+' invalid with non-int type.");
                return NULL;
            }
        }
        case UOP_NOT:
        {
            if (requireSubtype(loc,GetIntType(typer,INT_1),arg)) {
                return arg;
            } else {
                PostFeedback(FBK_ERROR, NULL, "Unary operator 'not' invalid with non-boolean type.");
                return NULL;
            }
        }
        default:
        {
            if (DEBUG) {
                printf("!!- NotImplemented: GetUnaryIntrinsicType for AstUnaryOperator %s\n", AstUnaryOperatorAsText(op));
            } else {
                assert(0 && "NotImplemented: GetUnaryIntrinsicType for AstUnaryOperator <?>");
            }
            return NULL;
        }
    }
}
Type* GetBinaryIntrinsicType(Typer* typer, Loc loc, AstBinaryOperator op, Type* ltArg, Type* rtArg) {
    switch (op)
    {
        case BOP_LTHAN:
        case BOP_GTHAN:
        case BOP_LETHAN:
        case BOP_GETHAN:
        case BOP_EQUALS:
        case BOP_NEQUALS:
        {
            // expect args to be of the same type:
            if (requireSubtype(loc,ltArg,rtArg) && requireSubtype(loc,rtArg,ltArg)) {
                return GetIntType(typer,INT_1);
            } else {
                return NULL;
            }
        }
        case BOP_AND:
        case BOP_XOR:
        case BOP_OR:
        {
            // expect args to both be bool:
            Type* boolType = GetIntType(typer,INT_1);
            if (requireSubtype(loc,boolType,ltArg) && requireSubtype(loc,boolType,rtArg)) {
                return boolType;
            } else {
                return NULL;
            }
        }
        case BOP_MUL:
        case BOP_DIV:
        case BOP_REM:
        case BOP_ADD:
        case BOP_SUB:
        {
            // todo: implement arithmetic operations for floats as well as ints
            // for now, expect args and result to be ints.
            Type* intType = GetIntType(typer,INT_64);
            if (requireSubtype(loc,intType,ltArg) && requireSubtype(loc,intType,rtArg)) {
                return intType;
            } else {
                return NULL;
            }
        }
        default:
        {
            if (DEBUG) {
                printf("!!- NotImplemented: GetBinaryIntrinsicType for AstBinaryOperator '%s'\n", AstBinaryOperatorAsText(op));
            } else {
                assert(0 && "NotImplemented: GetBinaryIntrinsicType for AstBinaryOperator <?>");
            }
            return NULL;
        }
    }
}
Type* GetPhiType(Typer* typer, Loc loc, Type* cond, Type* ifTrue, Type* ifFalse) {
    Type* boolType = GetIntType(typer,INT_1);
    if (requireSubtype(loc,boolType,cond)) {
        Type* outType = CreateMetatype(loc,typer,"ite-result");
        if (requireSubtype(loc,ifTrue,outType) && requireSubtype(loc,ifFalse,outType)) {
            return outType;
        }
    }
    return NULL;
}

Type* CreateMetatype(Loc loc, Typer* typer, char const* format, ...) {
    Type* metatype = pushTypeBuf(&typer->metatypeBuf);
    metatype->kind = T_META;
    metatype->as.Meta.loc = loc;
    metatype->as.Meta.subtypesSB = NULL;
    metatype->as.Meta.supertypesSB = NULL;
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
    metatype->llvmRepr = NULL;
    return metatype;
}

//
// Getters:
//

Type* GetConcreteType(Type* type) {
    if (type->kind == T_META) {
        return type->as.Meta.soln;
    } else {
        return type;
    }
}
TypeKind GetTypeKind(Type* type) {
    return type->kind;
}
IntWidth GetIntTypeWidth(Type* type) {
    return type->as.Int_width;
}
int GetIntTypeWidthInBits(Type* type) {
    assert(type->kind == T_INT);
    switch (type->as.Int_width)
    {
        case INT_1: return 1;
        case INT_8: return 8;
        case INT_16: return 16;
        case INT_32: return 32;
        case INT_64: return 64;
        case INT_128: return 128;
        default: return 0;
    }
}
FloatWidth GetFloatTypeWidth(Type* type) {
    if (type != NULL) {
        if (type->kind == T_FLOAT) {
            return type->as.Float_width;
        } else if (type->kind == T_META) {
            return GetFloatTypeWidth(type->as.Meta.soln);
        }
    }
    if (DEBUG) {
        printf("!!- GetFloatTypeWidth called on an invalid type.\n");
    } else {
        assert(0 && "GetFloatTypeWidth called on an invalid type.");
    }
    return NULL;
}
int GetFloatTypeWidthInBits(Type* type) {
    assert(type->kind == T_FLOAT);
    switch (type->as.Float_width)
    {
        case FLOAT_32: return 32;
        case FLOAT_64: return 64;
        default: return 0;
    }
}
Type* GetPtrTypePointee(Type* type) {
    return type->as.Ptr_pointee;
}
Type* GetFuncTypeDomain(Type* func) {
    if (func != NULL) {
        if (func->kind == T_FUNC) {
            return func->as.Func.domain;
        } else if (func->kind == T_META) {
            return GetFuncTypeDomain(func->as.Meta.soln);
        }
    }
    if (DEBUG) {
        printf("!!- GetFuncTypeDomain called on an invalid type.\n");
    } else {
        assert(0 && "GetFuncTypeDomain called on an invalid type.");
    }
    return NULL;
}
Type* GetFuncTypeImage(Type* func) {
    if (func != NULL) {
        if (func->kind == T_FUNC) {
            return func->as.Func.image;
        } else if (func->kind == T_META) {
            return GetFuncTypeImage(func->as.Meta.soln);
        }
    }
    if (DEBUG) {
        printf("!!- GetFuncTypeDomain called on an invalid type.\n");
    } else {
        assert(0 && "GetFuncTypeDomain called on an invalid type.");
    }
    return NULL;
}
int GetTupleTypeLength(Type* type) {
    if (type != NULL) {
        if (type->kind == T_TUPLE) {
            return type->as.Compound_atn->depth;
        } else if (type->kind == T_META) {
            return GetTupleTypeLength(type->as.Meta.soln);
        }
    }
    if (DEBUG) {
        printf("!!- GetTupleTypeLength called on an invalid type.\n");
    } else {
        assert(0 && "GetFuncTypeDomain called on an invalid type.");
    }
    return NULL;
    if (type->kind == T_TUPLE) {
        
    }
}
int GetUnionTypeLength(Type* type) {
    return type->as.Compound_atn->depth;
}

void MapCompoundType(Typer* typer, Type* compound, FieldCB cb, void* context) {
    mapCompoundType(typer,compound->as.Compound_atn,cb,context);
}

char const* GetMetatypeName(Type* type) {
    return type->as.Meta.name;
}

//
// Typer:
//

void TypeNode(Typer* typer, AstNode* node) {
    RecursivelyVisitAstNode(typer, node, NULL, typer_post);
}

//
// Type checker:
//

int Typecheck(Typer* typer) {
    // todo: sort these solutions by dependency order
    int res = 1;
    int failureCount = 0;
    for (int index = 0; index < typer->metatypeBuf.count; index++) {
        Type* metatype = &typer->metatypeBuf.ptr[index];        
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

size_t GetTypeSizeInBytes(Typer* typer, Type* type) {
    TypeKind typeKind = type->kind;
    switch (typeKind)
    {
        case T_UNIT: 
        {
            return 0;
        }
        case T_INT:
        {
            switch (type->as.Int_width)
            {
                case INT_1: return 1;
                case INT_8: return 1;
                case INT_16: return 2;
                case INT_32: return 4;
                case INT_64: return 8;
                case INT_128: return 16;
                default:
                {
                    if (DEBUG) {
                        printf("!!- Unknown int width in GetTypeSizeInBytes.\n");
                    } else {
                        assert(0 && "Unknown int width in GetTypeSizeInBytes.");
                    }
                    break;
                }
            }
        }
        case T_TUPLE:
        {
            int size = 0;
            MapCompoundType(typer,type,accumulateCompoundFieldSizeSum,&size);
            return size;
        }
        case T_UNION:
        {
            int size = 0;
            MapCompoundType(typer,type,accumulateCompoundFieldSizeMax,&size);
            // fixme: size computation for unions uses a hard-coded, fixed 8-byte tag.
            return 8+size;  // tag+data 
        }
        default:
        {
            if (DEBUG) {
                printf("!!- Unknown type kind in GetTypeSizeInBytes: %s", TypeKindAsText(typeKind));
            } else {
                assert(0 && "Unknown type kind in GetTypeSizeInBytes.");
            }
            return -1;
        }
    }
}
void accumulateCompoundFieldSizeSum(Typer* typer, void* rawSumP, SymbolID name, Type* fieldType) {
    int* sumP = rawSumP;
    int fieldTypeSize = GetTypeSizeInBytes(typer,fieldType);
    if (sumP) {
        *sumP += fieldTypeSize;
    }
}
void accumulateCompoundFieldSizeMax(Typer* typer, void* rawMaxP, SymbolID name, Type* fieldType) {
    int* maxP = rawMaxP;
    int fieldTypeSize = GetTypeSizeInBytes(typer,fieldType);
    if (maxP) {
        if (fieldTypeSize > *maxP) {
            *maxP = fieldTypeSize;
        }
    }
}

//
// LLVM representation:
//

void* GetTypeLlvmRepr(Type* type) {
    return type->llvmRepr;
}

void SetTypeLlvmRepr(Type* type, void* repr) {
    type->llvmRepr = repr;
}

//
// DEBUG:
//

void PrintTyper(Typer* typer) {
    printTyper(typer);
}


// FIXME: this premise is flipped; we must request supertypes and provide subtype solutions.
