#include "import_stmt.hh"

#include "pdm/scoper/defn.hh"
#include "pdm/types/var.hh"

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

    types::TypeVar* ImportStmt::Field::x_exported_tv() const {
        auto tv = dynamic_cast<types::TypeVar*>(m_x_defn->var());
        assert(tv && "Expected TypeVar of Defn Var");
        return tv;
    }

}