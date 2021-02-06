#ifndef INCLUDED_PDM_TYPES_TYPE_KIND_HH
#define INCLUDED_PDM_TYPES_TYPE_KIND_HH

#include <cassert>

#include "pdm/core/integer.hh"

namespace pdm::types {

    // A 'Kind' is a lightweight type that partitions the set of values
    // based on the type operations supported on them.
    // https://en.wikipedia.org/wiki/Kind_(type_theory)
    enum class Kind {
        META_Unknown,
        META_GetKindFromEdgesError,
        Void,
        String,
        UnsignedInt,
        SignedInt,
        Float,
        Tuple,
        Struct,
        Enum,
        Module,
        Fn,
        Array
    };

    inline char const* type_kind_as_str(Kind tk) {
        switch (tk)
        {
            case Kind::META_Unknown: return "UNKNOWN";
            case Kind::META_GetKindFromEdgesError: return "GET_KIND_FROM_EDGES_ERROR";
            case Kind::Void: return "Void";
            case Kind::String: return "String";
            case Kind::SignedInt: return "SignedInt";
            case Kind::UnsignedInt: return "UnsignedInt";
            case Kind::Float: return "Float";
            case Kind::Tuple: return "Tuple";
            case Kind::Struct: return "Struct";
            case Kind::Enum: return "Enum";
            case Kind::Module: return "Module";
            case Kind::Fn: return "Fn";
            case Kind::Array: return "Array";
        }
    }

    inline bool is_number_type_kind(Kind type_kind) {
        return (
            type_kind == Kind::SignedInt ||
            type_kind == Kind::UnsignedInt ||
            type_kind == Kind::Float
        );
    }

}

#endif  // INCLUDED_PDM_TYPES_TYPE_KIND_HH
