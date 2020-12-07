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
      private:
        BinaryOperator m_operator;
        Exp* m_lhs_operand;
        Exp* m_rhs_operand;

      public:
        BinaryExp(source::Loc loc, BinaryOperator binary_operator, Exp* lhs_operand, Exp* rhs_operand)
        : Exp(loc, Kind::BinaryExp),
          m_operator(binary_operator),
          m_lhs_operand(lhs_operand),
          m_rhs_operand(rhs_operand) {}

      public:
        BinaryOperator binary_operator() const {
            return m_operator;
        }
        Exp* lhs_operand() const {
            return m_lhs_operand;
        }
        Exp* rhs_operand() const {
            return m_rhs_operand;
        }
    };

}

#endif  // INCLUDED_PDM_AST_EXP_BINARY_HH