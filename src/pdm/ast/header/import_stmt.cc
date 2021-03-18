#include "import_stmt.hh"

namespace pdm::ast {

    ImportStmt::ImportStmt(
        source::Loc loc,
        std::vector<FieldGroup*> field_groups
    )
    :   HeaderStmt(loc, Kind::ImportStmt),
        m_field_groups(std::move(field_groups))
    {
        for (FieldGroup* group: m_field_groups) {
            group->m_parent_import_stmt = this;
        }
    }

}