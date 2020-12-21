#ifndef INCLUDED_PDM_AST_EXP_INT_HH
#define INCLUDED_PDM_AST_EXP_INT_HH

#include "pdm/core/integer.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/exp/exp.hh"

namespace pdm::ast {

    class Manager;

    class IntExp: public Exp {
        friend Manager;
      
      private:
        u64 m_value;
    
      protected:
        IntExp(source::Loc loc, u64 value)
        : Exp(loc, Kind::IntExp),
          m_value(value) {}
      
      public:
        u64 value() const {
            return m_value;
        }
    };

}

#endif  // INCLUDED_PDM_AST_EXP_INT_HH