#ifndef INCLUDED_PDM_AST_EXP_TYPE_QUERY_HH
#define INCLUDED_PDM_AST_EXP_TYPE_QUERY_HH

#include "pdm/source/loc.hh"
#include "pdm/ast/exp/exp.hh"
#include "pdm/ast/typespec/typespec.hh"

namespace pdm::ast {

    class TypeQueryExp: public Exp {
      private:
        Typespec* m_lhs_typespec;
        Typespec* m_rhs_typespec;
      public:
        TypeQueryExp(source::Loc loc, Typespec* lhs_typespec, Typespec* rhs_typespec)
        : Exp(loc, Kind::TypeQueryExp),
          m_lhs_typespec(lhs_typespec),
          m_rhs_typespec(rhs_typespec) {}
    };

}

#endif  // INCLUDED_PDM_AST_EXP_TYPE_QUERY_HH


// todo: implement me!
//  T :: U
//  T :< U
//  T >: U
// where T,U typespecs.
