#ifndef INCLUDED_PDM_AST_EXP_DOT_HH
#define INCLUDED_PDM_AST_EXP_DOT_HH

#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/stmt/stmt.hh"
#include "pdm/ast/exp/exp.hh"

namespace pdm::ast {
    class Manager;
    class Exp;
}

namespace pdm::ast {

    // vid-prefixed modules:
    class ModuleDotExp: public Exp {
        friend Manager;

      private:
        std::vector<intern::String> m_lhs_prefix_module_names;
        intern::String              m_rhs_name;

      public:
        ModuleDotExp(source::Loc loc, std::vector<intern::String>&& prefix_module_names, intern::String rhs_name);

      public:
        std::vector<intern::String> const& lhs_prefix_module_names() const;
        intern::String rhs_name() const;
    };
    inline ModuleDotExp::ModuleDotExp(source::Loc loc, std::vector<intern::String>&& prefix_module_names, intern::String rhs_name)
    :   Exp(loc, Kind::ModuleDotExp),
        m_lhs_prefix_module_names(std::move(prefix_module_names)),
        m_rhs_name(rhs_name)
    {}
    inline std::vector<intern::String> const& ModuleDotExp::lhs_prefix_module_names() const {
        return m_lhs_prefix_module_names;
    }
    inline intern::String ModuleDotExp::rhs_name() const {
        return m_rhs_name;
    }

    // other kinds of dot exp:
    class DotExp: public Exp {
        friend Manager;

      private:
        Exp* m_lhs;
      
      protected:
        DotExp(source::Loc loc, Kind node_kind, Exp* lhs)
        : Exp(loc, node_kind),
          m_lhs(lhs) {}

      public:
        Exp* lhs() const {
            return m_lhs;
        }
    };

    class DotNameExp: public DotExp {
        friend Manager;

      public:
        enum class RhsHint {
            LhsStruct,
            LhsEnum,
        };

      private:
        intern::String      m_rhs_name;
        DotNameExp::RhsHint m_rhs_hint;

      protected:
        DotNameExp(source::Loc loc, Exp* lhs, intern::String rhs_name, RhsHint rhs_hint)
        : DotExp(loc, Kind::DotNameExp, lhs),
          m_rhs_name(rhs_name),
          m_rhs_hint(rhs_hint) {}

      public:
        intern::String rhs_name() const {
            return m_rhs_name;
        }
        DotNameExp::RhsHint rhs_hint() const {
            return m_rhs_hint;
        }
    };
    class StructDotNameExp: public DotNameExp {
        friend Manager;

      public:
        inline StructDotNameExp(source::Loc loc, Exp* lhs, intern::String rhs_name);
    };
    inline StructDotNameExp::StructDotNameExp(source::Loc loc, Exp* lhs, intern::String rhs_name)
    :   DotNameExp(loc, lhs, rhs_name, DotNameExp::RhsHint::LhsStruct)
    {}
    class EnumDotNameExp: public DotNameExp {
        friend Manager;

      private:
        std::vector<Exp*> m_args;

      public:
        inline EnumDotNameExp(source::Loc loc, Exp* lhs, intern::String rhs_name, std::vector<Exp*>&& args);
    };
    inline EnumDotNameExp::EnumDotNameExp(source::Loc loc, Exp* lhs, intern::String rhs_name, std::vector<ast::Exp*>&& args)
    :   DotNameExp(loc, lhs, rhs_name, DotNameExp::RhsHint::LhsEnum),
        m_args(std::move(args))
    {}

    class DotIndexExp: public DotExp {
        friend Manager;

      public:
        enum class RhsHint {
            LhsNotPtr,
            LhsPtr
        };

      private:
        Exp*    m_rhs_exp;
        RhsHint m_rhs_hint;

      protected:
        DotIndexExp(source::Loc loc, Exp* lhs, Exp* rhs_exp, RhsHint rhs_hint)
        : DotExp(loc, Kind::DotIndexExp, lhs),
          m_rhs_exp(rhs_exp),
          m_rhs_hint(rhs_hint) {}

      public:
        Exp* rhs_exp() const {
            return m_rhs_exp;
        }
        RhsHint rhs_hint() const {
            return m_rhs_hint;
        }
    };

}

#endif  // INCLUDED_PDM_AST_EXP_DOT_HH