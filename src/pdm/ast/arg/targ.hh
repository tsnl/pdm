#ifndef INCLUDED_PDM_AST_ARG_TARG_HH
#define INCLUDED_PDM_AST_ARG_TARG_HH

#include "pdm/ast/node.hh"
#include "pdm/ast/exp/exp.hh"
#include "pdm/ast/setspec/type_spec.hh"

namespace pdm::ast {
    class Manager;
}

namespace pdm::ast {

    enum class TArgKind {
        Value,
        TypeSpec
    };
    
    class TArg: public Node {
        friend ast::Manager;

      private:
        Node*    m_node;
        TArgKind m_arg_kind;

      private:
        TArg(source::Loc loc, Node* ref_node, TArgKind arg_kind);
        
      protected:
        TArg(source::Loc loc, ast::Exp* exp);

        TArg(source::Loc loc, ast::TypeSpec* typespec);

      // getters:  
      public:
        [[nodiscard]] Node* arg_node() const;
        [[nodiscard]] TArgKind arg_kind() const;

      // convenience properties:
      public:
        [[nodiscard]] bool is_value() const;
        [[nodiscard]] bool is_typespec() const;
    };

    inline TArg::TArg(source::Loc loc, Node* ref_node, TArgKind arg_kind)
    :   Node(loc, Kind::TArg),
        m_node(ref_node), m_arg_kind(arg_kind)
    {}

    inline TArg::TArg(source::Loc loc, ast::Exp* exp)
    :   TArg(loc, exp, TArgKind::Value)
    {}

    inline TArg::TArg(source::Loc loc, ast::TypeSpec* typespec)
    :   TArg(loc, typespec, TArgKind::TypeSpec)
    {}

    inline Node* TArg::arg_node() const {
        return m_node;
    }

    inline TArgKind TArg::arg_kind() const {
        return m_arg_kind;
    }

    inline bool TArg::is_value() const {
        return m_arg_kind == TArgKind::Value;
    }

    inline bool TArg::is_typespec() const {
        return m_arg_kind == TArgKind::TypeSpec;
    }

}

#endif  // INCLUDED_PDM_AST_ARG_TARG_HH