#ifndef INCLUDED_AST_NODE_HH
#define INCLUDED_AST_NODE_HH

#include <string>
#include "pdm/source/loc.hh"

#include "kind.hh"

namespace pdm::ast {

    // NodeState specifies a growing series of capabilities.
    // - only 'Fresh' nodes can be modified
    // - 'Primed' nodes and newer have placeholder free types
    // - only 'Typed' nodes have either concrete solutions or errors
    // * Fresh -> Primed -> Typed
    enum class NodeState {
        Fresh,
        Primed,
        Typed
    };

    class Node {
      // data members:
      private:
        Kind        m_kind;
        source::Loc m_loc;
        NodeState   m_state;

      // general-purpose getters
      public:
        Kind kind() const {
            return m_kind;
        }
        source::Loc const& loc() const {
            return m_loc;
        }
        NodeState state() const {
            return m_state;
        }

      // state transitions:
      public:
        void chgstate__fresh_to_primed();
        void chgstate__primed_to_typed();

      // protected constructor:
      protected:
        Node(source::Loc loc, Kind kind)
        : m_kind(kind),
          m_loc(loc),
          m_state(NodeState::Fresh) {}

      public:
        virtual ~Node() {}
    };

}   // namespace pdm::ast

#endif  // INCLUDED_AST_NODE_HH