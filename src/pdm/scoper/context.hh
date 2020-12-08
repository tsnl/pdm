#ifndef INCLUDED_PDM_SCOPER_CONTEXT_HH
#define INCLUDED_PDM_SCOPER_CONTEXT_HH

#include "pdm/core/intern.hh"
#include "pdm/ast/stmt/stmt.hh"

#include "pdm/scoper/defn.hh"

namespace pdm::scoper {

    class Frame;

    class Context {
        friend Frame;

      private:
        Frame*   m_frame;
        Context* m_opt_parent_context;
        Defn*    m_opt_defn;

      // protected constructor, intended for 'Frame'
      protected:
        Context(Frame* frame, Context* opt_parent_context, Defn* opt_defn = nullptr)
        : m_frame(frame),
          m_opt_parent_context(opt_parent_context),
          m_opt_defn(opt_defn) {
            if (m_opt_defn) {
                m_opt_defn->buddy_context(this);
            }
        }

      public:
        Context* opt_parent_context() {
            return m_opt_parent_context;
        }
        Defn* opt_defn() {
            return m_opt_defn;
        }

      public:
        Defn* lookup(intern::String name);

      protected:
        Defn* help_lookup(intern::String name);
    };

}

#endif  // INCLUDED_PDM_SCOPER_CONTEXT_HH