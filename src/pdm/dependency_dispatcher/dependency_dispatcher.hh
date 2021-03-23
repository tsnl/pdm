#ifndef INCLUDED_PDM_DEPENDENCY_DISPATCHER_DEPENDENCY_DISPATCHER_HH
#define INCLUDED_PDM_DEPENDENCY_DISPATCHER_DEPENDENCY_DISPATCHER_HH

#include <string>

#include "pdm/ast/visitor.hh"

namespace pdm {
    class Compiler;
}
namespace pdm::ast {
    class Script;
    class Package;
}

namespace pdm::dependency_dispatcher {

    void dispatch_script_dependencies(Compiler* compiler, ast::Script* script);

    void dispatch_package_dependencies(Compiler* compiler, ast::Package* package);

}

#endif  // INCLUDED_PDM_DEPENDENCY_DISPATCHER_DEPENDENCY_DISPATCHER_HH
