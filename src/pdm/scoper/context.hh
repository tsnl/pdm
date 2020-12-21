#ifndef INCLUDED_PDM_SCOPER_CONTEXT_HH
#define INCLUDED_PDM_SCOPER_CONTEXT_HH

#include <vector>
#include <string>

#include "pdm/core/intern.hh"
#include "pdm/ast/stmt/stmt.hh"

#include "pdm/scoper/defn.hh"

namespace pdm::scoper {

    // use push_frame/pop_frame when 'Context*' must be restored
    // use define when multiple non-overlapping symbols exist in the same lookup node.
    // use shadow when shadowing all symbols defined so far.

    class Frame;

    enum class ContextKind {
        Root,
        Script,
        Module,
        TPattern,
        VPattern,
        LPattern
    };

    class Context {
        friend Frame;

      private:
        ContextKind        m_kind;
        Frame*             m_frame;
        Context*           m_opt_parent_context;
        Frame*             m_opt_link;
        std::string        m_opt_link_prefix;
        std::vector<Defn*> m_defns;

      // protected constructor, intended for 'Frame'
      private:
        Context(ContextKind kind, Frame* frame, Context* opt_parent_context)
        : m_kind(kind),
          m_frame(frame),
          m_opt_parent_context(opt_parent_context),
          m_opt_link(nullptr),
          m_defns() {}

      // public property getters:
      public:
        ContextKind kind() {
            return m_kind;
        }
        Context* opt_parent_context() {
            return m_opt_parent_context;
        }
        std::vector<Defn*> const& defns() {
            return m_defns;
        }

      //
      // Define/Shadow: (see 'Frame')
      //

      protected:
        // define tries to add a new symbol to this context
        bool define(Defn* new_defn) {
            for (Defn* old_defn: m_defns) {
                if (old_defn->name() == new_defn->name()) {
                    return false;
                }
            }
            new_defn->container_context(this);
            m_defns.push_back(new_defn);
            return true;
        }

        // shadow creates a new child context
        // * must accept new 'frame' param since frames pushed/popped
        Context* shadow(ContextKind context_kind, Frame* frame) {
            return new Context(context_kind, frame, this);
        }

        // link adds a frame to query *after* any defined symbols
        void link(Frame* link_frame) {
            m_opt_link = link_frame;
            m_opt_link_prefix = "";
        }
        void link(Frame* link_frame, std::string&& opt_link_prefix) {
            link(link_frame);
            m_opt_link_prefix = std::move(opt_link_prefix);
        }

      //
      // Lookup:
      //

      // public query API:
      public:
        Defn* lookup(intern::String name);
        Defn* lookup_until(intern::String name, Context* opt_until_context);

      protected:
        Defn* help_lookup_shallow(intern::String name);
        Defn* help_lookup_link(intern::String name);
        Defn* help_lookup_parent(intern::String name, Context* opt_until_context);
    };

}

#endif  // INCLUDED_PDM_SCOPER_CONTEXT_HH