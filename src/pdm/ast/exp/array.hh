#ifndef INCLUDED_PDM_AST_EXP_ARRAY_HH
#define INCLUDED_PDM_AST_EXP_ARRAY_HH

#include <vector>

#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/exp/exp.hh"

namespace pdm::ast {

    class Manager;

    class ArrayExp: public Exp {
        friend Manager;
      
      private:
        std::vector<Exp*> m_items;
      
      protected:
        ArrayExp(source::Loc loc, std::vector<Exp*>&& items)
        : Exp(loc, Kind::ArrayExp),
          m_items(std::move(items)) {}
      
      public:
        std::vector<Exp*> const& items() const {
            return m_items;
        }
    };

}

#endif  // INCLUDED_PDM_AST_EXP_ARRAY_HH
