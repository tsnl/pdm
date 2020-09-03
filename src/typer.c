#include "typer.h"

#include <stddef.h>
#include <assert.h>

#include "config.h"

struct Type {
    TypeKind kind;
    union {
        IntWidth Int;
        FloatWidth Float;
        Type* Ptr;
        size_t Meta;
    } as;
};

static Type builtinUnitType = {T_UNIT, {}};
static Type builtinIntTypeBuffer[] = {
    {T_INT, {.Int = INT8}},
    {T_INT, {.Int = INT16}},
    {T_INT, {.Int = INT32}},
    {T_INT, {.Int = INT64}}
};
static Type builtinFloatTypeBuffer[] = {
    {T_FLOAT, {.Float = FLOAT32}},
    {T_FLOAT, {.Float = FLOAT64}}
};

static const size_t MAX_PTR_STRUCTURE_COUNT = (16*1024);
static const size_t MAX_METAVAR_COUNT       = (16*1024);

static size_t ptrTypeBufferCount = 0;
static Type ptrTypeBuffer[MAX_PTR_STRUCTURE_COUNT];

static size_t metaTypeBufferCount = 0;
static Type metaTypeBuffer[MAX_METAVAR_COUNT];

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

Type* CreateMetaType(void) {
    Type* metaTypeP = &metaTypeBuffer[metaTypeBufferCount++];
    metaTypeP->kind = T_META;
    metaTypeP->as.Meta = metaTypeBufferCount;   // using the buffer count as a unique ID.
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
    return typeP->as.Meta;
}

//
// Substitutions:
//

Type* GetTypeAfterSubs(Type* arg, TypeSub* firstTypeSubP) {
    switch (arg->kind) {
    case T_INT:
    case T_FLOAT:
    case T_UNIT:
    {
        return arg;
    }
    case T_PTR:
    {
        return GetPtrType(GetTypeAfterSubs(arg->as.Ptr, firstTypeSubP));
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
        assert(0 && "NotImplemented: ApplySubstitution for X type kind.");
        return NULL;
    }
}
