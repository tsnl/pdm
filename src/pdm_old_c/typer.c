#include "typer.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "stb/stretchy_buffer.h"

#include "useful.h"
#include "config.h"
#include "primer.h"
#include "symbols.h"

// each 'Type' instance is a tagged union.
// - unit is unique and a universal subtype.
// - integers,floats are unique, referenced by width.
// - any,tuples,unions are stored in a Trie, where each node is a unique type.
// - pointers,funcs,etc. are called 'compounds' and contain references to other types.
// - metatypes contain iteratively updated solutions. Upon applying each new typing relationship, the 'soln' property is updated.
// * we work hard to ensure ptr1==ptr2<=>t1==t2 uniqueness (except for metatypes)

// A 'typer' models a GRAPH of types whose EDGES ARE SUBTYPING RELATIONS.
// The goal is to provide a CONCRETE SOLUTION for each METAVAR.

// STEP 1: REQUEST SUBTYPING RELATIONS
// used to set up the system.
// see: 'requireSubtyping'
// - CONCRETE := primitive, or compound of primitives, or compound of concretes
// - METAVAR/ABSTRACT := a 'hole' to be replaced by a CONCRETE.
// - edges are first added by the `requireSubtype` function
//   - both non-metavar endpoints => check relation
//     - if compound, recursively apply relation on compound items!
//     - compound items may be metavars, so T_FUNC may not be concrete.
//   - one or more metavar endpoints => DEFER, i.e. store in SBs for later
//   * WARNING: do not use unfinished solutions instead of deferring
//   * WARNING: beware deferral cycles

// STEP 2: SOLVE ALL METAVARS
// - each metavar is lazily checked
//   - each metavar soln starts as NULL.
//   - if sup/sub checks are OK, 'soln' is stored and the metavar 'becomes' concrete
// - metavar may have 'numericOnly'
//   - means metavar soln must further be int or float
//   - primitive polymorphism for few supported datatypes
//   - can later be expanded to include structs of ints/floats
//   * each unary/binary intrinsic can use ONE metavar to perform typing.

// the 'typer' function applies all program typing constraints in one pass.

#define SUBTYPING_ERROR_BUF_SIZE (256)

typedef union GenericTypeInfo GenericTypeInfo;

typedef enum AdtOperator AdtOperator;
typedef struct AdtTrieNode AdtTrieNode;
typedef struct AdtTrieEdge AdtTrieEdge;

typedef struct TypeBuf TypeBuf;

typedef struct IntInfo IntInfo;
typedef struct MetaInfo MetaInfo;
typedef struct MetaInfoExt MetaInfoExt;
typedef struct FuncInfo FuncInfo;
typedef struct CastInfo CastInfo;
typedef struct TypefuncInfo TypefuncInfo;
typedef struct ModuleInfo ModuleInfo;
typedef struct UnaryInfo UnaryInfo;
typedef struct BinaryInfo BinaryInfo;
// typedef struct IntrinsicInfo IntrinsicInfo;
// typedef struct PhiInfo PhiInfo;

typedef struct SubOrSuperTypeRec SubOrSuperTypeRec;
typedef SubOrSuperTypeRec SubtypeRec;
typedef SubOrSuperTypeRec SupertypeRec;
typedef enum TypingResult TypingResult;

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

struct IntInfo {
    IntWidth width;
    int isSigned;
};
struct MetaInfo {
    Type* soln;
    char* name;
    MetaInfoExt* ext;
    int poisoned;
};
struct MetaInfoExt {
    Loc createdLoc;
    SubtypeRec* deferredSubSB;
    SupertypeRec* deferredSuperSB;
    int solnUpdatedThisPass;
    int numericOnly;
};
struct FuncInfo {
    Type** domainArray;
    Type* image;
    int domainCount;
};
struct CastInfo {
    Type* to;
    Type* from;
    int checkStatus;
};
struct TypefuncInfo {
    Type* arg;
    Type* body;
};
struct ModuleInfo {
    AstNode* node;
};
struct UnaryInfo {
    Type* soln;
    AstUnaryOperator op;
    Type* argType;
};
struct BinaryInfo {
    Type* soln;
    AstBinaryOperator op;
    Type* lhsType;
    Type* rhsType;
};
union GenericTypeInfo {
    IntInfo Int;
    FloatWidth Float_width;
    Type* Ptr_pointee;
    Type* Slice_element;
    MetaInfo Meta;
    FuncInfo Func;
    TypefuncInfo Typefunc;
    ModuleInfo Module;
    AdtTrieNode* Compound_atn;
    CastInfo Cast;
    UnaryInfo Unary;
    BinaryInfo Binary;
};
struct Type {
    TypeKind kind;
    union GenericTypeInfo as;
};

struct Manager {
    ManagerCfg backupCfg;

    Type anyType;
    Type unitType;
    Type stringType;
    Type unsignedIntType[__INT_COUNT];
    Type signedIntType[__INT_COUNT];
    Type floatType[__FLOAT_COUNT];
    
    TypeBuf metatypeBuf;
    MetaInfoExt* metatypeExtBuf;

    TypeBuf ptrTypeBuf;
    TypeBuf sliceTypeBuf;
    TypeBuf typefuncTypeBuf;
    TypeBuf funcTypeBuf;
    TypeBuf moduleTypeBuf;
    TypeBuf tupleTypeBuf;
    TypeBuf unionTypeBuf;
    TypeBuf unaryTypeBuf;
    TypeBuf binaryTypeBuf;
    TypeBuf miscTypeBuf;

    AdtTrieNode anyATN;

    char* subtypingError;
};

struct SubOrSuperTypeRec {
    char const* why;
    Loc loc;
    Type* ptr;
};
enum TypingResult {
    // note: while merging results, we select the min. See `mergeSubtypingResults`.
    TYPING_FAILURE = 0,
    TYPING_DEFERRED,
    TYPING_CONFIRM,
};

//
// Functions:
//

// typer creation:
static ManagerCfg newDefaultManagerCfg(void);
static Manager* newManager(ManagerCfg config);

// type creation:
inline static Type newType(TypeKind typeKind, union GenericTypeInfo typeInfo);
static TypeBuf newTypeBuf(char const* name, size_t capacity);
static Type* tryPushToTypeBuf(TypeBuf* buf);
static Type* helpPushToTypeBuf(TypeBuf* buf);
Type* pushToTypeBuf(TypeBuf* buf, TypeKind kind);

// ATNs: a way to track compounds:
static AdtTrieNode* newATN(AdtTrieNode* parent, Type* owner);
static AdtTrieNode* getAtnChild(AdtTrieNode* root, AdtOperator operator, TypeField* typefields, int typefieldCount, int index, int noNewEdges);
// static AdtTrieNode* getCommonAncestorATN(AdtTrieNode* a, AdtTrieNode* b);
// static int isAncestorATN(AdtTrieNode* parent, AdtTrieNode* child);

// typing constraints:
// 1. we attempt to eagerly check typing constraints (CONFIRM/FAILURE), but
// 2. if the result depends on a metavar, we return FAILURE if (noDeferral) else DEFERRED
// 3. after typing (no more solution possible), call 'solveDeferredMetavars' 
// usage:
// - call 'requireMetavarIsNumericOnly' to assert T is an int or float ONLY
// - call 'requireSubtyping' to assert that A sup B, thereby modifying the system.
static void requireMetavarIsNumericOnly(Type* type);
static TypingResult checkSubtyping(Manager* typer, char const* why, Loc locWhere, Type* super, Type* sub);
static TypingResult requireSubtyping(Manager* typer, char const* why, Loc locWhere, Type* super, Type* sub);
static int solveAndCheckAllMetavars(Manager* typer);
// helpers (1)...
static TypingResult helpSubtypeOp(Manager* typer, char const* why, Loc locWhere, Type* super, Type* sub, int noDeferral);
static TypingResult helpSubtypeOp_unitSuper(Manager* typer,char const* why,Loc loc, Type* super, Type* sub, int noDeferral);
static TypingResult helpSubtypeOp_stringSuper(Manager* typer,char const* why,Loc loc, Type* super, Type* sub, int noDeferral);
static TypingResult helpSubtypeOp_intSuper(Manager* typer, char const* why, Loc loc, Type* super, Type* sub, int noDeferral);
static TypingResult helpSubtypeOp_floatSuper(Manager* typer, char const* why, Loc loc, Type* super, Type* sub, int noDeferral);
static TypingResult helpSubtypeOp_ptrSuper(Manager* typer, char const* why, Loc loc, Type* super, Type* sub, int noDeferral);
static TypingResult helpSubtypeOp_funcSuper(Manager* typer, char const* why, Loc loc, Type* super, Type* sub, int noDeferral);
static TypingResult helpSubtypeOp_tupleSuper(Manager* typer, char const* why, Loc loc, Type* super, Type* sub, int noDeferral);
static TypingResult helpSubtypeOp_unionSuper(Manager* typer, char const* why, Loc loc, Type* super, Type* sub, int noDeferral);
static TypingResult helpSubtypeOp_castSuper(Manager* typer, char const* why, Loc loc, Type* super, Type* sub, int noDeferral);
static TypingResult helpSubtypeOp_metaSuper(Manager* typer, char const* why, Loc loc, Type* meta, Type* sub, int noDeferral);
static TypingResult helpRequestSubtyping_genericMetaSub(Manager* typer, char const* why, Loc loc, Type* super, Type* metaSub, int noDeferral);
static TypingResult mergeSubtypingResults(TypingResult fst, TypingResult snd);
// helpers (2)...
static Type* getConcreteSoln(Manager* typer, Type* type, Type*** visitedMetavarSBP);
// helpers (3)...
static void resetSubtypingError(Manager* typer);
static char* getAndResetSubtypingError(Manager* typer);
static void setGenericSubtypingError(Manager* typer, char const* format, ...);
static void setMismatchedKindsSubtypingError(Manager* typer, Type* sup, Type* sub);
// helpers (4)
static int addTypeToSBSetP(Type*** sbp, Type* type);

// THE typer callback:
static int typer_post(void* rawManager, AstNode* node);

// compound field traversal:
static void mapCompoundType(Manager* typer, AdtTrieNode* compound, FieldCB cb, void* sb);
static void accumulateCompoundFieldSizeSum(Manager* typer, void* sumP, SymbolID name, Type* type);
static void accumulateCompoundFieldSizeMax(Manager* typer, void* maxP, SymbolID name, Type* type);

// printing:
static void printManager(Manager* typer, int metaOnly);
static void printType(Manager* typer, Type* type);
static void printTypeLn(Manager* typer, Type* type);

// deprecated:
// static Type* getConcreteType__deprecated(Manager* typer, Type* visited, Type*** visitedSBP);

//
//
// Implementations:
//
//

ManagerCfg newDefaultManagerCfg(void) {
    int const chunkSize = MAX_AST_NODE_COUNT / 8;
    return (ManagerCfg) {
        .maxMetavarCount = chunkSize,
        .maxPtrCount = chunkSize,
        .maxSliceCount = chunkSize,
        .maxTypefuncCount = chunkSize,
        .maxFuncCount = chunkSize,
        .maxModuleCount = chunkSize,
        .maxStructCount = chunkSize,
        .maxUnionCount = chunkSize,
        .maxMiscCount = chunkSize,
        .maxUnaryIntrinsicCount = chunkSize,
        .maxBinaryIntrinsicCount = chunkSize,
        .maxPhiCount = chunkSize
    };
}
Manager* newManager(ManagerCfg config) {
    Manager* typer = malloc(sizeof(Manager));
    
    typer->backupCfg = config;
    
    typer->anyType = newType(T_ANY,(union GenericTypeInfo){});
    
    typer->unitType = newType(T_UNIT,(union GenericTypeInfo){});
    
    typer->stringType = newType(T_STRING,(union GenericTypeInfo){});

    typer->floatType[FLOAT_16] = newType(T_FLOAT,(union GenericTypeInfo){.Float_width=FLOAT_16});
    typer->floatType[FLOAT_32] = newType(T_FLOAT,(union GenericTypeInfo){.Float_width=FLOAT_32});
    typer->floatType[FLOAT_64] = newType(T_FLOAT,(union GenericTypeInfo){.Float_width=FLOAT_64});

    typer->unsignedIntType[INT_1] = newType(T_INT,(union GenericTypeInfo){.Int={.width=INT_1,.isSigned=0}});
    typer->unsignedIntType[INT_8] = newType(T_INT,(union GenericTypeInfo){.Int={.width=INT_8,.isSigned=0}});
    typer->unsignedIntType[INT_16] = newType(T_INT,(union GenericTypeInfo){.Int={.width=INT_16,.isSigned=0}});
    typer->unsignedIntType[INT_32] = newType(T_INT,(union GenericTypeInfo){.Int={.width=INT_32,.isSigned=0}});
    typer->unsignedIntType[INT_64] = newType(T_INT,(union GenericTypeInfo){.Int={.width=INT_64,.isSigned=0}});
    typer->unsignedIntType[INT_128] = newType(T_INT,(union GenericTypeInfo){.Int={.width=INT_128,.isSigned=0}});
    
    typer->signedIntType[INT_8] = newType(T_INT,(union GenericTypeInfo){.Int={.width=INT_8,.isSigned=1}});
    typer->signedIntType[INT_16] = newType(T_INT,(union GenericTypeInfo){.Int={.width=INT_16,.isSigned=1}});
    typer->signedIntType[INT_32] = newType(T_INT,(union GenericTypeInfo){.Int={.width=INT_32,.isSigned=1}});
    typer->signedIntType[INT_64] = newType(T_INT,(union GenericTypeInfo){.Int={.width=INT_64,.isSigned=1}});
    typer->signedIntType[INT_128] = newType(T_INT,(union GenericTypeInfo){.Int={.width=INT_128,.isSigned=1}});
    
    typer->metatypeBuf = newTypeBuf("metatypeBuf", typer->backupCfg.maxMetavarCount);
    typer->metatypeExtBuf = malloc(sizeof(MetaInfoExt) * typer->backupCfg.maxMetavarCount);
    
    typer->ptrTypeBuf = newTypeBuf("ptrTypeBuf", typer->backupCfg.maxPtrCount);
    typer->sliceTypeBuf = newTypeBuf("sliceTypeBuf", typer->backupCfg.maxSliceCount);
    typer->funcTypeBuf = newTypeBuf("funcTypeBuf", typer->backupCfg.maxFuncCount);
    typer->typefuncTypeBuf = newTypeBuf("typefuncTypeBuf", typer->backupCfg.maxTypefuncCount);
    typer->moduleTypeBuf = newTypeBuf("moduleTypeBuf", typer->backupCfg.maxModuleCount);
    typer->tupleTypeBuf = newTypeBuf("structTypeBuf", typer->backupCfg.maxStructCount);
    typer->unionTypeBuf = newTypeBuf("unionTypeBuf", typer->backupCfg.maxUnionCount);
    typer->miscTypeBuf = newTypeBuf("miscTypeBuf", typer->backupCfg.maxMiscCount);

    typer->anyATN = (AdtTrieNode) {NULL,NULL,&typer->anyType,-1,0};
    
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
AdtTrieNode* getAtnChild(AdtTrieNode* parent, AdtOperator operator, TypeField* typefields, int typefieldCount, int index, int noNewEdges) {
    if (index >= typefieldCount) {
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
            int nameMatch = (typefields[index].name == edge.name);
            int typeMatch = 0;
            if (typefields[index].type != NULL) {
                typeMatch = (typefields[index].type == edge.type);
            }
            if (operatorMatch && nameMatch && typeMatch) {
                return getAtnChild(
                    child,operator,
                    typefields,typefieldCount,index+1,
                    noNewEdges
                );
            }
        }
        // trying to insert a new edge since one could not be found in a child.
        if (noNewEdges) {
            return NULL;
        } else {
            AdtTrieNode* infant = newATN(parent, NULL);
            AdtTrieEdge edge = {operator, typefields[index].name, typefields[index].type, infant};
            sb_push(parent->edgesSb, edge);
            return getAtnChild(infant,operator, typefields,typefieldCount,index+1, 0);
        }
    }
}
// AdtTrieNode* getCommonAncestorATN(AdtTrieNode* a, AdtTrieNode* b) {
//     if (a == b) {
//         return a;
//     } else if (a == NULL) {
//         return NULL;
//     } else if (b == NULL) {
//         return NULL;
//     } else {
//         return getCommonAncestorATN(
//             getCommonAncestorATN(a->parent, b),
//             getCommonAncestorATN(a, b->parent)
//         );
//     }
// }
// int isAncestorATN(AdtTrieNode* parent, AdtTrieNode* child) {
//     return getCommonAncestorATN(parent,child) == parent;
// }

//
//
//
// Typing constraints:
//
//
//

void requireMetavarIsNumericOnly(Type* type) {
    COMPILER_ASSERT(type->kind == T_META, "requireMetavarIsNumericOnly invalid for non-metavar");
    type->as.Meta.ext->numericOnly = 1;
}
TypingResult checkSubtyping(Manager* typer, char const* why, Loc locWhere, Type* super, Type* sub) {
    // leaving the subtyping error as is; attempts to overwrite fail

    // performing the operation with noDefer=1 => don't add sup/sub, just return FAIL since it should be concretized.
    TypingResult result = helpSubtypeOp(typer,why,locWhere,super,sub,1);
    return result;
}
TypingResult requireSubtyping(Manager* typer, char const* why, Loc locWhere, Type* super, Type* sub) {
    // clearing the subtyping error:
    resetSubtypingError(typer);

    // attempting to perform the operation:
    TypingResult result = helpSubtypeOp(typer,why,locWhere,super,sub,0);
    
    // if the operation failed, and we were supposed to write, generating feedback from the subtyping error (must be present).
    char* subtypingError = getAndResetSubtypingError(typer);
    if (result == TYPING_FAILURE) {
        if (subtypingError) {
            FeedbackNote* note = CreateFeedbackNote("caused here...",locWhere,NULL);
            PostFeedback(
                FBK_ERROR,note,
                "Failed to apply subtyping for %s: %s", why, subtypingError
            );
            free(subtypingError);
        } else {
            COMPILER_ERROR("helper returned TYPING_FAILURE but subtypingError (string) is unset/NULL.");
        }
    }

    // returning whatever result we obtained.
    return result;
}
int solveAndCheckAllMetavars(Manager* typer) {
    // todo: consider sorting in dependency order and avoiding multi-pass approach?
    int printDebugSnapshots = 1;

    int maxPassCount = 5000;
    int failureCountThisPass = -1;
    int failureCountLastPass = -1;
    
    if (DEBUG && printDebugSnapshots) {
        printf("!!- SNAPSHOT[INIT]\n");
        printManager(typer,0);
    }

    int passIndex;
    for (passIndex = 0; passIndex < maxPassCount; passIndex++) {
        failureCountThisPass = 0;
        for (int metavarIndex = 0; metavarIndex < typer->metatypeBuf.count; metavarIndex++) {
            Type* metavar = &typer->metatypeBuf.ptr[metavarIndex];
            
            Type** visitedSB = NULL;
            metavar->as.Meta.ext->solnUpdatedThisPass = 0;
            Type* solution = getConcreteSoln(typer,metavar,&visitedSB);
            sb_free(visitedSB);

            if (solution == NULL) {
                failureCountThisPass++;
            }

            // todo: validate each solution in solveAllMetavars here, update failureCount
            else if (solution->kind == T_ANY) {
                FeedbackNote* note = CreateFeedbackNote("here...", metavar->as.Meta.ext->createdLoc, NULL);
                PostFeedback(FBK_ERROR, note, "Variant solution T_ANY not implemented.");
                failureCountThisPass++;
            }

            // COMPILER_ERROR("NotImplemented: validate 'solution' in solveAllMetavars.");
        }

        // dump:
        if (DEBUG && printDebugSnapshots) {
            printf("!!- SNAPSHOT[PASS %d/%d]\n", passIndex+1,maxPassCount);
            printManager(typer,1);
        }

        // determining whether or not to terminate:
        if (failureCountLastPass < 0) {
            failureCountLastPass = failureCountThisPass;
        } else {
            if (failureCountLastPass == failureCountThisPass) {
                // stagnation.
                break;
            } else {
                // continue...
                failureCountLastPass = failureCountThisPass;
            }
        }
    }
    if (passIndex >= maxPassCount) {
        COMPILER_ERROR_VA("solveAllMetavars exceeded max typing pass count (%d) without finding a fixed-point solution.", maxPassCount);
        return 0;
    } else {
        return failureCountThisPass == 0;
    }

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

TypingResult helpSubtypeOp(Manager* typer, char const* why, Loc locWhere, Type* super, Type* sub, int noDeferral) {
    if (super->kind == T_CAST) {
        return helpSubtypeOp(typer,why,locWhere,super->as.Cast.to,sub,noDeferral);
    }
    switch (super->kind)
    {
        case T_UNIT: { return helpSubtypeOp_unitSuper(typer,why,locWhere,super,sub,noDeferral); }
        case T_STRING: { return helpSubtypeOp_stringSuper(typer,why,locWhere,super,sub,noDeferral); }
        case T_INT: { return helpSubtypeOp_intSuper(typer,why,locWhere,super,sub,noDeferral); }
        case T_FLOAT: { return helpSubtypeOp_floatSuper(typer,why,locWhere,super,sub,noDeferral); }
        case T_PTR: { return helpSubtypeOp_ptrSuper(typer,why,locWhere,super,sub,noDeferral); }
        case T_FUNC: { return helpSubtypeOp_funcSuper(typer,why,locWhere,super,sub,noDeferral); }
        case T_TUPLE: { return helpSubtypeOp_tupleSuper(typer,why,locWhere,super,sub,noDeferral); }
        case T_UNION: { return helpSubtypeOp_unionSuper(typer,why,locWhere,super,sub,noDeferral); }
        case T_META: { return helpSubtypeOp_metaSuper(typer,why,locWhere,super,sub,noDeferral); }
        case T_CAST: { return helpSubtypeOp_castSuper(typer,why,locWhere,super,sub,noDeferral); }
        default:
        {
            COMPILER_ERROR_VA("NotImplemented: helpRequestSubtyping for super of unknown type kind %s.", TypeKindAsText(super->kind));
            return TYPING_FAILURE;
        }
    }
}
TypingResult helpSubtypeOp_unitSuper(Manager* typer,char const* why,Loc loc, Type* super, Type* sub, int noDeferral) {
    switch (sub->kind)
    {
        case T_UNIT:
        {
            return TYPING_CONFIRM;
        }
        case T_META:
        {
            return helpRequestSubtyping_genericMetaSub(typer,why,loc,super,sub,noDeferral);
        }
        default:
        {
            setMismatchedKindsSubtypingError(typer,super,sub);
            return TYPING_FAILURE;
        }
    }
}
TypingResult helpSubtypeOp_stringSuper(Manager* typer,char const* why,Loc loc, Type* super, Type* sub, int noDeferral) {
    switch (sub->kind)
    {
        case T_STRING:
        {
            return TYPING_CONFIRM;
        }
        case T_META:
        {
            return helpRequestSubtyping_genericMetaSub(typer,why,loc,super,sub,noDeferral);
        }
        default:
        {
            setMismatchedKindsSubtypingError(typer,super,sub);
            return TYPING_FAILURE;
        }
    }
}
TypingResult helpSubtypeOp_intSuper(Manager* typer, char const* why, Loc loc, Type* super, Type* sub, int noDeferral) {
    switch (sub->kind)
    {
        case T_INT:
        {
            // A subtypes B <=> width(A) >= width(B)
            if (sub->as.Int.isSigned != super->as.Int.isSigned) {
                setGenericSubtypingError(typer,"subtyping mismatch: signed and unsigned");
                return TYPING_FAILURE;
            }
            // we encode integer promotion as subtyping rather than implement a separate checker.
            // error messages MUST EXPLICITLY CALL THIS 'promotion/truncation' rather than 'subtyping/supertyping'.
            if (sub->as.Int.width <= super->as.Int.width) {
                return TYPING_CONFIRM;
            } else {
                int subWidthInBits = GetIntTypeWidthInBits(sub);
                int superWidthInBits = GetIntTypeWidthInBits(super);
                setGenericSubtypingError(typer,"cannot truncate Int[%d] to Int[%d]",subWidthInBits,superWidthInBits);
                return TYPING_FAILURE;
            }
        }
        case T_META:
        {
            return helpRequestSubtyping_genericMetaSub(typer,why,loc,super,sub,noDeferral);
        }
        case T_CAST:
        {
            return helpSubtypeOp_intSuper(typer,why,loc,super,sub->as.Cast.to,noDeferral);
        }
        default:
        {
            setMismatchedKindsSubtypingError(typer,super,sub);
            return TYPING_FAILURE;
        }
    }
}
TypingResult helpSubtypeOp_floatSuper(Manager* typer, char const* why, Loc loc, Type* super, Type* sub, int noDeferral) {
    switch (sub->kind)
    {
        case T_FLOAT:
        {
            // A subtypes B <=> width(A) >= width(B)
            if (sub->as.Int.width >= super->as.Int.width) {
                return TYPING_CONFIRM;
            } else {
                int subWidthInBits = GetFloatTypeWidthInBits(sub);
                int superWidthInBits = GetFloatTypeWidthInBits(super);
                setGenericSubtypingError(typer,"cannot promote subtype Float[%d] to supertype Float[%d]",subWidthInBits,superWidthInBits);
                return TYPING_FAILURE;
            }
        }
        case T_META:
        {
            return helpRequestSubtyping_genericMetaSub(typer,why,loc,super,sub,noDeferral);
        }
        default:
        {
            setMismatchedKindsSubtypingError(typer,super,sub);
            return TYPING_FAILURE;
        }
    }
}
TypingResult helpSubtypeOp_ptrSuper(Manager* typer, char const* why, Loc loc, Type* super, Type* sub, int noDeferral) {
    switch (sub->kind)
    {
        case T_PTR:
        {
            return helpSubtypeOp(typer,why,loc,GetPtrTypePointee(super),GetPtrTypePointee(sub),noDeferral);
        }
        case T_META:
        {
            return helpRequestSubtyping_genericMetaSub(typer,why,loc,super,sub,noDeferral);
        }
        default:
        {
            setMismatchedKindsSubtypingError(typer,super,sub);
            return TYPING_FAILURE;
        }
    }
}
TypingResult helpSubtypeOp_funcSuper(Manager* typer, char const* why, Loc loc, Type* super, Type* sub, int noDeferral) {
    switch (sub->kind)
    {
        case T_FUNC:
        {
            // check 1: do arg counts match?
            int superArgCount = GetFuncTypeArgCount(super);
            int subArgCount = GetFuncTypeArgCount(sub);
            if (superArgCount != subArgCount) {
                setGenericSubtypingError(typer,
                    "function argument counts mismatched, got %d for supertype, %d for subtype",
                    superArgCount,subArgCount
                );
                return TYPING_FAILURE;
            }

            // check 2: is the image (return type) subtyping in error?
            TypingResult imageResult = helpSubtypeOp(
                typer,
                why,loc,
                GetFuncTypeImage(super),GetFuncTypeImage(sub),
                noDeferral
            );
            if (imageResult == TYPING_FAILURE) {
                setGenericSubtypingError(typer,"function return type subtyping failed");
                return TYPING_FAILURE;
            }

            // check 3: are any arg subtypings in error?
            TypingResult mergedArgsResult = TYPING_CONFIRM;
            int argCount = superArgCount;
            for (int argIndex = 0; argIndex < argCount; argIndex++) {
                Type* superArg = GetFuncTypeArgAt(super,argIndex);
                Type* subArg = GetFuncTypeArgAt(sub,argIndex);
                
                TypingResult result = helpSubtypeOp(typer,why,loc,superArg,subArg,noDeferral);
                if (result == TYPING_FAILURE) {
                    setGenericSubtypingError(typer,"function arg %d subtyping failed",argIndex);
                }
                mergedArgsResult = mergeSubtypingResults(mergedArgsResult,result);
            }
            if (mergedArgsResult == TYPING_FAILURE) {
                return TYPING_FAILURE;
            }

            // all checks passed? return result so far, i.e. DEFERRED or CONFIRM:
            return mergeSubtypingResults(imageResult,mergedArgsResult);
        }
        case T_META:
        {
            return helpRequestSubtyping_genericMetaSub(typer,why,loc,super,sub,noDeferral);
        }
        default:
        {
            setMismatchedKindsSubtypingError(typer,super,sub);
            return TYPING_FAILURE;
        }
    }
}
TypingResult helpSubtypeOp_tupleSuper(Manager* typer, char const* why, Loc loc, Type* super, Type* sub, int noDeferral) {
    switch (sub->kind) {
        case T_TUPLE:
        {
            if (super->as.Compound_atn == sub->as.Compound_atn) {
                return TYPING_CONFIRM;
            } else {
                AdtTrieNode* superATN = super->as.Compound_atn;
                AdtTrieNode* subATN = sub->as.Compound_atn;
                
                // check 1: are the tuples of the same length?
                if (superATN->depth != subATN->depth) {
                    setGenericSubtypingError(typer,"supertype %d-tuple and subtype %d-tuple do not have the same field count.",superATN->depth,subATN->depth);
                    return TYPING_FAILURE;
                }

                // check 2: merge helpReadOrWriteSubtyping on each corresponding field type:
                TypingResult mergedFieldResults = TYPING_CONFIRM;
                while (superATN->parent && subATN->parent && superATN != subATN) {
                    AdtTrieEdge superEdge = superATN->parent->edgesSb[superATN->parentEdgeIndex];
                    AdtTrieEdge subEdge = subATN->parent->edgesSb[subATN->parentEdgeIndex];
                    mergedFieldResults = mergeSubtypingResults(
                        mergedFieldResults,
                        helpSubtypeOp(typer,why,loc,superEdge.type,subEdge.type,noDeferral)
                    );

                    superATN = superATN->parent;
                    subATN = subATN->parent;
                }
                return mergedFieldResults;
            }
        }
        case T_META:
        {
            return helpRequestSubtyping_genericMetaSub(typer,why,loc,super,sub,noDeferral);
        }
        default:
        {
            setMismatchedKindsSubtypingError(typer,super,sub);
            return TYPING_FAILURE;
        }
    }
}
TypingResult helpSubtypeOp_unionSuper(Manager* typer, char const* why, Loc loc, Type* super, Type* sub, int noDeferral) {
    switch (sub->kind) {
        case T_UNION:
        {
            if (super->as.Compound_atn == sub->as.Compound_atn) {
                return TYPING_CONFIRM;
            } else {
                AdtTrieNode* superATN = super->as.Compound_atn;
                AdtTrieNode* subATN = sub->as.Compound_atn;
                
                // check 1: are the unions of the same length?
                if (superATN->depth != subATN->depth) {
                    setGenericSubtypingError(typer,
                        "supertype %d-union and subtype %d-union do not have the same field count.",
                        superATN->depth,subATN->depth
                    );
                    return TYPING_FAILURE;
                }
                // check 2: merge helpReadOrWriteSubtyping on each corresponding field type:
                TypingResult mergedFieldResults = TYPING_CONFIRM;
                while (superATN->parent && subATN->parent && superATN != subATN) {
                    AdtTrieEdge superEdge = superATN->parent->edgesSb[superATN->parentEdgeIndex];
                    AdtTrieEdge subEdge = subATN->parent->edgesSb[subATN->parentEdgeIndex];
                    mergedFieldResults = mergeSubtypingResults(
                        mergedFieldResults,
                        helpSubtypeOp(typer,why,loc,superEdge.type,subEdge.type,noDeferral)
                    );
                    superATN = superATN->parent;
                    subATN = subATN->parent;
                }
                return mergedFieldResults;
            }
        }
        case T_META:
        {
            return helpRequestSubtyping_genericMetaSub(typer,why,loc,super,sub,noDeferral);
        }
        default:
        {
            setMismatchedKindsSubtypingError(typer,super,sub);
            return TYPING_FAILURE;
        }
    }
}
TypingResult helpSubtypeOp_castSuper(Manager* typer, char const* why, Loc loc, Type* super, Type* sub, int noDeferral) {
    // todo: check the cast at some point after solving metavars.
    return helpSubtypeOp(typer,why,loc,super->as.Cast.to,sub,noDeferral);
}
TypingResult helpSubtypeOp_metaSuper(Manager* typer, char const* why, Loc loc, Type* meta, Type* sub, int noDeferral) {
    if (noDeferral) {
        return TYPING_FAILURE;
    } else {
        SubtypeRec subtypingRec = {why,loc,sub};
        sb_push(meta->as.Meta.ext->deferredSubSB, subtypingRec);
        return TYPING_DEFERRED;
    }
}
TypingResult helpRequestSubtyping_genericMetaSub(Manager* typer, char const* why, Loc loc, Type* super, Type* meta, int noDeferral) {
    if (noDeferral) {
        return TYPING_FAILURE;
    } else {
        SupertypeRec supertypingRec = {why,loc,super};
        sb_push(meta->as.Meta.ext->deferredSuperSB, supertypingRec);
        return TYPING_DEFERRED;
    }
}
TypingResult mergeSubtypingResults(TypingResult fst, TypingResult snd) {
    return (fst < snd ? fst : snd);
}

//
// typing constraint helpers (2)
//

Type* getConcreteSoln(Manager* typer, Type* type, Type*** visitedMetavarSBP) {
    switch (type->kind) 
    {
        case T_UNIT:
        case T_FLOAT:
        case T_INT:
        case T_STRING:
        {
            return type;
        }
        case T_PTR:
        {
            Type* concretePointee = getConcreteSoln(typer,type->as.Ptr_pointee,visitedMetavarSBP);
            if (concretePointee) {
                return NewOrGetPtrType(typer,concretePointee);
            } else {
                return NULL;
            }
        }
        case T_FUNC:
        {
            Type* concreteImage = getConcreteSoln(typer,type->as.Func.image,visitedMetavarSBP);
            if (concreteImage == NULL) {
                return NULL;
            }

            Type* concreteResult = NULL;

            int failed = 0;
            int argsCount = type->as.Func.domainCount;
            Type** concreteArgsBuf = NULL;
            if (argsCount > 0) {
                concreteArgsBuf = malloc(sizeof(Type) * argsCount);
                for (int domainIndex = 0; domainIndex < argsCount; domainIndex++) {
                    Type* concreteArg = getConcreteSoln(typer,type->as.Func.domainArray[domainIndex],visitedMetavarSBP);
                    if (concreteArg == NULL) {
                        failed = 1;
                        break;
                    }
                    concreteArgsBuf[domainIndex] = concreteArg;
                }
            }
            if (!failed) {
                concreteResult = NewOrGetFuncType(typer,argsCount,concreteArgsBuf,concreteImage);
            }
            
            free(concreteArgsBuf); 
            concreteArgsBuf = NULL;
            return concreteResult;
        }
        case T_TUPLE:
        case T_UNION:
        {
            AdtTrieNode* atn = type->as.Compound_atn;
            int fieldsCount = atn->depth;
            TypeField* concreteFieldsBuf = malloc(sizeof(TypeField) * fieldsCount);

            for (AdtTrieNode* currentATN = atn; currentATN->parent; currentATN = currentATN->parent) {
                AdtTrieEdge edge = currentATN->parent->edgesSb[currentATN->parentEdgeIndex];
                Type* concreteFieldType = getConcreteSoln(typer,edge.type,visitedMetavarSBP);
                if (concreteFieldType == NULL) {
                    return NULL;
                } else {
                    concreteFieldsBuf[currentATN->depth-1] = (TypeField){edge.name,concreteFieldType};
                }
            }
            Type* result = NULL;
            if (type->kind == T_TUPLE) {
                result = NewOrGetTupleType(typer,concreteFieldsBuf,fieldsCount);
            } else if (type->kind == T_UNION) {
                result = NewOrGetUnionType(typer,concreteFieldsBuf,fieldsCount);
            } else {
                COMPILER_ERROR("Expected a T_TUPLE or T_UNION here.");
                result = NULL;
            }

            free(concreteFieldsBuf);
            return result;
        }
        case T_META:
        {
            Type* metavar = type;

            // if metavar is poisoned, return NULL
            if (metavar->as.Meta.poisoned) {
                return NULL;
            }

            // if metavar is already solved, just return 'soln'
            if (metavar->as.Meta.soln) {
                return metavar->as.Meta.soln;
            }

            // if visitedMetavarSBP is NULL, we don't solve, just return NULL.
            if (visitedMetavarSBP == NULL) {
                return NULL;
            } else {
                // If this metavar was already visited, and 'soln' is still NULL, then 
                // this metavar...
                // 1. may be a supertype or subtype of itself, indicating equality.
                // 2. may be a field of its compound self, indicating a cyclic dependency.
                // in any case, a 'NULL' concrete signals "no more information"
                int inserted = addTypeToSBSetP(visitedMetavarSBP,metavar);
                if (!inserted) {
                    // not inserted => pre-existing element => cycle encountered
                    return NULL;
                }

                // gathering a hypothesis type from supertypes:
                Type* hypothesis = NULL; {
                    int supertypeCount = sb_count(metavar->as.Meta.ext->deferredSuperSB);
                    for (int supertypeIndex = 0; supertypeIndex < supertypeCount; supertypeIndex++) {
                        SupertypeRec supertypeRec = metavar->as.Meta.ext->deferredSuperSB[supertypeIndex];
                        Type* concreteSupertype = getConcreteSoln(typer,supertypeRec.ptr,visitedMetavarSBP);
                        if (concreteSupertype) {
                            if (hypothesis == NULL) {
                                hypothesis = concreteSupertype;
                            } else {
                                TypingResult comparison = checkSubtyping(
                                    typer,"get-hypothesis",metavar->as.Meta.ext->createdLoc,
                                    concreteSupertype,hypothesis
                                );
                                COMPILER_ASSERT(comparison != TYPING_DEFERRED, "expected 'getConcreteSoln' to return concrete types; no deferral allowed.");
                                if (comparison == TYPING_CONFIRM) {
                                    // new concreteSupertype is a supertype of the existing hypothesis. Updating...
                                    hypothesis = concreteSupertype;
                                }
                            }
                        }
                    }
                }

                // gathering a test type from subtypes:
                Type* test = NULL; {
                    int subtypeCount = sb_count(metavar->as.Meta.ext->deferredSubSB);
                    for (int subtypeIndex = 0; subtypeIndex < subtypeCount; subtypeIndex++) {
                        SubtypeRec subtypeRec = metavar->as.Meta.ext->deferredSubSB[subtypeIndex];
                        Type* concreteSubtype = getConcreteSoln(typer,subtypeRec.ptr,visitedMetavarSBP);
                        if (concreteSubtype) {
                            if (test == NULL) {
                                test = concreteSubtype;
                            } else {
                                TypingResult comparison = requireSubtyping(
                                    typer,"get-test",metavar->as.Meta.ext->createdLoc,
                                    test,concreteSubtype
                                );
                                COMPILER_ASSERT(comparison != TYPING_DEFERRED, "expected 'getConcreteSoln' to return concrete types; no deferral allowed.");
                                if (comparison == TYPING_CONFIRM) {
                                    // new concreteSubtype is a subtype of the existing test. Updating...
                                    test = concreteSubtype;
                                }
                            }
                        }
                    }
                }
                
                // solving from hypothesis and test types:
                if (hypothesis == NULL && test == NULL) {
                    // metavar solution failed, incomplete information.
                    metavar->as.Meta.soln = NULL;
                } else if (hypothesis == NULL) {
                    // no supertype info => use the most suitable subtype.
                    metavar->as.Meta.soln = test;
                } else if (test == NULL) {
                    // no subtype info => use the most suitable supertype.
                    metavar->as.Meta.soln = hypothesis;
                } else {
                    // subtype and supertype info => compare and return if OK.
                    TypingResult result = requireSubtyping(typer,"new-soln-update",metavar->as.Meta.ext->createdLoc,hypothesis,test);
                    COMPILER_ASSERT(result != TYPING_DEFERRED, "expected 'requireSubtyping' to operate on purely concrete args; no deferral allowed.");
                    if (result == TYPING_CONFIRM) {
                        // hypothesis works!
                        metavar->as.Meta.soln = hypothesis;
                    } else {
                        // conflicting constraints, no solution exists. poison and return NULL
                        metavar->as.Meta.poisoned = 1;
                        metavar->as.Meta.soln = NULL;
                    }
                }

                // checking numericOnly constraint:
                if (metavar->as.Meta.soln && metavar->as.Meta.ext->numericOnly) {
                    Type* soln = metavar->as.Meta.soln;
                    int isNumeric = (
                        (soln->kind == T_INT) ||
                        (soln->kind == T_FLOAT)
                    );
                    if (!isNumeric) {
                        // not numeric.
                        FeedbackNote* note = CreateFeedbackNote("for type here...", metavar->as.Meta.ext->createdLoc, NULL);
                        PostFeedback(
                            FBK_ERROR,note,
                            "Expected a numeric (int,float) type, instead received type of kind %s", TypeKindAsText(soln->kind)
                        );
                        metavar->as.Meta.soln = NULL;
                        metavar->as.Meta.poisoned = 1;
                    }
                }

                // if solved, propagating soln to related types:
                if (metavar->as.Meta.soln) {
                    // since we have found a solution, we can propagate this info to all super and subtypes.
                    // this should be requested by super and subtypes later, but this may be required since we get only concrete types earlier.
                    int subtypeCount = sb_count(metavar->as.Meta.ext->deferredSubSB);
                    TypingResult result = TYPING_CONFIRM;
                    for (int subtypeIndex = 0; subtypeIndex < subtypeCount; subtypeIndex++) {
                        SubtypeRec subtypeRec = metavar->as.Meta.ext->deferredSubSB[subtypeIndex];
                        
                        TypingResult subtypeResult = requireSubtyping(typer,subtypeRec.why,subtypeRec.loc,metavar->as.Meta.soln,subtypeRec.ptr);
                        result = mergeSubtypingResults(result,subtypeResult);
                    }
                    if (result == TYPING_FAILURE) {
                        COMPILER_ERROR("Invalid metavar solution; returned TYPING_FAILURE when applied to subtypes.");
                        return NULL;
                    }

                    // updating the 'solution found' flag:
                    metavar->as.Meta.ext->solnUpdatedThisPass = 1;
                }

                // returning soln:
                return metavar->as.Meta.soln;
            }
        }
        case T_CAST:
        {
            Type* cast = type;
            Type* concreteTo = getConcreteSoln(typer,cast->as.Cast.to,visitedMetavarSBP);
            Type* concreteFrom = getConcreteSoln(typer,cast->as.Cast.from,visitedMetavarSBP);

            if (cast->as.Cast.checkStatus == 0) {
                // try solving
                if (concreteTo == NULL || concreteFrom == NULL) {
                    cast->as.Cast.checkStatus = -1;
                } else {
                    int isNumericConversion = (
                        ((concreteTo->kind == T_INT) || (concreteTo->kind == T_FLOAT)) &&
                        ((concreteFrom->kind == T_INT) || (concreteFrom->kind == T_FLOAT))
                    );
                    if (isNumericConversion) {
                        // numeric conversions always work, through bitcasts, extension casts, and fp casts.
                        cast->as.Cast.checkStatus = 1;
                    } else {
                        // ensuring subtyping
                        TypingResult subtypingResult = requireSubtyping(typer,"vcast",NullLoc(),concreteTo,concreteFrom);
                        if (subtypingResult == TYPING_CONFIRM) {
                            cast->as.Cast.checkStatus = 1;
                        } else if (subtypingResult == TYPING_FAILURE) {
                            cast->as.Cast.checkStatus = -1;
                        } else {
                            COMPILER_ASSERT(subtypingResult == TYPING_DEFERRED,"Unexpected subtypingResult == TYPING_DEFERRED when operating on concrete types.");
                        }
                    }
                }
            }
            
            // based on stored check status, return:
            if (cast->as.Cast.checkStatus < 0) {
                return NULL;
            } else {
                return getConcreteSoln(typer,concreteTo,visitedMetavarSBP);
            }
        }
        default:
        {
            COMPILER_ERROR_VA(
                "NotImplemented: 'getConcreteSoln' for type of kind '%s'",
                TypeKindAsText(type->kind)
            );
            return NULL;
        }
    }
}

//
// typing constraint helpers (3)
//

void resetSubtypingError(Manager* typer) {
    if (typer->subtypingError) {
        free(typer->subtypingError);
        typer->subtypingError = NULL;
    }
}
char* getAndResetSubtypingError(Manager* typer) {
    char* message = typer->subtypingError;
    if (message) {
        // reset, but do not free! just move out and return.
        typer->subtypingError = NULL;
    }
    return message;
}
void setGenericSubtypingError(Manager* typer, char const* format, ...) {
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
void setMismatchedKindsSubtypingError(Manager* typer, Type* super, Type* sub) {
    setGenericSubtypingError(
        typer,
        "super kind %s incompatible with sub kind %s",
        TypeKindAsText(super->kind),TypeKindAsText(sub->kind)
    );
}
int isTypeInSBSetP(Type*** sbp, Type* testType) {
    int count = sb_count(*sbp);
    for (int index = 0; index < count; index++) {
        Type* existingType = (*sbp)[index];
        if (existingType == testType) {
            return 1;
        }
    }
    return 0;
}
int addTypeToSBSetP(Type*** sbp, Type* addedType) {
    int count = sb_count(*sbp);
    for (int index = 0; index < count; index++) {
        Type* existingType = (*sbp)[index];
        if (existingType == addedType) {
            return 0;
        }
    }
    sb_push((*sbp),addedType);
    return 1;
}

//
// Manager:
//

int typer_post(void* rawManager, AstNode* node) {
    Manager* typer = rawManager;
    Loc nodeLoc = GetAstNodeLoc(node);
    AstKind nodeKind = GetAstNodeKind(node);
    switch (nodeKind) {
        case AST_UNIT:
        {
            Type* t = GetUnitType(typer);
            SetAstNodeTypingExt_Value(node,t);
            break;
        }
        case AST_LITERAL_INT:
        {
            // size_t value = GetAstIntLiteralValue(node);
            Type* type;
            // just default to S32
            type = GetIntType(typer,INT_32,1);
            // if (value < (1ULL << 8)) {
            //     type = GetIntType(typer,INT_8,1);
            // } else if (value < (1ULL << 16)) {
            //     type = GetIntType(typer,INT_16,1);
            // } else if (value < (1ULL << 32)) {
            //     type = GetIntType(typer,INT_32,1);
            // } else {
            //     type = GetIntType(typer,INT_64,1);
            // }
            SetAstNodeTypingExt_Value(node,type);
            break;
        }
        case AST_LITERAL_FLOAT:
        {
            Type* t = GetFloatType(typer, FLOAT_32);
            SetAstNodeTypingExt_Value(node,t);
            break;
        }
        case AST_LITERAL_STRING:
        {
            Type* t = GetStringType(typer);
            SetAstNodeTypingExt_Value(node,t);
            break;
        }
        case AST_VID:
        case AST_TID:
        {
            Loc loc = GetAstNodeLoc(node);
            SymbolID name = GetAstIdName(node);
            Scope* scope = GetAstIdLookupScope(node);
            
            DefnScope* foundDefn = LookupSymbol(scope, name);
            if (foundDefn == NULL) {
                FeedbackNote* note = CreateFeedbackNote("here...", loc, NULL);
                PostFeedback(
                    FBK_ERROR, note,
                    "Symbol '%s' not defined in this context",
                    GetSymbolText(name)
                );
            } else {
                SetAstIdDefnScope(node,foundDefn);

                AstKind nodeKind = GetAstNodeKind(node);
                AstNode* foundDefnNode = GetDefnNode(foundDefn);
                if (nodeKind == AST_TID) {
                    Type* foundType = GetAstNodeTypingExt_Type(foundDefnNode);
                    SetAstNodeTypingExt_Type(node,foundType);
                } else if (nodeKind == AST_VID) {
                    Type* foundType = GetAstNodeTypingExt_Value(foundDefnNode);
                    SetAstNodeTypingExt_Value(node,foundType);
                } else {
                    COMPILER_ERROR_VA("Unable to decide context while typing %s.", AstKindAsText(nodeKind));
                    break;
                }
            }
            // tracking closures
            // ReqAstLambdaDefn(GetAstNodeParentFunc(node),foundDefn);
            break;
        }
        case AST_STMT_MODULE:
        {
            // modules are type-initialized in the primer.
            break;
        }
        case AST_SCRIPT:
        {
            // scripts do not contain type information.
            break;
        }
        case AST_STMT_VLET:
        {
            Loc loc = GetAstNodeLoc(node);
            
            // symbols defined while visiting lhs pattern, we just need to get the pattern type:
            AstNode* lhs = GetAstLetStmtLhs(node);
            Type* lhsType = NULL; {
                AstKind lhsKind = GetAstNodeKind(lhs);
                if (lhsKind == AST_VPATTERN_SINGLETON) {
                    AstNode* lhsSingletonField = GetAstSingletonPatternField(lhs);
                    AstNode* lhsSingletonRhs = GetAstFieldRhs(lhsSingletonField);
                    lhsType = GetAstNodeTypingExt_Type(lhsSingletonRhs);
                } else if (lhsKind == AST_VPATTERN) {
                    int patternCount = GetAstPatternLength(lhs);
                    if (patternCount == 0) {
                        // unit pattern
                        lhsType = GetUnitType(typer);
                    } else {
                        // tuple pattern
                        TypeField* typefieldsSb = NULL;
                        for (int index = 0; index < patternCount; index++) {
                            AstNode* field = GetAstPatternFieldAt(node,index);
                            TypeField typefield = {
                                GetAstFieldName(field), 
                                GetAstNodeTypingExt_Value(GetAstFieldRhs(field))
                            };
                            sb_push(typefieldsSb,typefield);
                        }
                        lhsType = NewOrGetTupleType(typer,typefieldsSb,sb_count(typefieldsSb));
                        sb_free(typefieldsSb);
                    }
                } else {
                    COMPILER_ERROR("Expected VPATTERN or VPATTERN_SINGLETON as lpattern for AST_STMT_VLET");
                }
            }
            
            AstNode* rhs = GetAstLetStmtRhs(node);
            Type* rhsType = GetAstNodeTypingExt_Value(rhs);

            if (lhsType && rhsType) {
                requireSubtyping(typer, "<lhs> = <rhs>",loc, lhsType,rhsType);
            } else {
                COMPILER_ERROR("typer: lhsType or rhsType is NULL (or both) in AST_STMT_VLET");
            }
            break;
        }
        case AST_STMT_DISCARD:
        {
            break;
        }
        case AST_VLAMBDA:
        {
            AstNode* lambda = node;

            AstNode* pattern = GetAstVLambdaPattern(lambda);
            int argsCount = GetAstPatternLength(pattern);
            Type** argsTypes = NULL;
            if (argsCount) {
                argsTypes = malloc(sizeof(Type*) * argsCount);
            } else {
                argsTypes = malloc(sizeof(Type*));
                argsTypes[0] = GetUnitType(typer);
            }
            for (int argIndex = 0; argIndex < argsCount; argIndex++) {
                AstNode* argNode = GetAstPatternFieldAt(pattern,argIndex);
                argsTypes[argIndex] = GetAstNodeTypingExt_Value(argNode);
            }
            
            AstNode* rhsNode = GetAstVLambdaBody(node);
            Type* rhsType = GetAstNodeTypingExt_Value(rhsNode);
            if (rhsType) {
                SetAstNodeTypingExt_Value(node, NewOrGetFuncType(typer, argsCount, argsTypes, rhsType));
            } else {
                COMPILER_ERROR("typer: NULL rhsType for AST_LAMBDA");
            }

            Type* funcType = NewOrGetFuncType(typer,argsCount,argsTypes,rhsType);
            if (argsTypes) {
                free(argsTypes); 
                argsTypes = NULL;
            }

            SetAstNodeTypingExt_Value(node,funcType);

            break;
        }
        case AST_STMT_VDEF:
        {
            // module items can be used in value and typing contexts
            Loc loc = GetAstNodeLoc(node);

            // todo: check for a template pattern, define a typefunc if required
            
            AstNode* rhs = GetAstDefValueStmtRhs(node);
            Type* rhsType = GetAstNodeTypingExt_Value(rhs);
            
            // the sole defined value was stored in the value slot in 'primer':
            Type* lhsType = GetAstNodeTypingExt_Value(node);

            int ok = (
                COMPILER_ASSERT(lhsType, "typer: Invalid lhsType in AST_STMT_VDEF") && 
                COMPILER_ASSERT(rhsType, "typer: Invalid rhsType in AST_STMT_VDEF")
            );
            if (ok) {
                requireSubtyping(typer,"def <lhs> = <rhs>",loc, rhsType,lhsType);
            }
            break;
        }
        case AST_TPATTERN_FIELD:
        case AST_VPATTERN_FIELD:
        case AST_TPATTERN_SINGLETON_FIELD:
        case AST_VPATTERN_SINGLETON_FIELD:
        {
            // metatypes created by scoper (since lexically scoped), so TypingExt_V/T already set.
            int typingContext = (nodeKind == AST_TPATTERN_FIELD) || (nodeKind == AST_TPATTERN_SINGLETON_FIELD);
            int valueContext = (nodeKind == AST_VPATTERN_FIELD) || (nodeKind == AST_VPATTERN_SINGLETON_FIELD);
            COMPILER_ASSERT(typingContext ^ valueContext, "Bad typing/value context setup.");

            // getting the RHS:
            AstNode* rhs = GetAstFieldRhs(node);
            
            // getting the field type as set in the primer, and the rhs typespec:
            Type* fieldType = NULL;
            Type* rhsTypingType = NULL;
            if (rhs) {
                if (typingContext) {
                    fieldType = GetAstNodeTypingExt_Type(node);
                    rhsTypingType = GetAstNodeTypingExt_Type(rhs);
                } else if (valueContext) {
                    fieldType = GetAstNodeTypingExt_Value(node);
                    rhsTypingType = GetAstNodeTypingExt_Type(rhs);
                }

                COMPILER_ASSERT(fieldType, "Non-null RHS but null field type in Manager.");
                Loc loc = GetAstNodeLoc(node);
                if (rhsTypingType) {
                    requireSubtyping(typer,"pattern-field-rhs",loc, rhsTypingType,fieldType);
                } else {
                    COMPILER_ERROR("RHS type is NULL.");
                }
            } else {
                COMPILER_ERROR("No RHS provided.");
            }
            break;
        }
        case AST_VSTRUCT_FIELD:
        case AST_VTUPLE_FIELD:
        {
            Loc loc = GetAstNodeLoc(node);
            AstNode* rhs = GetAstFieldRhs(node);
            Type* tv;
            if (rhs) {
                tv = GetAstNodeTypingExt_Value(rhs);
            } else {
                SymbolID name = GetAstFieldName(node);
                char const* nameText = GetSymbolText(name);
                tv = NewMetavarType(loc, typer, "field:%s", nameText);
            }
            SetAstNodeTypingExt_Value(node,tv);
            break;
        }
        case AST_VPATTERN:
        case AST_TPATTERN:
        case AST_VPATTERN_SINGLETON:
        case AST_TPATTERN_SINGLETON:
        {
            break;
        }
        case AST_VSTRUCT:
        case AST_VTUPLE:
        {
            int fieldCount = CountAstStructFields(node);
            TypeField* typefieldBuf = malloc(fieldCount*sizeof(TypeField));
            for (int index = 0; index < fieldCount; index++) {
                AstNode* field = GetAstStructFieldAt(node,index);
                SymbolID fieldName = GetAstFieldName(field);
                Type* fieldType = GetAstNodeTypingExt_Value(field);

                typefieldBuf[index] = (TypeField) {fieldName,fieldType};
            }
            Type* tuple = NewOrGetTupleType(typer,typefieldBuf,fieldCount);
            SetAstNodeTypingExt_Value(node,tuple);
            free(typefieldBuf);
            break;
        }
        case AST_CHAIN:
        {
            AstNode* result = GetAstChainResult(node);
            if (result) {
                SetAstNodeTypingExt_Value(node, GetAstNodeTypingExt_Value(result));
            } else {
                SetAstNodeTypingExt_Value(node, GetUnitType(typer));
            }
            break;
        }
        case AST_UNARY:
        {
            AstUnaryOperator operator = GetAstUnaryOperator(node);
            AstNode* arg = GetAstUnaryOperand(node);
            Type* argType = GetAstNodeTypingExt_Value(arg);
            Type* type = NewOrGetUnaryIntrinsicType(typer,nodeLoc,operator,argType);
            SetAstNodeTypingExt_Value(node,type);
            break;
        }
        case AST_BINARY:
        {
            AstBinaryOperator binop = GetAstBinaryOperator(node);
            AstNode* ltArg = GetAstBinaryLtOperand(node);
            AstNode* rtArg = GetAstBinaryRtOperand(node);
            Type* ltArgType = GetAstNodeTypingExt_Value(ltArg);
            Type* rtArgType = GetAstNodeTypingExt_Value(rtArg);
            Type* type = NewOrGetBinaryIntrinsicType(typer,nodeLoc,binop,ltArgType,rtArgType);
            SetAstNodeTypingExt_Value(node,type);
            break;
        }
        case AST_ITE:
        {
            // COMPILER_ERROR("DISABLED: GetPhiType in typer for AST_ITE.");
            AstNode* cond = GetAstIteCond(node);
            AstNode* ifTrue = GetAstIteIfTrue(node);
            AstNode* ifFalse = GetAstIteIfFalse(node);
            Type* condType = GetAstNodeTypingExt_Value(cond);
            Type* ifTrueType = GetAstNodeTypingExt_Value(ifTrue);
            Type* optIfFalseType = ifFalse ? GetAstNodeTypingExt_Value(ifFalse) : NULL;
            Type* type = GetPhiType(typer,nodeLoc,condType,ifTrueType,optIfFalseType);
            // Type* type = NULL;
            SetAstNodeTypingExt_Value(node,type);
            break;
        }
        case AST_VCALL:
        {
            Loc loc = GetAstNodeLoc(node);

            AstNode* lhs = GetAstCallLhs(node);
            Type* lhsType = GetAstNodeTypingExt_Value(lhs);
            Type* formalFuncType = lhsType;

            int actualArgsCount = GetAstCallArgCount(node);
            Type** actualArgsTypes = malloc(actualArgsCount*sizeof(Type*)); {
                for (int argIndex = 0; argIndex < actualArgsCount; argIndex++) {
                    AstNode* actualArgNode = GetAstCallArgAt(node,argIndex);
                    actualArgsTypes[argIndex] = GetAstNodeTypingExt_Value(actualArgNode);
                }
            }
            Type* retType = NewMetavarType(loc, typer, "vcall-ret");
            
            Type* actualFuncType = NewOrGetFuncType(typer, actualArgsCount, actualArgsTypes, retType);
            
            // requiring the formal functype to supertype the actual functype
            requireSubtyping(typer,"vcall",loc, formalFuncType,actualFuncType);
            
            SetAstNodeTypingExt_Value(node,retType);
            break;
        }
        case AST_TCALL:
        {
            COMPILER_ERROR("NotImplemented: typing AST_TCALL");
            break;
        }
        case AST_VPAREN:
        {
            AstNode* itNode = GetAstParenItem(node);
            Type* itType = GetAstNodeTypingExt_Value(itNode);
            SetAstNodeTypingExt_Value(node,itType);
            break;
        }
        case AST_STMT_TDEF:
        {
            Loc loc = GetAstNodeLoc(node);
            AstNode* optRhs = GetAstTypedefStmtOptRhs(node);
            if (optRhs) {
                AstNode* rhs = optRhs;
                Type* rhsType = GetAstNodeTypingExt_Type(rhs);
                Type* metavarType = GetAstNodeTypingExt_Type(node);

                // filling rhsType as a solution for the typing metavar:
                int inputsOk = (
                    COMPILER_ASSERT(rhsType,"Invalid rhsType while typing 'tdef' statement.") && 
                    COMPILER_ASSERT(metavarType,"Invalid lhsType while typing 'tdef' statement.")
                );
                if (inputsOk) {
                    requireSubtyping(typer,"<Lhs> = <Rhs>",loc,rhsType,metavarType);
                }
            }
            break;
        }
        case AST_STMT_LINK:
        {
            break;
        }
        case AST_STMT_LINK_ITEM:
        {
            Loc loc = GetAstNodeLoc(node);

            AstNode* lhsPattern = AstLinkItem_GetPattern(node);
            int patternCount = GetAstPatternLength(lhsPattern);
            Type** argTypeBuf = NULL;
            if (patternCount > 0) {
                argTypeBuf = malloc(sizeof(Type*) * patternCount);
                for (int index = 0; index < patternCount; index++) {
                    AstNode* argNode = GetAstPatternFieldAt(lhsPattern,index);
                    COMPILER_ASSERT(GetAstNodeKind(argNode) == AST_VPATTERN_FIELD, "Invalid pattern field kind.");
                    Type* argType = GetAstNodeTypingExt_Value(argNode);
                    COMPILER_ASSERT(argType, "NULL argtype for extern arg field.");
                    argTypeBuf[index] = argType;
                }
            }

            AstNode* rhsTypespec = AstLinkItem_RetTs(node);
            Type* rhsTypespecType = GetAstNodeTypingExt_Value(rhsTypespec);
            
            Type* defType = GetAstNodeTypingExt_Value(node);

            if (defType && rhsTypespecType) {
                // filling func as a solution (supertype) for defType
                Type* solnType = NewOrGetFuncType(typer,patternCount,argTypeBuf,rhsTypespecType);
                // TypingResult result = requireSubtyping(typer,"extern",loc,solnType,defType);
                requireSubtyping(typer,"extern",loc,solnType,defType);
            }

            break;
        }
        case AST_VCAST:
        {
            AstNode* vcast = node;
            AstNode* type2val = GetAstVCastTypespec(vcast);
            AstNode* rhs = GetAstVCastRhs(vcast);
            Type* toType = GetAstNodeTypingExt_Value(type2val);
            Type* fromType = GetAstNodeTypingExt_Value(rhs);
            Type* castType = NewCastHelperType(typer,toType,fromType);
            SetAstNodeTypingExt_Value(vcast,castType);
            break;
        }
        case AST_TYPE2VAL:
        {
            AstNode* type2val = node;
            AstNode* typespec = GetAstType2ValTypespec(type2val);
            Type* type = GetAstNodeTypingExt_Type(typespec);
            SetAstNodeTypingExt_Value(type2val,type);
            SetAstNodeTypingExt_Type(type2val,type);
            break;
        }
        case AST_VAL2TYPE:
        {
            AstNode* val2type = node;
            AstNode* expr = GetAstVal2TypeExpr(val2type);
            Type* type = GetAstNodeTypingExt_Value(expr);
            SetAstNodeTypingExt_Type(val2type,type);
            SetAstNodeTypingExt_Value(val2type,type);
            break;
        }
        case AST_VPTR:
        {
            AstNode* pointerNode = node;
            AstNode* pointeeNode = GetAstVPtrPointee(pointerNode);
            Type* pointeeType = GetAstNodeTypingExt_Value(pointeeNode);
            Type* pointerType = NewOrGetPtrType(typer,pointeeType);
            SetAstNodeTypingExt_Value(pointerNode,pointerType);
            break;
        }
        case AST_TPTR:
        {
            AstNode* pointerNode = node;
            AstNode* pointeeNode = GetAstTPtrPointee(pointerNode);
            Type* pointeeType = GetAstNodeTypingExt_Type(pointeeNode);
            Type* pointerType = NewOrGetPtrType(typer,pointeeType);
            SetAstNodeTypingExt_Type(pointerNode,pointerType);
            break;
        }
        case AST_COLON_NAME:
        {
            // colon LHS-es must be of type T_MODULE,
            // this code looks up the module, finds the referenced value in the frame, 
            // stores it on the node, and copies any type variables.

            AstNode* lhsNode = GetAstColonNameLhs(node);
            SymbolID rhsName = GetAstColonNameRhs(node);

            Type* lhsType = GetAstNodeTypingExt_Value(lhsNode);
            if (lhsType) {
                COMPILER_ASSERT(GetTypeKind(lhsType) == T_MODULE, "Non-module lhs type in ':' expr");
                AstNode* moduleNode = GetModuleTypeAstNode(lhsType);
                Frame* moduleFrame = GetAstModuleContentFrame(moduleNode);
                DefnScope* moduleLookupDefnScope = LookupSymbolInFrame(moduleFrame, rhsName);
                if (moduleLookupDefnScope) {
                    // setting the defn scope for the emitter:
                    SetAstColonNameRefedDefnScope(node,moduleLookupDefnScope);
                
                    // further typing ...
                    AstNode* moduleLookupDefnNode = GetDefnNode(moduleLookupDefnScope);
                    if (GetAstNodeKind(moduleLookupDefnNode) == AST_STMT_MODULE) {
                        // if submodule, create new module type.
                        Type* newModuleType = NewModuleType(typer,moduleLookupDefnNode);
                        SetAstNodeTypingExt_Value(node, newModuleType);
                    } else {
                        // otherwise, just copy value and type exts:
                        Type* vext = GetAstNodeTypingExt_Value(moduleLookupDefnNode);
                        if (vext) {
                            SetAstNodeTypingExt_Value(node, vext);
                        }
                        Type* text = GetAstNodeTypingExt_Type(moduleLookupDefnNode);
                        if (text) {
                            SetAstNodeTypingExt_Type(node, text);
                        }
                    }
                } else {
                    COMPILER_ERROR_VA("TODO: PostFeedback, module-field :%s not found", GetSymbolText(rhsName));
                }
            }
            break;
        }
        default:
        {
            COMPILER_ERROR_VA("NotImplemented: TypeNode for AST node kind %s",AstKindAsText(nodeKind));
            break;
        }
    }
    return 1;
}

void mapCompoundType(Manager* typer, AdtTrieNode* compoundATN, FieldCB cb, void* context) {
    if (compoundATN != NULL && compoundATN != &typer->anyATN) {
        mapCompoundType(typer, compoundATN->parent, cb, context);
        AdtTrieNode* node = compoundATN;
        AdtTrieEdge* edge = &node->parent->edgesSb[node->parentEdgeIndex];
        cb(typer,context,edge->name,edge->type);
    }
}
void accumulateCompoundFieldSizeSum(Manager* typer, void* rawSumP, SymbolID name, Type* fieldType) {
    int* sumP = rawSumP;
    int fieldTypeSize = GetTypeSizeInBytes(typer,fieldType);
    if (sumP) {
        *sumP += fieldTypeSize;
    }
}
void accumulateCompoundFieldSizeMax(Manager* typer, void* rawMaxP, SymbolID name, Type* fieldType) {
    int* maxP = rawMaxP;
    int fieldTypeSize = GetTypeSizeInBytes(typer,fieldType);
    if (maxP) {
        if (fieldTypeSize > *maxP) {
            *maxP = fieldTypeSize;
        }
    }
}

void printManager(Manager* typer, int metaOnly) {
    printf("!!- Manager dump:\n");
    
    if (!metaOnly) {
        printTypeLn(typer, &typer->unitType);
        printTypeLn(typer, &typer->unsignedIntType[INT_1]);
        printTypeLn(typer, &typer->unsignedIntType[INT_8]);
        printTypeLn(typer, &typer->unsignedIntType[INT_16]);
        printTypeLn(typer, &typer->unsignedIntType[INT_32]);
        printTypeLn(typer, &typer->unsignedIntType[INT_64]);
        printTypeLn(typer, &typer->unsignedIntType[INT_128]);
        printTypeLn(typer, &typer->signedIntType[INT_8]);
        printTypeLn(typer, &typer->signedIntType[INT_16]);
        printTypeLn(typer, &typer->signedIntType[INT_32]);
        printTypeLn(typer, &typer->signedIntType[INT_64]);
        printTypeLn(typer, &typer->signedIntType[INT_128]);
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
    }

    for (int it = 0; it < typer->metatypeBuf.count; it++) {
        printTypeLn(typer, &typer->metatypeBuf.ptr[it]);
    }
}
void printType(Manager* typer, Type* type) {
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
            printf("%s-int %d", (GetIntTypeIsSigned(type) ? "signed":"unsigned"), GetIntTypeWidthInBits(type));
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
            int printSupAndSubTypeCount = 1;
            if (printSupAndSubTypeCount) {
                printf(
                    "%smeta%s %s (%d supers, %d subs)",
                    (type->as.Meta.poisoned ? "poisoned-" : ""),
                    (type->as.Meta.ext->solnUpdatedThisPass ? "*" : ""),
                    type->as.Meta.name, sb_count(type->as.Meta.ext->deferredSuperSB), sb_count(type->as.Meta.ext->deferredSubSB)
                );
            } else {
                printf(
                    "meta%s %s", 
                    (type->as.Meta.ext->solnUpdatedThisPass ? "*" : ""),
                    type->as.Meta.name
                );
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
            AstNode* node = GetModuleTypeAstNode(type);
            SymbolID moduleName = AstModuleStmt_GetName(node);
            printf("module %s", GetSymbolText(moduleName));
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
void printTypeLn(Manager* typer, Type* type) {
    printType(typer, type);
    printf("\n");
}

//
//
//
// API:
//
//
//

ManagerCfg NewDefaultManagerCfg(void) {
    return newDefaultManagerCfg();
}
Manager* NewManager(ManagerCfg config) {
    return newManager(config);
}

//
// Constructors:
//

Type* NewModuleType(Manager* typer, AstNode* moduleNode) {
    Type* type = pushToTypeBuf(&typer->moduleTypeBuf, T_MODULE);
    type->as.Module.node = moduleNode;
    return type;
}

Type* GetUnitType(Manager* typer) {
    return &typer->unitType;
}
Type* GetStringType(Manager* typer) {
    return &typer->stringType;
}
Type* GetIntType(Manager* typer, IntWidth width, int isSigned) {
    if (isSigned) {
        return &typer->signedIntType[width];
    } else {
        return &typer->unsignedIntType[width];
    }
}
Type* GetFloatType(Manager* typer, FloatWidth width) {
    return &typer->floatType[width];
}
Type* NewOrGetPtrType(Manager* typer, Type* pointee) {
    // todo: disable pointers to T_FUNC.

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
Type* NewOrGetSliceType(Manager* typer, Type* elementType) {
    // searching for an existing, structurally equivalent type:
    for (size_t index = 0; index < typer->sliceTypeBuf.count; index++) {
        Type* cmpType = &typer->sliceTypeBuf.ptr[index];
        if (cmpType->as.Slice_element == elementType) {
            return cmpType;
        }
    }
    // allocating a new type:
    Type* sliceType = pushToTypeBuf(&typer->sliceTypeBuf,T_SLICE);
    sliceType->as.Slice_element = elementType;
    return sliceType;
}
Type* NewOrGetFuncType(Manager* typer, int argsCount, Type* args[], Type* image) {
    // normalizing NULL args for 0-args: 
    if (argsCount == 0) {
        args = NULL;
        // printf("!!- INFO: Func with NULL args created.\n");
    }
    
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
    Type* funcType = pushToTypeBuf(&typer->funcTypeBuf,T_FUNC);
    funcType->as.Func.domainCount = argsCount;
    if (funcType->as.Func.domainCount > 0) {
        funcType->as.Func.domainArray = malloc(argsCount*sizeof(Type*));
        memcpy(funcType->as.Func.domainArray, args, argsCount*sizeof(Type*));
    } else {
        funcType->as.Func.domainArray = NULL;
    }
    funcType->as.Func.image = image;
    return funcType;
}
Type* NewOrGetTypefuncType(Manager* typer, Type* arg, Type* body) {
    // todo: consider de-duplicating typefuncs?
    Type* typefuncType = pushToTypeBuf(&typer->typefuncTypeBuf,T_TYPEFUNC);
    typefuncType->as.Typefunc.arg = arg;
    typefuncType->as.Typefunc.body = body;
    return typefuncType;
}
Type* NewOrGetTupleType(Manager* typer, TypeField* typefields, int typefieldCount) {
    Type* tupleType = pushToTypeBuf(&typer->tupleTypeBuf,T_TUPLE);
    tupleType->as.Compound_atn = getAtnChild(&typer->anyATN, ADT_MUL, typefields,typefieldCount,0, 0);
    tupleType->as.Compound_atn->owner = tupleType;
    return tupleType;
}
Type* NewOrGetUnionType(Manager* typer, TypeField* typefields, int typefieldCount) {
    Type* unionType = pushToTypeBuf(&typer->unionTypeBuf,T_UNION);
    unionType->as.Compound_atn = getAtnChild(&typer->anyATN, ADT_SUM, typefields,typefieldCount,0, 0);
    unionType->as.Compound_atn->owner = unionType;
    return unionType;
}
Type* NewOrGetUnaryIntrinsicType(Manager* typer, Loc loc, AstUnaryOperator op, Type* arg) {
    switch (op)
    {
        case UOP_GETREF:
        {
            return NewOrGetPtrType(typer,arg);
        }
        case UOP_DEREF:
        {
            // deref can be obtained through pattern-matching with a pointer
            Type* pointee = NewMetavarType(loc,typer, "deref-pointee");
            Type* derefedType = NewOrGetPtrType(typer,pointee);
            if (requireSubtyping(typer,"unary '*' (deref) operator",loc,arg,derefedType)) {
                return derefedType;
            } else {
                return NULL;
            }
        }
        case UOP_PLUS:
        case UOP_MINUS:
        {
            // T -> T, where T in {signed-int,float}
            Type* t = NewMetavarType(loc,typer, "unary-intrinsic-t");
            char const* why = (op == UOP_PLUS ? "unary-plus" : "unary-minus");
            requireSubtyping(typer,why,loc,arg,t);
            requireMetavarIsNumericOnly(t);
            // todo: add constraint requiring metavar be signed only.
            return t;
        }
        case UOP_NOT:
        {
            // always bool -> bool
            // recall s32 sub s64 (since we convert s32 to s64)
            // so t sub u1 <=> t = bool
            Type* boolType = GetIntType(typer,INT_1,0);
            if (requireSubtyping(typer,"unary 'not' operator",loc,boolType,arg)) {
                return boolType;
            } else {
                PostFeedback(FBK_ERROR, NULL, "Unary operator 'not' invalid with non-boolean type.");
                return NULL;
            }
        }
        default:
        {
            COMPILER_ERROR_VA("NotImplemented: NewOrGetUnaryIntrinsicType for AstUnaryOperator %s.", AstUnaryOperatorAsText(op));
            return NULL;
        }
    }
}
Type* NewOrGetBinaryIntrinsicType(Manager* typer, Loc loc, AstBinaryOperator op, Type* ltArg, Type* rtArg) {
    switch (op)
    {
        case BOP_LTHAN:
        case BOP_GTHAN:
        case BOP_LETHAN:
        case BOP_GETHAN:
        case BOP_EQUALS:
        case BOP_NEQUALS:
        {
            // (t,t) -> bool such that t is numeric
            // expect args to be of the same type.
            Type* boolType = GetIntType(typer,INT_1,0);
            Type* t = NewMetavarType(loc,typer,"binary-cmpeq-intrinsic-t");
            requireMetavarIsNumericOnly(t);
            TypingResult lhsResult = requireSubtyping(typer,"binary-cmp-lhs",loc,t,ltArg);
            TypingResult rhsResult = requireSubtyping(typer,"binary-cmp-rhs",loc,t,rtArg);
            if ((lhsResult != TYPING_FAILURE) && (rhsResult != TYPING_FAILURE)) {
                return boolType;
            } else {
                return NULL;
            }
        }
        case BOP_AND:
        case BOP_XOR:
        case BOP_OR:
        {
            // expect args to both be bool:
            Type* boolType = GetIntType(typer,INT_1,0);
            TypingResult lhsResult = requireSubtyping(typer,"binary-bool-lhs",loc,boolType,ltArg);
            TypingResult rhsResult = requireSubtyping(typer,"binary-bool-rhs",loc,boolType,rtArg);
            if ((lhsResult != TYPING_FAILURE) && (rhsResult != TYPING_FAILURE)) {
                return boolType;
            } else {
                return NULL;
            }
        }
        case BOP_MUL:
        case BOP_DIV:
        case BOP_REM:
        case BOP_ADD:
        case BOP_SUBTRACT:
        {
            // (t,t) -> t where t is numeric
            Type* t = NewMetavarType(loc,typer,"binary-addmul-intrinsic-t");
            requireMetavarIsNumericOnly(t);
            TypingResult lhsResult = requireSubtyping(typer,"binary-arithmetic-lhs",loc,t,ltArg);
            TypingResult rhsResult = requireSubtyping(typer,"binary-arithmetic-rhs",loc,t,rtArg);
            if ((lhsResult != TYPING_FAILURE) && (rhsResult != TYPING_FAILURE)) {
                return t;
            } else {
                return NULL;
            }
        }
        default:
        {
            COMPILER_ERROR_VA("NotImplemented: NewOrGetBinaryIntrinsicType for AstBinaryOperator %s.", AstBinaryOperatorAsText(op));
            return NULL;
        }
    }
}
Type* GetPhiType(Manager* typer, Loc loc, Type* cond, Type* ifTrue, Type* optIfFalse) {
    Type* boolType = GetIntType(typer,INT_1,0);
    if (requireSubtyping(typer,"if-bool",loc,boolType,cond) != TYPING_FAILURE) {
        if (optIfFalse != NULL) {
            Type* ifFalse = optIfFalse;
            Type* outType = NewMetavarType(loc,typer,"ite-result");
            TypingResult thenResult = requireSubtyping(typer,"if-then-equality",loc,ifTrue,outType);
            TypingResult elseResult = requireSubtyping(typer,"if-else-equality",loc,ifFalse,outType);
            if ((thenResult != TYPING_FAILURE) && (elseResult != TYPING_FAILURE)) {
                return outType;
            }
        } else {
            return GetUnitType(typer);
        }
    }
    return NULL;
}
Type* NewCastHelperType(Manager* typer, Type* to, Type* from) {
    Type* castType = pushToTypeBuf(&typer->miscTypeBuf,T_CAST);
    castType->as.Cast.to = to;
    castType->as.Cast.from = from;
    castType->as.Cast.checkStatus = 0;
    return castType;
}
Type* NewMetavarType(Loc loc, Manager* typer, char const* format, ...) {
    int metatypeIndexInBuf = typer->metatypeBuf.count;
    
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
    metatype->as.Meta.poisoned = 0;

    metatype->as.Meta.ext = &typer->metatypeExtBuf[metatypeIndexInBuf];
    metatype->as.Meta.ext->createdLoc = loc;
    metatype->as.Meta.ext->deferredSuperSB = NULL;
    metatype->as.Meta.ext->deferredSubSB = NULL;
    metatype->as.Meta.ext->solnUpdatedThisPass = 0;
    metatype->as.Meta.ext->numericOnly = 0;
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
            return type->as.Int.width;
        } else if (type->kind == T_META) {
            return GetIntTypeWidth(type);
        }
    }
    return __INT_NONE;
}
int GetIntTypeIsSigned(Type* type) {
    return type->as.Int.isSigned;
}
int GetIntTypeWidthInBits(Type* type) {
    assert(type->kind == T_INT);
    switch (type->as.Int.width)
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
Type** GetFuncTypeArgArray(Type* func) {
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

void MapCompoundType(Manager* typer, Type* compound, FieldCB cb, void* context) {
    mapCompoundType(typer,compound->as.Compound_atn,cb,context);
}

char const* GetMetatypeName(Type* type) {
    return type->as.Meta.name;
}

AstNode* GetModuleTypeAstNode(Type* moduleType) {
    return moduleType->as.Module.node;
}

//
// Manager:
// Recursively visits, calling 'applySubtyping'
// 'applySubtyping' updates types
//

void TypeNode(Manager* typer, AstNode* node) {
    RecursivelyVisitAstNode(typer, node, NULL, typer_post);
}

//
// Type checker:
//

int SolveAndCheckManager(Manager* typer) {
    return solveAndCheckAllMetavars(typer);
}

size_t GetTypeSizeInBytes(Manager* typer, Type* type) {
    TypeKind typeKind = type->kind;
    switch (typeKind)
    {
        case T_UNIT: 
        {
            return 0;
        }
        case T_INT:
        {
            switch (type->as.Int.width)
            {
                case INT_1: return 1;
                case INT_8: return 1;
                case INT_16: return 2;
                case INT_32: return 4;
                case INT_64: return 8;
                case INT_128: return 16;
                default: COMPILER_ERROR("Unknown int type size"); return -1;
            }
        }
        case T_FLOAT:
        {
            switch (type->as.Float_width) {
                case FLOAT_16: return 2;
                case FLOAT_32: return 4;
                case FLOAT_64: return 8;
                default: COMPILER_ERROR("Unknown float type size"); return -1;
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
        case T_FUNC:
        {
            // fixme: hard-coded func pointer size
            return 8;
        }
        default:
        {
            COMPILER_ERROR_VA("Unknown type kind in GetTypeSizeInBytes: %s", TypeKindAsText(typeKind));
            return -1;
        }
    }
}
Type* GetTypeSoln(Manager* typer, Type* type) {
    return getConcreteSoln(typer,type,NULL);
}

//
// Debug:
//

void PrintManager(Manager* typer) {
    printManager(typer,0);
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
        case T_STRING: return "T_STRING";
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
