#ifndef INCLUDED_PDM_AST_STMT_ENUM_HH
#define INCLUDED_PDM_AST_STMT_ENUM_HH

#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/stmt/stmt.hh"
#include "pdm/ast/setspec/struct.hh"
#include "mod_content.hh"

namespace pdm::ast {
    class Manager;
    class TPattern;
}
namespace pdm::types {
    class Var;
}

namespace pdm::ast {

    class ModEnumStmt: public ModContentStmt {
        friend Manager;

      // field:
      public:
        class Field {
            friend Manager;

          private:
            source::Loc    m_loc;
            intern::String m_name;
            ast::TypeSpec* m_opt_type_spec;
            
          protected:
            Field(source::Loc loc, intern::String name);

            Field(source::Loc loc, intern::String name, ast::TypeSpec* opt_type_spec);

          public:
            [[nodiscard]] intern::String name() const;
            [[nodiscard]] ast::TypeSpec* opt_type_spec() const;
        };

      // body:
      private:
        intern::String                   m_name;
        std::vector<ast::TPattern*>      m_tpatterns;
        std::vector<ModEnumStmt::Field*> m_fields;
        types::Var*                      m_x_defn_var;
      
      protected:
        ModEnumStmt(source::Loc loc, intern::String name, std::vector<ast::TPattern*>&& tpatterns, std::vector<ModEnumStmt::Field*>&& fields);
      
      public:
        [[nodiscard]] intern::String name() const;
        [[nodiscard]] std::vector<ast::TPattern*> const& tpatterns() const;
        [[nodiscard]] std::vector<ModEnumStmt::Field*> const& fields() const;

      public:
        [[nodiscard]] types::Var* x_defn_var() const;
        void x_defn_var(types::Var* defn_var);
    };

    inline intern::String ModEnumStmt::name() const {
        return m_name;
    }

    inline std::vector<ast::TPattern*> const& ModEnumStmt::tpatterns() const {
        return m_tpatterns;
    }

    inline std::vector<ModEnumStmt::Field*> const& ModEnumStmt::fields() const {
        return m_fields;
    }

    inline types::Var* ModEnumStmt::x_defn_var() const {
        return m_x_defn_var;
    }

    inline void ModEnumStmt::x_defn_var(types::Var *defn_var) {
        m_x_defn_var = defn_var;
    }

    inline ModEnumStmt::ModEnumStmt(
        source::Loc loc, intern::String name, std::vector<ast::TPattern*>&& tpatterns,
        std::vector<ModEnumStmt::Field*>&& fields
    )
    :   ModContentStmt(loc, Kind::ModEnumStmt),
        m_name(name),
        m_tpatterns(std::move(tpatterns)),
        m_fields(std::move(fields)),
        m_x_defn_var(nullptr)
    {}

    inline ModEnumStmt::Field::Field(source::Loc loc, intern::String name)
    :   m_loc(loc),
        m_name(name)
    {}

    inline ModEnumStmt::Field::Field(
        source::Loc loc,
        intern::String name,
        ast::TypeSpec* opt_type_spec
    )
    :   m_loc(loc),
        m_name(name),
        m_opt_type_spec(opt_type_spec)
    {}

    inline intern::String ModEnumStmt::Field::name() const {
        return m_name;
    }

    inline ast::TypeSpec* ModEnumStmt::Field::opt_type_spec() const {
        return m_opt_type_spec;
    }

}

#endif  // INCLUDED_PDM_AST_STMT_ENUM_HH
