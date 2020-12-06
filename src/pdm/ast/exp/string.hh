#ifndef INCLUDED_PDM_AST_EXP_STRING_HH
#define INCLUDED_PDM_AST_EXP_STRING_HH

#include <vector>

#include "pdm/ast/kind.hh"
#include "pdm/ast/exp/exp.hh"
#include "pdm/ast/pattern/vpattern.hh"
#include "pdm/source/loc.hh"

namespace pdm::ast {

    class StringExp: public Exp {
        std::vector<int> m_content;
    
      public:
        StringExp(source::Loc loc, std::vector<int>&& content)
        : Exp(loc, Kind::StringExp),
          m_content(std::move(content)) {}
    };

}

#endif  // INCLUDED_PDM_AST_EXP_STRING_HH