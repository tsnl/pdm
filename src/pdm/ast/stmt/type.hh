#ifndef INCLUDED_PDM_AST_STMT_TYPE_HH
#define INCLUDED_PDM_AST_STMT_TYPE_HH

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/stmt/stmt.hh"
#include "pdm/ast/typespec/typespec.hh"

namespace pdm::ast {

    class TypeStmt: public Stmt {
      private:
        intern::String m_lhs_name;
        Typespec*      m_rhs_typespec;

      public:
        TypeStmt(source::Loc loc, intern::String lhs_name, Typespec* rhs_typespec)
        : Stmt(loc, Kind::TypeStmt),
          m_lhs_name(lhs_name),
          m_rhs_typespec(rhs_typespec) {}
      
      public:
        intern::String lhs_name() const {
            return m_lhs_name;
        }
        Typespec* rhs_typespec() const {
            return m_rhs_typespec;
        }
    };

}

#endif  // INCLUDED_PDM_AST_STMT_TYPE_HH