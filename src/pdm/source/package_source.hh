#ifndef INCLUDED__PDM__SOURCE__SCRIPT_SOURCE_HH
#define INCLUDED__PDM__SOURCE__SCRIPT_SOURCE_HH

#include <string>

#include "i_source.hh"
#include "source_kind.hh"

namespace pdm::source {

    class PackageSource: public ISource {
      public:
        explicit PackageSource(std::string&& pkg_dir_abs_path);
    };

    inline PackageSource::PackageSource(std::string&& pkg_dir_abs_path)
    :   ISource(std::move(pkg_dir_abs_path), SourceKind::Package)
    {}

}

#endif  // INCLUDED__PDM__SOURCE__SCRIPT_SOURCE_HH