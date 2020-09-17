#include "typer.h"

#include <stddef.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>

#include "stb/stretchy_buffer.h"

#include "config.h"

typedef struct MetaInfo MetaInfo;
typedef struct TypeList TypeList;

struct MetaInfo {
    size_t id;
    char* name;
};

struct Type {
    TypeKind kind;
    union {
        IntWidth Int;
        FloatWidth Float;
        Type* Ptr;
        MetaInfo Meta;
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

static const size_t MAX_PTR_COUNT = (16*1024);
static const size_t MAX_METAVAR_COUNT = (MAX_AST_NODE_COUNT);

static size_t ptrTypeBufferCount = 0;
static Type ptrTypeBuffer[MAX_PTR_COUNT];

static size_t metaTypeBufferCount = 0;
static Type metaTypeBuffer[MAX_METAVAR_COUNT];

void pushSuperType(Type* sub, Type* sup) {
    int count = sb_count(sub->supTypesSb);
    for (int i = 0; i < count; i++) {
        if (sub->supTypesSb[i] == sup) {
            return;
        }
    }
    sb_push(sub->supTypesSb, sup);
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
        if (DEBUG && writeCount > 1024) {
            assert(0 && "Metatype name too long");
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

Type* SubstituteType(Type* arg, TypeSub* firstTypeSubP) {
    switch (arg->kind) {
        case T_INT:
        case T_FLOAT:
        case T_UNIT:
        {
            return arg;
        }
        case T_PTR:
        {
            return GetPtrType(SubstituteType(arg->as.Ptr, firstTypeSubP));
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
            assert(0 && "NotImplemented: ApplySubstitution for X type kind.");
            return NULL;
        }
    }
}

Type* TypeNode(AstNode* node) {
    switch (GetAstNodeKind(node)) {
        case AST_UNIT:
        {
            return GetUnitType();
        }
        case AST_LITERAL_FLOAT:
        {
            return GetFloatType(FLOAT64);
        }
        case AST_LITERAL_INT:
        {
            // TODO: automatically select width based on int value
            return GetIntType(INT64);
        }
        case AST_ID:
        {
            // using the type already provided by `scoper` based on the context used
            return GetAstNodeTypeP(node);
        }
        case AST_MODULE:
        {
            // TODO: type a module
            break;
        }
        case AST_STMT_BIND:
        {
            void* lhsType = GetAstBindStmtValueTypeP(node);
            void* rhsType = TypeNode(GetAstBindStmtRhs(node));
            if (!lhsType || !rhsType) {
                return NULL;
            }
            // TODO: set a subtyping relation between lhs and rhs types here.
            return NULL;
        }
        default:
        {
            if (DEBUG) {
                assert(0 && "Not implemented: TypeNode for AST node kind <?>");
            }
            break;
        }
    }
    return NULL;
}
