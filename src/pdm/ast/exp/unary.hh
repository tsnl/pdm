#ifndef INCLUDED_PDM_AST_EXP_UNARY_HH
#define INCLUDED_PDM_AST_EXP_UNARY_HH

#include "pdm/ast/kind.hh"
#include "pdm/ast/exp/exp.hh"
#include "pdm/source/loc.hh"

namespace pdm::ast {

    class Manager;

    enum class UnaryOperator {
        Not,    // UnsignedInt -> UnsignedInt
        Plus,   // UnsignedInt -> SignedInt
        Minus,  // SignedInt -> SignedInt
        META_Count
    };

    class UnaryExp: public Exp {
        friend Manager;

      private:
        UnaryOperator m_operator;
        Exp*          m_operand;

      protected:
        UnaryExp(source::Loc loc, UnaryOperator unary_operator, Exp* operand);
      
      public:
        [[nodiscard]] UnaryOperator unary_operator() const;
        [[nodiscard]] Exp* operand() const;
    };

    inline UnaryExp::UnaryExp(source::Loc loc, UnaryOperator unary_operator, Exp *operand)
    :   Exp(loc, Kind::UnaryExp),
        m_operator(unary_operator),
        m_operand(operand) {}

    inline Exp *UnaryExp::operand() const {
        return m_operand;
    }

    inline UnaryOperator UnaryExp::unary_operator() const {
        return m_operator;
    }

}

#endif  // INCLUDED_PDM_AST_EXP_UNARY_HH