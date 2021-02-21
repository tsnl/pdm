#ifndef INCLUDED__PDM__AST__TYPE_SPEC__FUNC_HH
#define INCLUDED__PDM__AST__TYPE_SPEC__FUNC_HH

#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/core/intern.hh"
#include "type_spec.hh"
#include "pdm/ast/pattern/vpattern.hh"

namespace pdm::ast {

    class Manager;

    class FnTypeSpec: public TypeSpec {
        friend Manager;

      private:
        VPattern* m_lhs_vpattern;
        TypeSpec* m_opt_ret_typespec;

      protected:
        FnTypeSpec(source::Loc loc, VPattern* lhs_vpattern, TypeSpec* opt_rhs_typespec);

      public:
        [[nodiscard]] VPattern* lhs_vpattern() const;
        [[nodiscard]] TypeSpec* opt_ret_type_spec() const;
    };

    inline TypeSpec* FnTypeSpec::opt_ret_type_spec() const {
        return m_opt_ret_typespec;
    }

    inline VPattern* FnTypeSpec::lhs_vpattern() const {
        return m_lhs_vpattern;
    }

    inline FnTypeSpec::FnTypeSpec(source::Loc loc, VPattern* lhs_vpattern, TypeSpec* opt_rhs_typespec)
    :   TypeSpec(loc, Kind::FnTypeSpec),
        m_lhs_vpattern(lhs_vpattern),
        m_opt_ret_typespec(opt_rhs_typespec) {}

}

#endif  // INCLUDED__PDM__AST__TYPE_SPEC__FUNC_HH