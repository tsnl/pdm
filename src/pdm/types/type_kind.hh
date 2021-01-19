#ifndef INCLUDED_PDM_TYPES_TYPE_KIND_HH
#define INCLUDED_PDM_TYPES_TYPE_KIND_HH

#include "pdm/core/integer.hh"

namespace pdm::types {

    using TypeKindBitset = u32;

    // A 'TypeKind' is a lightweight type that partitions the set of values
    // based on the type operations supported on them.
    enum class TypeKind: TypeKindBitset {
        Void = 1,
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
        __Max = Fn,
    };

    template <typename T>
    constexpr inline 
    T __tk_bits_impl(TypeKind tk) {
        return static_cast<T>(1) << static_cast<T>(tk);
    }

    static_assert(
        __tk_bits_impl<size_t>(TypeKind::__Max) <= static_cast<size_t>(std::numeric_limits<TypeKindBitset>::max()),
        "TypeKindBitset overflow: too many TypeKinds!"
    );
    
    inline TypeKindBitset tk_bits(TypeKind tk) {
        return __tk_bits_impl<TypeKindBitset>(tk);
    }

}

#endif  // INCLUDED_PDM_TYPES_TYPE_KIND_HH
