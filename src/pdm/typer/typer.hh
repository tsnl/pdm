#ifndef INCLUDED_PDM_TYPER_TYPER_HH
#define INCLUDED_PDM_TYPER_TYPER_HH

#include "pdm/ast/visitor.hh"

namespace pdm::types {
    class Manager;
}
namespace pdm::ast {
    class Script;
}

namespace pdm::typer {

    bool type(types::Manager* manager, ast::Script* script);

}

#endif  // INCLUDED_PDM_TYPER_TYPER_HH