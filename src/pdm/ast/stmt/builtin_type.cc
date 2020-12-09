#include "pdm/ast/stmt/builtin_type.hh"

#include "pdm/source/loc.hh"
#include "pdm/typer/tv.hh"

namespace pdm::ast {

    BuiltinTypeStmt::BuiltinTypeStmt(std::string&& desc, typer::TV* tv)
    : Stmt(source::Loc::none, Kind::BuiltinTypeStmt),
      m_desc(std::move(desc)),
      m_tv(tv) {}

}