#include "pdm/ast/stmt/builtin_type.hh"

#include <cassert>

#include "pdm/source/loc.hh"
#include "pdm/typer/var.hh"

namespace pdm::ast {

    BuiltinTypeStmt::BuiltinTypeStmt(std::string&& desc, typer::TypeVar* tv)
    : Stmt(source::Loc::none, Kind::BuiltinTypeStmt),
      m_desc(std::move(desc)),
      m_tv(tv) {
        assert(m_tv->soln_fixed());
    }

}