#include "soln.hh"

namespace pdm::typer {

    UnitSoln UnitSoln::s_singleton {};

    IntSoln IntSoln::s_i8_singleton {"I8", 8, true};
    IntSoln IntSoln::s_i16_singleton {"I16", 16, true};
    IntSoln IntSoln::s_i32_singleton {"I32", 32, true};
    IntSoln IntSoln::s_i64_singleton {"I64", 64, true};
    IntSoln IntSoln::s_i128_singleton {"I128", 128, true};
    IntSoln IntSoln::s_u1_singleton {"U1", 1, false};
    IntSoln IntSoln::s_u8_singleton {"U8", 8, false};
    IntSoln IntSoln::s_u16_singleton {"U16", 16, false};
    IntSoln IntSoln::s_u32_singleton {"U32", 32, false};
    IntSoln IntSoln::s_u64_singleton {"U64", 64, false};
    IntSoln IntSoln::s_u128_singleton {"U128", 128, false};

    FloatSoln FloatSoln::s_float16_singleton {"F16", 16};
    FloatSoln FloatSoln::s_float32_singleton {"F32", 32};
    FloatSoln FloatSoln::s_float64_singleton {"F64", 64};
};