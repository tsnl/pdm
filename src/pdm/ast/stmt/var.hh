#ifndef INCLUDED_PDM_AST_STMT_VAR_HH
#define INCLUDED_PDM_AST_STMT_VAR_HH

#include "stmt.hh"

#include "vax.hh"

namespace pdm::ast {
    class Manager;
    class LPattern;
    class Exp;
}

namespace pdm::ast {

    class VarStmt: public VaxStmt {
        friend Manager;

      protected:
        VarStmt(source::Loc loc, LPattern* lhs_lpattern, Exp* rhs_exp);
    };

    inline VarStmt::VarStmt(source::Loc loc, LPattern* lhs_lpattern, Exp* rhs_exp)
    :   VaxStmt(loc, Kind::VarStmt, lhs_lpattern, rhs_exp)
    {}

}

#endif  // INCLUDED_PDM_AST_STMT_VAR_HH