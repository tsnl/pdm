#ifndef INCLUDED__PDM__TYPES__TYPEOP_RESULT_HH
#define INCLUDED__PDM__TYPES__TYPEOP_RESULT_HH

#include <algorithm>

namespace pdm::types {
    
    enum class TestOpResult {
        Confirmed,
        Denied,
        ErrorOccurred
    };
}

#endif  // INCLUDED__PDM__TYPES__TYPEOP_RESULT_HH
