#ifndef INCLUDED_PDM_AST_EXP_TUPLE_HH
#define INCLUDED_PDM_AST_EXP_TUPLE_HH

#include <vector>

#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/exp/exp.hh"

namespace pdm::ast {

    class TupleExp: public Exp {
      private:
        std::vector<Exp*> m_items;

      public:
        TupleExp(source::Loc loc, std::vector<Exp*>&& items)
        : Exp(loc, Kind::TupleExp),
          m_items(std::move(items)) {}
      
      public:
        std::vector<Exp*> const& items() const {
            return m_items;
        }
    };

}

#endif  // INCLUDED_PDM_AST_EXP_TUPLE_HH