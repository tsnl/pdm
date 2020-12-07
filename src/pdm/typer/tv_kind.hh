#ifndef INCLUDED_PDM_TYPER_TV_KIND_HH
#define INCLUDED_PDM_TYPER_TV_KIND_HH

namespace pdm::typer {

    // TvKind helps decide which contexts a Tv can be used in.
    enum class TvKind {
        Error = -1,
        Unknown = 0,
        Value,
        Type,
        Typeclass,
        TFunc_Value,
        TFunc_Type
    };

}

#endif  // INCLUDED_PDM_TYPER_TV_KIND_HH
