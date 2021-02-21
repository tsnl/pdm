#ifndef INCLUDED__PDM__AST__MOD_ADDRESS_HH
#define INCLUDED__PDM__AST__MOD_ADDRESS_HH

#include "pdm/ast/node.hh"
#include "pdm/source/loc.hh"
#include "pdm/core/intern.hh"

namespace pdm::ast {
    class ModExp;
}
namespace pdm::ast {

    class ModAddress: public Node {
      private:
        ModAddress* m_opt_parent_address;
        ast::ModExp* m_x_origin_mod_exp;
        intern::String m_rhs_name;

      protected:
        ModAddress(
            source::Loc loc,
            Kind kind,
            ModAddress* opt_parent_address,
            intern::String rhs_name
        );

      public:
        ModAddress(
            source::Loc loc,
            ModAddress* opt_parent_address,
            intern::String rhs_name
        );

      public:
        [[nodiscard]] ModAddress* opt_parent_address() const;
        [[nodiscard]] intern::String rhs_name() const;
        [[nodiscard]] ast::ModExp* x_origin_mod_exp() const;
        void x_origin_mod_exp(ast::ModExp* origin_mod_exp);
    };
    class TemplateModAddress: public ModAddress {
      private:
        std::vector<ast::TArg*> m_template_args;

      public:
        TemplateModAddress(
            source::Loc loc,
            ModAddress* opt_parent_address,
            intern::String rhs_name, std::vector<ast::TArg*>&& template_args
        );
    };

    //
    // Inline implementations:
    //

    inline ModAddress::ModAddress(source::Loc loc, ModAddress *opt_parent_address, intern::String rhs_name)
    :   ModAddress(loc, Kind::ModAddress, opt_parent_address, rhs_name)
    {}

    inline ModAddress::ModAddress(
        source::Loc loc, Kind kind,
        ModAddress* opt_parent_address,
        intern::String rhs_name
    )
    :   Node(loc, kind),
        m_opt_parent_address(opt_parent_address),
        m_rhs_name(rhs_name),
        m_x_origin_mod_exp(nullptr)
    {}

    inline TemplateModAddress::TemplateModAddress(
        source::Loc loc,
        ModAddress* opt_parent_address,
        intern::String rhs_name, std::vector<ast::TArg*>&& template_args
    )
    :   ModAddress(loc, Kind::TemplateModAddress, opt_parent_address, rhs_name),
        m_template_args(std::move(template_args))
    {}

    ModAddress* ModAddress::opt_parent_address() const {
        return m_opt_parent_address;
    }

    intern::String ModAddress::rhs_name() const {
        return m_rhs_name;
    }

    ast::ModExp* ModAddress::x_origin_mod_exp() const {
        return m_x_origin_mod_exp;
    }

    void ModAddress::x_origin_mod_exp(ast::ModExp* origin_mod_exp) {
        m_x_origin_mod_exp = origin_mod_exp;
    }

}

#endif  // INCLUDED__PDM__AST__MOD_ADDRESS_HH