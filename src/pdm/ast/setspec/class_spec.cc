#include "class_spec.hh"

#include "pdm/types/var.hh"

namespace pdm::ast {

    bool ClassSpec::check_x_spec_var(types::Var* var) const {
        return (
            var->var_kind() == types::VarKind::Class ||
            var->var_kind() == types::VarKind::Template_RetClass
        );
    }

}