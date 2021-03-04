#include "base_emitter.hh"

namespace pdm::emitter {
    void* BaseEmitter::emit(ast::Script* entry_point_script) {
        return on_emit(entry_point_script);
    }
}