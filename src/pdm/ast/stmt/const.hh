#ifndef INCLUDED_PDM_AST_STMT_CONST_HH
#define INCLUDED_PDM_AST_STMT_CONST_HH

#include "pdm/source/loc.hh"
#include "pdm/ast/stmt/stmt.hh"
#include "pdm/ast/exp/exp.hh"
#include "pdm/ast/pattern/lpattern.hh"

namespace pdm::ast {

    class ConstStmt: public Stmt {
      private:
        LPattern* m_lhs_lpattern;
        Exp*      m_rhs_exp;

      public:
        ConstStmt(source::Loc loc, LPattern* lhs_lpattern, Exp* rhs_exp);

      public:
        [[nodiscard]] LPattern* lhs_lpattern() const;
        [[nodiscard]] Exp* rhs_exp() const;
    };

    inline ConstStmt::ConstStmt(source::Loc loc, LPattern* lhs_lpattern, Exp* rhs_exp)
    :   Stmt(loc, Kind::ConstStmt),
        m_lhs_lpattern(lhs_lpattern),
        m_rhs_exp(rhs_exp) {}

    inline LPattern* ConstStmt::lhs_lpattern() const {
        return m_lhs_lpattern;
    }

    inline Exp* ConstStmt::rhs_exp() const {
        return m_rhs_exp;
    }

}

#endif  // INCLUDED_PDM_AST_STMT_CONST_HH