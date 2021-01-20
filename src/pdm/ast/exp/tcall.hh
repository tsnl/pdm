#ifndef INCLUDED_PDM_AST_EXP_TCALL_HH
#define INCLUDED_PDM_AST_EXP_TCALL_HH

#include <vector>

#include "pdm/ast/kind.hh"

namespace pdm::ast {
    class Manager;
    class Exp;
    class TypeSpec;
    class TArg;
}

namespace pdm::ast {

    class TCallExp: public Exp {
        friend Manager;

      private:
        Exp*               m_lhs_called;
        std::vector<TArg*> m_args;

      public:
        TCallExp(source::Loc loc, Exp* lhs_called, std::vector<TArg*>&& args)
        : Exp(loc, Kind::TCallExp),
          m_lhs_called(lhs_called),
          m_args(std::move(args)) {}

      public:
        Exp* lhs_called() const {
            return m_lhs_called;
        }
        std::vector<TArg*> const& args() const {
            return m_args;
        }
    };

}

#endif  // INCLUDED_PDM_AST_EXP_TCALL_HH