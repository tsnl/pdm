#ifndef INCLUDED_PDM_AST_EXP_BINARY_HH
#define INCLUDED_PDM_AST_EXP_BINARY_HH

#include "pdm/ast/kind.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/exp/exp.hh"

namespace pdm::ast {

    enum class BinaryOperator {
        Mul, Div, Rem,
        Add, Subtract,
        Less, LessOrEq, Greater, GreaterOrEq,
        Equals, NotEquals,
        And, Or, XOr,
        __Count
    };

    class BinaryExp: public Exp {
      public:
        BinaryExp(source::Loc loc)
        : Exp(loc, Kind::BinaryExp) {}
    };

}

#endif  // INCLUDED_PDM_AST_EXP_BINARY_HH