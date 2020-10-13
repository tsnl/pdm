#include "typer.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "stb/stretchy_buffer.h"

#include "config.h"
#include "primer.h"
#include "symbols.h"

// each 'Type' instance is a tagged union.
// - unit is unique and a universal subtype.
// - integers,floats are unique, referenced by width.
// - any,tuples,unions are stored in a Trie, where each node is a unique type.
// - pointers,funcs,etc. are called 'compounds' and contain references to other types.
// - metatypes contain iteratively updated solutions. Upon applying each new typing relationship, the 'soln' property is updated.

// the 'typer' function applies all program typing constraints in one pass.

#define SUBTYPING_ERROR_BUF_SIZE (256)

typedef struct Type;
typedef union GenericTypeInfo;

typedef enum AdtOperator AdtOperator;
typedef struct AdtTrieNode AdtTrieNode;
typedef struct AdtTrieEdge AdtTrieEdge;

typedef struct TypeBuf TypeBuf;

typedef struct MetaInfo MetaInfo;
typedef struct FuncInfo FuncInfo;
typedef struct TypefuncInfo TypefuncInfo;
typedef struct ModuleInfo ModuleInfo;
typedef struct IntrinsicInfo IntrinsicInfo;
typedef struct PhiInfo PhiInfo;

typedef struct SubOrSuperTypeRec SubOrSuperTypeRec;
typedef SubOrSuperTypeRec SubTypeRec;
typedef SubOrSuperTypeRec SuperTypeRec;
typedef enum SubtypingResult SubtypingResult;

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

struct TypeBuf {
    char const* name;
    size_t capacity;
    size_t count;
    Type* ptr;
};

struct MetaInfo {
    void* soln;
    char* name;
    Loc loc;
    SubTypeRec* subtypeRecSB;
    SuperTypeRec* supertypeRecSB;
};
struct FuncInfo {
    Type** domainArray;
    Type* image;
    int domainCount;
};
struct TypefuncInfo {
    Type* arg;
    Type* body;
};
struct ModuleInfo {
    // todo: implement type ModuleInfo
};
union GenericTypeInfo {
    IntWidth Int_width;
    FloatWidth Float_width;
    Type* Ptr_pointee;
    MetaInfo Meta;
    FuncInfo Func;
    TypefuncInfo Typefunc;
    ModuleInfo Module;
    AdtTrieNode* Compound_atn;
};
struct Type {
    TypeKind kind;
    union GenericTypeInfo as;
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

    AdtTrieNode anyATN;

    char const* subtypingError;
};

struct SubOrSuperTypeRec {
    Loc loc;
    Type* ptr;
};
enum SubtypingResult {
    // note: while merging results, we select the max. See `mergeSubtypingResults`.
    SUBTYPING_CONFIRM,
    SUBTYPING_DEFERRED,
    SUBTYPING_FAILURE
};

//
// Functions:
//

// typer creation:
static TyperCfg newDefaultTyperCfg(void);
static Typer* newTyper(TyperCfg config);

// type creation:
inline static Type newType(TypeKind typeKind, union GenericTypeInfo typeInfo);
static TypeBuf newTypeBuf(char const* name, size_t capacity);
static Type* tryPushToTypeBuf(TypeBuf* buf);
static Type* helpPushToTypeBuf(TypeBuf* buf);
Type* pushToTypeBuf(TypeBuf* buf, TypeKind kind);

// ATNs: a way to track compounds:
static AdtTrieNode* newATN(AdtTrieNode* parent, Type* owner);
static AdtTrieNode* getAtnChild(AdtTrieNode* root, AdtOperator operator, InputTypeFieldNode const* inputFieldList, int noNewEdges);
static AdtTrieNode* getCommonAncestorATN(AdtTrieNode* a, AdtTrieNode* b);
static int isAncestorATN(AdtTrieNode* parent, AdtTrieNode* child);

// typing constraints:
// 1. we attempt to eagerly check typing constraints (CONFIRM/FAILURE), but
// 2. if the result depends on a metavar, we return FAILURE unless matches hypothesis so far, then DEFERRED
// 3. after typing (no more solution possible), call 'checkDeferredMetavarSubtypings' 
// usage:
// - call 'readSubtyping' to check if A sup B without modifying the system.
// - call 'writeSubtyping' to assert that A sup B, thereby modifying the system.
// - call 'checkDeferredMetavarSubtypings' to check metavar subtypings against final solutions.
static SubtypingResult readSubtyping(Typer* typer, char const* why, Loc locWhere, Type* super, Type* sub);
static SubtypingResult writeSubtyping(Typer* typer, char const* why, Loc locWhere, Type* super, Type* sub);
static SubtypingResult checkDeferredMetavarSubtypings(Typer* typer);   // all metavar subtypes
// helpers (1)...
static SubtypingResult readOrWriteSubtyping(Typer* typer, char const* why, Loc locWhere, Type* super, Type* sub, int readOnly);
static SubtypingResult helpReadOrWriteSubtyping(Typer* typer, char const* why, Loc locWhere, Type* super, Type* sub, int readOnly);
static SubtypingResult helpReadOrWriteSubtyping_intSuper(Typer* typer, char const* why, Loc loc, Type* super, Type* sub, int readOnly);
static SubtypingResult helpReadOrWriteSubtyping_floatSuper(Typer* typer, char const* why, Loc loc, Type* super, Type* sub, int readOnly);
static SubtypingResult helpReadOrWriteSubtyping_ptrSuper(Typer* typer, char const* why, Loc loc, Type* super, Type* sub, int readOnly);
static SubtypingResult helpReadOrWriteSubtyping_funcSuper(Typer* typer, char const* why, Loc loc, Type* super, Type* sub, int readOnly);
static SubtypingResult helpReadOrWriteSubtyping_tupleSuper(Typer* typer, char const* why, Loc loc, Type* super, Type* sub, int readOnly);
static SubtypingResult helpReadOrWriteSubtyping_unionSuper(Typer* typer, char const* why, Loc loc, Type* super, Type* sub, int readOnly);
static SubtypingResult helpReadOrWriteSubtyping_metaSuper(Typer* typer, char const* why, Loc loc, Type* meta, Type* sub, int readOnly);
static SubtypingResult helpReadOrWriteSubtyping_metaSub(Typer* typer, char const* why, Loc loc, Type* meta, Type* super, int readOnly);
// helpers (2)...
static void resetSubtypingError(Typer* typer);
static char const* getAndResetSubtypingError(Typer* typer);
static void setGenericSubtypingError(Typer* typer, char const* format, ...);
static void setMismatchedKindsSubtypingError(Typer* typer, Type* sup, Type* sub);
// helpers (3)...
static SubtypingResult mergeSubtypingResults(SubtypingResult fst, SubtypingResult snd);

// checking solved-ness:
static int isSolved(Type* type);

// THE typer callback:
static int typer_post(void* rawTyper, AstNode* node);

// compound field traversal:
static void mapCompoundType(Typer* typer, AdtTrieNode* compound, FieldCB cb, void* sb);
static void accumulateCompoundFieldSizeSum(Typer* typer, void* sumP, SymbolID name, Type* type);
static void accumulateCompoundFieldSizeMax(Typer* typer, void* maxP, SymbolID name, Type* type);

// printing:
static void printTyper(Typer* typer);
static void printType(Typer* typer, Type* type);
static void printTypeLn(Typer* typer, Type* type);

// deprecated:
static Type* getConcreteType__deprecated(Typer* typer, Type* visited, Type*** visitedSBP);

//
//
// Implementations:
//
//

TyperCfg newDefaultTyperCfg(void) {
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
Typer* newTyper(TyperCfg config) {
    Typer* typer = malloc(sizeof(Typer));
    
    typer->backupCfg = config;
    
    typer->anyType = newType(T_ANY,(union GenericTypeInfo){});
    typer->unitType = newType(T_UNIT,(union GenericTypeInfo){});
    typer->floatType[FLOAT_16] = newType(T_FLOAT,(union GenericTypeInfo){.Float_width=FLOAT_16});
    typer->floatType[FLOAT_32] = newType(T_FLOAT,(union GenericTypeInfo){.Float_width=FLOAT_32});
    typer->floatType[FLOAT_64] = newType(T_FLOAT,(union GenericTypeInfo){.Float_width=FLOAT_64});
    typer->intType[INT_1] = newType(T_INT,(union GenericTypeInfo){.Int_width=INT_1});
    typer->intType[INT_8] = newType(T_INT,(union GenericTypeInfo){.Int_width=INT_8});
    typer->intType[INT_16] = newType(T_INT,(union GenericTypeInfo){.Int_width=INT_16});
    typer->intType[INT_32] = newType(T_INT,(union GenericTypeInfo){.Int_width=INT_32});
    typer->intType[INT_64] = newType(T_INT,(union GenericTypeInfo){.Int_width=INT_64});
    typer->intType[INT_64] = newType(T_INT,(union GenericTypeInfo){.Int_width=INT_64});
    typer->intType[INT_128] = newType(T_INT,(union GenericTypeInfo){.Int_width=INT_128});
    typer->metatypeBuf = newTypeBuf("metatypeBuf", typer->backupCfg.maxMetavarCount);
    typer->ptrTypeBuf = newTypeBuf("ptrTypeBuf", typer->backupCfg.maxPtrCount);
    typer->funcTypeBuf = newTypeBuf("funcTypeBuf", typer->backupCfg.maxFuncCount);
    typer->typefuncTypeBuf = newTypeBuf("typefuncTypeBuf", typer->backupCfg.maxTypefuncCount);
    typer->moduleTypeBuf = newTypeBuf("moduleTypeBuf", typer->backupCfg.maxModuleCount);
    typer->tupleTypeBuf = newTypeBuf("structTypeBuf", typer->backupCfg.maxStructCount);
    typer->unionTypeBuf = newTypeBuf("unionTypeBuf", typer->backupCfg.maxUnionCount);
    
    typer->anyATN = (AdtTrieNode) {NULL,NULL,&typer->anyType,-1,0};
    // todo: singleton structs and tuples / unions == identity operation (!!)
    
    // initializing the subtyping error string to 'clear'; no message:
    typer->subtypingError = NULL;

    return typer;
}
Type newType(TypeKind typeKind, union GenericTypeInfo typeInfo) {
    return (Type) {
        .kind = typeKind,
        .as = typeInfo
    };
}
TypeBuf newTypeBuf(char const* name, size_t capacity) {
    return (TypeBuf) {
        name,
        capacity, 0,
        malloc(capacity * sizeof(Type))
    };
}
Type* tryPushToTypeBuf(TypeBuf* buf) {
    if (buf->count >= buf->capacity) {
        return NULL;
    } else {
        return &buf->ptr[buf->count++];
    }
}
Type* helpPushToTypeBuf(TypeBuf* buf) {
    Type* type = tryPushToTypeBuf(buf);
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
Type* pushToTypeBuf(TypeBuf* buf, TypeKind kind) {
    Type* type = helpPushToTypeBuf(buf);
    type->kind = kind;
    return type;
}

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
AdtTrieNode* getCommonAncestorATN(AdtTrieNode* a, AdtTrieNode* b) {
    if (a == b) {
        return a;
    } else if (a == NULL) {
        return NULL;
    } else if (b == NULL) {
        return NULL;
    } else {
        return getCommonAncestorATN(
            getCommonAncestorATN(a->parent, b),
            getCommonAncestorATN(a, b->parent)
        );
    }
}
int isAncestorATN(AdtTrieNode* parent, AdtTrieNode* child) {
    return getCommonAncestorATN(parent,child) == parent;
}

//
//
//
// Typing constraints:
//
//
//

SubtypingResult readSubtyping(Typer* typer, char const* why, Loc locWhere, Type* super, Type* sub) {
    return helpReadOrWriteSubtyping(typer,why,locWhere,super,sub,1);
}
SubtypingResult writeSubtyping(Typer* typer, char const* why, Loc locWhere, Type* super, Type* sub) {
    return helpReadOrWriteSubtyping(typer,why,locWhere,super,sub,0);
}
SubtypingResult checkDeferredMetavarSubtypings(Typer* typer) {
    // todo: implement checkDeferredMetavarSubtypings

    // for each metavar,
    //   hypothesis = *select* submost supertype (including super metas)
    //   test = *select* supermost subtype (including sub metas)
    //
    //   if hypothesis and test are empty,
    //      error out, not enough info. :/
    //      make an exception for templates?
    //   elif hypothesis is empty,
    //      soln <- test
    //   elif test is empty,
    //      soln <- hypothesis
    //   else
    //     if hypothesis \super-or-equal test,
    //        soln <- hypothesis

    // NOTE:
    // when selecting supertypes/subtypes from a meta,
    // - if meta is solved, just return the solution
    // - else forward super/sub types
    // - beware of forwarding cycles! if cycle detected, terminate without adding unsolved-meta super/sub, since already added.
}

//
// typing constraint helpers (1)
//

SubtypingResult readOrWriteSubtyping(Typer* typer, char const* why, Loc locWhere, Type* super, Type* sub, int readOnly) {
    // clearing the subtyping error:
    resetSubtypingError(typer);

    // attempting to perform the operation:
    SubtypingResult result = helpReadOrWriteSubtyping(typer,why,locWhere,super,sub,readOnly);
    
    // if the operation failed, and we were supposed to write, generating feedback from the subtyping error (must be present).
    char const* subtypingError = getAndResetSubtypingError(typer);
    if (subtypingError) {
        if (!readOnly && result == SUBTYPING_FAILURE) {
            FeedbackNote* note = CreateFeedbackNote("caused here...",locWhere,NULL);
            PostFeedback(
                FBK_ERROR,note,
                "Failed to apply subtyping for %s: %s", why, subtypingError
            );
        }
        free(subtypingError);
    } else {
        if (DEBUG) {
            printf("!!- readOrWriteSubtyping: helper returned SUBTYPING_FAILURE, but subtypingError is NULL.\n");
        } else {
            assert(0 && "readOrWriteSubtyping: helper returned SUBTYPING_FAILURE, but subtypingError is NULL.");
        }
    }
}
SubtypingResult helpReadOrWriteSubtyping(Typer* typer, char const* why, Loc locWhere, Type* super, Type* sub, int readOnly) {
    switch (super->kind)
    {
        case T_INT: { return helpReadOrWriteSubtyping_intSuper(typer,why,locWhere,super,sub,readOnly); }
        case T_FLOAT: { return helpReadOrWriteSubtyping_floatSuper(typer,why,locWhere,super,sub,readOnly); }
        case T_PTR: { return helpReadOrWriteSubtyping_ptrSuper(typer,why,locWhere,super,sub,readOnly); }
        case T_FUNC: { return helpReadOrWriteSubtyping_funcSuper(typer,why,locWhere,super,sub,readOnly); }
        case T_TUPLE: { return helpReadOrWriteSubtyping_tupleSuper(typer,why,locWhere,super,sub,readOnly); }
        case T_UNION: { return helpReadOrWriteSubtyping_unionSuper(typer,why,locWhere,super,sub,readOnly); }
        case T_META: { return helpReadOrWriteSubtyping_metaSuper(typer,why,locWhere,super,sub,readOnly); }
        default:
        {
            if (DEBUG) {
                printf("!!- NotImplemented: helpReadOrWriteSubtyping for super of type kind %s.\n", TypeKindAsText(super->kind));
            } else {
                assert(0 && "NotImplemented: helpReadOrWriteSubtyping for unknown type kind.");
            }
            return SUBTYPING_FAILURE;
        }
    }
}
SubtypingResult helpReadOrWriteSubtyping_intSuper(Typer* typer, char const* why, Loc loc, Type* super, Type* sub, int readOnly) {
    switch (sub->kind)
    {
        case T_INT:
        {
            // A subtypes B <=> width(A) >= width(B)
            if (sub->as.Int_width >= super->as.Int_width) {
                return SUBTYPING_CONFIRM;
            } else {
                int subWidthInBits = GetIntTypeWidthInBits(sub);
                int superWidthInBits = GetIntTypeWidthInBits(super);
                setGenericSubtypingError(typer,"cannot promote subtype Int[%d] to supertype Int[%d]",subWidthInBits,superWidthInBits);
                return SUBTYPING_FAILURE;
            }
        }
        case T_META:
        {
            SuperTypeRec supertypingRec = {loc,super};
            sb_push(sub->as.Meta.supertypeRecSB,supertypingRec);
            return SUBTYPING_DEFERRED;
        }
        default:
        {
            setMismatchedKindsSubtypingError(typer,super,sub);
            return SUBTYPING_FAILURE;
        }
    }
}
SubtypingResult helpReadOrWriteSubtyping_floatSuper(Typer* typer, char const* why, Loc loc, Type* super, Type* sub, int readOnly) {
    switch (sub->kind)
    {
        case T_FLOAT:
        {
            // A subtypes B <=> width(A) >= width(B)
            if (sub->as.Int_width >= super->as.Int_width) {
                return SUBTYPING_CONFIRM;
            } else {
                int subWidthInBits = GetFloatTypeWidthInBits(sub);
                int superWidthInBits = GetFloatTypeWidthInBits(super);
                setGenericSubtypingError(typer,"cannot promote subtype Float[%d] to supertype Float[%d]",subWidthInBits,superWidthInBits);
                return SUBTYPING_FAILURE;
            }
        }
        case T_META:
        {
            SuperTypeRec supertypingRec = {loc,super};
            sb_push(sub->as.Meta.supertypeRecSB,supertypingRec);
            return SUBTYPING_DEFERRED;
        }
        default:
        {
            setMismatchedKindsSubtypingError(typer,super,sub);
            return SUBTYPING_FAILURE;
        }
    }
}
SubtypingResult helpReadOrWriteSubtyping_ptrSuper(Typer* typer, char const* why, Loc loc, Type* super, Type* sub, int readOnly) {
    switch (sub->kind)
    {
        case T_PTR:
        {
            return helpReadOrWriteSubtyping(
                typer,why,loc,
                GetPtrTypePointee(super),GetPtrTypePointee(sub),
                readOnly
            );
        }
        case T_META:
        {
            SuperTypeRec supertypingRec = {loc,super};
            sb_push(sub->as.Meta.supertypeRecSB,supertypingRec);
            return SUBTYPING_DEFERRED;
        }
        default:
        {
            setMismatchedKindsSubtypingError(typer,super,sub);
            return SUBTYPING_FAILURE;
        }
    }
}
SubtypingResult helpReadOrWriteSubtyping_funcSuper(Typer* typer, char const* why, Loc loc, Type* super, Type* sub, int readOnly) {
    switch (sub->kind)
    {
        case T_FUNC:
        {
            // check 1: do arg counts match?
            int superArgCount = GetFuncTypeArgCount(super);
            int subArgCount = GetFuncTypeArgCount(sub);
            if (superArgCount != subArgCount) {
                setGenericSubtypingError(typer,"function argument counts mismatched, got %d for supertype, %d for subtype",superArgCount,subArgCount);
                return SUBTYPING_FAILURE;
            }

            // check 2: is the image (return type) subtyping in error?
            SubtypingResult imageResult = helpReadOrWriteSubtyping(
                typer,
                why,loc,
                GetFuncTypeImage(super),GetFuncTypeImage(sub),
                readOnly
            );
            if (imageResult == SUBTYPING_FAILURE) {
                return SUBTYPING_FAILURE;
            }

            // check 3: are any arg subtypings in error?
            SubtypingResult mergedArgsResult = SUBTYPING_CONFIRM;
            int argCount = superArgCount;
            for (int argIndex = 0; argIndex < argCount; argIndex++) {
                Type* superArg = GetFuncTypeArgAt(super,argIndex);
                Type* subArg = GetFuncTypeArgAt(sub,argIndex);
                mergedArgsResult = mergeSubtypingResults(
                    mergedArgsResult,
                    helpReadOrWriteSubtyping(typer,why,loc,superArg,subArg,readOnly)
                );
            }
            if (mergedArgsResult == SUBTYPING_FAILURE) {
                return SUBTYPING_FAILURE;
            }

            // all checks passed? return result so far, i.e. DEFERRED or CONFIRM:
            return mergeSubtypingResults(imageResult,mergedArgsResult);
        }
        case T_META:
        {
            SuperTypeRec supertypingRec = {loc,super};
            sb_push(sub->as.Meta.supertypeRecSB,supertypingRec);
            return SUBTYPING_DEFERRED;
        }
        default:
        {
            setMismatchedKindsSubtypingError(typer,super,sub);
            return SUBTYPING_FAILURE;
        }
    }
}
SubtypingResult helpReadOrWriteSubtyping_tupleSuper(Typer* typer, char const* why, Loc loc, Type* super, Type* sub, int readOnly) {
    switch (sub->kind) {
        case T_TUPLE:
        {
            if (super->as.Compound_atn == sub->as.Compound_atn) {
                return SUBTYPING_CONFIRM;
            } else {
                AdtTrieNode* superATN = super->as.Compound_atn;
                AdtTrieNode* subATN = sub->as.Compound_atn;
                
                // check 1: are the tuples of the same length?
                if (superATN->depth != subATN->depth) {

                }

                // check 2: helpReadOrWriteSubtyping on each field
                // todo!!!

                return SUBTYPING_FAILURE;
            }
        }
        case T_META:
        {
            SuperTypeRec supertypingRec = {loc,super};
            sb_push(sub->as.Meta.supertypeRecSB,supertypingRec);
            return SUBTYPING_DEFERRED;
        }
        default:
        {
            setMismatchedKindsSubtypingError(typer,super,sub);
            return SUBTYPING_FAILURE;
        }
    }
}
SubtypingResult helpReadOrWriteSubtyping_unionSuper(Typer* typer, char const* why, Loc loc, Type* super, Type* sub, int readOnly) {

}
SubtypingResult helpReadOrWriteSubtyping_metaSuper(Typer* typer, char const* why, Loc loc, Type* meta, Type* sub, int readOnly) {
    // store subtypes, but do not check yet! wait for 'super' to finalize.
    // checks performed later, in 'checkDeferredMetavarSubtypings'
}
SubtypingResult helpReadOrWriteSubtyping_metaSub(Typer* typer, char const* why, Loc loc, Type* meta, Type* super, int readOnly) {
    // store suptypes, but do not solve yet! metavar supertypes may offer better solutions, but should not pre-emptively compare.
    // suptype collection performed later, in 'checkDeferredMetavarSubtypings'
}

//
// typing constraint helpers (2)
//

void resetSubtypingError(Typer* typer) {
    if (typer->subtypingError) {
        free(typer->subtypingError);
        typer->subtypingError = NULL;
    }
}
char const* getAndResetSubtypingError(Typer* typer) {
    char const* message = typer->subtypingError;
    if (message) {
        typer->subtypingError = NULL;
    }
    return message;
}
void setGenericSubtypingError(Typer* typer, char const* format, ...) {
    // only 1 message can be set; all subsequent messages are ignored.
    if (typer->subtypingError == NULL) {
        char buffer[SUBTYPING_ERROR_BUF_SIZE];
        
        va_list args;
        va_start(args,format);
        assert(vsnprintf(buffer,SUBTYPING_ERROR_BUF_SIZE,format,args) < SUBTYPING_ERROR_BUF_SIZE);
        va_end(args);

        typer->subtypingError = strdup(buffer);
    }
}
void setMismatchedKindsSubtypingError(Typer* typer, Type* super, Type* sub) {
    setGenericSubtypingError(
        typer,
        "super kind %s incompatible with sub kind %s",
        TypeKindAsText(super->kind),TypeKindAsText(sub->kind)
    );
}

//
// typing constraint helpers (3)
//

SubtypingResult mergeSubtypingResults(SubtypingResult fst, SubtypingResult snd) {
    if (fst == snd) {
        return fst;
    }
    return (fst > snd ? fst : snd);
}

//
// checking solved-ness
//

int isSolved(Type* type) {
    switch (type->kind)
    {
        // primitives:
        case T_UNIT:
        case T_INT:
        case T_FLOAT:
        {
            return 1;
        }

        // compounds:
        case T_PTR:
        {
            return isSolved(type->as.Ptr_pointee);
        }
        case T_FUNC:
        {
            int imageSolved = isSolved(type->as.Func.image);
            if (imageSolved) {
                for (int argIndex = 0; argIndex < type->as.Func.domainCount; argIndex++) {
                    Type* arg = type->as.Func.domainArray[argIndex];
                    if (!isSolved(arg)) {
                        return 0;
                    }
                }
                return 1;
            } else {
                return 0;
            }
        }
        case T_TUPLE:
        case T_UNION:
        {
            for (AdtTrieNode* atn = type->as.Compound_atn; atn->parent; atn = atn->parent) {
                AdtTrieEdge edge = atn->parent->edgesSb[atn->parentEdgeIndex];
                if (!isSolved(edge.type)) {
                    return 0;
                }
            }
            return 1;
        }
        
        // metavar:
        case T_META:
        {
            return type->as.Meta.soln != NULL;
        }

        default:
        {
            if (DEBUG) {
                printf("!!- Unknown type kind in `isSolved`: %s\n", TypeKindAsText(type->kind));
            } else {
                assert(0 && "Unknown type kind in `isSolved`");
            }
            return 0;
        }
    }
}

//
// Typer:
//

int typer_post(void* rawTyper, AstNode* node) {
    Typer* typer = rawTyper;
    Loc nodeLoc = GetAstNodeLoc(node);
    AstKind nodeKind = GetAstNodeKind(node);
    switch (nodeKind) {
        case AST_UNIT:
        {
            Type* t = NewOrGetUnitType(typer);
            SetSingleAstNodeTypingExtV(node,t);
            break;
        }
        case AST_LITERAL_INT:
        {
            size_t value = GetAstIntLiteralValue(node);
            Type* type;
            if (value < (1u << 8)) {
                type = NewOrGetIntType(typer,INT_8);
            } else if (value < (1u << 16)) {
                type = NewOrGetIntType(typer,INT_16);
            } else if (value < (1u << 32)) {
                type = NewOrGetIntType(typer,INT_32);
            } else {
                type = NewOrGetIntType(typer,INT_64);
            }
            SetSingleAstNodeTypingExtV(node,type);
            break;
        }
        case AST_LITERAL_FLOAT:
        {
            Type* t = NewOrGetFloatType(typer, FLOAT_32);
            SetSingleAstNodeTypingExtV(node,t);
            break;
        }
        case AST_VID:
        case AST_TID:
        {
            Loc loc = GetAstNodeLoc(node);
            SymbolID name = GetAstIdName(node);
            Scope* scope = GetAstIdLookupScope(node);
            AstContext lookupContext = GetAstNodeLookupContext(node);
            Defn* foundDefn = LookupSymbol(scope, name, lookupContext);
            if (foundDefn == NULL) {
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
                SetSingleAstNodeTypingExtT(node,foundType);
            } else if (lookupContext == ASTCTX_VALUE) {
                SetSingleAstNodeTypingExtV(node,foundType);
            } else {
                if (DEBUG) {
                    printf("!!- Invalid lookup context while typing AST_?ID.\n");
                } else {
                    assert(0 && "Invalid lookup context while typing in AST_?ID.\n");
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
            Type* lhsValueType = GetSingleAstNodeTypingExtV(node);
            Type* rhsType = GetSingleAstNodeTypingExtV(GetAstLetStmtRhs(node));
            if (lhsValueType && rhsType) {
                requireSubtype(GetAstNodeLoc(node), rhsType, lhsValueType);
            }
            break;
        }
        case AST_LAMBDA:
        {
            int argsCount;
            Type** argsTypes = GetArrayAstNodeTypingExtV(GetAstLambdaPattern(node),&argsCount);
            Type* rhsType = GetSingleAstNodeTypingExtV(GetAstLambdaBody(node));
            if (rhsType) {
                SetSingleAstNodeTypingExtV(node, NewOrGetFuncType(typer, argsCount, argsTypes, rhsType));
            }
            break;
        }
        case AST_DEF_VALUE:
        {
            // module items can be used in value and typing contexts
            // todo: make these types the results of Typefunc instances
            Loc loc = GetAstNodeLoc(node);
            Type* definedValueType = GetSingleAstNodeTypingExtV(node);
            Type* definedTypingType = GetSingleAstNodeTypingExtT(node);
            
            AstNode* desugaredRhs = GetAstDefStmtRhs(node);
            Type* desugaredRhsType = GetSingleAstNodeTypingExtV(desugaredRhs);

            AstNode* rhs = GetAstDefStmtRhs(node);
            Type* rhsType = GetSingleAstNodeTypingExtV(rhs);

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
            Type* fieldType = GetSingleAstNodeTypingExtV(node);
            if (rhs && fieldType) {
                Loc loc = GetAstNodeLoc(node);

                Type* rhsValueType = GetSingleAstNodeTypingExtV(rhs);
                if (rhsValueType) {
                    requireSubtype(loc, rhsValueType, fieldType);
                }

                Type* rhsTypingType = GetSingleAstNodeTypingExtT(rhs);
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
                tv = GetSingleAstNodeTypingExtV(rhs);
            } else {
                SymbolID name = GetAstFieldName(node);
                char const* nameText = GetSymbolText(name);
                tv = NewMetavarType(loc, typer, "field:%s", nameText);
            }
            SetSingleAstNodeTypingExtV(node,tv);
            break;
        }
        case AST_V_PATTERN:
        {
            // todo: update with an array for multiple items
            if (DEBUG) {
                printf("!!- NotImplemented: typing AST_V_PATTERN\n");
            } else {
                assert(0 && "NotImplemented: typing AST_V_PATTERN.");
            }

            // int patternCount = GetAstPatternLength(node);
            // Type* type = NULL;
            // if (patternCount == 0) {
            //     type = GetUnitType(typer);
            // } else if (patternCount == 1) {
            //     type = GetSingleAstNodeTypingExtV(GetAstPatternFieldAt(node,0));
            // } else {
            //     InputTypeFieldList* lastInputFieldList = NULL;
            //     for (int index = patternCount-1; index >= 0; index--) {
            //         AstNode* field = GetAstPatternFieldAt(node,index);
                    
            //         InputTypeFieldNode* node = malloc(sizeof(InputTypeFieldNode));
            //         node->name = GetAstFieldName(field);
            //         node->next = lastInputFieldList;
            //         node->type = GetSingleAstNodeTypingExtT(GetAstFieldRhs(field));
            //         lastInputFieldList = node;
            //     }
            //     InputTypeFieldList* firstITF = lastInputFieldList;
            //     type = GetTupleType(typer,lastInputFieldList);

            //     // todo: de-allocate ITF list.
            // }

            // int typeNotValueContext = (nodeKind == AST_T_PATTERN);
            // if (typeNotValueContext) {
            //     SetSingleAstNodeTypingExtT(node, type);
            // } else {
            //     SetSingleAstNodeTypingExtV(node, type);
            // }
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
                typingITF->type = GetSingleAstNodeTypingExtV(field);
                typingITF->next = inputTypeFieldHead;
                inputTypeFieldHead = typingITF;
            }
            Type* tuple = NewOrGetTupleType(typer, inputTypeFieldHead);
            SetSingleAstNodeTypingExtV(node,tuple);
            break;
        }
        case AST_VTUPLE:
        {
            InputTypeFieldNode* inputTypeFieldHead = NULL;
            int tupleCount = GetAstTupleLength(node);
            for (int index = tupleCount-1; index >= 0; index--) {
                AstNode* field = GetAstTupleItemAt(node, index);
                SymbolID fieldName = GetAstFieldName(field);
                InputTypeFieldNode* typingITF = malloc(sizeof(InputTypeFieldNode));
                typingITF->name = fieldName;
                typingITF->type = GetSingleAstNodeTypingExtV(field);
                typingITF->next = inputTypeFieldHead;
                inputTypeFieldHead = typingITF;
            }
            SetSingleAstNodeTypingExtV(node, NewOrGetTupleType(typer, inputTypeFieldHead));
            break;
        }
        case AST_CHAIN:
        {
            AstNode* result = GetAstChainResult(node);
            if (result) {
                SetSingleAstNodeTypingExtV(node, GetSingleAstNodeTypingExtV(result));
            } else {
                SetSingleAstNodeTypingExtV(node, NewOrGetUnitType(typer));
            }
            break;
        }
        case AST_UNARY:
        {
            AstUnaryOperator operator = GetAstUnaryOperator(node);
            AstNode* arg = GetAstUnaryOperand(node);
            Type* argType = GetSingleAstNodeTypingExtV(arg);
            Type* type = GetUnaryIntrinsicType(typer,nodeLoc,operator,argType);
            SetSingleAstNodeTypingExtV(node,type);
            break;
        }
        case AST_BINARY:
        {
            AstBinaryOperator binop = GetAstBinaryOperator(node);
            AstNode* ltArg = GetAstBinaryLtOperand(node);
            AstNode* rtArg = GetAstBinaryRtOperand(node);
            Type* ltArgType = GetSingleAstNodeTypingExtV(ltArg);
            Type* rtArgType = GetSingleAstNodeTypingExtV(rtArg);
            Type* type = GetBinaryIntrinsicType(typer,nodeLoc,binop,ltArgType,rtArgType);
            SetSingleAstNodeTypingExtV(node,type);
            break;
        }
        case AST_ITE:
        {
            AstNode* cond = GetAstIteCond(node);
            AstNode* ifTrue = GetAstIteIfTrue(node);
            AstNode* ifFalse = GetAstIteIfFalse(node);
            Type* condType = GetSingleAstNodeTypingExtV(cond);
            Type* ifTrueType = GetSingleAstNodeTypingExtV(ifTrue);
            Type* ifFalseType = ifFalse ? GetSingleAstNodeTypingExtV(ifFalse) : NewOrGetUnitType(typer);
            Type* type = GetPhiType(typer,nodeLoc,condType,ifTrueType,ifFalseType);
            SetSingleAstNodeTypingExtV(node,type);
            break;
        }
        case AST_VCALL:
        {
            Loc loc = GetAstNodeLoc(node);

            AstNode* lhs = GetAstCallLhs(node);
            int argsCount = GetAstCallArgCount(node);
            Type** argsTypes = malloc(argsCount*sizeof(Type*)); {
                for (int argIndex = 0; argIndex < argsCount; argIndex++) {
                    AstNode* argNode = GetAstCallArgAt(node,argIndex);
                    argsTypes[argIndex] = GetSingleAstNodeTypingExtV(argNode);
                }
            }
            Type* retType = NewMetavarType(loc, typer, "in-ret");
            
            Type* actualFuncType = NewOrGetFuncType(typer, argsCount, argsTypes, retType);
            requireSubtype(loc, GetSingleAstNodeTypingExtV(lhs), actualFuncType);
            
            SetSingleAstNodeTypingExtV(node,retType);
            break;
        }
        case AST_TCALL:
        {
            if (DEBUG) {
                printf("!!- NotImplemented: typing AST_T_CALL\n");
            } else {
                assert(0 && "NotImplemented: typing AST_T_CALL");
            }
            break;
        }
        case AST_VPAREN:
        {
            AstNode* itNode = GetAstParenItem(node);
            Type* itType = GetSingleAstNodeTypingExtV(itNode);
            SetSingleAstNodeTypingExtV(node,itType);
            break;
        }
        case AST_DEF_TYPE:
        {
            Loc loc = GetAstNodeLoc(node);
            AstNode* optRhs = GetAstTypedefStmtOptRhs(node);
            if (optRhs) {
                AstNode* rhs = optRhs;
                Type* rhsType = GetSingleAstNodeTypingExtT(rhs);
                Type* metavarType = GetSingleAstNodeTypingExtT(node);

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
            Type* typespecType = GetSingleAstNodeTypingExtT(typespec);
            
            Type* defType = GetSingleAstNodeTypingExtV(node);

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

void mapCompoundType(Typer* typer, AdtTrieNode* compoundATN, FieldCB cb, void* context) {
    if (compoundATN != NULL && compoundATN != &typer->anyATN) {
        mapCompoundType(typer, compoundATN->parent, cb, context);
        AdtTrieNode* node = compoundATN;
        AdtTrieEdge* edge = &node->parent->edgesSb[node->parentEdgeIndex];
        cb(typer,context,edge->name,edge->type);
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
            printf("func");
            int domainSize = type->as.Func.domainCount;
            for (int index = 0; index < domainSize; index++) {
                printf(" ");
                printType(typer, type->as.Func.domainArray[index]);
            }
            printf(" -> ");
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
            int atnDepth = GetTupleTypeFieldCount(type);
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
            int atnDepth = GetTupleTypeFieldCount(type);
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

Type* getConcreteType__deprecated(Typer* typer, Type* visitedType, Type*** visitedSBP) {
    if (visitedType == NULL) {
        return NULL;
    }

    int visitedCount = sb_count((*visitedSBP));
    for (int index = 0; index < visitedCount; index++) {
        Type* oldVisited = (*visitedSBP)[index];
        if (visitedType == oldVisited) {
            // todo: cycle encountered, return the metavar itself/do something
            if (DEBUG) {
                printf("!!- Cycle encountered in `getConcreteType`, returning NULL.\n");
            }
            // todo: return soln here.
            return NULL;
        }
    }
    sb_push((*visitedSBP), visitedType);

    Type* type = visitedType;
    switch (type->kind) {
        case T_META:
        {
            return type->as.Meta.soln;
        }
        case T_PTR:
        {
            return NewOrGetPtrType(typer,getConcreteType__deprecated(typer,GetPtrTypePointee(type),visitedSBP));
        }
        case T_TUPLE:
        case T_UNION:
        {
            InputTypeFieldList* itfListHead = NULL;
            for (AdtTrieNode* atn = type->as.Compound_atn; atn->parent; atn = atn->parent) {
                AdtTrieEdge edge = atn->parent->edgesSb[atn->parentEdgeIndex];
 
                // creating a replacement head:
                InputTypeFieldNode* newHead = malloc(sizeof(InputTypeFieldNode));
                newHead->name = edge.name;
                newHead->type = getConcreteType__deprecated(typer,edge.type,visitedSBP);
                newHead->next = itfListHead;

                // updating head:
                itfListHead = newHead;
            }
            if (type->kind == T_TUPLE) {
                return NewOrGetTupleType(typer,itfListHead);
            } else {
                assert(type->kind == T_UNION);
                return NewOrGetUnionType(typer,itfListHead);
            }
        }
        case T_UNIT:
        case T_INT:
        case T_FLOAT:
        {
            return type;
        }
        case T_FUNC:
        {
            int argCount = type->as.Func.domainCount;
            Type** concreteArgTypes = malloc(sizeof(AstNode*)*argCount);
            for (int argIndex = 0; argIndex < argCount; argIndex++) {
                concreteArgTypes[argIndex] = getConcreteType__deprecated(typer,type->as.Func.domainArray[argIndex],visitedSBP);
            }
            Type* imageType = getConcreteType__deprecated(typer,GetFuncTypeImage(type),visitedSBP);
            Type* funcType = NewOrGetFuncType(typer,argCount,concreteArgTypes,imageType);
            free(concreteArgTypes); concreteArgTypes = NULL;
            return funcType;
        }
        default:
        {
            if (DEBUG) {
                printf("!!- NotImplemented: GetConcreteType for type kind %s\n", TypeKindAsText(type->kind));
            } else {
                assert(0 && "NotImplemented: GetConcreteType for unknown type kind.");
            }
            return NULL;
        }
    }
}

//
//
//
// API:
//
//
//

TyperCfg NewDefaultTyperCfg(void) {
    return newDefaultTyperCfg();
}
Typer* NewTyper(TyperCfg config) {
    return newTyper(config);
}

//
// Constructors:
//

Type* NewOrGetUnitType(Typer* typer) {
    return &typer->unitType;
}
Type* NewOrGetIntType(Typer* typer, IntWidth width) {
    return &typer->intType[width];
}
Type* NewOrGetFloatType(Typer* typer, FloatWidth width) {
    return &typer->floatType[width];
}
Type* NewOrGetPtrType(Typer* typer, Type* pointee) {
    // searching for an existing, structurally equivalent type:
    for (size_t index = 0; index < typer->ptrTypeBuf.count; index++) {
        Type* cmpType = &typer->ptrTypeBuf.ptr[index];
        if (cmpType->as.Ptr_pointee == pointee) {
            return cmpType;
        }
    }
    // allocating and a new type:
    Type* ptrType = pushToTypeBuf(&typer->ptrTypeBuf,T_PTR);
    ptrType->as.Ptr_pointee = pointee;
    return ptrType;
}
Type* NewOrGetFuncType(Typer* typer, int argsCount, Type* args[], Type* image) {
    // searching for an existing, structurally equivalent type:
    for (size_t index = 0; index < typer->funcTypeBuf.count; index++) {
        FuncInfo existingFuncInfo = typer->funcTypeBuf.ptr[index].as.Func;
        int existingCount = existingFuncInfo.domainCount;
        int argCountMatch = (existingCount == argsCount);
        int imageMatch = (existingFuncInfo.image == image);
        if (argCountMatch && imageMatch) {
            int allArgsMatch = 1;
            for (int argIndex = 0; argIndex < argsCount; argIndex++) {
                if (existingFuncInfo.domainArray[argIndex] != args[argIndex]) {
                    allArgsMatch = 0;
                    break;
                }
            }
            if (allArgsMatch) {
                // match found.
                return &typer->funcTypeBuf.ptr[index];
            }
        }
    }
    // match not found, so allocating a new type:
    Type* funcType = pushToTypeBuf(&typer->ptrTypeBuf,T_FUNC);
    funcType->as.Func.domainCount = argsCount;
    funcType->as.Func.domainArray = malloc(argsCount*sizeof(Type*));
    memcpy(funcType->as.Func.domainArray,args,argsCount*sizeof(Type*));
    funcType->as.Func.image = image;
    return funcType;
}
Type* NewOrGetTypefuncType(Typer* typer, Type* arg, Type* body) {
    // todo: consider de-duplicating typefuncs?
    Type* typefuncType = pushToTypeBuf(&typer->typefuncTypeBuf,T_TYPEFUNC);
    typefuncType->as.Typefunc.arg = arg;
    typefuncType->as.Typefunc.body = body;
    return typefuncType;
}
Type* NewOrGetTupleType(Typer* typer, InputTypeFieldList const* inputFieldList) {
    Type* tupleType = pushToTypeBuf(&typer->tupleTypeBuf,T_TUPLE);
    tupleType->as.Compound_atn = getAtnChild(&typer->anyATN, ADT_MUL, inputFieldList, 0);
    tupleType->as.Compound_atn->owner = tupleType;
    return tupleType;
}
Type* NewOrGetUnionType(Typer* typer, InputTypeFieldList const* inputFieldList) {
    Type* unionType = pushToTypeBuf(&typer->unionTypeBuf,T_UNION);
    unionType->as.Compound_atn = getAtnChild(&typer->anyATN, ADT_SUM, inputFieldList, 0);
    unionType->as.Compound_atn->owner = unionType;
    return unionType;
}
Type* NewMetavarType(Loc loc, Typer* typer, char const* format, ...) {
    Type* metatype = pushToTypeBuf(&typer->metatypeBuf,T_META);
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
    metatype->as.Meta.subtypeRecSB = NULL;
    metatype->as.Meta.supertypeRecSB = NULL;
    return metatype;
}

//
// Getters:
//

TypeKind GetTypeKind(Type* type) {
    return type->kind;
}
IntWidth GetIntTypeWidth(Type* type) {
    if (type) {
        if (type->kind == T_INT) {
            return type->as.Int_width;
        } else if (type->kind == T_META) {
            return GetIntTypeWidth(type);
        }
    }
    return __INT_NONE;
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
    return __FLOAT_NONE;
}
int GetFloatTypeWidthInBits(Type* type) {
    assert(type->kind == T_FLOAT);
    switch (type->as.Float_width)
    {
        case FLOAT_16: return 16;
        case FLOAT_32: return 32;
        case FLOAT_64: return 64;
        default: return 0;
    }
}
Type* GetPtrTypePointee(Type* type) {
    return type->as.Ptr_pointee;
}
int GetFuncTypeArgCount(Type* func) {
    return func->as.Func.domainCount;
}
Type* GetFuncTypeArgArray(Type* func) {
    return func->as.Func.domainArray;
}
Type* GetFuncTypeArgAt(Type* func, int index) {
    return func->as.Func.domainArray[index];
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
int GetTupleTypeFieldCount(Type* type) {
    if (type != NULL) {
        if (type->kind == T_TUPLE) {
            return type->as.Compound_atn->depth;
        } else if (type->kind == T_META) {
            return GetTupleTypeFieldCount(type->as.Meta.soln);
        }
    }
    if (DEBUG) {
        printf("!!- GetTupleTypeLength called on an invalid type.\n");
    } else {
        assert(0 && "GetFuncTypeDomain called on an invalid type.");
    }
    return -1;
}
int GetUnionTypeFieldCount(Type* type) {
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
// Recursively visits, calling 'applySubtyping'
// 'applySubtyping' updates types
//

void TypeNode(Typer* typer, AstNode* node) {
    RecursivelyVisitAstNode(typer, node, NULL, typer_post);
}

//
// Type checker:
//

int CheckTyper(Typer* typer) {
    return checkTyper(typer);
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

//
// Debug:
//

void PrintTyper(Typer* typer) {
    printTyper(typer);
}

//
// Reflection:
//

char const* TypeKindAsText(TypeKind typeKind) {
    switch (typeKind) {
        case T_ANY: return "T_ANY";
        case T_UNIT: return "T_UNIT";
        case T_INT: return "T_INT";
        case T_FLOAT: return "T_FLOAT";
        case T_PTR: return "T_PTR";
        case T_FUNC: return "T_FUNC";
        case T_TUPLE: return "T_TUPLE";
        case T_UNION: return "T_UNION";
        case T_TYPEFUNC: return "T_TYPEFUNC";
        case T_MODULE: return "T_MODULE";
        case T_META: return "T_META";
        default: return "<?>";
    }
}
