#ifndef INCLUDED__PDM__AST__MOD_ADDRESS_HH
#define INCLUDED__PDM__AST__MOD_ADDRESS_HH

#include "pdm/ast/node.hh"
#include "pdm/source/loc.hh"
#include "pdm/core/intern.hh"

namespace pdm::ast {
    class BaseModExp;
}
namespace pdm::ast {

    class ModAddress: public Node {
      private:
        ModAddress* m_opt_parent_address;
        ast::BaseModExp* m_x_origin_mod_exp;
        intern::String m_rhs_name;
        std::vector<ast::TArg*> m_template_args;

      public:
        ModAddress(
            source::Loc loc,
            ModAddress* opt_parent_address,
            intern::String rhs_name,
            std::vector<ast::TArg*>&& template_args
        );

      public:
        [[nodiscard]] ModAddress* opt_parent_address() const;
        [[nodiscard]] intern::String rhs_name() const;
        [[nodiscard]] std::vector<ast::TArg*> const& template_args() const;

    public:
        [[nodiscard]] ast::BaseModExp* x_origin_mod_exp() const;
        void x_origin_mod_exp(ast::BaseModExp* origin_mod_exp);
    };

    //
    // Inline implementations:
    //

    inline ModAddress::ModAddress(
        source::Loc loc,
        ModAddress *opt_parent_address, intern::String rhs_name,
        std::vector<ast::TArg*>&& template_args
    )
    :   Node(loc, Kind::ModAddress),
        m_opt_parent_address(opt_parent_address),
        m_rhs_name(rhs_name),
        m_x_origin_mod_exp(nullptr),
        m_template_args(std::move(template_args))
    {}

    inline ModAddress* ModAddress::opt_parent_address() const {
        return m_opt_parent_address;
    }

    inline intern::String ModAddress::rhs_name() const {
        return m_rhs_name;
    }

    inline ast::BaseModExp* ModAddress::x_origin_mod_exp() const {
        return m_x_origin_mod_exp;
    }

    inline void ModAddress::x_origin_mod_exp(ast::BaseModExp* origin_mod_exp) {
        m_x_origin_mod_exp = origin_mod_exp;
    }

    inline std::vector<ast::TArg*> const& ModAddress::template_args() const {
        return m_template_args;
    }

}

#endif  // INCLUDED__PDM__AST__MOD_ADDRESS_HH