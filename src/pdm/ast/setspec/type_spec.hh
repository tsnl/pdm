#ifndef INCLUDED_PDM_AST_SETSPEC_TYPESPEC_HH
#define INCLUDED_PDM_AST_SETSPEC_TYPESPEC_HH

#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/node.hh"

#include "setspec.hh"

namespace pdm::ast {

    class TypeSpec: public SetSpec {
      public:
        inline TypeSpec(source::Loc loc, Kind node_kind);
    
      protected:
        bool check_x_spec_var(types::Var* var) const override;
    };

    inline TypeSpec::TypeSpec(source::Loc loc, Kind node_kind)
    :   SetSpec(loc, node_kind)
    {}
    
}

#endif  // INCLUDED_PDM_AST_TYPESPEC_TYPESPEC_HH