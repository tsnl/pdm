#ifndef INCLUDED_PDM_AST_STMT_IMPORT_HH
#define INCLUDED_PDM_AST_STMT_IMPORT_HH

#include "pdm/core/intern.hh"
#include "pdm/ast/stmt/stmt.hh"
#include "pdm/ast/exp/exp.hh"

namespace pdm::ast {
    class Manager;
    class Script;
}

namespace pdm::ast {
    class ImportStmt: public Stmt {
        friend Manager;

      private:
        intern::String m_imported_name;
        utf8::String   m_imported_from;
        utf8::String   m_imported_type;
        Script*        m_x_imported_script;

      protected:
        ImportStmt(source::Loc loc, intern::String imported_name, utf8::String imported_from, utf8::String imported_type)
        : Stmt(loc, Kind::ImportStmt),
          m_imported_name(imported_name),
          m_imported_from(imported_from),
          m_imported_type(imported_type),
          m_x_imported_script(nullptr) {}
      
      // getters:
      public:
        intern::String imported_name() const {
            return m_imported_name;
        }
        utf8::String const& imported_from_str() const {
            return m_imported_from;
        }
        utf8::String const& imported_type_str() const {
            return m_imported_type;
        }

      // constructed/inferred properties:
      // - x_imported_script set by dependency_dispatcher
      public:
        Script* x_imported_script() const {
            return m_x_imported_script;
        }
        void x_imported_script(Script* script) {
            m_x_imported_script = script;
        }
    };

}

#endif  // INCLUDED_PDM_AST_STMT_IMPORT_HH