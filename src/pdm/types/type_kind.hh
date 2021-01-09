#ifndef INCLUDED_PDM_TYPES_TYPE_KIND_HH
#define INCLUDED_PDM_TYPES_TYPE_KIND_HH

#include "pdm/core/integer.hh"

namespace pdm::types {
    enum class TypeKind: u64 {
        Void    = 0x1,
        String  = 0x2,
        Int     = 0x4,
        Float   = 0x8,
        Ref     = 0x10,
        Tuple   = 0x20,
        Struct  = 0x40,
        Enum    = 0x80,
        Module  = 0x100,
        Fn    = 0x200,

        __BitsetLimit = 0x200
    };
}

#endif  // INCLUDED_PDM_TYPES_TYPE_KIND_HH
