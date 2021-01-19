#include "pdm/ast/stmt/builtin.hh"

#include <cassert>

#include "pdm/source/loc.hh"
#include "pdm/types/var.hh"

namespace pdm::ast {

    BuiltinStmt::BuiltinStmt(std::string&& desc)
    : Stmt(source::Loc::none, Kind::BuiltinStmt),
      m_desc(std::move(desc)),
      m_x_tv(nullptr) {}

    void BuiltinStmt::x_tv(types::TypeVar* tv) {
        assert(tv->is_soln_fixed());
        m_x_tv = tv;
    }

    types::TypeVar* BuiltinStmt::x_tv() const {
        return m_x_tv;
    }
}