#ifndef INCLUDED__PDM__LLVM_EMITTER__LLVM_EMITTER_HH
#define INCLUDED__PDM__LLVM_EMITTER__LLVM_EMITTER_HH

#include <string>

#include "pdm/compiler/compiler.hh"

namespace pdm::emitter {

    bool emit_llvm(Compiler* compiler_with_loaded_sources);

}

#endif  // INCLUDED__PDM__LLVM_EMITTER__LLVM_EMITTER_HH