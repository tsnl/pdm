#include "script.hh"

#include "pdm/ast/module/mod_exp.hh"
#include "pdm/ast/header/header_stmt.hh"

namespace pdm::ast {

    Script::Script(
        source::Source* source,
        source::Loc loc,
        std::vector<HeaderStmt*>&& header_stmts,
        std::vector<Script::Field*>&& body_fields
    )
    : Node(loc, Kind::Script),
      m_source(source),
      m_header_stmts(std::move(header_stmts)),
      m_body_fields(std::move(body_fields)),
      m_x_script_frame(nullptr)
    {}

}