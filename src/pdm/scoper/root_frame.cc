#include "pdm/scoper/root_frame.hh"
#include "pdm/typer/typer.hh"
#include "pdm/typer/var.hh"

#include "pdm/ast/stmt/builtin_type.hh"

namespace pdm::scoper {

    RootFrame::RootFrame(typer::Typer* frame_typer)
    : Frame(FrameKind::Root, nullptr, frame_typer) {}

}
