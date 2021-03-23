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

    bool type_script(types::Manager* manager, ast::Script* script);
    bool type_package(types::Manager* manager, ast::Package* package);

}

#endif  // INCLUDED_PDM_TYPER_TYPER_HH