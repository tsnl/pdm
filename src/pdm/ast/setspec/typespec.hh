#ifndef INCLUDED_PDM_AST_SETSPEC_TYPESPEC_HH
#define INCLUDED_PDM_AST_SETSPEC_TYPESPEC_HH

#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/node.hh"

#include "setspec.hh"

namespace pdm::types {
    class Var;
}

namespace pdm::ast {

    class TypeSpec: public SetSpec {
      public:
        inline TypeSpec(source::Loc loc, Kind node_kind);
    };

    inline TypeSpec::TypeSpec(source::Loc loc, Kind node_kind)
    :   SetSpec(loc, node_kind)
    {}

}

#endif  // INCLUDED_PDM_AST_TYPESPEC_TYPESPEC_HH