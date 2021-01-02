#ifndef INCLUDED_PDM_AST_MOD_STMT_HH
#define INCLUDED_PDM_AST_MOD_STMT_HH

#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/stmt/stmt.hh"

namespace pdm::scoper {
    class Frame;
}
namespace pdm::types {
    class TypeVar;
}

namespace pdm::ast {

    class Manager;

    class ModStmt: public Stmt {
        friend Manager;

      private:
        intern::String     m_module_name;
        std::vector<Stmt*> m_defns;

      private:
        scoper::Frame*  m_x_module_frame;
        types::TypeVar* m_x_module_tv;

      public:
        ModStmt(source::Loc loc, intern::String module_name, std::vector<Stmt*>&& defns)
        : Stmt(loc, Kind::ModStmt),
          m_module_name(module_name),
          m_defns(defns),
          m_x_module_frame(nullptr),
          m_x_module_tv(nullptr) {}
      
      public:
        intern::String module_name() const {
            return m_module_name;
        }
        std::vector<Stmt*> const& defns() const {
            return m_defns;
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

}

#endif  // INCLUDED_PDM_AST_MODULE_STMT_HH