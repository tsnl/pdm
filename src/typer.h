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
    T_UNIT,
    T_INT,
    T_FLOAT,
    T_PTR,
    T_META,
    T_FUNC,
    T_TUPLE, T_UNION,
    T_TYPEFUNC,
    T_MODULE,
};
enum IntWidth {
    INT_1,
    INT_8,
    INT_16,
    INT_32,
    INT_64,
    __INT_COUNT
};
enum FloatWidth {
    FLOAT_32,
    FLOAT_64,
    __FLOAT_COUNT
};

typedef struct Type Type;
typedef struct InputTypeFieldNode InputTypeFieldNode;
typedef struct InputTypeFieldNode InputTypeFieldList;

struct InputTypeFieldNode {
    SymbolID name;
    Type* type;
    InputTypeFieldNode* next;
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
};
TyperCfg CreateDefaultTyperCfg(void);
Typer* CreateTyper(TyperCfg config);

//
// Constructor methods:
//

Type* GetUnitType(Typer* typer);
Type* GetIntType(Typer* typer, IntWidth width);
Type* GetFloatType(Typer* typer, FloatWidth width);
Type* GetPtrType(Typer* typer, Type* pointee);
Type* GetFuncType(Typer* typer, Type* domain, Type* image);
Type* GetTypefuncType(Typer* typer, Type* arg, Type* body);
Type* GetTupleType(Typer* typer, InputTypeFieldList const* inputFieldList);
Type* GetUnionType(Typer* typer, InputTypeFieldList const* inputFieldList);

Type* CreateMetatype(Typer* typer, char const* format, ...);

//
// Getter methods for type info:
//

TypeKind GetTypeKind(Type* typeP);
IntWidth GetIntTypeWidth(Type* typeP);
FloatWidth GetFloatTypeWidth(Type* typeP);
Type* GetPtrTypePointee(Type* typeP);
int GetTupleTypeLength(Type* type);
int GetUnionTypeLength(Type* type);

size_t GetMetatypeID(Type* typeP);
char const* GetMetatypeName(Type* typeP);


//
// Typing and type-checking:
//

void TypeNode(Typer* typer, AstNode* node);
int Typecheck(Typer* typer);

#endif  // INCLUDED_TYPER_H
