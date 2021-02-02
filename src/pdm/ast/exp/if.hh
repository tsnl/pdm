#ifndef INCLUDED_PDM_AST_EXP_IF_HH
#define INCLUDED_PDM_AST_EXP_IF_HH

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/exp/exp.hh"

namespace pdm::ast {

    class Manager;

    class IfExp: public Exp {
        friend Manager;

      private:
        Exp* m_cond_exp;
        Exp* m_then_exp;
        Exp* m_else_exp;
    
      protected:
        IfExp(source::Loc loc, Exp* cond_exp, Exp* then_exp, Exp* else_exp);

      public:
        [[nodiscard]] Exp* cond_exp() const;
        [[nodiscard]] Exp* then_exp() const;
        [[nodiscard]] Exp* else_exp() const;
    };

    inline IfExp::IfExp(source::Loc loc, Exp* cond_exp, Exp* then_exp, Exp* else_exp)
    :   Exp(loc, Kind::IfExp),
        m_cond_exp(cond_exp),
        m_then_exp(then_exp),
        m_else_exp(else_exp) {}

    inline Exp* IfExp::cond_exp() const {
        return m_cond_exp;
    }

    inline Exp* IfExp::then_exp() const {
        return m_then_exp;
    }

    inline Exp* IfExp::else_exp() const {
        return m_else_exp;
    }

}

#endif  // INCLUDED_PDM_AST_EXP_IF_HH