#include "vpattern.hh"

#include "pdm/scoper/defn.hh"
#include "pdm/types/var.hh"

namespace pdm::ast {

    types::TypeVar* VPattern::Field::x_defn_tv() const {
        auto tv = dynamic_cast<types::TypeVar*>(x_defn()->var());
        assert(tv && "Expected TypeVar of Var in VPattern");
        return tv;
    }

}
