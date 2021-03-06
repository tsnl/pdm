#ifndef INCLUDED__PDM__AST__SOURCE_NODE__I_SOURCE_NODE_HH
#define INCLUDED__PDM__AST__SOURCE_NODE__I_SOURCE_NODE_HH

#include "pdm/ast/node.hh"
#include "pdm/source/i_source.hh"
#include "pdm/source/loc.hh"

namespace pdm::ast {

    class ISourceNode: public Node {
      private:
        source::ISource* m_source;

      protected:
        ISourceNode(source::ISource* node_source, source::Loc loc, Kind node_kind);

      public:
        [[nodiscard]] source::ISource* source() const;
    };

    inline ISourceNode::ISourceNode(source::ISource* node_source, source::Loc loc, Kind node_kind)
    :   Node(loc, node_kind),
        m_source(node_source)
    {}

    inline source::ISource* ISourceNode::source() const {
        return m_source;
    }
}

#endif  // INCLUDED__PDM__AST__SOURCE_NODE__I_SOURCE_NODE_HH