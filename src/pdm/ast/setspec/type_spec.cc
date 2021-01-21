#include "type_spec.hh"

#include "pdm/types/var.hh"

namespace pdm::ast {

    bool TypeSpec::check_x_spectype_var(types::Var* var) const {
        return (
            var->var_kind() == types::VarKind::Type ||
            var->var_kind() == types::VarKind::Template_RetType
        );
    }

}