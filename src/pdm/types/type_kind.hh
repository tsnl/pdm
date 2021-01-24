#ifndef INCLUDED_PDM_TYPES_TYPE_KIND_HH
#define INCLUDED_PDM_TYPES_TYPE_KIND_HH

#include <cassert>

#include "pdm/core/integer.hh"

namespace pdm::types {

    using TypeKindBitset = u32;

    // A 'TypeKind' is a lightweight type that partitions the set of values
    // based on the type operations supported on them.
    enum class TypeKind: TypeKindBitset {
        META_Min = 1,

        Void = META_Min,
        String,
        UnsignedInt,
        SignedInt,
        Float,
        Tuple,
        Struct,
        Enum,
        Module,
        Fn,
        Array,

        META_Max = Array,
    };

    template <typename T>
    constexpr inline 
    T _tk_bits_impl(TypeKind tk) {
        return static_cast<T>(1) << static_cast<T>(tk);
    }

    static_assert(
        _tk_bits_impl<size_t>(TypeKind::META_Max) <= static_cast<size_t>(std::numeric_limits<TypeKindBitset>::max()),
        "TypeKindBitset overflow: too many TypeKinds!"
    );
    
    inline TypeKindBitset tk_bits(TypeKind tk) {
        return _tk_bits_impl<TypeKindBitset>(tk);
    }

    inline char const* type_kind_as_str(TypeKind tk) {
        switch (tk)
        {
            case TypeKind::Void: return "Void";
            case TypeKind::String: return "String";
            case TypeKind::SignedInt: return "SignedInt";
            case TypeKind::UnsignedInt: return "UnsignedInt";
            case TypeKind::Float: return "Float";
            case TypeKind::Tuple: return "Tuple";
            case TypeKind::Struct: return "Struct";
            case TypeKind::Enum: return "Enum";
            case TypeKind::Module: return "Module";
            case TypeKind::Fn: return "Fn";
            case TypeKind::Array: return "Array";
        }
    }

    inline TypeKind extract_type_kind_from_bitset(TypeKindBitset bitset) {
        if (1 << static_cast<TypeKindBitset>(TypeKind::Void) == bitset) {
            return TypeKind::Void;
        }
        if (1 << static_cast<TypeKindBitset>(TypeKind::String) == bitset) {
            return TypeKind::String;
        }
        if (1 << static_cast<TypeKindBitset>(TypeKind::SignedInt) == bitset) {
            return TypeKind::SignedInt;
        }
        if (1 << static_cast<TypeKindBitset>(TypeKind::UnsignedInt) == bitset) {
            return TypeKind::UnsignedInt;
        }
        if (1 << static_cast<TypeKindBitset>(TypeKind::Float) == bitset) {
            return TypeKind::Float;
        }
        if (1 << static_cast<TypeKindBitset>(TypeKind::Tuple) == bitset) {
            return TypeKind::Tuple;
        }
        if (1 << static_cast<TypeKindBitset>(TypeKind::Struct) == bitset) {
            return TypeKind::Struct;
        }
        if (1 << static_cast<TypeKindBitset>(TypeKind::Enum) == bitset) {
            return TypeKind::Enum;
        }
        if (1 << static_cast<TypeKindBitset>(TypeKind::Module) == bitset) {
            return TypeKind::Module;
        }
        if (1 << static_cast<TypeKindBitset>(TypeKind::Fn) == bitset) {
            return TypeKind::Fn;
        }
        if (1 << static_cast<TypeKindBitset>(TypeKind::Array) == bitset) {
            return TypeKind::Array;
        }
        else {
            assert(0 && "Invalid bitset passed to `extract_type_kind_from_bitset`");
        }
    }

}

#endif  // INCLUDED_PDM_TYPES_TYPE_KIND_HH
