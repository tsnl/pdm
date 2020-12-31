#include "import.hh"

namespace pdm::ast {

    ImportStmt::ImportStmt(source::Loc loc, intern::String import_name, utf8::String import_from, utf8::String import_type)
    : Stmt(loc, Kind::ImportStmt),
        m_import_name(import_name),
        m_import_from(import_from),
        m_import_type(import_type),
        m_x_origin_script(nullptr),
        m_x_exported_tv(nullptr),
        m_x_origin_mod_stmt(nullptr) {}
        
}