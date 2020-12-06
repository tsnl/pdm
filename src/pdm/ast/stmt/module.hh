#ifndef INCLUDED_PDM_AST_MODULE_STMT_HH
#define INCLUDED_PDM_AST_MODULE_STMT_HH

#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/stmt/stmt.hh"

namespace pdm::ast {

    class ModuleStmt: public Stmt {
      private:
        source::Loc        m_loc;
        intern::String     m_module_name;
        std::vector<Stmt*> m_defns;
      public:
        ModuleStmt(source::Loc loc, intern::String module_name, std::vector<Stmt*> defns)
        : Stmt(loc, Kind::ModuleStmt),
          m_loc(loc),
          m_module_name(module_name),
          m_defns(defns) {}
    };

}

#endif  // INCLUDED_PDM_AST_MODULE_STMT_HH