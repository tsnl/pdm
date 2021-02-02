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
        TCallExp(source::Loc loc, Exp* lhs_called, std::vector<TArg*>&& args);

      public:
        [[nodiscard]] Exp* lhs_called() const;
        [[nodiscard]] std::vector<TArg*> const& args() const;
    };

    inline TCallExp::TCallExp(source::Loc loc, Exp* lhs_called, std::vector<TArg*>&& args)
    :   Exp(loc, Kind::TCallExp),
        m_lhs_called(lhs_called),
        m_args(std::move(args)) {}

    inline Exp* TCallExp::lhs_called() const {
        return m_lhs_called;
    }

    inline std::vector<TArg*> const& TCallExp::args() const {
        return m_args;
    }

}

#endif  // INCLUDED_PDM_AST_EXP_TCALL_HH