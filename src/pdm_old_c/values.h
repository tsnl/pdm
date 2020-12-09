#ifndef INCLUDED_VALUES_H
#define INCLUDED_VALUES_H

#include <stdint.h>

#include "useful.h"

// A limited execution environment for template evaluation

typedef struct ConstVal ConstVal;
typedef enum ConstValKind ConstValKind;
typedef union ConstValInfo ConstValInfo;

enum ConstValKind {
    CVK_SINT,
    CVK_UINT,
    CVK_FLOAT
};
union ConstValInfo {
    uint64_t Int;
    double Float;
};
struct ConstVal {
    ConstValKind kind;
    ConstValInfo as;
};

ConstVal* ConstVal_newSInt(ssize_t value);
ConstVal* ConstVal_newUInt(size_t value);
ConstVal* ConstVal_newFloat(long double value);

ConstVal* ConstVal_add(ConstVal* lhs, ConstVal* rhs);
ConstVal* ConstVal_subtract(ConstVal* lhs, ConstVal* rhs);
ConstVal* ConstVal_multiply(ConstVal* lhs, ConstVal* rhs);
ConstVal* ConstVal_divide(ConstVal* lhs, ConstVal* rhs);
ConstVal* ConstVal_modulo(ConstVal* lhs, ConstVal* rhs);
ConstVal* ConstVal_lt(ConstVal* lhs, ConstVal* rhs);
ConstVal* ConstVal_le(ConstVal* lhs, ConstVal* rhs);
ConstVal* ConstVal_gt(ConstVal* lhs, ConstVal* rhs);
ConstVal* ConstVal_ge(ConstVal* lhs, ConstVal* rhs);
ConstVal* ConstVal_eq(ConstVal* lhs, ConstVal* rhs);
ConstVal* ConstVal_neq(ConstVal* lhs, ConstVal* rhs);
ConstVal* ConstVal_and(ConstVal* lhs, ConstVal* rhs);
ConstVal* ConstVal_xor(ConstVal* lhs, ConstVal* rhs);
ConstVal* ConstVal_or(ConstVal* lhs, ConstVal* rhs);

// todo: run a visitor pass to postfix-eval nodes, with contagious NULL.
// then, we can run template monomorphization in emitter.

#endif  // INCLUDED_VALUES_H
