#ifndef INCLUDED_PDM_AST_STMT_SET_HH
#define INCLUDED_PDM_AST_STMT_SET_HH

#include "stmt.hh"
#include "../kind.hh"

#include "pdm/source/loc.hh"

namespace pdm::ast {
    class Manager;
    class Exp;
}

namespace pdm::ast {

    class SetStmt: public Stmt {
        friend Manager;
      
      private:
        ast::Exp* m_lhs_exp;
        ast::Exp* m_rhs_exp;

      protected:
        SetStmt(source::Loc loc, ast::Exp* lhs_exp, ast::Exp* rhs_exp)
        : Stmt(loc, Kind::SetStmt),
          m_lhs_exp(lhs_exp), 
          m_rhs_exp(rhs_exp) {}

      public:
        ast::Exp* lhs_exp() const {
            return m_lhs_exp;
        }
        ast::Exp* rhs_exp() const {
            return m_rhs_exp;
        }
    };

}


#endif // INCLUDED_PDM_AST_STMT_SET_HH
