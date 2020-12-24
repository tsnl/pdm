#ifndef INCLUDED_PDM_AST_STMT_SET_HH
#define INCLUDED_PDM_AST_STMT_SET_HH

#include "stmt.hh"
#include "../kind.hh"

#include "pdm/source/loc.hh"

namespace pdm::ast {
    class Manager;
    class Expr;
}

namespace pdm::ast {

    class SetStmt: public Stmt {
        friend Manager;
      
      private:
        ast::Expr* m_lhs;
        ast::Expr* m_rhs;

      protected:
        SetStmt(source::Loc loc, ast::Expr* lhs, ast::Expr* rhs)
        : Stmt(loc, Kind::SetStmt),
          m_lhs(lhs), m_rhs(rhs) {}
    };

}


#endif // INCLUDED_PDM_AST_STMT_SET_HH