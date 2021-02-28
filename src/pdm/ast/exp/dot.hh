#ifndef INCLUDED_PDM_AST_EXP_DOT_HH
#define INCLUDED_PDM_AST_EXP_DOT_HH

#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/stmt/stmt.hh"
#include "pdm/ast/exp/exp.hh"
#include "pdm/ast/type_spec/type_spec.hh"

namespace pdm::ast {
    class Manager;
    class Exp;
    class ModAddress;
}

namespace pdm::ast {

    // vid-prefixed modules:
    class ModuleDotExp: public Exp {
        friend Manager;

      private:
        ast::ModAddress* m_lhs_mod_address;
        intern::String   m_rhs_name;

      public:
        ModuleDotExp(source::Loc loc, ast::ModAddress* m_lhs_mod_address, intern::String rhs_name);

      public:
        [[nodiscard]] ast::ModAddress* lhs_mod_address() const;
        [[nodiscard]] intern::String rhs_name() const;
    };

    inline ModuleDotExp::ModuleDotExp(source::Loc loc, ast::ModAddress* lhs_mod_address, intern::String rhs_name)
    :   Exp(loc, Kind::ModuleDotExp),
        m_lhs_mod_address(lhs_mod_address),
        m_rhs_name(rhs_name)
    {}

    inline ast::ModAddress* ModuleDotExp::lhs_mod_address() const {
        return m_lhs_mod_address;
    }

    inline intern::String ModuleDotExp::rhs_name() const {
        return m_rhs_name;
    }

    // other kinds of dot exp:
    class DotExp: public Exp {
        friend Manager;

      private:
        Node* m_lhs;
      
      protected:
        DotExp(source::Loc loc, Kind node_kind, Node* lhs)
        : Exp(loc, node_kind),
          m_lhs(lhs) {}

      public:
        [[nodiscard]] Node* lhs() const {
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
        DotNameExp(source::Loc loc, Node* lhs, intern::String rhs_name, RhsHint rhs_hint)
        : DotExp(loc, Kind::DotNameExp, lhs),
          m_rhs_name(rhs_name),
          m_rhs_hint(rhs_hint) {}

      public:
        [[nodiscard]] intern::String rhs_name() const {
            return m_rhs_name;
        }
        [[nodiscard]] DotNameExp::RhsHint rhs_hint() const {
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
        Exp* m_opt_using_arg;

      public:
        inline EnumDotNameExp(source::Loc loc, TypeSpec* lhs, intern::String rhs_name, Exp* opt_using_arg);

      public:
        [[nodiscard]] inline Exp* opt_using_arg() const;
    };
    inline EnumDotNameExp::EnumDotNameExp(source::Loc loc, TypeSpec* lhs, intern::String rhs_name, Exp* opt_using_arg)
    :   DotNameExp(loc, lhs, rhs_name, DotNameExp::RhsHint::LhsEnum),
        m_opt_using_arg(opt_using_arg)
    {}
    inline Exp* EnumDotNameExp::opt_using_arg() const {
        return m_opt_using_arg;
    }

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