#ifndef INCLUDED_PDM_AST_EXP_INT_HH
#define INCLUDED_PDM_AST_EXP_INT_HH

#include "pdm/core/integer.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/exp/exp.hh"

namespace pdm::ast {

    class IntExp: public Exp {
        u64 m_value;
    
      public:
        IntExp(source::Loc loc, u64 value)
        : Exp(loc, Kind::IntExp),
          m_value(value) {}
    };

}

#endif  // INCLUDED_PDM_AST_EXP_INT_HH