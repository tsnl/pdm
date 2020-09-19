#ifndef INCLUDED_TYPER_H
#define INCLUDED_TYPER_H

#include <stddef.h>

#include "source.h"
#include "ast.h"

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
    T_MODULE, T_STRUCT, T_TUPLE
};
enum IntWidth {
    INT8,
    INT16,
    INT32,
    INT64
};
enum FloatWidth {
    FLOAT32,
    FLOAT64
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
// - if two types are structurally equivalent, they are also pointer equivalent
//

Type* GetUnitType(void);
Type* GetIntType(IntWidth width);
Type* GetFloatType(FloatWidth width);
Type* GetPtrType(Type* pointee);
Type* GetFuncType(Type* domain, Type* image);
Type* GetTypefuncType(Type* arg, Type* body);
Type* GetStruct(InputTypeFieldList const* inputFieldList);
Type* GetUnion(InputTypeFieldList const* inputFieldList);

Type* CreateMetatype(char const* format, ...);

//
// Getters for type info:
//

TypeKind GetTypeKind(Type* typeP);
IntWidth GetIntTypeWidth(Type* typeP);
FloatWidth GetFloatTypeWidth(Type* typeP);
Type* GetPtrTypePointee(Type* typeP);
size_t GetMetatypeID(Type* typeP);
char const* GetMetatypeName(Type* typeP);

//
// Recursively typing:
//

void TypeNode(Source* source, AstNode* node);

//
// Once nodes are typed, ready to typecheck:
//

int Typecheck(void);

#endif  // INCLUDED_TYPER_H
