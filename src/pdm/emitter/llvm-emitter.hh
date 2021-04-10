#ifndef INCLUDED__PDM__LLVM_EMITTER__LLVM_EMITTER_HH
#define INCLUDED__PDM__LLVM_EMITTER__LLVM_EMITTER_HH

#include <string>

#include "pdm/compiler/compiler.hh"

namespace pdm::emitter {

    // NOTE: when loading 'inout' or 'out' parameters, we need to...
    // 1. look up the actual value's llvm stack ptr var
    // 2. load the ptr of the formal parameter
    // 3. load from the ptr of the formal parameter
    // A similar **indirection** applies while 'storing'.
    enum class DimKind {
        Global_Val,
        Global_Fn,
        Arg_In,
        Arg_InOut,
        Arg_Out,
        Val,
        Var
    };
    struct Dim;

    DimKind dim_kind(Dim* dim);

    bool emit_llvm(Compiler* compiler_with_loaded_sources);

}

#endif  // INCLUDED__PDM__LLVM_EMITTER__LLVM_EMITTER_HH