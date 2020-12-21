#ifndef INCLUDED_PDM_AST_EXP_TCALL_HH
#define INCLUDED_PDM_AST_EXP_TCALL_HH

#include <vector>

#include "pdm/ast/kind.hh"
#include "pdm/ast/exp/exp.hh"
#include "pdm/ast/typespec/typespec.hh"

namespace pdm::ast {

    class Manager;
    class Exp;
    class Typespec;

    class TCallExp: public Exp {
        friend Manager;

      public:
        enum class ArgKind {
            Exp,
            Typespec
        };
        class Arg {
            friend Manager;

          private:
            Node* m_node;
            ArgKind m_arg_kind;

          private:
            Arg(Node* node, ArgKind arg_kind)
            : m_node(node), m_arg_kind(arg_kind) {}
            
          protected:
            Arg(Exp* exp)
            : Arg(exp, ArgKind::Exp) {}

            Arg(Typespec* typespec)
            : Arg(typespec, ArgKind::Typespec) {}
          
          public:
            Node* node() const { return m_node; }
            ArgKind arg_kind() const { return m_arg_kind; }

          // convenience properties:
          public:
            bool is_exp() const {
                return m_arg_kind == TCallExp::ArgKind::Exp;
            }
            bool is_typespec() const {
                return m_arg_kind == TCallExp::ArgKind::Typespec; 
            }
        };

      private:
        Exp*                        m_lhs_called;
        std::vector<TCallExp::Arg*> m_args;

      public:
        TCallExp(source::Loc loc, Exp* lhs_called, std::vector<TCallExp::Arg*>&& args)
        : Exp(loc, Kind::TCallExp),
          m_lhs_called(lhs_called),
          m_args(std::move(args)) {}

      public:
        Exp* lhs_called() const {
            return m_lhs_called;
        }
        std::vector<Arg*> const& args() const {
            return m_args;
        }
    };

}

#endif  // INCLUDED_PDM_AST_EXP_TCALL_HH