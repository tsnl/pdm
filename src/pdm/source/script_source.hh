#ifndef INCLUDED__PDM__SOURCE__SCRIPT_SOURCE_HH
#define INCLUDED__PDM__SOURCE__SCRIPT_SOURCE_HH

#include <string>

#include "i_source.hh"
#include "source_kind.hh"

namespace pdm::source {

    class ScriptSource: public ISource {
      public:
        explicit ScriptSource(std::string&& script_abs_path);
    };

    inline ScriptSource::ScriptSource(std::string&& script_abs_path)
    :   ISource(std::move(script_abs_path), SourceKind::Script)
    {}

}

#endif  // INCLUDED__PDM__SOURCE__SCRIPT_SOURCE_HH