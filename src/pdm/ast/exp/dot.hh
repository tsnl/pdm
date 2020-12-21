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

    class DotExp: public Exp {
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

      private:
        intern::String m_rhs_name;

      protected:
        DotNameExp(source::Loc loc, Exp* lhs, intern::String rhs_name)
        : DotExp(loc, Kind::DotNameExp, lhs),
          m_rhs_name(rhs_name) {}

      public:
        intern::String rhs_name() const {
            return m_rhs_name;
        }
    };

    class DotIndexExp: public DotExp {
        friend Manager;

      private:
        Exp* m_rhs_exp;

      protected:
        DotIndexExp(source::Loc loc, Exp* lhs, Exp* rhs_exp)
        : DotExp(loc, Kind::DotIndexExp, lhs),
          m_rhs_exp(rhs_exp) {}

      public:
        Exp* rhs_exp() const {
            return m_rhs_exp;
        }
    };

}

#endif  // INCLUDED_PDM_AST_EXP_DOT_HH