#ifndef INCLUDED__PDM__AST__TYPE_SPEC__DOT_HH
#define INCLUDED__PDM__AST__TYPE_SPEC__DOT_HH

#include "type_spec.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"

namespace pdm::ast {
    class ModAddress;
}

namespace pdm::ast {

    class ModAddressIdTypeSpec: public TypeSpec {
      private:
        ModAddress* m_lhs_mod_address;
        intern::String m_rhs_type_name;

      public:
        ModAddressIdTypeSpec(source::Loc loc, ModAddress* lhs_mod_address, intern::String rhs_type_name);

      public:
        [[nodiscard]] ModAddress* lhs_mod_address() const;
        [[nodiscard]] intern::String rhs_type_name() const;
    };

    //
    // Inline implementations:
    //

    inline ModAddressIdTypeSpec::ModAddressIdTypeSpec(source::Loc loc, ModAddress *lhs_mod_address, intern::String rhs_type_name)
    :   TypeSpec(loc, Kind::ModAddressIdTypeSpec),
        m_lhs_mod_address(lhs_mod_address),
        m_rhs_type_name(rhs_type_name)
    {}

    inline ModAddress* ModAddressIdTypeSpec::lhs_mod_address() const {
        return m_lhs_mod_address;
    }

    inline intern::String ModAddressIdTypeSpec::rhs_type_name() const {
        return m_rhs_type_name;
    }
}

#endif //   INCLUDED__PDM__AST__TYPE_SPEC__DOT_HH
