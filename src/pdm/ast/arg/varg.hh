#ifndef INCLUDED_PDM_AST_ARG_VARG_HH
#define INCLUDED_PDM_AST_ARG_VARG_HH

#include "pdm/ast/node.hh"

namespace pdm::ast {
    class Manager;
    class Exp;
}

namespace pdm::ast {
    
    enum class VArgKind {
        In,
        Out,
        InOut,
    };

    class VArg: public Node {
        friend Manager;

      private:
        source::Loc m_loc;
        ast::Exp*   m_arg_exp;
        VArgKind    m_arg_kind;

      public:
        VArg(source::Loc loc, Exp* arg_exp, VArgKind arg_kind)
        : Node(loc, Kind::VArg),
          m_loc(loc),
          m_arg_exp(arg_exp),
          m_arg_kind(arg_kind) {}

      public:
        Exp* arg_exp() const {
            return m_arg_exp;
        }
        VArgKind arg_kind() const {
            return m_arg_kind;
        }
    };

}

#endif  // INCLUDED_PDM_AST_ARG_VARG_HH
