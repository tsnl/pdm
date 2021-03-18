#ifndef INCLUDED__PDM__SOURCE__SOURCE_KIND_HH
#define INCLUDED__PDM__SOURCE__SOURCE_KIND_HH

namespace pdm::source {
    enum class SourceKind {
        LocalScript,
        LocalPackage,
        RemotePackage,
        META_Count
    };
}

#endif  // INCLUDED__PDM__SOURCE__SOURCE_KIND_HH
