#ifndef INCLUDED__PDM__AST__HEADER__IMPORT_STMT_HH
#define INCLUDED__PDM__AST__HEADER__IMPORT_STMT_HH

#include "header_stmt.hh"

#include "pdm/core/intern.hh"
#include "pdm/core/utf8.hh"

namespace pdm::ast {
    class Manager;
    class ModExp;
    class Script;
}
namespace pdm::types {
    class TypeVar;
}
namespace pdm::ast {

    class ImportStmt: public HeaderStmt {
        friend Manager;

      private:
        intern::String  m_import_name;
        utf8::String    m_import_from;
        utf8::String    m_import_type;
        Script*         m_x_origin_script;
        ast::ModExp*    m_x_origin_mod_exp;
        types::TypeVar* m_x_exported_tv;

      protected:
        ImportStmt(source::Loc loc, intern::String import_name, utf8::String import_from, utf8::String import_type);

        // getters:
      public:
        [[nodiscard]] intern::String import_name() const;
        [[nodiscard]] utf8::String const& import_from_str() const;
        [[nodiscard]] utf8::String const& import_type_str() const;

        // set by dependency dispatcher:
      public:
        [[nodiscard]] Script* x_origin_script() const;
        void x_origin_script(Script* script);

        // set by scoper:
      public:
        [[nodiscard]] types::TypeVar* x_exported_tv() const;
        void x_exported_tv(types::TypeVar* exported_tv);

        [[nodiscard]] ast::ModExp* x_origin_mod_exp() const;
        void x_origin_mod_exp(ast::ModExp* set_mod_stmt);
    };

    inline intern::String ImportStmt::import_name() const {
        return m_import_name;
    }

    inline utf8::String const &ImportStmt::import_from_str() const {
        return m_import_from;
    }

    inline utf8::String const &ImportStmt::import_type_str() const {
        return m_import_type;
    }

    inline Script* ImportStmt::x_origin_script() const {
        return m_x_origin_script;
    }

    inline types::TypeVar* ImportStmt::x_exported_tv() const {
        return m_x_exported_tv;
    }

    inline ast::ModExp* ImportStmt::x_origin_mod_exp() const {
        return m_x_origin_mod_exp;
    }

    inline void ImportStmt::x_origin_mod_exp(ast::ModExp *set_mod_stmt) {
        m_x_origin_mod_exp = set_mod_stmt;
    }

    inline void ImportStmt::x_exported_tv(types::TypeVar *exported_tv) {
        m_x_exported_tv = exported_tv;
    }

    inline void ImportStmt::x_origin_script(Script *script) {
        m_x_origin_script = script;
    }

}

#endif  // INCLUDED__PDM__AST__HEADER__IMPORT_STMT_HH