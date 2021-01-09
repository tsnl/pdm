#ifndef INCLUDED__PDM__TYPES__TYPEOP_RESULT_HH
#define INCLUDED__PDM__TYPES__TYPEOP_RESULT_HH

namespace pdm::types {
    enum class AssumeOpResult {
        Applied,
        ErrorOccurred
    };
    enum class TestOpResult {
        Confirmed,
        Denied,
        ErrorOccurred
    };
    enum class SolveIterResult {
        AtFixedPoint,
        UpdatedOrFresh,
        AtError
    };
}

#endif  // INCLUDED__PDM__TYPES__TYPEOP_RESULT_HH
