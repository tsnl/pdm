#ifndef INCLUDED_PDM_AST_STMT_STMT_HH
#define INCLUDED_PDM_AST_STMT_STMT_HH

#include <pdm/ast/kind.hh>
#include <pdm/ast/node.hh>

#include <pdm/source/loc.hh>

namespace pdm::ast {

    class Stmt: public Node {
      protected:
        Stmt(source::Loc loc, Kind stmt_kind)
        : Node(loc, stmt_kind) {}
    };

}

#endif  // INCLUDED_PDM_AST_STMT_STMT_HH