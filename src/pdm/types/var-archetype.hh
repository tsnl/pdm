#ifndef INCLUDED__PDM__TYPES__VAR_KIND_HH
#define INCLUDED__PDM__TYPES__VAR_KIND_HH

namespace pdm::types {

    enum class VarArchetype {
        Type,
        Class
    };

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
