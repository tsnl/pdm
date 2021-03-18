#ifndef INCLUDED__PDM__SOURCE__LOCAL_PACKAGE_SOURCE_HH
#define INCLUDED__PDM__SOURCE__LOCAL_PACKAGE_SOURCE_HH

#include <string>

#include "i-source.hh"
#include "source-kind.hh"

namespace pdm::source {

    class LocalPackageSource: public ISource {
      public:
        explicit LocalPackageSource(std::string&& pkg_dir_abs_path);
    };

    inline LocalPackageSource::LocalPackageSource(std::string&& pkg_dir_abs_path)
    :   ISource(std::move(pkg_dir_abs_path), SourceKind::LocalPackage)
    {}

}

#endif  // INCLUDED__PDM__SOURCE__LOCAL_PACKAGE_SOURCE_HH