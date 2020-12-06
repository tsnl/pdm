#ifndef INCLUDED_PDM_AST_EXP_ARRAY_HH
#define INCLUDED_PDM_AST_EXP_ARRAY_HH

#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/exp/exp.hh"

namespace pdm::ast {

    class ArrayExp: public Exp {
      private:
        std::vector<Node*> m_items;
      public:
        ArrayExp(source::Loc loc, std::vector<Node*>&& items)
        : Exp(Kind::ArrayExp, loc),
          m_items(std::move(items)) {}
    };

}

#endif  // INCLUDED_PDM_AST_EXP_ARRAY_HH