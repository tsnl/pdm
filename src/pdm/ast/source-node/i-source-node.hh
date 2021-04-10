#ifndef INCLUDED__PDM__AST__SOURCE_NODE__I_SOURCE_NODE_HH
#define INCLUDED__PDM__AST__SOURCE_NODE__I_SOURCE_NODE_HH

// forward-declaring LLVM dependencies:

#include "pdm/ast/node.hh"
#include "pdm/source/i-source.hh"
#include "pdm/source/loc.hh"

namespace pdm::ast {
    class BaseModExp;
}

namespace pdm::ast {

    class ISourceNode: public Node {
      private:
        source::ISource* m_source;
        scoper::Frame* m_x_export_frame;
        ast::BaseModExp* m_x_container_mod_exp;
        void* m_x_llvm_module_ref;

      protected:
        ISourceNode(source::ISource* node_source, source::Loc loc, Kind node_kind);

      public:
        [[nodiscard]] source::ISource* source() const;

      public:
        [[nodiscard]] scoper::Frame* x_export_frame() const;
        void x_export_frame(scoper::Frame* frame);

      public:
        // The 'container' module is an ANONYMOUS module whose fields contain each module defined in this source node.
        // It is used to import all modules from this source node in a bundle.
        // It is initialized in the dependency dispatcher, immediately after fetching dependencies [and before the
        // scoper].
        [[nodiscard]] ast::BaseModExp* x_container_mod_exp() const;
        void x_container_mod_exp(ast::BaseModExp* container_mod_exp);

      public:
        [[nodiscard]] void* x_llvm_module_ref() const;
        void x_llvm_module_ref(void* llvm_module_ref);
    };

    inline ISourceNode::ISourceNode(source::ISource* node_source, source::Loc loc, Kind node_kind)
    :   Node(loc, node_kind),
        m_source(node_source),
        m_x_export_frame(nullptr),
        m_x_container_mod_exp(nullptr)
    {}

    inline source::ISource* ISourceNode::source() const {
        return m_source;
    }

    inline scoper::Frame* ISourceNode::x_export_frame() const {
        return m_x_export_frame;
    }
    inline void ISourceNode::x_export_frame(scoper::Frame *frame) {
        m_x_export_frame = frame;
    }

    inline ast::BaseModExp* ISourceNode::x_container_mod_exp() const {
        return m_x_container_mod_exp;
    }
    inline void ISourceNode::x_container_mod_exp(ast::BaseModExp* container_mod_exp) {
        m_x_container_mod_exp = container_mod_exp;
    }

    inline void* ISourceNode::x_llvm_module_ref() const {
        return m_x_llvm_module_ref;
    }
    inline void ISourceNode::x_llvm_module_ref(void* llvm_module_ref) {
        m_x_llvm_module_ref = llvm_module_ref;
    }

}

#endif  // INCLUDED__PDM__AST__SOURCE_NODE__I_SOURCE_NODE_HH