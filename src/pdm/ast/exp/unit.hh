#ifndef INCLUDED_PDM_AST_EXP_UNIT_HH
#define INCLUDED_PDM_AST_EXP_UNIT_HH

#include "pdm/core/integer.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/exp/exp.hh"

namespace pdm::ast {

    class UnitExp: public Exp {
      public:
        UnitExp(source::Loc loc)
        : Exp(loc, Kind::UnitExp) {}
    };

}

#endif  // INCLUDED_PDM_AST_EXP_UNIT_HH