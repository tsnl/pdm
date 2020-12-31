#include "context.hh"

#include <cassert>

#include "frame.hh"

namespace pdm::scoper {

    //
    // misc
    //

    Context::Context(ContextKind kind, Frame* frame, Context* opt_parent_context)
    : m_kind(kind),
        m_frame(frame),
        m_opt_parent_context(opt_parent_context),
        m_opt_link(nullptr),
        m_opt_link_filter_prefix(),
        m_defns() {}

    bool Context::is_placeholder() const {
        return (
            m_kind == ContextKind::PH_ChainLink ||
            m_kind == ContextKind::PH_ChainStart ||
            m_kind == ContextKind::PH_EnumRhsStart ||
            m_kind == ContextKind::PH_FnRhsStart ||
            m_kind == ContextKind::PH_TypeclassRhsStart ||
            m_kind == ContextKind::PH_TypeRhsStart
        );
    }

    //
    // define
    //

    bool Context::define(Defn new_defn) {
        if (pdm::DEBUG) {
            assert(!is_placeholder() && "Placeholder contexts can only be shadowed.");
        }

        for (Defn const& old_defn: m_defns) {
            if (old_defn.name() == new_defn.name()) {
                return false;
            }
        }
        new_defn.container_context(this);
        m_defns.push_back(new_defn);
        return true;
    }

    //
    // shadow
    //

    // NOTE: expects scoper's latest 'frame' param since frames may be pushed/popped, so cannot blindly reuse parent's.
    Context* Context::shadow(Context* parent_context, ContextKind context_kind, Frame* frame) {
        return new Context(context_kind, frame, parent_context);
    }

    //
    // link
    //

    void Context::link(Frame* link_frame, std::string opt_filter_prefix) {
        m_opt_link = link_frame;
        m_opt_link_filter_prefix = std::move(opt_filter_prefix);
    }


    //
    // lookup
    //

    Defn const* Context::lookup(intern::String name) {
        return lookup_until(name, nullptr);
    }
    Defn const* Context::lookup_until(intern::String name, Context* opt_until_context) {
        Defn const* defn = nullptr; {
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

    //
    // lookup helpers
    //

    Defn const* Context::help_lookup_shallow(intern::String name) {
        for (Defn const& my_defn: m_defns) {
            if (my_defn.name() == name) {
                return &my_defn;
            }
        }
        return nullptr;
    }
    Defn const* Context::help_lookup_link(intern::String name) {
        if (m_opt_link != nullptr) {
            Context* first_context = m_opt_link->first_context();
            Context* last_context = m_opt_link->last_context();
            if (first_context != nullptr && last_context != nullptr) {
                return last_context->lookup_until(name, first_context);
            }
        }
        return nullptr;
    }
    Defn const* Context::help_lookup_parent(intern::String name, Context* opt_until_context) {
        if (m_opt_parent_context != nullptr) {
            return m_opt_parent_context->lookup_until(name, opt_until_context);
        } else {
            return nullptr;
        }
    }

    //
    // notes
    //

    // it is possible to replace 'deque' with 'vector' if we forbid 'define'
    // 'vector' is stable as long as we don't mutate it.
}