#include "relation.hh"

namespace pdm::types {

    bool Relation::apply() {
        if (m_apply_state == ApplyState::NotApplied) {
            // todo: call an abstract virtual method here
            // todo: update m_apply_state based on the above result here.
            // - set Applied_OK if successful
            // - set Applied_Fail if unsuccessful
            return true;
        } else {
            return false;
        }
    }

}