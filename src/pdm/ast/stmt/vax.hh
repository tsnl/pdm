#ifndef INCLUDED__PDM__AST__STMT__VAX_HH
#define INCLUDED__PDM__AST__STMT__VAX_HH

#include "stmt.hh"

namespace pdm::ast {

    class VaxStmt: public Stmt {
      private:
        LPattern* m_lhs_lpattern;
        Exp*      m_rhs_exp;

      protected:
        VaxStmt(source::Loc loc, Kind kind, LPattern* lhs_lpattern, Exp* rhs_exp);

      public:
        [[nodiscard]] LPattern* lhs_lpattern() const;
        [[nodiscard]] Exp* rhs_exp() const;
    };

    inline VaxStmt::VaxStmt(source::Loc loc, Kind kind, LPattern* lhs_lpattern, Exp* rhs_exp)
    :   Stmt(loc, kind),
        m_lhs_lpattern(lhs_lpattern),
        m_rhs_exp(rhs_exp)
    {}

    inline LPattern* VaxStmt::lhs_lpattern() const {
        return m_lhs_lpattern;
    }
    inline Exp* VaxStmt::rhs_exp() const {
        return m_rhs_exp;
    }

}

#endif // INCLUDED__PDM__AST__STMT__VAX_HH
