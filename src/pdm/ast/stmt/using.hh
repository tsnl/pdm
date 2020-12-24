#ifndef INCLUDED_PDM_AST_STMT_USING_HH
#define INCLUDED_PDM_AST_STMT_USING_HH

#include "stmt.hh"

namespace pdm::ast {
    class Manager;
    class Exp;
}

namespace pdm::ast {

    class UsingStmt: public Stmt {
        friend Manager;

      private:
        Exp* m_used_exp;
    
      protected:
        UsingStmt(source::Loc loc, Exp* used_exp)
        : Stmt(loc, Kind::UsingStmt),
          m_used_exp(used_exp) {}

      public:
        Exp* used_exp() const {
            return m_used_exp;
        }
    };

}

#endif  // INCLUDED_PDM_AST_STMT_USING_HH
