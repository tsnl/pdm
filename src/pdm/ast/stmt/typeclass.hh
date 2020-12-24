#ifndef INCLUDED_PDM_AST_STMT_TYPECLASS_HH
#define INCLUDED_PDM_AST_STMT_TYPECLASS_HH

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/stmt/stmt.hh"
#include "pdm/ast/typespec/typespec.hh"
#include "pdm/ast/pattern/vpattern.hh"
#include "pdm/ast/pattern/tpattern.hh"

namespace pdm::ast {
    class Manager;
    class TPattern;
    class Typespec;
    class Exp;
}

namespace pdm::ast {

    class TypeclassStmt: public Stmt {
        friend Manager;

      private:
        intern::String          m_lhs_name;
        intern::String          m_candidate_name;
        Typespec*               m_candidate_typespec;
        std::vector<TPattern*>  m_tpatterns;
        std::vector<Exp*>       m_conditions;

      public:
        TypeclassStmt(
            source::Loc loc, 
            intern::String lhs_name,
            intern::String candidate_name,
            Typespec* candidate_typespec,
            std::vector<TPattern*>&& tpatterns,
            std::vector<Exp*>&& conditions
        )
        : Stmt(loc, Kind::TypeStmt),
          m_lhs_name(lhs_name),
          m_candidate_name(candidate_name),
          m_candidate_typespec(candidate_typespec),
          m_tpatterns(std::move(tpatterns)),
          m_conditions(std::move(conditions)) {}
      
      public:
        intern::String lhs_name() const {
            return m_lhs_name;
        }
        intern::String candidate_name() const {
            return m_candidate_name;
        }
        Typespec* candidate_typespec() const {
            return m_candidate_typespec;
        }
        std::vector<TPattern*> const& tpatterns() const {
            return m_tpatterns;
        }
        std::vector<Exp*> const& conditions() const {
            return m_conditions;
        }
    };

}

#endif  // INCLUDED_PDM_AST_STMT_TYPECLASS_HH
