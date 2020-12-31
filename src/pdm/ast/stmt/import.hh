#ifndef INCLUDED_PDM_AST_STMT_IMPORT_HH
#define INCLUDED_PDM_AST_STMT_IMPORT_HH

#include "stmt.hh"
#include "pdm/core/intern.hh"
#include "pdm/core/utf8.hh"

namespace pdm::ast {
    class Manager;
    class Script;
    class Exp;
    class Stmt;
    class ModStmt;
}
namespace pdm::typer {
    class TypeVar;
}

namespace pdm::ast {
    class ImportStmt: public Stmt {
        friend Manager;

      private:
        intern::String  m_import_name;
        utf8::String    m_import_from;
        utf8::String    m_import_type;
        Script*         m_x_origin_script;
        ast::ModStmt*   m_x_origin_mod_stmt;
        typer::TypeVar* m_x_exported_tv;

      protected:
        ImportStmt(source::Loc loc, intern::String import_name, utf8::String import_from, utf8::String import_type);
      
      // getters:
      public:
        intern::String import_name() const {
            return m_import_name;
        }
        utf8::String const& import_from_str() const {
            return m_import_from;
        }
        utf8::String const& import_type_str() const {
            return m_import_type;
        }

      // set by dependency dispatcher:
      public:
        Script* x_origin_script() const {
            return m_x_origin_script;
        }
        void x_origin_script(Script* script) {
            m_x_origin_script = script;
        }

      // set by scoper:
      public:
        typer::TypeVar* x_exported_tv() const {
            return m_x_exported_tv;
        }
        void x_exported_tv(typer::TypeVar* exported_tv) {
            m_x_exported_tv = exported_tv;
        }
        ast::ModStmt* x_origin_mod_stmt() const {
            return m_x_origin_mod_stmt;
        }
        void x_origin_mod_stmt(ast::ModStmt* set_mod_stmt) {
            m_x_origin_mod_stmt = set_mod_stmt;
        }
    };

}

#endif  // INCLUDED_PDM_AST_STMT_IMPORT_HH