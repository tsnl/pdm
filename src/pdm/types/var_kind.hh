#ifndef INCLUDED__PDM__TYPES__VAR_KIND_HH
#define INCLUDED__PDM__TYPES__VAR_KIND_HH

namespace pdm::types {

    enum class VarKind {
        Type,
        Class,
        Template_RetValue,
        Template_RetType,
        Template_RetClass,
    };

    inline bool is_type_var_kind(VarKind var_kind);
    inline bool is_template_var_kind(VarKind var_kind);
}


namespace pdm::types {
    inline bool is_type_var_kind(VarKind var_kind) {
        return var_kind == VarKind::Type;
    }
    inline bool is_class_var_kind(VarKind var_kind) {
        return var_kind == VarKind::Class;
    }
    inline bool is_template_var_kind(VarKind var_kind) {
        return (
            var_kind == VarKind::Template_RetValue ||
            var_kind == VarKind::Template_RetType ||
            var_kind == VarKind::Template_RetClass
        );
    }
}

#endif  // INCLUDED__PDM__TYPES__VAR_KIND_HH
