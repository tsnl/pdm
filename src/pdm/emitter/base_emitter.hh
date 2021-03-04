#ifndef INCLUDED__PDM__EMITTER__BASE_EMITTER_HH
#define INCLUDED__PDM__EMITTER__BASE_EMITTER_HH

#include "pdm/ast/visitor.hh"


namespace pdm::emitter {

    class BaseEmitter {
      protected:
        BaseEmitter() = default;

      protected:
        void* emit(ast::Script* entry_point_script);
      protected:
        virtual void* on_emit(ast::Script* entry_point_script) = 0;
    };

}

#endif  // INCLUDED__PDM__EMITTER__BASE_EMITTER_HH
