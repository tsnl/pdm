#include "type_soln.hh"

namespace pdm::types {

    VoidTypeSoln VoidTypeSoln::s_singleton {};
    StringTypeSoln StringTypeSoln::s_singleton {};

    IntTypeSoln IntTypeSoln::s_i8_singleton {"I8", 8, true};
    IntTypeSoln IntTypeSoln::s_i16_singleton {"I16", 16, true};
    IntTypeSoln IntTypeSoln::s_i32_singleton {"I32", 32, true};
    IntTypeSoln IntTypeSoln::s_i64_singleton {"I64", 64, true};
    IntTypeSoln IntTypeSoln::s_i128_singleton {"I128", 128, true};
    IntTypeSoln IntTypeSoln::s_u1_singleton {"U1", 1, false};
    IntTypeSoln IntTypeSoln::s_u8_singleton {"U8", 8, false};
    IntTypeSoln IntTypeSoln::s_u16_singleton {"U16", 16, false};
    IntTypeSoln IntTypeSoln::s_u32_singleton {"U32", 32, false};
    IntTypeSoln IntTypeSoln::s_u64_singleton {"U64", 64, false};
    IntTypeSoln IntTypeSoln::s_u128_singleton {"U128", 128, false};

    FloatTypeSoln FloatTypeSoln::s_float16_singleton {"F16", 16};
    FloatTypeSoln FloatTypeSoln::s_float32_singleton {"F32", 32};
    FloatTypeSoln FloatTypeSoln::s_float64_singleton {"F64", 64};
};