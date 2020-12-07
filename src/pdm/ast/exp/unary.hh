#ifndef INCLUDED_PDM_AST_EXP_UNARY_HH
#define INCLUDED_PDM_AST_EXP_UNARY_HH

#include "pdm/ast/kind.hh"
#include "pdm/ast/exp/exp.hh"
#include "pdm/source/loc.hh"

namespace pdm::ast {

    enum class UnaryOperator {
        Not,
        GetRef, DeRef,
        Plus, Minus,
        __Count
    };

    class UnaryExp: public Exp {
      private:
        UnaryOperator m_operator;
        Exp*          m_operand;

      public:
        UnaryExp(source::Loc loc, UnaryOperator unary_operator, Exp* operand)
        : Exp(loc, Kind::UnaryExp),
          m_operator(unary_operator),
          m_operand(operand) {}
      
      public:
        UnaryOperator unary_operator() const {
            return m_operator;
        }
        Exp* operand() const {
            return m_operand;
        }
    };

}

#endif  // INCLUDED_PDM_AST_EXP_UNARY_HH