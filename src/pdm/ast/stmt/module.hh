#ifndef INCLUDED_PDM_AST_MODULE_STMT_HH
#define INCLUDED_PDM_AST_MODULE_STMT_HH

#include <string>

#include <pdm/core/intern.hh>
#include <pdm/source/loc.hh>

#include "node.hh"

namespace pdm::ast {

    class ModuleStmt: public Node {
      public:
        ModuleStmt(source::Loc loc, intern::String module_name)
        : Node(Kind::ModuleStmt, "module:"+std::string(module_name.str()), loc) {}
    };

}

#endif  // INCLUDED_PDM_AST_MODULE_STMT_HH