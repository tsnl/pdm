#ifndef INCLUDED_PDM_SCOPER_DEFN_HH
#define INCLUDED_PDM_SCOPER_DEFN_HH

#include "pdm/core/intern.hh"
#include "pdm/printer/printer.hh"

namespace pdm::ast {
    class Node;
}
namespace pdm::types {
    class Var;
}
namespace pdm::scoper {
    class Context;
}

namespace pdm::scoper {

    enum class DefnKind {
        BuiltinType,
        Module, ImportModule,
        Const,
        Val, Var,
        Type, Enum,
        Typeclass,
        Using,
        Import,
        ExternObject,
        FormalVArg, FormalTArg,
        IGNORE_FnTypeSpecFormalVArg
    };

    char const* defn_kind_as_text(DefnKind defn_kind);

    inline bool module_defn_kind(DefnKind defn_kind) {
        return (0
            || defn_kind == DefnKind::Module
            || defn_kind == DefnKind::ImportModule
        );
    }

    class Defn {
      private:
        DefnKind       m_kind;
        intern::String m_name;
        ast::Node*     m_defn_node;
        types::Var*    m_var;
        Context*       m_container_context;

      public:
        Defn(DefnKind kind, intern::String name, ast::Node* defn_node, types::Var* typer_var)
        : m_kind(kind), 
          m_name(name), 
          m_defn_node(defn_node),
          m_var(typer_var),
          m_container_context(nullptr) {}

      public:
        DefnKind kind() const {
            return m_kind;
        }
        intern::String name() const {
            return m_name;
        }
        ast::Node* defn_node() const {
            return m_defn_node;
        }
        types::Var* var() const {
            return m_var;
        }
        Context* container_context() const {
            return m_container_context;
        }

      public:
        Context* container_context(Context* context) {
            return m_container_context = context;
        }

      public:
        void print(printer::Printer& p) const;
    };

}

#endif  // INCLUDED_PDM_SCOPER_DEFN_HH