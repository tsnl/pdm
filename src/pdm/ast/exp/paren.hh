#ifndef INCLUDED_PDM_AST_EXP_PAREN_HH
#define INCLUDED_PDM_AST_EXP_PAREN_HH

#include "pdm/ast/kind.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/pattern/vpattern.hh"
#include "pdm/ast/exp/exp.hh"

namespace pdm::ast {

    class ParenExp: public Exp {
        Exp* m_nested;
    
      public:
        ParenExp(source::Loc loc, Exp* nested)
        : Exp(loc, Kind::ParenExp),
          m_nested(nested) {}
    };

}

#endif  // INCLUDED_PDM_AST_EXP_PAREN_HH