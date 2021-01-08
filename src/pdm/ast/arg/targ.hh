#ifndef INCLUDED_PDM_AST_ARG_TARG_HH
#define INCLUDED_PDM_AST_ARG_TARG_HH

#include "pdm/ast/node.hh"
#include "pdm/ast/exp/exp.hh"
#include "pdm/ast/typespec/typespec.hh"

namespace pdm::ast {
    class Manager;
}

namespace pdm::ast {

    enum class TArgKind {
        Value,
        Typespec
    };
    
    class TArg: public Node {
        friend ast::Manager;

      private:
        Node*    m_node;
        TArgKind m_arg_kind;

      private:
        TArg(source::Loc loc, Node* ref_node, TArgKind arg_kind)
        : Node(loc, Kind::TArg),
          m_node(ref_node), m_arg_kind(arg_kind) {}
        
      protected:
        TArg(source::Loc loc, ast::Exp* exp)
        : TArg(loc, exp, TArgKind::Value) {}

        TArg(source::Loc loc, ast::Typespec* typespec)
        : TArg(loc, typespec, TArgKind::Typespec) {}

      // getters:  
      public:
        Node* arg_node() const {
            return m_node;
        }
        TArgKind arg_kind() const {
            return m_arg_kind;
        }

      // convenience properties:
      public:
        bool is_value() const {
            return m_arg_kind == TArgKind::Value;
        }
        bool is_typespec() const {
            return m_arg_kind == TArgKind::Typespec; 
        }
    };

}

#endif  // INCLUDED_PDM_AST_ARG_TARG_HH