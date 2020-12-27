#ifndef INCLUDED_PDM_CORE_UNITS_HH
#define INCLUDED_PDM_CORE_UNITS_HH

#include <cstddef>

namespace pdm {

    // returns the number of bytes occupied by N...
    inline size_t kilobytes_in_bytes(size_t count) { return 1024 * count; }
    inline size_t megabytes_in_bytes(size_t count) { return 1024 * kilobytes_in_bytes(count); }
    inline size_t gigabytes_in_bytes(size_t count) { return 1024 * megabytes_in_bytes(count); }

}

#endif  // INCLUDED_PDM_CORE_UNITS_HH