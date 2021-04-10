#include "lpattern.hh"

#include "pdm/scoper/scoper.hh"
#include "pdm/types/var.hh"

namespace pdm::ast {

    types::TypeVar* LPattern::Field::x_defn_tv() const {
        auto tv = dynamic_cast<types::TypeVar*>(x_defn()->var());
        assert(tv && "Cannot access `x_defn_tv` from non-TV symbol");
        return tv;
    }

}