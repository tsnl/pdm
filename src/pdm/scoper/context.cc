#include "pdm/scoper/context.hh"

namespace pdm::scoper {

    Defn* Context::lookup(intern::String name) {
        Defn* defn = help_lookup(name);
        if (defn->kind() == DefnKind::Using) {
            // todo: invoke lookup_iter on a frame argument for 'using'
            return nullptr;
        }
        if (defn->kind() == DefnKind::Import) {
            // todo: invoke lookup_iter on a frame argument for 'import'
            return nullptr;
        }
        return defn;
    }

    Defn* Context::help_lookup(intern::String name) {
        if (m_opt_defn) {
            if (m_opt_defn->name() == name) {
                return m_opt_defn;
            }
        }
        if (m_opt_parent_context) {
            return m_opt_parent_context->lookup(name);
        }
        return nullptr;
    }

}