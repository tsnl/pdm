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
      
      public:
        enum class Base {
            Dec,
            Hex
        };

      private:
        u64          m_value;
        IntExp::Base m_base;

      protected:
        IntExp(source::Loc loc, u64 value, IntExp::Base base)
        : Exp(loc, Kind::IntExp),
          m_value(value),
          m_base(base) {}
      
      public:
        u64 value() const {
            return m_value;
        }
        IntExp::Base base() const {
            return m_base;
        }
    };

}

#endif  // INCLUDED_PDM_AST_EXP_INT_HH