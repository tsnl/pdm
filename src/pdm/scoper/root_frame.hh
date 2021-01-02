#ifndef INCLUDED_PDM_SCOPER_ROOT_FRAME_HH
#define INCLUDED_PDM_SCOPER_ROOT_FRAME_HH

#include "pdm/scoper/frame.hh"

namespace pdm::types {
    class Manager;
    class Var;
}

namespace pdm::scoper {

    class RootFrame: public Frame {
      public:
        RootFrame(types::Manager* typer);

      private:
        void help_define_builtin_type(intern::String name, types::Var* typer_var);
    };

}

#endif  // INCLUDED_PDM_SCOPER_ROOT_FRAME_HH
