#include "pdm/ast/stmt/builtin.hh"

#include <cassert>

#include "pdm/types/var.hh"

namespace pdm::ast {

    void BuiltinStmt::x_tv(types::TypeVar* tv) {
        assert(tv->is_soln_fixed());
        m_x_tv = tv;
    }

}