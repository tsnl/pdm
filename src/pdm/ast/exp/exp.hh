#ifndef INCLUDED_PDM_AST_EXP_EXP_HH
#define INCLUDED_PDM_AST_EXP_EXP_HH

#include "pdm/ast/node.hh"

namespace pdm::ast {

    class Exp: public Node {
      public:
        Exp(source::Loc loc, Kind kind)
        : Node(loc, kind) {}
    };

}

#endif  // INCLUDED_PDM_AST_EXP_EXP_HH