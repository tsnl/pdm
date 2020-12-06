#ifndef INCLUDED_PDM_AST_SCRIPT_SCRIPT_HH
#define INCLUDED_PDM_AST_SCRIPT_SCRIPT_HH

#include <pdm/ast/node.hh>
#include <pdm/source/source.hh>

namespace pdm::ast {
    class Manager;
}

namespace pdm::ast {

    class Script: public Node {
        friend Manager;

      protected:
        Script(source::Source* source)
        : Node(source::Loc::none, Kind::Script) {}
    };

}   // namespace pdm::ast

#endif  // INCLUDED_PDM_AST_SCRIPT_SCRIPT_HH