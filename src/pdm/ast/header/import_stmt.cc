#include "import_stmt.hh"

namespace pdm::ast {

    ImportStmt::ImportStmt(
        source::Loc loc,
        intern::String import_name,
        utf8::String import_from,
        utf8::String import_type
    )
    :   HeaderStmt(loc, Kind::ImportStmt),
        m_import_name(import_name),
        m_import_from(std::move(import_from)),
        m_import_type(std::move(import_type)),
        m_x_origin_script(nullptr),
        m_x_exported_tv(nullptr),
        m_x_origin_mod_exp(nullptr) {}

}