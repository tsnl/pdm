#ifndef INCLUDED_PDM_AST_EXP_TYPE_QUERY_HH
#define INCLUDED_PDM_AST_EXP_TYPE_QUERY_HH

#include "pdm/source/loc.hh"
#include "pdm/ast/exp/exp.hh"
#include "pdm/ast/typespec/typespec.hh"

namespace pdm::ast {

    enum class TypeQueryKind {
        LhsSubtypeRhs,
        LhsSuperRhs,
        LhsEqualRhs
    };

    class TypeQueryExp: public Exp {
      private:
        TypeQueryKind m_kind;
        Typespec*     m_lhs_typespec;
        Typespec*     m_rhs_typespec;
      public:
        TypeQueryExp(source::Loc loc, TypeQueryKind kind, Typespec* lhs_typespec, Typespec* rhs_typespec)
        : Exp(loc, Kind::TypeQueryExp),
          m_kind(kind),
          m_lhs_typespec(lhs_typespec),
          m_rhs_typespec(rhs_typespec) {}
      
      public:
        TypeQueryKind kind() const {
            return m_kind;
        }
        Typespec* lhs_typespec() const {
            return m_lhs_typespec;
        }
        Typespec* rhs_typespec() const {
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
