#ifndef INCLUDED__PDM__TYPES__VAR_KIND_HH
#define INCLUDED__PDM__TYPES__VAR_KIND_HH

namespace pdm::types {

    enum class VarKind {
        Type,
        Class,
        ValueTemplate,
        TypeTemplate,
        ClassTemplate,
    };

    inline bool is_type_var_kind(VarKind var_kind);
    inline bool is_template_var_kind(VarKind var_kind);
}


namespace pdm::types {
    inline bool is_type_var_kind(VarKind var_kind) {
        return (
            var_kind == VarKind::Type ||
            var_kind == VarKind::TypeTemplate || 
            var_kind == VarKind::ValueTemplate
        );
    }
    inline bool is_class_var_kind(VarKind var_kind) {
        return (
            var_kind == VarKind::Class ||
            var_kind == VarKind::ClassTemplate
        );
    }
    inline bool is_template_var_kind(VarKind var_kind) {
        return (
            var_kind == VarKind::ValueTemplate ||
            var_kind == VarKind::TypeTemplate ||
            var_kind == VarKind::ClassTemplate
        );
    }
}

#endif  // INCLUDED__PDM__TYPES__VAR_KIND_HH
