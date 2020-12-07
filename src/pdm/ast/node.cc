#include "node.hh"

#include <cassert>


namespace pdm::ast {

    void Node::chgstate__fresh_to_primed() {
        assert(m_state == NodeState::Fresh);
        m_state = NodeState::Primed;
    }

    void Node::chgstate__primed_to_typed() {
        assert(m_state == NodeState::Primed);
        m_state = NodeState::Typed;
    }

}
