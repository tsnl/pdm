#ifndef INCLUDED_PDM_SCOPER_ROOT_FRAME_HH
#define INCLUDED_PDM_SCOPER_ROOT_FRAME_HH

#include "pdm/scoper/frame.hh"

namespace pdm::typer {
    class Typer;
}

namespace pdm::scoper {

    class RootFrame: public Frame {
      public:
        RootFrame(typer::Typer* typer);

      private:
        void help_append_new_builtin_type_context(intern::String name, typer::TV* tv);
    };

}

#endif  // INCLUDED_PDM_SCOPER_ROOT_FRAME_HH
