#include "context.hh"

#include <cassert>
#include <ostream>
#include <iomanip>

#include "frame.hh"
#include "context.hh"

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

    //
    // define
    //

    bool Context::define(Defn new_defn) {
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
    // debug
    //

    void Context::print(printer::Printer& p) const {
        p.print_cstr(context_kind_as_text(kind()));
        p.print_cstr(" {");
        for (int defn_index = 0; defn_index < m_defns.size(); defn_index++) {
            Defn const& defn = m_defns[defn_index];
            defn.print(p);
            if (defn_index+1 != m_defns.size()) {
                p.print_cstr(", ");
            }
        }
        p.print_cstr("}");
        if (m_opt_link) {
            p.print_cstr(" link_to (Frame at ");
            p.print_uint_hex(reinterpret_cast<u64>(m_opt_link));
            p.print_cstr(")");
        }
    }

    char const* context_kind_as_text(ContextKind context_kind) {
        switch (context_kind)
        {
            case ContextKind::RootDefs: return "RootDefs";
            case ContextKind::ScriptDefs: return "ScriptDefs";
            case ContextKind::ModuleDefs: return "ModuleDefs";
            case ContextKind::TPatternDefs: return "TPatternDefs";
            case ContextKind::VPatternDefs: return "VPatternDefs";
            case ContextKind::LPatternDefs: return "LPatternDefs";
            case ContextKind::FnRhsStart: return "FnRhsStart";
            case ContextKind::TypeRhsStart: return "TypeRhsStart";
            case ContextKind::EnumRhsStart: return "EnumRhsStart";
            case ContextKind::TypeclassRhsStart: return "TypeclassRhsStart";
            case ContextKind::ChainStart: return "ChainStart";
            case ContextKind::ChainLink: return "ChainLink";
        }
        return nullptr;
    }

    //
    // notes
    //

    // it is possible to replace 'deque' with 'vector' if we forbid 'define' after any 'lookup'
    // since any 'vector' instance is stable as long as we don't mutate it.

}