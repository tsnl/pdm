#ifndef INCLUDED_PDM_AST_TARG_TARG_HH
#define INCLUDED_PDM_AST_TARG_TARG_HH

namespace pdm::ast {

    enum class TArgKind {
        Exp,
        Typespec
    };
    
    class TArg {
        friend Manager;

      private:
        Node*    m_node;
        TArgKind m_arg_kind;

      private:
        TArg(Node* node, TArgKind arg_kind)
        : m_node(node), m_arg_kind(arg_kind) {}
        
      protected:
        TArg(Exp* exp)
        : TArg(exp, TArgKind::Exp) {}

        TArg(Typespec* typespec)
        : TArg(typespec, TArgKind::Typespec) {}

      // getters:  
      public:
        Node* node() const {
            return m_node;
        }
        TArgKind arg_kind() const {
            return m_arg_kind;
        }

      // convenience properties:
      public:
        bool is_exp() const {
            return m_arg_kind == TArgKind::Exp;
        }
        bool is_typespec() const {
            return m_arg_kind == TArgKind::Typespec; 
        }
    };

}

#endif  // INCLUDED_PDM_AST_TARG_TARG_HH