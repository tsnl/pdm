#ifndef INCLUDED_PDM_AST_STMT_ENUM_HH
#define INCLUDED_PDM_AST_STMT_ENUM_HH

#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/stmt/stmt.hh"
#include "pdm/ast/typespec/struct.hh"

namespace pdm::ast {
    class Manager;
    class TPattern;
}
namespace pdm::types {
    class Var;
}

namespace pdm::ast {

    class EnumStmt: public Stmt {
        friend Manager;

      // field:
      public:
        class Field {
            friend Manager;

          private:
            source::Loc                 m_loc;
            intern::String              m_name;
            std::vector<ast::Typespec*> m_typespecs;
            bool                        m_has_explicit_typespecs;
            
          protected:
            Field(source::Loc loc, intern::String name)
            : m_loc(loc),
              m_name(name),
              m_typespecs(),
              m_has_explicit_typespecs(false) {}

            Field(source::Loc loc, intern::String name, std::vector<ast::Typespec*>&& typespecs, bool has_explicit_typespecs)
            : m_loc(loc),
              m_name(name),
              m_typespecs(std::move(typespecs)),
              m_has_explicit_typespecs(has_explicit_typespecs) {}

          public:
            intern::String name() const {
                return m_name;
            }
            std::vector<ast::Typespec*> const& typespecs() const {
                return m_typespecs;
            }
            bool has_explicit_typespecs() const {
                return m_has_explicit_typespecs;
            }
        };

      // body:
      private:
        intern::String                m_name;
        std::vector<ast::TPattern*>   m_tpatterns;
        std::vector<EnumStmt::Field*> m_fields;
        types::Var*                   m_x_defn_var;
      
      protected:
        EnumStmt(source::Loc loc, intern::String name, std::vector<ast::TPattern*>&& tpatterns, std::vector<EnumStmt::Field*>&& fields)
        : Stmt(loc, Kind::EnumStmt),
          m_name(name),
          m_tpatterns(std::move(tpatterns)),
          m_fields(std::move(fields)),
          m_x_defn_var(nullptr) {}
      
      public:
        intern::String name() const {
            return m_name;
        }
        std::vector<ast::TPattern*> const& tpatterns() const {
            return m_tpatterns;
        }
        std::vector<EnumStmt::Field*> const& fields() const {
            return m_fields;
        }

      public:
        types::Var* x_defn_var() const {
            return m_x_defn_var;
        }
        void x_defn_var(types::Var* defn_var) {
            m_x_defn_var = defn_var;
        }
    };

}

#endif  // INCLUDED_PDM_AST_STMT_ENUM_HH
