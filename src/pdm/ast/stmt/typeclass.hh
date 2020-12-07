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

    class TypeclassStmt: public Stmt {
      public:
        enum class FieldKind {
            Exp,
            Fun
        };
        class Field {
          private:
            FieldKind m_kind;
          protected:
            Field(FieldKind kind);
            virtual ~Field() {}
          public:
            FieldKind kind() const {
                return m_kind;
            }
        };
        class ExpField: public TypeclassStmt::Field {
          private:
            Exp* m_const_exp;
          public:
            ExpField(Exp* const_exp)
            : TypeclassStmt::Field(FieldKind::Exp),
              m_const_exp(const_exp) {}
          public:
            Exp* const_exp() const {
                return m_const_exp;
            }
        };
        class FunField: public TypeclassStmt::Field {
          private:
            VPattern* m_lhs_pattern;
            Exp* m_rhs_body;
          public:
            FunField(VPattern* lhs_pattern, Exp* rhs_body)
            : TypeclassStmt::Field(FieldKind::Fun),
              m_lhs_pattern(lhs_pattern),
              m_rhs_body(rhs_body) {}

          public:
            VPattern* lhs_pattern() const {
                return m_lhs_pattern;
            }
            Exp* rhs_body() const {
                return m_rhs_body;
            }
        };
      
      private:
        intern::String                     m_lhs_name;
        intern::String                     m_candidate_name;
        std::vector<TPattern*>             m_tpatterns;
        std::vector<TypeclassStmt::Field*> m_fields;

      public:
        TypeclassStmt(
            source::Loc loc, 
            intern::String lhs_name, 
            intern::String candidate_name,
            std::vector<TPattern*>&& tpatterns,
            std::vector<TypeclassStmt::Field*>&& fields
        )
        : Stmt(loc, Kind::TypeStmt),
          m_lhs_name(lhs_name),
          m_candidate_name(candidate_name),
          m_tpatterns(std::move(tpatterns)),
          m_fields(std::move(fields)) {}
      
      public:
        intern::String lhs_name() const {
            return m_lhs_name;
        }
        intern::String candidate_name() const {
            return m_candidate_name;
        }
        std::vector<TPattern*> const& tpatterns() const {
            return m_tpatterns;
        }
        std::vector<TypeclassStmt::Field*> const& fields() const {
            return m_fields;
        }
    };

}

#endif  // INCLUDED_PDM_AST_STMT_TYPECLASS_HH
