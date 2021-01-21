#ifndef INCLUDED_PDM_AST_MOD_STMT_HH
#define INCLUDED_PDM_AST_MOD_STMT_HH

#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/stmt/stmt.hh"

#include "mod_content.hh"

namespace pdm::scoper {
    class Frame;
}
namespace pdm::types {
    class TypeVar;
}
namespace pdm::ast {
    class Manager;
    class TPattern;
}

namespace pdm::ast {

    enum class ModStmtKind {
        TopModule,
        SubModule
    };

    class ModStmt: public ModContentStmt {
        friend Manager;

      private:
        intern::String               m_module_name;
        std::vector<TPattern*>       m_module_tpatterns;
        std::vector<ModContentStmt*> m_defns;
        ModStmtKind m_mod_stmt_kind;

      private:
        scoper::Frame*  m_x_module_frame;
        types::TypeVar* m_x_module_tv;

      public:
        ModStmt(source::Loc loc, intern::String module_name, std::vector<TPattern*> module_tpatterns, std::vector<ModContentStmt*>&& defns, ModStmtKind mod_stmt_kind);
      
      public:
        intern::String module_name() const {
            return m_module_name;
        }
        std::vector<ModContentStmt*> const& defns() const {
            return m_defns;
        }
        std::vector<TPattern*> const& tpatterns() const {
            return m_module_tpatterns;
        }
        ModStmtKind mod_stmt_kind() const {
            return m_mod_stmt_kind;
        }

      public:
        scoper::Frame* x_module_frame() const {
            return m_x_module_frame;
        }
        void x_module_frame(scoper::Frame* frame) {
            m_x_module_frame = frame;
        }

      public:
        types::TypeVar* x_module_tv() const {
            return m_x_module_tv;
        }
        void x_module_tv(types::TypeVar* module_tv) {
            m_x_module_tv = module_tv;
        }
    };

    inline ModStmt::ModStmt(source::Loc loc, intern::String module_name, std::vector<TPattern*> module_tpatterns, std::vector<ModContentStmt*>&& defns, ModStmtKind mod_stmt_kind)
    :   ModContentStmt(loc, Kind::ModStmt),
        m_module_name(module_name),
        m_defns(defns),
        m_x_module_frame(nullptr),
        m_x_module_tv(nullptr) ,
        m_mod_stmt_kind(mod_stmt_kind)
    {
        // setting this module as each node's parent:
        for (ModContentStmt* child_stmt: defns) {
            child_stmt->opt_parent_mod_stmt(this);
        }

        // ensuring top modules are not created with targs (syntactically impossible)
        if (m_mod_stmt_kind == ModStmtKind::TopModule) {
            assert(m_module_tpatterns.empty() && "Cannot pass tpatterns to TopModule.");
        }
    }

}

#endif  // INCLUDED_PDM_AST_MODULE_STMT_HH