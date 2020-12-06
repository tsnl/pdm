#ifndef INCLUDED_PDM_AST_TYPESPEC_TYPESPEC_HH
#define INCLUDED_PDM_AST_TYPESPEC_TYPESPEC_HH

#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/node.hh"

namespace pdm::ast {

    class Typespec: public Node {
      public:
        Typespec(source::Loc loc, Kind kind)
        : Node(loc, kind) {}
    };

}

#endif  // INCLUDED_PDM_AST_TYPESPEC_TYPESPEC_HH