#ifndef PDM__COMPILER__PLATFORM_HH
#define PDM__COMPILER__PLATFORM_HH

#include "pdm/core/intern.hh"

namespace pdm {

    bool validate_platform_string(intern::String platform_string);

    std::vector<intern::String> const& platform_strings();

}

#endif  // PDM__COMPILER__PLATFORM_HH
