#ifndef INCLUDED_PDM_AST_EXP_EXP_HH
#define INCLUDED_PDM_AST_EXP_EXP_HH

#include "pdm/ast/node.hh"

namespace pdm::ast {

    class Exp: public Node {
      protected:
        Exp(source::Loc loc, Kind kind)
        : Node(loc, kind) {}

      protected:
        virtual bool is_const_evaluable() const;
    };

}

#endif  // INCLUDED_PDM_AST_EXP_EXP_HH
