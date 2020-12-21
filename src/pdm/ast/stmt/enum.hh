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
