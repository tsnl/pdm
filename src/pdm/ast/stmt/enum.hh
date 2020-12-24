#ifndef INCLUDED_PDM_AST_STMT_ENUM_HH
#define INCLUDED_PDM_AST_STMT_ENUM_HH

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/stmt/stmt.hh"
#include "pdm/ast/typespec/struct.hh"

namespace pdm::ast {

    class Manager;

    class EnumStmt: public Stmt {
        friend Manager;

      public:
        class Field {
            friend Manager;

          private:
            intern::String              m_name;
            std::vector<ast::Typespec*> m_typespecs;
            bool                        m_has_explicit_typespecs;
            
          protected:
            Field(intern::String name)
            : m_name(name),
              m_typespecs(),
              m_has_explicit_typespecs(false) {}

            Field(intern::String name, std::vector<ast::Typespec*>&& typespecs, bool has_explicit_typespecs)
            : m_name(name),
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

      private:
        intern::String  m_name;
        StructTypespec* m_body_struct_typespec;
      
      protected:
        EnumStmt(source::Loc loc, intern::String name, StructTypespec* body_struct_typespec)
        : Stmt(loc, Kind::EnumStmt),
          m_name(name),
          m_body_struct_typespec(body_struct_typespec) {}
      
      public:
        intern::String name() const {
            return m_name;
        }
        StructTypespec* body_struct_typespec() const {
            return m_body_struct_typespec;
        }
    };

}

#endif  // INCLUDED_PDM_AST_STMT_ENUM_HH
