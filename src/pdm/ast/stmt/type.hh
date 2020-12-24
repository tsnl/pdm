#ifndef INCLUDED_PDM_AST_STMT_TYPE_HH
#define INCLUDED_PDM_AST_STMT_TYPE_HH

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/stmt/stmt.hh"
#include "pdm/ast/typespec/typespec.hh"

namespace pdm::ast {
    class Manager;
    class TPattern;
}

namespace pdm::ast {

    class TypeStmt: public Stmt {
        friend Manager;

      private:
        intern::String         m_lhs_name;
        std::vector<TPattern*> m_lhs_tpatterns;
        Typespec*              m_rhs_typespec;

      public:
        TypeStmt(source::Loc loc, intern::String lhs_name, std::vector<TPattern*>&& lhs_tpatterns, Typespec* rhs_typespec)
        : Stmt(loc, Kind::TypeStmt),
          m_lhs_name(lhs_name),
          m_lhs_tpatterns(std::move(lhs_tpatterns)),
          m_rhs_typespec(rhs_typespec) {}
      
      public:
        intern::String lhs_name() const {
            return m_lhs_name;
        }
        std::vector<TPattern*> const& lhs_tpatterns() const {
            return m_lhs_tpatterns;
        }
        Typespec* rhs_typespec() const {
            return m_rhs_typespec;
        }
    };

}

#endif  // INCLUDED_PDM_AST_STMT_TYPE_HH