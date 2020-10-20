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
// typedef struct IntrinsicInfo IntrinsicInfo;
// typedef struct PhiInfo PhiInfo;

typedef struct SubOrSuperTypeRec SubOrSuperTypeRec;
typedef SubOrSuperTypeRec SubtypeRec;
typedef SubOrSuperTypeRec SupertypeRec;
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

struct IntInfo {
    IntWidth width;
    int isSigned;
};
struct MetaInfo {
    void* soln;
    char* name;
    MetaInfoExt* ext;
    int poisoned;
};
struct MetaInfoExt {
    Loc createdLoc;
    SubtypeRec* deferredSubSB;
    SupertypeRec* deferredSuperSB;
    int solnUpdatedThisPass;

    // todo: add multiple 'meta solvers' for different cases:
    // - unary intrinsic
    // - binary intrinsic
    // - toggle use 'test' (subtypes) as soln (only in phi, ...)
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
    // todo: implement type ModuleInfo
};
union GenericTypeInfo {
    IntInfo Int;
    FloatWidth Float_width;
    Type* Ptr_pointee;
    MetaInfo Meta;
    FuncInfo Func;
    TypefuncInfo Typefunc;
    ModuleInfo Module;
    AdtTrieNode* Compound_atn;
    CastInfo Cast;
};
struct Type {
    TypeKind kind;
    union GenericTypeInfo as;
};

struct Typer {
    TyperCfg backupCfg;

    Type anyType;
    Type unitType;
    Type unsignedIntType[__INT_COUNT];
    Type signedIntType[__INT_COUNT];
    Type floatType[__FLOAT_COUNT];
    
    TypeBuf metatypeBuf;
    MetaInfoExt* metatypeExtBuf;

    TypeBuf ptrTypeBuf;
    TypeBuf typefuncTypeBuf;
    TypeBuf funcTypeBuf;
    TypeBuf moduleTypeBuf;
    TypeBuf tupleTypeBuf;
    TypeBuf unionTypeBuf;
    TypeBuf miscTypeBuf;

    AdtTrieNode anyATN;

    char* subtypingError;
};

struct SubOrSuperTypeRec {
    char const* why;
    Loc loc;
    Type* ptr;
};
enum SubtypingResult {
    // note: while merging results, we select the min. See `mergeSubtypingResults`.
    SUBTYPING_FAILURE = 0,
    SUBTYPING_DEFERRED,
    SUBTYPING_CONFIRM,
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
static AdtTrieNode* getAtnChild(AdtTrieNode* root, AdtOperator operator, TypeField* typefields, int typefieldCount, int index, int noNewEdges);
static AdtTrieNode* getCommonAncestorATN(AdtTrieNode* a, AdtTrieNode* b);
static int isAncestorATN(AdtTrieNode* parent, AdtTrieNode* child);

// typing constraints:
// 1. we attempt to eagerly check typing constraints (CONFIRM/FAILURE), but
// 2. if the result depends on a metavar, we return FAILURE unless matches hypothesis so far, then DEFERRED
// 3. after typing (no more solution possible), call 'solveDeferredMetavars' 
// usage:
// - call 'requireSubtyping' to assert that A sup B, thereby modifying the system.
static SubtypingResult requireSubtyping(Typer* typer, char const* why, Loc locWhere, Type* super, Type* sub);
static int solveAndCheckAllMetavars(Typer* typer);
// helpers (1)...
static SubtypingResult helpRequestSubtyping(Typer* typer, char const* why, Loc locWhere, Type* super, Type* sub);
static SubtypingResult helpRequestSubtyping_unitSuper(Typer* typer,char const* why,Loc loc, Type* super, Type* sub);
static SubtypingResult helpRequestSubtyping_intSuper(Typer* typer, char const* why, Loc loc, Type* super, Type* sub);
static SubtypingResult helpRequestSubtyping_floatSuper(Typer* typer, char const* why, Loc loc, Type* super, Type* sub);
static SubtypingResult helpRequestSubtyping_ptrSuper(Typer* typer, char const* why, Loc loc, Type* super, Type* sub);
static SubtypingResult helpRequestSubtyping_funcSuper(Typer* typer, char const* why, Loc loc, Type* super, Type* sub);
static SubtypingResult helpRequestSubtyping_tupleSuper(Typer* typer, char const* why, Loc loc, Type* super, Type* sub);
static SubtypingResult helpRequestSubtyping_unionSuper(Typer* typer, char const* why, Loc loc, Type* super, Type* sub);
static SubtypingResult helpRequestSubtyping_castSuper(Typer* typer, char const* why, Loc loc, Type* super, Type* sub);
static SubtypingResult helpRequestSubtyping_metaSuper(Typer* typer, char const* why, Loc loc, Type* meta, Type* sub);
static SubtypingResult helpRequestSubtyping_genericMetaSub(Typer* typer, char const* why, Loc loc, Type* super, Type* metaSub);
static SubtypingResult mergeSubtypingResults(SubtypingResult fst, SubtypingResult snd);
// helpers (2)...
static Type* getConcreteSoln(Typer* typer, Type* type, Type*** visitedMetavarSBP);
// helpers (3)...
static void resetSubtypingError(Typer* typer);
static char* getAndResetSubtypingError(Typer* typer);
static void setGenericSubtypingError(Typer* typer, char const* format, ...);
static void setMismatchedKindsSubtypingError(Typer* typer, Type* sup, Type* sub);
// helpers (4)
static int addTypeToSBSetP(Type*** sbp, Type* type);

// THE typer callback:
static int typer_post(void* rawTyper, AstNode* node);

// compound field traversal:
static void mapCompoundType(Typer* typer, AdtTrieNode* compound, FieldCB cb, void* sb);
static void accumulateCompoundFieldSizeSum(Typer* typer, void* sumP, SymbolID name, Type* type);
static void accumulateCompoundFieldSizeMax(Typer* typer, void* maxP, SymbolID name, Type* type);

// printing:
static void printTyper(Typer* typer, int metaOnly);
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
        .maxMiscCount = chunkSize,
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
    typer->funcTypeBuf = newTypeBuf("funcTypeBuf", typer->backupCfg.maxFuncCount);
    typer->typefuncTypeBuf = newTypeBuf("typefuncTypeBuf", typer->backupCfg.maxTypefuncCount);
    typer->moduleTypeBuf = newTypeBuf("moduleTypeBuf", typer->backupCfg.maxModuleCount);
    typer->tupleTypeBuf = newTypeBuf("structTypeBuf", typer->backupCfg.maxStructCount);
    typer->unionTypeBuf = newTypeBuf("unionTypeBuf", typer->backupCfg.maxUnionCount);
    typer->miscTypeBuf = newTypeBuf("miscTypeBuf", typer->backupCfg.maxMiscCount);

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

SubtypingResult requireSubtyping(Typer* typer, char const* why, Loc locWhere, Type* super, Type* sub) {
    // clearing the subtyping error:
    resetSubtypingError(typer);

    // attempting to perform the operation:
    SubtypingResult result = helpRequestSubtyping(typer,why,locWhere,super,sub);
    
    // if the operation failed, and we were supposed to write, generating feedback from the subtyping error (must be present).
    char* subtypingError = getAndResetSubtypingError(typer);
    if (result == SUBTYPING_FAILURE) {
        if (subtypingError) {
            FeedbackNote* note = CreateFeedbackNote("caused here...",locWhere,NULL);
            PostFeedback(
                FBK_ERROR,note,
                "Failed to apply subtyping for %s: %s", why, subtypingError
            );
            free(subtypingError);
        } else {
            COMPILER_ERROR("helper returned SUBTYPING_FAILURE but subtypingError (string) is unset/NULL.");
        }
    }

    // returning whatever result we obtained.
    return result;
}
int solveAndCheckAllMetavars(Typer* typer) {
    // todo: consider sorting in dependency order and avoiding multi-pass approach?
    int printDebugSnapshots = 1;

    int maxPassCount = 5000;
    int failureCountThisPass = -1;
    int failureCountLastPass = -1;
    
    if (DEBUG && printDebugSnapshots) {
        printf("!!- SNAPSHOT[INIT]\n");
        printTyper(typer,0);
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
            printTyper(typer,1);
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

SubtypingResult helpRequestSubtyping(Typer* typer, char const* why, Loc locWhere, Type* super, Type* sub) {
    switch (super->kind)
    {
        case T_UNIT: { return helpRequestSubtyping_unitSuper(typer,why,locWhere,super,sub); }
        case T_INT: { return helpRequestSubtyping_intSuper(typer,why,locWhere,super,sub); }
        case T_FLOAT: { return helpRequestSubtyping_floatSuper(typer,why,locWhere,super,sub); }
        case T_PTR: { return helpRequestSubtyping_ptrSuper(typer,why,locWhere,super,sub); }
        case T_FUNC: { return helpRequestSubtyping_funcSuper(typer,why,locWhere,super,sub); }
        case T_TUPLE: { return helpRequestSubtyping_tupleSuper(typer,why,locWhere,super,sub); }
        case T_UNION: { return helpRequestSubtyping_unionSuper(typer,why,locWhere,super,sub); }
        case T_META: { return helpRequestSubtyping_metaSuper(typer,why,locWhere,super,sub); }
        default:
        {
            COMPILER_ERROR_VA("NotImplemented: helpRequestSubtyping for super of unknown type kind %s.", TypeKindAsText(super->kind));
            return SUBTYPING_FAILURE;
        }
    }
}
SubtypingResult helpRequestSubtyping_unitSuper(Typer* typer,char const* why,Loc loc, Type* super, Type* sub) {
    switch (sub->kind)
    {
        case T_UNIT:
        {
            return SUBTYPING_CONFIRM;
        }
        case T_META:
        {
            return helpRequestSubtyping_genericMetaSub(typer,why,loc,super,sub);
        }
        case T_CAST:
        {
            return helpRequestSubtyping_unitSuper(typer,why,loc,super,sub->as.Cast.to);
        }
        default:
        {
            setMismatchedKindsSubtypingError(typer,super,sub);
            return SUBTYPING_FAILURE;
        }
    }
}
SubtypingResult helpRequestSubtyping_intSuper(Typer* typer, char const* why, Loc loc, Type* super, Type* sub) {
    switch (sub->kind)
    {
        case T_INT:
        {
            // A subtypes B <=> width(A) >= width(B)
            if (sub->as.Int.isSigned != super->as.Int.isSigned) {
                setGenericSubtypingError(typer,"subtyping mismatch: signed and unsigned");
                return SUBTYPING_FAILURE;
            }
            if (sub->as.Int.width >= super->as.Int.width) {
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
            return helpRequestSubtyping_genericMetaSub(typer,why,loc,super,sub);
        }
        case T_CAST:
        {
            return helpRequestSubtyping_intSuper(typer,why,loc,super,sub->as.Cast.to);
        }
        default:
        {
            setMismatchedKindsSubtypingError(typer,super,sub);
            return SUBTYPING_FAILURE;
        }
    }
}
SubtypingResult helpRequestSubtyping_floatSuper(Typer* typer, char const* why, Loc loc, Type* super, Type* sub) {
    switch (sub->kind)
    {
        case T_FLOAT:
        {
            // A subtypes B <=> width(A) >= width(B)
            if (sub->as.Int.width >= super->as.Int.width) {
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
            return helpRequestSubtyping_genericMetaSub(typer,why,loc,super,sub);
        }
        case T_CAST:
        {
            return helpRequestSubtyping_floatSuper(typer,why,loc,super,sub->as.Cast.to);
        }
        default:
        {
            setMismatchedKindsSubtypingError(typer,super,sub);
            return SUBTYPING_FAILURE;
        }
    }
}
SubtypingResult helpRequestSubtyping_ptrSuper(Typer* typer, char const* why, Loc loc, Type* super, Type* sub) {
    switch (sub->kind)
    {
        case T_PTR:
        {
            return helpRequestSubtyping(typer,why,loc,GetPtrTypePointee(super),GetPtrTypePointee(sub));
        }
        case T_META:
        {
            return helpRequestSubtyping_genericMetaSub(typer,why,loc,super,sub);
        }
        case T_CAST:
        {
            return helpRequestSubtyping_ptrSuper(typer,why,loc,super,sub->as.Cast.to);
        }
        default:
        {
            setMismatchedKindsSubtypingError(typer,super,sub);
            return SUBTYPING_FAILURE;
        }
    }
}
SubtypingResult helpRequestSubtyping_funcSuper(Typer* typer, char const* why, Loc loc, Type* super, Type* sub) {
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
            SubtypingResult imageResult = helpRequestSubtyping(
                typer,
                why,loc,
                GetFuncTypeImage(super),GetFuncTypeImage(sub)
            );
            if (imageResult == SUBTYPING_FAILURE) {
                setGenericSubtypingError(typer,"function return type subtyping failed");
                return SUBTYPING_FAILURE;
            }

            // check 3: are any arg subtypings in error?
            SubtypingResult mergedArgsResult = SUBTYPING_CONFIRM;
            int argCount = superArgCount;
            for (int argIndex = 0; argIndex < argCount; argIndex++) {
                Type* superArg = GetFuncTypeArgAt(super,argIndex);
                Type* subArg = GetFuncTypeArgAt(sub,argIndex);
                
                SubtypingResult result = helpRequestSubtyping(typer,why,loc,superArg,subArg);
                if (result == SUBTYPING_FAILURE) {
                    setGenericSubtypingError(typer,"function arg %d subtyping failed",argIndex);
                }
                mergedArgsResult = mergeSubtypingResults(mergedArgsResult,result);
            }
            if (mergedArgsResult == SUBTYPING_FAILURE) {
                return SUBTYPING_FAILURE;
            }

            // all checks passed? return result so far, i.e. DEFERRED or CONFIRM:
            return mergeSubtypingResults(imageResult,mergedArgsResult);
        }
        case T_META:
        {
            return helpRequestSubtyping_genericMetaSub(typer,why,loc,super,sub);
        }
        case T_CAST:
        {
            return helpRequestSubtyping_funcSuper(typer,why,loc,super,sub->as.Cast.to);
        }
        default:
        {
            setMismatchedKindsSubtypingError(typer,super,sub);
            return SUBTYPING_FAILURE;
        }
    }
}
SubtypingResult helpRequestSubtyping_tupleSuper(Typer* typer, char const* why, Loc loc, Type* super, Type* sub) {
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
                    setGenericSubtypingError(typer,"supertype %d-tuple and subtype %d-tuple do not have the same field count.",superATN->depth,subATN->depth);
                    return SUBTYPING_FAILURE;
                }

                // check 2: merge helpReadOrWriteSubtyping on each corresponding field type:
                SubtypingResult mergedFieldResults = SUBTYPING_CONFIRM;
                while (superATN->parent && subATN->parent && superATN != subATN) {
                    AdtTrieEdge superEdge = superATN->parent->edgesSb[superATN->parentEdgeIndex];
                    AdtTrieEdge subEdge = subATN->parent->edgesSb[subATN->parentEdgeIndex];
                    mergedFieldResults = mergeSubtypingResults(
                        mergedFieldResults,
                        helpRequestSubtyping(typer,why,loc,superEdge.type,subEdge.type)
                    );

                    superATN = superATN->parent;
                    subATN = subATN->parent;
                }
                return mergedFieldResults;
            }
        }
        case T_META:
        {
            return helpRequestSubtyping_genericMetaSub(typer,why,loc,super,sub);
        }
        case T_CAST:
        {
            return helpRequestSubtyping_tupleSuper(typer,why,loc,super,sub->as.Cast.to);
        }
        default:
        {
            setMismatchedKindsSubtypingError(typer,super,sub);
            return SUBTYPING_FAILURE;
        }
    }
}
SubtypingResult helpRequestSubtyping_unionSuper(Typer* typer, char const* why, Loc loc, Type* super, Type* sub) {
    switch (sub->kind) {
        case T_UNION:
        {
            if (super->as.Compound_atn == sub->as.Compound_atn) {
                return SUBTYPING_CONFIRM;
            } else {
                AdtTrieNode* superATN = super->as.Compound_atn;
                AdtTrieNode* subATN = sub->as.Compound_atn;
                
                // check 1: are the unions of the same length?
                if (superATN->depth != subATN->depth) {
                    setGenericSubtypingError(typer,"supertype %d-union and subtype %d-union do not have the same field count.",superATN->depth,subATN->depth);
                    return SUBTYPING_FAILURE;
                }
                // check 2: merge helpReadOrWriteSubtyping on each corresponding field type:
                SubtypingResult mergedFieldResults = SUBTYPING_CONFIRM;
                while (superATN->parent && subATN->parent && superATN != subATN) {
                    AdtTrieEdge superEdge = superATN->parent->edgesSb[superATN->parentEdgeIndex];
                    AdtTrieEdge subEdge = subATN->parent->edgesSb[subATN->parentEdgeIndex];
                    mergedFieldResults = mergeSubtypingResults(
                        mergedFieldResults,
                        helpRequestSubtyping(typer,why,loc,superEdge.type,subEdge.type)
                    );
                    superATN = superATN->parent;
                    subATN = subATN->parent;
                }
                return mergedFieldResults;
            }
        }
        case T_META:
        {
            return helpRequestSubtyping_genericMetaSub(typer,why,loc,super,sub);
        }
        case T_CAST:
        {
            return helpRequestSubtyping_unionSuper(typer,why,loc,super,sub->as.Cast.to);
        }
        default:
        {
            setMismatchedKindsSubtypingError(typer,super,sub);
            return SUBTYPING_FAILURE;
        }
    }
}
SubtypingResult helpRequestSubtyping_castSuper(Typer* typer, char const* why, Loc loc, Type* super, Type* sub) {
    // todo: check the cast at some point after solving metavars.
    return helpRequestSubtyping(typer,why,loc,super->as.Cast.to,sub);
}
SubtypingResult helpRequestSubtyping_metaSuper(Typer* typer, char const* why, Loc loc, Type* meta, Type* sub) {
    SubtypeRec subtypingRec = {why,loc,sub};
    sb_push(meta->as.Meta.ext->deferredSubSB, subtypingRec);
    return SUBTYPING_DEFERRED;
}
SubtypingResult helpRequestSubtyping_genericMetaSub(Typer* typer, char const* why, Loc loc, Type* super, Type* meta) {
    SupertypeRec supertypingRec = {why,loc,super};
    sb_push(meta->as.Meta.ext->deferredSuperSB, supertypingRec);
    return SUBTYPING_DEFERRED;
}
SubtypingResult mergeSubtypingResults(SubtypingResult fst, SubtypingResult snd) {
    return (fst < snd ? fst : snd);
}

//
// typing constraint helpers (2)
//

Type* getConcreteSoln(Typer* typer, Type* type, Type*** visitedMetavarSBP) {
    switch (type->kind) 
    {
        case T_UNIT:
        case T_FLOAT:
        case T_INT:
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
            Type** concreteArgsBuf = malloc(sizeof(Type) * argsCount);
            for (int domainIndex = 0; domainIndex < argsCount; domainIndex++) {
                Type* concreteArg = getConcreteSoln(typer,type->as.Func.domainArray[domainIndex],visitedMetavarSBP);
                if (concreteArg == NULL) {
                    failed = 1;
                    break;
                }
                concreteArgsBuf[domainIndex] = concreteArg;
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
                                SubtypingResult comparison = requireSubtyping(
                                    typer,"get-hypothesis",metavar->as.Meta.ext->createdLoc,
                                    concreteSupertype,hypothesis
                                );
                                COMPILER_ASSERT(comparison != SUBTYPING_DEFERRED, "expected 'getConcreteSoln' to return concrete types; no deferral allowed.");
                                if (comparison == SUBTYPING_CONFIRM) {
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
                                SubtypingResult comparison = requireSubtyping(
                                    typer,"get-test",metavar->as.Meta.ext->createdLoc,
                                    test,concreteSubtype
                                );
                                COMPILER_ASSERT(comparison != SUBTYPING_DEFERRED, "expected 'getConcreteSoln' to return concrete types; no deferral allowed.");
                                if (comparison == SUBTYPING_CONFIRM) {
                                    // new concreteSubtype is a subtype of the existing test. Updating...
                                    test = concreteSubtype;
                                }
                            }
                        }
                    }
                }
                
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
                    SubtypingResult result = requireSubtyping(typer,"new-soln-update",metavar->as.Meta.ext->createdLoc,hypothesis,test);
                    COMPILER_ASSERT(result != SUBTYPING_DEFERRED, "expected 'requireSubtyping' to operate on purely concrete args; no deferral allowed.");
                    if (result == SUBTYPING_CONFIRM) {
                        // hypothesis works!
                        metavar->as.Meta.soln = hypothesis;
                    } else {
                        // bad constraints, no solution exists. poison and return NULL
                        metavar->as.Meta.poisoned = 1;
                        metavar->as.Meta.soln = NULL;
                    }
                }

                if (metavar->as.Meta.soln) {
                    // since we have found a solution, we can propagate this info to all super and subtypes.
                    // this should be requested by super and subtypes later, but this may be required since we get only concrete types earlier.
                    int subtypeCount = sb_count(metavar->as.Meta.ext->deferredSubSB);
                    SubtypingResult result = SUBTYPING_CONFIRM;
                    for (int subtypeIndex = 0; subtypeIndex < subtypeCount; subtypeIndex++) {
                        SubtypeRec subtypeRec = metavar->as.Meta.ext->deferredSubSB[subtypeIndex];
                        
                        SubtypingResult subtypeResult = requireSubtyping(typer,subtypeRec.why,subtypeRec.loc,metavar->as.Meta.soln,subtypeRec.ptr);
                        result = mergeSubtypingResults(result,subtypeResult);
                    }
                    if (result == SUBTYPING_FAILURE) {
                        COMPILER_ERROR("Invalid metavar solution; returned SUBTYPING_FAILURE when applied to subtypes.");
                        return NULL;
                    }

                    // updating the 'solution found' flag:
                    metavar->as.Meta.ext->solnUpdatedThisPass = 1;
                }
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
                        SubtypingResult subtypingResult = requireSubtyping(typer,"vcast",NullLoc(),concreteTo,concreteFrom);
                        if (subtypingResult == SUBTYPING_CONFIRM) {
                            cast->as.Cast.checkStatus = 1;
                        } else if (subtypingResult == SUBTYPING_FAILURE) {
                            cast->as.Cast.checkStatus = -1;
                        } else {
                            COMPILER_ASSERT(subtypingResult == SUBTYPING_DEFERRED,"Unexpected subtypingResult == SUBTYPING_DEFERRED when operating on concrete types.");
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

void resetSubtypingError(Typer* typer) {
    if (typer->subtypingError) {
        free(typer->subtypingError);
        typer->subtypingError = NULL;
    }
}
char* getAndResetSubtypingError(Typer* typer) {
    char* message = typer->subtypingError;
    if (message) {
        // reset, but do not free! just move out and return.
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
// Typer:
//

int typer_post(void* rawTyper, AstNode* node) {
    Typer* typer = rawTyper;
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
            size_t value = GetAstIntLiteralValue(node);
            Type* type;
            if (value < (1ULL << 8)) {
                type = GetIntType(typer,INT_8,1);
            } else if (value < (1ULL << 16)) {
                type = GetIntType(typer,INT_16,1);
            } else if (value < (1ULL << 32)) {
                type = GetIntType(typer,INT_32,1);
            } else {
                type = GetIntType(typer,INT_64,1);
            }
            SetAstNodeTypingExt_Value(node,type);
            break;
        }
        case AST_LITERAL_FLOAT:
        {
            Type* t = GetFloatType(typer, FLOAT_32);
            SetAstNodeTypingExt_Value(node,t);
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
                SetAstNodeTypingExt_Type(node,foundType);
            } else if (lookupContext == ASTCTX_VALUE) {
                SetAstNodeTypingExt_Value(node,foundType);
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
        case AST_VLET:
        {
            Loc loc = GetAstNodeLoc(node);
            
            // symbols defined while visiting lhs pattern, we just need to get the pattern type:
            AstNode* lhs = GetAstLetStmtLhs(node);
            Type* lhsType = GetAstNodeTypingExt_Value(lhs);
            
            AstNode* rhs = GetAstLetStmtRhs(node);
            Type* rhsType = GetAstNodeTypingExt_Value(rhs);

            if (lhsType && rhsType) {
                requireSubtyping(typer, "<lhs> = <rhs>",loc, lhsType,rhsType);
            } else {
                COMPILER_ERROR("typer: lhsValueType or rhsType is NULL (or both) in AST_VLET");
            }
            break;
        }
        case AST_LAMBDA:
        {
            int argsCount = CountAstLambdaPatterns(node);
            Type** argsTypes = malloc(argsCount*sizeof(Type*));
            for (int argIndex = 0; argIndex < argsCount; argIndex++) {
                AstNode* argNode = GetAstLambdaPatternAt(node,argIndex);
                argsTypes[argIndex] = GetAstNodeTypingExt_Value(argNode);
            }
            
            AstNode* rhsNode = GetAstLambdaBody(node);
            Type* rhsType = GetAstNodeTypingExt_Value(rhsNode);
            if (rhsType) {
                SetAstNodeTypingExt_Value(node, NewOrGetFuncType(typer, argsCount, argsTypes, rhsType));
            } else {
                COMPILER_ERROR("typer: NULL rhsType for AST_LAMBDA");
            }

            Type* funcType = NewOrGetFuncType(typer,argsCount,argsTypes,rhsType);
            free(argsTypes); argsTypes = NULL;

            SetAstNodeTypingExt_Value(node,funcType);

            break;
        }
        case AST_VDEF:
        {
            // module items can be used in value and typing contexts
            Loc loc = GetAstNodeLoc(node);

            // todo: check for a template pattern, define a typefunc if required
            
            AstNode* rhs = GetAstDefValueStmtRhs(node);
            Type* rhsType = GetAstNodeTypingExt_Value(rhs);
            
            // the sole defined value was stored in the value slot in 'primer':
            Type* lhsType = GetAstNodeTypingExt_Value(node);

            int ok = (
                COMPILER_ASSERT(lhsType, "typer: Invalid lhsType in AST_VDEF") && 
                COMPILER_ASSERT(rhsType, "typer: Invalid rhsType in AST_VDEF")
            );
            if (ok) {
                requireSubtyping(typer,"def <lhs> = <rhs>",loc, rhsType,lhsType);
            }
            break;
        }
        case AST_TPATTERN_FIELD:
        case AST_TPATTERN_SINGLETON:
        case AST_VPATTERN_FIELD:
        case AST_VPATTERN_SINGLETON:
        {
            // metatypes created by scoper (since lexically scoped), so TypingExt_V/T already set.
            
            int isField = ((nodeKind == AST_TPATTERN_FIELD) || (nodeKind == AST_VPATTERN_FIELD));
            int isPatternSingleton = ((nodeKind == AST_TPATTERN_SINGLETON) || (nodeKind == AST_VPATTERN_SINGLETON));
            COMPILER_ASSERT(isField ^ isPatternSingleton, "Bad field/singleton context setup.");
            
            int typingContext = ((nodeKind == AST_TPATTERN_FIELD) || (nodeKind == AST_TPATTERN_SINGLETON));
            int valueContext = ((nodeKind == AST_VPATTERN_FIELD) || (nodeKind == AST_VPATTERN_SINGLETON));
            COMPILER_ASSERT(typingContext ^ valueContext, "Bad typing/value context setup.");

            // getting the RHS:
            AstNode* rhs = NULL;
            if (isField) {
                rhs = GetAstFieldRhs(node);
            } else {
                rhs = GetAstSingletonPatternRhs(node);
            }
            
            // getting the RHS type:
            Type* fieldType = NULL;
            if (typingContext) {
                fieldType = GetAstNodeTypingExt_Type(node);
            } else {
                fieldType = GetAstNodeTypingExt_Value(node);
            }

            // subtyping from RHS if present:
            if (rhs) {
                COMPILER_ASSERT(fieldType, "Non-null RHS but null field type in Typer.");

                Loc loc = GetAstNodeLoc(node);
                Type* rhsTypingType = GetAstNodeTypingExt_Type(rhs);
                if (rhsTypingType) {
                    requireSubtyping(typer,"type-field-rhs",loc, rhsTypingType,fieldType);
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
        {
            int isValuePattern = (nodeKind == AST_VPATTERN);
            int isTypePattern = (nodeKind == AST_TPATTERN);
            COMPILER_ASSERT(isValuePattern ^ isTypePattern, "Invalid input state in typer: expected nodeKind to be AST_VPATTERN or AST_TPATTERN.");

            int patternCount = GetAstPatternLength(node);
            Type* patternType = NULL;
            if (patternCount == 0) {
                // unit
                patternType = GetUnitType(typer);
            } else {
                // tuple
                TypeField* typefieldSB = NULL;
                for (int index = 0; index < patternCount; index++) {
                    AstNode* field = GetAstPatternFieldAt(node,index);
                    TypeField typefield = {
                        GetAstFieldName(field),
                        (isValuePattern ? GetAstNodeTypingExt_Value:GetAstNodeTypingExt_Type)(GetAstFieldRhs(field))
                    };
                    sb_push(typefieldSB,typefield);
                }
                patternType = NewOrGetTupleType(typer,typefieldSB,sb_count(typefieldSB));
                sb_free(typefieldSB);
            }
            (isValuePattern ? SetAstNodeTypingExt_Value:SetAstNodeTypingExt_Type)(node,patternType);

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
            COMPILER_ERROR("DISABLED: GetUnaryIntrinsicType in typer for AST_UNARY.");
            
            AstUnaryOperator operator = GetAstUnaryOperator(node);
            AstNode* arg = GetAstUnaryOperand(node);
            Type* argType = GetAstNodeTypingExt_Value(arg);
            // Type* type = GetUnaryIntrinsicType(typer,nodeLoc,operator,argType);
            Type* type = NULL;
            SetAstNodeTypingExt_Value(node,type);
            break;
        }
        case AST_BINARY:
        {
            COMPILER_ERROR("DISABLED: GetBinaryIntrinsicType in typer for AST_BINARY.");
            
            AstBinaryOperator binop = GetAstBinaryOperator(node);
            AstNode* ltArg = GetAstBinaryLtOperand(node);
            AstNode* rtArg = GetAstBinaryRtOperand(node);
            Type* ltArgType = GetAstNodeTypingExt_Value(ltArg);
            Type* rtArgType = GetAstNodeTypingExt_Value(rtArg);
            // Type* type = GetBinaryIntrinsicType(typer,nodeLoc,binop,ltArgType,rtArgType);
            Type* type = NULL;
            SetAstNodeTypingExt_Value(node,type);
            break;
        }
        case AST_ITE:
        {
            COMPILER_ERROR("DISABLED: GetPhiType in typer for AST_ITE.");

            AstNode* cond = GetAstIteCond(node);
            AstNode* ifTrue = GetAstIteIfTrue(node);
            AstNode* ifFalse = GetAstIteIfFalse(node);
            Type* condType = GetAstNodeTypingExt_Value(cond);
            Type* ifTrueType = GetAstNodeTypingExt_Value(ifTrue);
            Type* ifFalseType = ifFalse ? GetAstNodeTypingExt_Value(ifFalse) : GetUnitType(typer);
            // Type* type = GetPhiType(typer,nodeLoc,condType,ifTrueType,ifFalseType);
            Type* type = NULL;
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
        case AST_TDEF:
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
        case AST_EXTERN:
        {
            Loc loc = GetAstNodeLoc(node);

            AstNode* typespec = GetAstExternTypespec(node);
            Type* typespecType = GetAstNodeTypingExt_Type(typespec);
            
            Type* defType = GetAstNodeTypingExt_Value(node);

            if (defType && typespecType) {
                // filling typespecType as a solution (supertype) for defType
                requireSubtyping(typer,"extern",loc,typespecType,defType);
            }

            break;
        }
        case AST_VCAST:
        {
            AstNode* vcast = node;
            AstNode* type2val = GetAstVCastToTypespecType2Val(vcast);
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

void printTyper(Typer* typer, int metaOnly) {
    printf("!!- Typer dump:\n");
    
    if (!metaOnly) {
        printTypeLn(typer, &typer->unsignedIntType[INT_1]);
        printTypeLn(typer, &typer->unsignedIntType[INT_8]);
        printTypeLn(typer, &typer->unsignedIntType[INT_16]);
        printTypeLn(typer, &typer->unsignedIntType[INT_32]);
        printTypeLn(typer, &typer->unsignedIntType[INT_64]);
        printTypeLn(typer, &typer->unsignedIntType[INT_128]);
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
                    "meta%s %s (%d supers, %d subs)",
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

Type* GetUnitType(Typer* typer) {
    return &typer->unitType;
}
Type* GetIntType(Typer* typer, IntWidth width, int isSigned) {
    if (isSigned) {
        return &typer->signedIntType[width];
    } else {
        return &typer->unsignedIntType[width];
    }
}
Type* GetFloatType(Typer* typer, FloatWidth width) {
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
Type* NewOrGetTupleType(Typer* typer, TypeField* typefields, int typefieldCount) {
    Type* tupleType = pushToTypeBuf(&typer->tupleTypeBuf,T_TUPLE);
    tupleType->as.Compound_atn = getAtnChild(&typer->anyATN, ADT_MUL, typefields,typefieldCount,0, 0);
    tupleType->as.Compound_atn->owner = tupleType;
    return tupleType;
}
Type* NewOrGetUnionType(Typer* typer, TypeField* typefields, int typefieldCount) {
    Type* unionType = pushToTypeBuf(&typer->unionTypeBuf,T_UNION);
    unionType->as.Compound_atn = getAtnChild(&typer->anyATN, ADT_SUM, typefields,typefieldCount,0, 0);
    unionType->as.Compound_atn->owner = unionType;
    return unionType;
}
Type* NewCastHelperType(Typer* typer, Type* to, Type* from) {
    Type* castType = pushToTypeBuf(&typer->miscTypeBuf,T_CAST);
    castType->as.Cast.to = to;
    castType->as.Cast.from = from;
    castType->as.Cast.checkStatus = 0;
    return castType;
}
Type* NewMetavarType(Loc loc, Typer* typer, char const* format, ...) {
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

    metatype->as.Meta.ext = &typer->metatypeExtBuf[metatypeIndexInBuf];
    metatype->as.Meta.ext->createdLoc = loc;
    metatype->as.Meta.ext->deferredSuperSB = NULL;
    metatype->as.Meta.ext->deferredSubSB = NULL;
    metatype->as.Meta.ext->solnUpdatedThisPass = 0;
    metatype->as.Meta.poisoned = 0;
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

int SolveAndCheckTyper(Typer* typer) {
    return solveAndCheckAllMetavars(typer);
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
            switch (type->as.Int.width)
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
Type* GetTypeSoln(Typer* typer, Type* type) {
    return getConcreteSoln(typer,type,NULL);
}

//
// Debug:
//

void PrintTyper(Typer* typer) {
    printTyper(typer,0);
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
