#ifndef INCLUDED_PDM_AST_EXP_UNIT_HH
#define INCLUDED_PDM_AST_EXP_UNIT_HH

#include "pdm/core/integer.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/exp/exp.hh"

namespace pdm::ast {

    class Manager;

    class UnitExp: public Exp {
        friend Manager;
      
      protected:
        explicit UnitExp(source::Loc loc);
    };

    inline UnitExp::UnitExp(source::Loc loc)
    :   Exp(loc, Kind::UnitExp) {}

}

#endif  // INCLUDED_PDM_AST_EXP_UNIT_HH