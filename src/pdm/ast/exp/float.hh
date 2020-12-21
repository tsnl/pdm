#ifndef INCLUDED_PDM_AST_EXP_FLOAT_HH
#define INCLUDED_PDM_AST_EXP_FLOAT_HH

#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/exp/exp.hh"

namespace pdm::ast {

    class Manager;

    class FloatExp: public Exp {
        friend Manager;
      
      private:
        long double m_value;
    
      protected:
        FloatExp(source::Loc loc, long double value)
        : Exp(loc, Kind::FloatExp),
          m_value(value) {}

      public:
        long double value() const {
            return m_value;
        }
    };

}

#endif  // INCLUDED_PDM_AST_EXP_FLOAT_HH