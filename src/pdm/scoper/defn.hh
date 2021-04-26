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
namespace pdm::emitter {
    struct Dim;
}

namespace pdm::scoper {

    enum class DefnKind {
        BuiltinType, BuiltinClass,
        Module, ImportModule,
        Const,
        Val, Var,
        Type, Enum,
        Typeclass, TypeclassCandidate,
        Using,
        Import,
        Package_ExternModule, Package_ImportBundleModule,
        FormalVArg, FormalTArg,
        NO_DEF_FnTypeSpecFormalVArg
    };

    char const* defn_kind_as_text(DefnKind defn_kind);

    inline bool module_defn_kind(DefnKind defn_kind) {
        return (
            defn_kind == DefnKind::Module ||
            defn_kind == DefnKind::ImportModule ||
            defn_kind == DefnKind::Package_ExternModule ||
            defn_kind == DefnKind::Package_ImportBundleModule
        );
    }

    class Defn {
      private:
        DefnKind       m_kind;
        intern::String m_name;
        ast::Node*     m_defn_node;
        types::Var*    m_var;
        Context*       m_container_context;
        emitter::Dim*  m_x_llvm_dim;

      public:
        Defn(DefnKind kind, intern::String name, ast::Node* defn_node, types::Var* typer_var)
        :   m_kind(kind),
            m_name(name),
            m_defn_node(defn_node),
            m_var(typer_var),
            m_container_context(nullptr),
            m_x_llvm_dim(nullptr)
        {}

      public:
        [[nodiscard]] DefnKind kind() const {
            return m_kind;
        }
        [[nodiscard]] intern::String name() const {
            return m_name;
        }
        [[nodiscard]] ast::Node* defn_node() const {
            return m_defn_node;
        }
        [[nodiscard]] types::Var* var() const {
             return m_var;
        }
        [[nodiscard]] Context* container_context() const {
            return m_container_context;
        }

      public:
        Context* container_context(Context* context) {
            return m_container_context = context;
        }

      public:
        void print(printer::Printer* p) const;

      public:
        void x_llvm_dim(emitter::Dim* dim);
        [[nodiscard]] emitter::Dim* x_llvm_dim() const;
    };

    inline void Defn::x_llvm_dim(emitter::Dim* dim) {
        m_x_llvm_dim = dim;
    }

    inline emitter::Dim* Defn::x_llvm_dim() const {
        return m_x_llvm_dim;
    }

}

#endif  // INCLUDED_PDM_SCOPER_DEFN_HH