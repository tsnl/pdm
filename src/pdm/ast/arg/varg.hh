#ifndef INCLUDED_PDM_AST_ARG_VARG_HH
#define INCLUDED_PDM_AST_ARG_VARG_HH

#include <algorithm>

#include "pdm/ast/node.hh"

namespace pdm::ast {
    class Manager;
    class Exp;
}

namespace pdm::ast {
    
    enum class VArgAccessSpec {
        In,     // input, cannot write
        Out,    // output ptr, MUST write.
        InOut,  // input/output ptr, may read or write.
    };
    inline VArgAccessSpec varg_access_spec_intersection(VArgAccessSpec vaas1, VArgAccessSpec vaas2) {
        return static_cast<VArgAccessSpec>(
            std::min(static_cast<int>(vaas1), static_cast<int>(vaas2))
        );
    }

    // used for function calls:
    class VArg: public Node {
        friend Manager;

      private:
        source::Loc     m_loc;
        ast::Exp*       m_arg_exp;
        VArgAccessSpec  m_access_spec;

      public:
        VArg(source::Loc loc, Exp* arg_exp, VArgAccessSpec access_spec)
        : Node(loc, Kind::VArg),
          m_loc(loc),
          m_arg_exp(arg_exp),
          m_access_spec(access_spec) {}

      public:
        Exp* arg_exp() const {
            return m_arg_exp;
        }
        VArgAccessSpec access_spec() const {
            return m_access_spec;
        }
    };

}

#endif  // INCLUDED_PDM_AST_ARG_VARG_HH
