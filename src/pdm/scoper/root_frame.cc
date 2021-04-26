#include "pdm/scoper/root_frame.hh"
#include "pdm/types/manager.hh"
#include "pdm/types/var.hh"

#include "pdm/ast/stmt/builtin.hh"

namespace pdm::scoper {

    RootFrame::RootFrame(types::Manager* frame_typer)
    :    Frame(FrameKind::Root, nullptr, frame_typer) {}

}
