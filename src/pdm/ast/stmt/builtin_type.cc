#include "pdm/ast/stmt/builtin_type.hh"

#include <cassert>

#include "pdm/source/loc.hh"
#include "pdm/typer/var.hh"

namespace pdm::ast {

    BuiltinTypeStmt::BuiltinTypeStmt(std::string&& desc)
    : Stmt(source::Loc::none, Kind::BuiltinTypeStmt),
      m_desc(std::move(desc)),
      m_x_tv(nullptr) {}

    void BuiltinTypeStmt::x_tv(typer::TypeVar* tv) {
        assert(tv->soln_fixed());
        m_x_tv = tv;
    }

    typer::TypeVar* BuiltinTypeStmt::x_tv() const {
        return m_x_tv;
    }
}