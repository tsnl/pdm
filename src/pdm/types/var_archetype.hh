#ifndef INCLUDED__PDM__TYPES__VAR_KIND_HH
#define INCLUDED__PDM__TYPES__VAR_KIND_HH

namespace pdm::types {

    enum class VarArchetype {
        Type,
        Class,
        // Template_RetValue,
        // Template_RetType,
        // Template_RetClass,
    };

    inline bool is_type_var_archetype(VarArchetype var_kind);
    inline bool is_template_var_kind(VarArchetype var_kind);

    inline char const* var_archetype_as_str(VarArchetype vk);
}

namespace pdm::types {
    inline char const* var_archetype_as_str(VarArchetype vk) {
        switch (vk)
        {
            case VarArchetype::Type: return "Type";
            case VarArchetype::Class: return "Class";
        }
    }
}

#endif  // INCLUDED__PDM__TYPES__VAR_KIND_HH
