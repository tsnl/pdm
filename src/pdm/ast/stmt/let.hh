#ifndef INCLUDED_PDM_AST_STMT_LET_HH
#define INCLUDED_PDM_AST_STMT_LET_HH

#include "pdm/source/loc.hh"
#include "pdm/ast/exp/exp.hh"
#include "pdm/ast/stmt/stmt.hh"
#include "pdm/ast/pattern/lpattern.hh"

namespace pdm::ast {

    class Manager;

    class LetStmt: public Stmt {
      private:
        LPattern* m_lhs_lpattern;
        Exp*      m_rhs_body;

      protected:
        LetStmt(source::Loc loc, LPattern* lhs_lpattern, Exp* rhs_exp)
        : Stmt(loc, Kind::LetStmt),
          m_lhs_lpattern(lhs_lpattern),
          m_rhs_body(rhs_exp) {}
      
      public:
        LPattern* lhs_lpattern() const {
            return m_lhs_lpattern;
        }
        Exp* rhs_exp() const {
            return m_rhs_body;
        }
    };

}

#endif  // INCLUDED_PDM_AST_STMT_LET_HH