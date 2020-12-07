#ifndef INCLUDED_PDM_AST_TYPESPEC_FUNC_HH
#define INCLUDED_PDM_AST_TYPESPEC_FUNC_HH

#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/typespec/typespec.hh"
#include "pdm/ast/pattern/vpattern.hh"

namespace pdm::ast {

    class FuncTypespec: public Typespec {
      private:
        VPattern* m_lhs_vpattern;
        Typespec* m_rhs_typespec;
      public:
        FuncTypespec(source::Loc loc, VPattern* lhs_vpattern, Typespec* rhs_typespec)
        : Typespec(loc, Kind::FuncTypespec),
          m_lhs_vpattern(lhs_vpattern),
          m_rhs_typespec(rhs_typespec) {}
      
      public:
        VPattern* lhs_vpattern() const {
            return m_lhs_vpattern;
        }
        Typespec* rhs_typespec() const {
            return m_rhs_typespec;
        }
    };

}

#endif  // INCLUDED_PDM_AST_TYPESPEC_FUNC_HH