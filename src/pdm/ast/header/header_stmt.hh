#ifndef INCLUDED__PDM__AST__HEADER__HEADER_STMT_HH
#define INCLUDED__PDM__AST__HEADER__HEADER_STMT_HH

#include "pdm/ast/node.hh"

#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"

namespace pdm::ast {
    class HeaderStmt: public Node {
      protected:
        HeaderStmt(source::Loc loc, ast::Kind kind);
    };

    //
    // Inline implementations:
    //

    inline HeaderStmt::HeaderStmt(source::Loc loc, ast::Kind kind)
    :   Node(loc, kind)
    {}
}

#endif  // INCLUDED__PDM__AST__HEADER__HEADER_STMT_HH