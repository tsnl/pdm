#ifndef INCLUDED__PDM__TYPES__SOLVING_HH
#define INCLUDED__PDM__TYPES__SOLVING_HH

namespace pdm::types {

    enum class SolvePhase1_Result {
        InsufficientInfo,
        Error_MixedKind,
        Ok
    };

    enum class SolvePhase2_Result {
        AtFixedPoint,
        UpdatedOrFresh,
        AtError
    };

}

#endif  // INCLUDED__PDM__TYPES__SOLVING_HH