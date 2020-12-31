#ifndef INCLUDED_PDM_SCOPER_ROOT_FRAME_HH
#define INCLUDED_PDM_SCOPER_ROOT_FRAME_HH

#include "pdm/scoper/frame.hh"

namespace pdm::typer {
    class Typer;
    class Var;
}

namespace pdm::scoper {

    class RootFrame: public Frame {
      public:
        RootFrame(typer::Typer* typer);

      private:
        void help_define_builtin_type(intern::String name, typer::Var* typer_var);
    };

}

#endif  // INCLUDED_PDM_SCOPER_ROOT_FRAME_HH
