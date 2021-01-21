#ifndef INCLUDED_PDM_AST_TYPESPEC_FUNC_HH
#define INCLUDED_PDM_AST_TYPESPEC_FUNC_HH

#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/setspec/type_spec.hh"
#include "pdm/ast/pattern/vpattern.hh"

namespace pdm::ast {

    class Manager;

    class FnTypeSpec: public TypeSpec {
        friend Manager;

      private:
        VPattern* m_lhs_vpattern;
        TypeSpec* m_opt_ret_typespec;

      protected:
        FnTypeSpec(source::Loc loc, VPattern* lhs_vpattern, TypeSpec* opt_rhs_typespec)
        : TypeSpec(loc, Kind::FnTypeSpec),
          m_lhs_vpattern(lhs_vpattern),
          m_opt_ret_typespec(opt_rhs_typespec) {}

      public:
        VPattern* lhs_vpattern() const {
            return m_lhs_vpattern;
        }
        TypeSpec* opt_ret_typespec() const {
            return m_opt_ret_typespec;
        }
    };

}

#endif  // INCLUDED_PDM_AST_TYPESPEC_FUNC_HH