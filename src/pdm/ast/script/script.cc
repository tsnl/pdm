#include "script.hh"

namespace pdm::ast {

    Script::Script(
        source::Source* source,
        source::Loc loc,
        std::vector<Stmt*>&& head_stmts,
        std::vector<ModStmt*>&& body_mod_stmts
    )
    :   Node(loc, Kind::Script),
        m_source(source),
        m_head_stmts(std::move(head_stmts)),
        m_body_mod_stmts(std::move(body_mod_stmts)),
        m_x_script_frame(nullptr)
    {}

}