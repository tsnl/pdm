#ifndef INCLUDED_PDM_FEEDBACK_SEVERITY_HH
#define INCLUDED_PDM_FEEDBACK_SEVERITY_HH

namespace pdm::feedback {

    enum class Severity {
        CompilerError,
        FatalError,
        Error,
        Warning,
        Info
    };

}

#endif  // INCLUDED_PDM_FEEDBACK_SEVERITY_HH