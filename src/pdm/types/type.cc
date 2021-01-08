#include "type.hh"

namespace pdm::types {

    VoidType VoidType::s_singleton {};
    StringType StringType::s_singleton {};

    IntType IntType::s_i8_singleton {"I8", 8, true};
    IntType IntType::s_i16_singleton {"I16", 16, true};
    IntType IntType::s_i32_singleton {"I32", 32, true};
    IntType IntType::s_i64_singleton {"I64", 64, true};
    IntType IntType::s_i128_singleton {"I128", 128, true};
    IntType IntType::s_u1_singleton {"U1", 1, false};
    IntType IntType::s_u8_singleton {"U8", 8, false};
    IntType IntType::s_u16_singleton {"U16", 16, false};
    IntType IntType::s_u32_singleton {"U32", 32, false};
    IntType IntType::s_u64_singleton {"U64", 64, false};
    IntType IntType::s_u128_singleton {"U128", 128, false};

    FloatType FloatType::s_float16_singleton {"F16", 16};
    FloatType FloatType::s_float32_singleton {"F32", 32};
    FloatType FloatType::s_float64_singleton {"F64", 64};
};