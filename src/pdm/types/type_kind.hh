#ifndef INCLUDED_PDM_TYPER_TYPE_KIND_HH
#define INCLUDED_PDM_TYPER_TYPE_KIND_HH

namespace pdm::types {
    enum class TypeKind {
        Unknown = 0,
        Void,
        String,
        Int,
        Float,
        Ref,
        Struct,
        Enum,
        Module,
        Func
    };
}

#endif  // INCLUDED_PDM_TYPER_TYPE_KIND_HH
