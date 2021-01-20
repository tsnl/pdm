#ifndef INCLUDED_PDM_AST_EXP_TYPE_QUERY_HH
#define INCLUDED_PDM_AST_EXP_TYPE_QUERY_HH

#include "pdm/source/loc.hh"
#include "pdm/ast/exp/exp.hh"
#include "pdm/ast/setspec/typespec.hh"

namespace pdm::ast {

    class Manager;

    enum class TypeQueryKind {
        LhsSubtypesRhs,
        LhsSupertypesRhs,
        LhsEqualsRhs
    };

    class TypeQueryExp: public Exp {
        friend Manager;

      private:
        TypeQueryKind m_query_kind;
        TypeSpec*     m_lhs_typespec;
        TypeSpec*     m_rhs_typespec;
      
      protected:
        TypeQueryExp(source::Loc loc, TypeQueryKind kind, TypeSpec* lhs_typespec, TypeSpec* rhs_typespec)
        : Exp(loc, Kind::TypeQueryExp),
          m_query_kind(kind),
          m_lhs_typespec(lhs_typespec),
          m_rhs_typespec(rhs_typespec) {}
      
      public:
        TypeQueryKind query_kind() const {
            return m_query_kind;
        }
        TypeSpec* lhs_typespec() const {
            return m_lhs_typespec;
        }
        TypeSpec* rhs_typespec() const {
            return m_rhs_typespec;
        }
    };

}

#endif  // INCLUDED_PDM_AST_EXP_TYPE_QUERY_HH


// todo: implement me!
//  T :: U
//  T :< U
//  T >: U
// where T,U typespecs.
