#ifndef INCLUDED_PDM_AST_EXP_ID_HH
#define INCLUDED_PDM_AST_EXP_ID_HH

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/exp/exp.hh"

namespace pdm::ast {

    class IdExp: public Exp {
      private:
        intern::String m_name;
    
      public:
        IdExp(source::Loc loc, intern::String name)
        : Exp(loc, Kind::IdExp),
          m_name(name) {}

      public:
        intern::String name() const {
            return m_name;
        }
    };

}

#endif  // INCLUDED_PDM_AST_EXP_ID_HH