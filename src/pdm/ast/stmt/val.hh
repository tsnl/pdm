#ifndef INCLUDED_PDM_AST_STMT_LET_HH
#define INCLUDED_PDM_AST_STMT_LET_HH

#include "pdm/source/loc.hh"
#include "pdm/ast/exp/exp.hh"
#include "pdm/ast/stmt/stmt.hh"
#include "pdm/ast/pattern/lpattern.hh"

#include "vax.hh"

namespace pdm::ast {

    class ValStmt: public VaxStmt {
        friend Manager;

      protected:
        ValStmt(source::Loc loc, LPattern* lhs_lpattern, Exp* rhs_exp);
    };

    inline ValStmt::ValStmt(source::Loc loc, LPattern* lhs_lpattern, Exp* rhs_exp)
    :   VaxStmt(loc, Kind::ValStmt, lhs_lpattern, rhs_exp)
    {}

}

#endif  // INCLUDED_PDM_AST_STMT_LET_HH