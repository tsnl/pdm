#ifndef INCLUDED_TYPER_H
#define INCLUDED_TYPER_H

#include <stddef.h>

#include "source.h"
#include "ast.h"

typedef struct Typer Typer;
typedef struct TyperCfg TyperCfg;

typedef enum IntWidth IntWidth;
typedef enum FloatWidth FloatWidth;
typedef enum TypeKind TypeKind;

enum TypeKind {
    // concrete:
    T_ANY,
    T_UNIT,
    T_INT,
    T_FLOAT,
    T_PTR,
    T_FUNC,
    T_TUPLE, T_UNION,
    T_CAST,
    T_TYPEFUNC,
    T_MODULE,

    // abstract:
    T_META,
    
    // internal:
    __T_COUNT,
    __T_NONE
};
enum IntWidth {
    INT_1,
    INT_8,
    INT_16,
    INT_32,
    INT_64,
    INT_128,
    __INT_COUNT,
    __INT_NONE
};
enum FloatWidth {
    FLOAT_16,
    FLOAT_32,
    FLOAT_64,
    __FLOAT_COUNT,
    __FLOAT_NONE
};

typedef struct Type Type;
typedef void(*FieldCB)(Typer* typer, void* context, SymbolID name, Type* type);

// typedef struct InputTypeFieldNode InputTypeFieldNode;
// typedef struct InputTypeFieldNode InputTypeFieldList;

// struct InputTypeFieldNode {
//     SymbolID name;
//     Type* type;
//     InputTypeFieldNode* next;
// };

typedef struct TypeField TypeField;
struct TypeField {
    SymbolID name;
    Type* type;
};

//
// To obtain types,
// - only types from the same typer are interoperable.
// - if two types are structurally equivalent, they are also pointer equivalent
//

struct TyperCfg {
    size_t maxMetavarCount;
    size_t maxPtrCount;
    size_t maxTypefuncCount;
    size_t maxFuncCount;
    size_t maxModuleCount;
    size_t maxStructCount;
    size_t maxUnionCount;
    size_t maxMiscCount;
    size_t maxUnaryIntrinsicCount;
    size_t maxBinaryIntrinsicCount;
    size_t maxPhiCount;
};
TyperCfg NewDefaultTyperCfg(void);
Typer* NewTyper(TyperCfg config);

//
// Constructor methods:
//

Type* GetUnitType(Typer* typer);
Type* GetIntType(Typer* typer, IntWidth width, int isSigned);
Type* GetFloatType(Typer* typer, FloatWidth width);
Type* NewOrGetPtrType(Typer* typer, Type* pointee);
Type* NewOrGetFuncType(Typer* typer, int argsCount, Type* args[], Type* image);
Type* NewOrGetTypefuncType(Typer* typer, Type* arg, Type* body);
Type* NewOrGetTupleType(Typer* typer, TypeField* typefields, int typefieldCount);
Type* NewOrGetUnionType(Typer* typer, TypeField* typefields, int typefieldCount);

Type* NewOrGetUnaryIntrinsicType(Typer* typer, Loc loc, AstUnaryOperator op, Type* arg);
Type* NewOrGetBinaryIntrinsicType(Typer* typer, Loc loc, AstBinaryOperator op, Type* ltArg, Type* rtArg);
Type* GetPhiType(Typer* typer, Loc loc, Type* cond, Type* ifTrue, Type* ifFalse);

Type* NewCastHelperType(Typer* typer, Type* to, Type* from);
Type* NewMetavarType(Loc loc, Typer* typer, char const* format, ...);

//
// Getter methods for type info:
//

// Type* GetTypeSoln(Typer* typer, Type* type);
TypeKind GetTypeKind(Type* type);
IntWidth GetIntTypeWidth(Type* type);
int GetIntTypeIsSigned(Type* type);
int GetIntTypeWidthInBits(Type* type);
FloatWidth GetFloatTypeWidth(Type* typeP);
int GetFloatTypeWidthInBits(Type* type);
Type* GetPtrTypePointee(Type* typeP);
int GetFuncTypeArgCount(Type* func);
Type** GetFuncTypeArgArray(Type* func);
Type* GetFuncTypeArgAt(Type* func, int index);
Type* GetFuncTypeImage(Type* func);
int GetTupleTypeFieldCount(Type* type);
int GetUnionTypeFieldCount(Type* type);
void MapCompoundType(Typer* typer, Type* compound, FieldCB cb, void* context);

char const* GetMetatypeName(Type* typeP);

//
// Typing and type-checking:
//

void TypeNode(Typer* typer, AstNode* node);
int SolveAndCheckTyper(Typer* typer);

size_t GetTypeSizeInBytes(Typer* typer, Type* type);
Type* GetTypeSoln(Typer* typer, Type* type);

//
// Debug:
//

void PrintTyper(Typer* typer);

//
// Reflection:
//

char const* TypeKindAsText(TypeKind typeKind);

#endif  // INCLUDED_TYPER_H
