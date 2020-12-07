#ifndef INCLUDED_PDM_AST_EXP_TCALL_HH
#define INCLUDED_PDM_AST_EXP_TCALL_HH

#include <vector>

#include "pdm/ast/kind.hh"
#include "pdm/ast/exp/exp.hh"
#include "pdm/ast/typespec/typespec.hh"

namespace pdm::ast {

    class TCallExp: public Exp {
      public:
        class Arg {
          private:
            Node* m_node;
            bool  m_is_type_not_val;

          public:
            Arg(Node* node, bool is_type_not_val)
            : m_node(node), m_is_type_not_val(is_type_not_val) {}
            
            virtual ~Arg() {};
          
          public:
            Node* node() const { return m_node; }
            bool is_type_not_val() const { return m_is_type_not_val; }
        };

      private:
        Exp*                       m_lhs_called;
        std::vector<TCallExp::Arg> m_args;

      public:
        TCallExp(source::Loc loc, Exp* lhs_called, std::vector<TCallExp::Arg>&& args)
        : Exp(loc, Kind::TCallExp),
          m_lhs_called(lhs_called),
          m_args(std::move(args)) {}

      public:
        Exp* lhs_called() const {
            return m_lhs_called;
        }
        std::vector<Arg> const& args() const {
            return m_args;
        }
    };

}

#endif  // INCLUDED_PDM_AST_EXP_TCALL_HH