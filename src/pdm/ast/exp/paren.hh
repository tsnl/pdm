#ifndef INCLUDED_PDM_AST_EXP_PAREN_HH
#define INCLUDED_PDM_AST_EXP_PAREN_HH

#include "pdm/ast/kind.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/pattern/vpattern.hh"
#include "pdm/ast/exp/exp.hh"

namespace pdm::ast {

    class Manager;

    class ParenExp: public Exp {
        friend Manager;

      private:
        Exp* m_nested;
    
      protected:
        ParenExp(source::Loc loc, Exp* nested)
        : Exp(loc, Kind::ParenExp),
          m_nested(nested) {}
      
      public:
        [[nodiscard]] Exp* nested_exp() const;
    };

    inline Exp* ParenExp::nested_exp() const {
        return m_nested;
    }

}

#endif  // INCLUDED_PDM_AST_EXP_PAREN_HH