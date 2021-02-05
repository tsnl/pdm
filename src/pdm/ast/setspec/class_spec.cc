#include "class_spec.hh"

#include "pdm/types/var.hh"

namespace pdm::ast {

    bool ClassSpec::check_x_spec_var(types::Var* var) const {
        return (
            var->var_archetype() == types::VarArchetype::Class ||
            var->var_archetype() == types::VarArchetype::Template_RetClass
        );
    }

}