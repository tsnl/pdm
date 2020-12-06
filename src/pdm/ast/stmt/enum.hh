#ifndef INCLUDED_PDM_AST_STMT_ENUM_HH
#define INCLUDED_PDM_AST_STMT_ENUM_HH

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/stmt/stmt.hh"
#include "pdm/ast/typespec/struct.hh"

namespace pdm::ast {

    class EnumStmt: public Stmt {
      private:
        intern::String  m_name;
        StructTypespec* m_body_struct_typespec;
      public:
        EnumStmt(source::Loc loc, intern::String name, StructTypespec* body_struct_typespec)
        : Stmt(loc, Kind::EnumStmt),
          m_name(name),
          m_body_struct_typespec(body_struct_typespec) {}
    };

}

#endif  // INCLUDED_PDM_AST_STMT_ENUM_HH
