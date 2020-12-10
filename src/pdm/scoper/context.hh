#ifndef INCLUDED_PDM_SCOPER_CONTEXT_HH
#define INCLUDED_PDM_SCOPER_CONTEXT_HH

#include <vector>

#include "pdm/core/intern.hh"
#include "pdm/ast/stmt/stmt.hh"

#include "pdm/scoper/defn.hh"

namespace pdm::scoper {

    // use push_frame/pop_frame when 'Context*' must be restored
    // use try_define_in_last_context when multiple non-overlapping symbols exist in the same lookup node.
    // use append_child_context when shadowing all symbols defined so far.

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
        std::vector<Defn*> m_defns;

      // protected constructor, intended for 'Frame'
      private:
        Context(ContextKind kind, Frame* frame, Context* opt_parent_context)
        : m_kind(kind),
          m_frame(frame),
          m_opt_parent_context(opt_parent_context),
          m_defns() {}

      protected:
        ContextKind kind() {
            return m_kind;
        }
        bool try_define(Defn* new_defn) {
            for (Defn* old_defn: m_defns) {
                if (old_defn->name() == new_defn->name()) {
                    return false;
                }
            }
            new_defn->container_context(this);
            m_defns.push_back(new_defn);
            return true;
        }
        Context* new_child_context(ContextKind context_kind, Frame* frame) {
            return new Context(context_kind, frame, this);
        }

      public:
        Context* opt_parent_context() {
            return m_opt_parent_context;
        }
        std::vector<Defn*> const& defns() {
            return m_defns;
        }

      public:
        Defn* lookup(intern::String name);

      protected:
        Defn* help_lookup(intern::String name);
    };

}

#endif  // INCLUDED_PDM_SCOPER_CONTEXT_HH