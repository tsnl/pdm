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
    };

}

#endif  // INCLUDED_PDM_SCOPER_ROOT_FRAME_HH
