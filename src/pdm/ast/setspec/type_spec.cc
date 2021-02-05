#include "type_spec.hh"

#include "pdm/types/var.hh"

namespace pdm::ast {

    bool TypeSpec::check_x_spec_var(types::Var* var) const {
        return (
            var->var_archetype() == types::VarArchetype::Type ||
            var->var_archetype() == types::VarArchetype::Template_RetType
        );
    }

}