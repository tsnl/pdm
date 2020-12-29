#include "pdm/scoper/context.hh"
#include "pdm/scoper/frame.hh"

namespace pdm::scoper {

    Defn* Context::lookup(intern::String name) {
        return lookup_until(name, nullptr);
    }
    Defn* Context::lookup_until(intern::String name, Context* opt_until_context) {
        Defn* defn = nullptr; {
            // 1. shallow defns:
            defn = help_lookup_shallow(name);
            if (defn != nullptr) {
                return defn;
            }

            // 2. link frame (using)
            defn = help_lookup_link(name);
            if (defn != nullptr) {
                return defn;
            }

            // 3. all possible parent definitions if this isn't the end:
            if (this != opt_until_context) {
                defn = help_lookup_parent(name, opt_until_context);
                if (defn != nullptr) {
                    return defn;
                }
            }
        }
        return defn;
    }

    Defn* Context::help_lookup_shallow(intern::String name) {
        for (Defn* my_defn: m_defns) {
            if (my_defn->name() == name) {
                return my_defn;
            }
        }
        return nullptr;
    }
    Defn* Context::help_lookup_link(intern::String name) {
        if (m_opt_link != nullptr) {
            Context* first_context = m_opt_link->first_context();
            Context* last_context = m_opt_link->last_context();
            if (first_context != nullptr && last_context != nullptr) {
                return last_context->lookup_until(name, first_context);
            }
        }
        return nullptr;
    }
    Defn* Context::help_lookup_parent(intern::String name, Context* opt_until_context) {
        if (m_opt_parent_context != nullptr) {
            return m_opt_parent_context->lookup_until(name, opt_until_context);
        } else {
            return nullptr;
        }
    }
}