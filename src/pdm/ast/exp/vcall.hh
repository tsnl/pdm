#ifndef INCLUDED_PDM_AST_EXP_VCALL_HH
#define INCLUDED_PDM_AST_EXP_VCALL_HH

#include <vector>

#include "pdm/ast/kind.hh"
#include "pdm/ast/exp/exp.hh"

namespace pdm::ast {
    class Manager;
    class VArg;
}

namespace pdm::ast {

    class VCallExp: public Exp {
        friend Manager;

      private:
        Exp*               m_lhs_called;
        std::vector<VArg*> m_args;

      protected:
        VCallExp(source::Loc loc, Exp* lhs_called, std::vector<VArg*>&& args);
      
      public:
        [[nodiscard]] Exp* lhs_called() const;
        [[nodiscard]] std::vector<VArg*> const& args() const;
    };

    inline VCallExp::VCallExp(source::Loc loc, Exp* lhs_called, std::vector<VArg*>&& args)
    :   Exp(loc, Kind::VCallExp),
        m_lhs_called(lhs_called),
        m_args(std::move(args)) {}

    inline Exp* VCallExp::lhs_called() const {
        return m_lhs_called;
    }

    inline std::vector<VArg*> const& VCallExp::args() const {
        return m_args;
    }

}

#endif  // INCLUDED_PDM_AST_EXP_VCALL_HH