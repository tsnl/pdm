#ifndef INCLUDED_PDM_AST_EXP_TUPLE_HH
#define INCLUDED_PDM_AST_EXP_TUPLE_HH

#include <vector>

#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/exp/exp.hh"

namespace pdm::ast {

    class Manager;

    class TupleExp: public Exp {
        friend Manager;

      private:
        std::vector<Exp*> m_items;

      protected:
        TupleExp(source::Loc loc, std::vector<Exp*>&& items);
      
      public:
        [[nodiscard]] std::vector<Exp*> const& items() const;
    };

    inline TupleExp::TupleExp(source::Loc loc, std::vector<Exp*>&& items)
    :   Exp(loc, Kind::TupleExp),
        m_items(std::move(items)) {}

    inline std::vector<Exp*> const& TupleExp::items() const {
        return m_items;
    }

}

#endif  // INCLUDED_PDM_AST_EXP_TUPLE_HH