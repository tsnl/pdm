#ifndef INCLUDED__PDM__SOURCE__SCRIPT_SOURCE_HH
#define INCLUDED__PDM__SOURCE__SCRIPT_SOURCE_HH

#include <string>

#include "i-source.hh"
#include "source-kind.hh"

namespace pdm::source {

    class LocalScriptSource: public ISource {
      public:
        explicit LocalScriptSource(std::string&& script_abs_path);
    };

    inline LocalScriptSource::LocalScriptSource(std::string&& script_abs_path)
    :   ISource(std::move(script_abs_path), SourceKind::LocalScript)
    {}

}

#endif  // INCLUDED__PDM__SOURCE__SCRIPT_SOURCE_HH