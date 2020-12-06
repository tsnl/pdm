#ifndef INCLUDED_PDM_AST_EXP_VCALL_HH
#define INCLUDED_PDM_AST_EXP_VCALL_HH

#include <vector>

#include "pdm/ast/kind.hh"
#include "pdm/ast/exp/exp.hh"

namespace pdm::ast {

    class VCallExp: public Exp {
      private:
        Exp*              m_lhs_called;
        std::vector<Exp*> m_args;

      public:
        VCallExp(source::Loc loc, Exp* lhs_called, std::vector<Exp*>&& args)
        : Exp(loc, Kind::TCallExp),
          m_lhs_called(lhs_called),
          m_args(std::move(args)) {}
    };

}

#endif  // INCLUDED_PDM_AST_EXP_VCALL_HH