#ifndef PDM__AST__CLASS_SPEC__DOT_HH
#define PDM__AST__CLASS_SPEC__DOT_HH

#include "pdm/ast/class_spec/class_spec.hh"

namespace pdm::ast {
    class ModAddress;
}

namespace pdm::ast {

    class ModAddressIdClassSpec: public ClassSpec {
      private:
        ModAddress* m_lhs_mod_address;
        intern::String m_rhs_type_name;

      public:
        ModAddressIdClassSpec(source::Loc loc, ast::ModAddress* lhs_mod_address, intern::String rhs_name);

      public:
        [[nodiscard]] ModAddress* lhs_mod_address() const;
        [[nodiscard]] intern::String rhs_type_name() const;
    };

    //
    // Inline implementations:
    //

    inline ModAddressIdClassSpec::ModAddressIdClassSpec(source::Loc loc, ast::ModAddress* lhs_mod_address, intern::String rhs_name)
    :   ClassSpec(loc, Kind::ModAddressIdClassSpec),
        m_lhs_mod_address(lhs_mod_address),
        m_rhs_type_name(rhs_name)
    {}

    inline ModAddress* ModAddressIdClassSpec::lhs_mod_address() const {
        return m_lhs_mod_address;
    }

    inline intern::String ModAddressIdClassSpec::rhs_type_name() const {
        return m_rhs_type_name;
    }

}

#endif  // PDM__AST__CLASS_SPEC__DOT_HH
