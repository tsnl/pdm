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

      public:
        class Field;
        class FieldGroup;

        class Field {
            friend FieldGroup;

          private:
            Script* m_x_origin_script;
            ast::ModExp* m_x_origin_mod_exp;
            types::TypeVar* m_x_exported_tv;
            FieldGroup* m_parent_group;
            intern::String m_import_name;
            source::Loc m_loc;

          public:
            explicit Field(source::Loc loc, intern::String import_name);

          public:
            [[nodiscard]] FieldGroup* parent_group() const;
            [[nodiscard]] intern::String import_name() const;
            [[nodiscard]] source::Loc loc() const;

            [[nodiscard]] Script* x_origin_script() const;
            [[nodiscard]] ast::ModExp* x_origin_mod_exp() const;
            [[nodiscard]] types::TypeVar* x_exported_tv() const;

            void x_origin_script(Script* set_script);
            void x_origin_mod_exp(ast::ModExp* set_mod_stmt);
            void x_exported_tv(types::TypeVar* set_exported_tv);
        };
        class FieldGroup {
            friend ImportStmt;

          private:
            std::vector<Field*> m_fields;
            utf8::String m_from_path;
            source::Loc m_loc;
            ImportStmt* m_parent_import_stmt;

          public:
            FieldGroup(source::Loc loc, std::vector<Field*> fields, utf8::String from_path);

          public:
            [[nodiscard]] ImportStmt* parent_import_stmt() const;
            [[nodiscard]] source::Loc loc() const;
            [[nodiscard]] utf8::String const& from_path() const;
            [[nodiscard]] std::vector<Field*> const& fields() const;
        };

      private:
        std::vector<FieldGroup*> m_field_groups;

      protected:
        ImportStmt(source::Loc loc, std::vector<FieldGroup*> field_groups);

      public:
        [[nodiscard]] std::vector<FieldGroup*> const& field_groups() const;
    };

    inline ImportStmt::Field::Field(source::Loc loc, intern::String import_name)
    :   m_x_origin_script(nullptr),
        m_x_origin_mod_exp(nullptr),
        m_x_exported_tv(nullptr),
        m_parent_group(nullptr),
        m_import_name(import_name),
        m_loc(loc)
    {}

    inline ImportStmt::FieldGroup::FieldGroup(source::Loc loc, std::vector<Field*> fields, utf8::String from_path)
    :   m_fields{std::move(fields)},
        m_from_path(std::move(from_path)),
        m_loc{loc},
        m_parent_import_stmt(nullptr)
    {
        for (Field* field: m_fields) {
            field->m_parent_group = this;
        }
    }

    inline source::Loc ImportStmt::FieldGroup::loc() const {
        return m_loc;
    }

    inline std::vector<ImportStmt::Field*> const& ImportStmt::FieldGroup::fields() const {
        return m_fields;
    }

    inline source::Loc ImportStmt::Field::loc() const {
        return m_loc;
    }

    inline ImportStmt::FieldGroup* ImportStmt::Field::parent_group() const {
        return m_parent_group;
    }

    inline ImportStmt* ImportStmt::FieldGroup::parent_import_stmt() const {
        return m_parent_import_stmt;
    }

    inline intern::String ImportStmt::Field::import_name() const {
        return m_import_name;
    }

    inline utf8::String const &ImportStmt::FieldGroup::from_path() const {
        return m_from_path;
    }

    inline Script* ImportStmt::Field::x_origin_script() const {
        return m_x_origin_script;
    }

    inline types::TypeVar* ImportStmt::Field::x_exported_tv() const {
        return m_x_exported_tv;
    }

    inline ast::ModExp* ImportStmt::Field::x_origin_mod_exp() const {
        return m_x_origin_mod_exp;
    }

    inline void ImportStmt::Field::x_origin_mod_exp(ast::ModExp *set_mod_stmt) {
        m_x_origin_mod_exp = set_mod_stmt;
    }

    inline void ImportStmt::Field::x_exported_tv(types::TypeVar *exported_tv) {
        m_x_exported_tv = exported_tv;
    }

    inline void ImportStmt::Field::x_origin_script(Script *script) {
        m_x_origin_script = script;
    }

    inline std::vector<ImportStmt::FieldGroup*> const& ImportStmt::field_groups() const {
        return m_field_groups;
    }

}

#endif  // INCLUDED__PDM__AST__HEADER__IMPORT_STMT_HH