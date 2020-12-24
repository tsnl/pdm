#ifndef INCLUDED_PDM_AST_STMT_VAR_HH
#define INCLUDED_PDM_AST_STMT_VAR_HH

#include "stmt.hh"

namespace pdm::ast {
    class Manager;
    class LPattern;
    class Exp;
}

namespace pdm::ast {

    class VarStmt: public Stmt {
        friend Manager;

      private:
        LPattern* m_lhs_lpattern;
        Exp*      m_rhs_exp;

      protected:
        VarStmt(source::Loc loc, LPattern* lhs_lpattern, Exp* rhs_exp)
        : Stmt(loc, Kind::VarStmt),
          m_lhs_lpattern(lhs_lpattern),
          m_rhs_exp(rhs_exp) {}
    
      public:
        LPattern* lhs_lpattern() const {
            return m_lhs_lpattern;
        }
        Exp* rhs_exp() const {
            return m_rhs_exp;
        }
    };

}

#endif  // INCLUDED_PDM_AST_STMT_VAR_HH