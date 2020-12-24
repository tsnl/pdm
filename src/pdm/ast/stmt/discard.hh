#ifndef INCLUDED_PDM_AST_STMT_DISCARD_HH
#define INCLUDED_PDM_AST_STMT_DISCARD_HH

#include "stmt.hh"

namespace pdm::ast {
    class Manager;
    class Exp;
}

namespace pdm::ast {

    class DiscardStmt: public Stmt {
        friend Manager;

      private:
        Exp* m_exp;

      protected:
        DiscardStmt(source::Loc loc, Exp* exp)
        : Stmt(loc, Kind::DiscardStmt),
          m_exp(exp) {}
    };

}

#endif  // INCLUDED_PDM_AST_STMT_DISCARD_HH