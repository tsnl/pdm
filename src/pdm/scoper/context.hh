#ifndef INCLUDED_PDM_SCOPER_CONTEXT_HH
#define INCLUDED_PDM_SCOPER_CONTEXT_HH

#include <vector>
#include <string>

#include "pdm/core/config.hh"
#include "pdm/core/intern.hh"

#include "pdm/ast/stmt/stmt.hh"

#include "pdm/scoper/defn.hh"

namespace pdm::scoper {

    class Frame;

    enum class ContextKind {
        RootDefs,       // contains all primitives, builtins in one context
        ScriptDefs,     // contains all modules in a script in one context  (out)
        ModuleDefs,     // contains all constants/defns in a module in one context (out of order query) [fn,const]
        TPatternDefs,   // contains all defns in a TPattern
        VPatternDefs,   // contains all defns in a VPattern
        LPatternDefs,   // contains all defns in an LPattern
        
        PH_FnRhsStart,  // placeholder: chain start.
    };

    // Context represents a point in code from where symbols can be looked up.
    // - At each context, some symbols are defined while all others are not.
    // - Defined symbols are either stored on this context or its parents.
    // - Each Context may define multiple symbols, corresponds to one defn statement.
    //   - store on one Context for out-of-order lookup to work.
    //   - store on chained Contexts for shadowing to work.
    // - For 'Using', can also pass a 'linked frame' that is looked up
    // * a frame is a chain of contexts
    // * when a frame is 'popped' from a frame manager, it means that frame's parent is now
    //   top frame, so multiple contexts are actually popped.
    // * use push_frame/pop_frame when 'Context*' must be restored

    class Context {
        friend Frame;

      private:
        ContextKind        m_kind;
        Frame*             m_frame;
        Context*           m_opt_parent_context;
        Frame*             m_opt_link;
        std::string        m_opt_link_filter_prefix;
        std::vector<Defn*> m_defns;

      // protected constructor, intended for 'Frame'
      private:
        Context(ContextKind kind, Frame* frame, Context* opt_parent_context)
        : m_kind(kind),
          m_frame(frame),
          m_opt_parent_context(opt_parent_context),
          m_opt_link(nullptr),
          m_opt_link_filter_prefix(),
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

      private:
        bool is_placeholder() const {
            return m_kind == ContextKind::PH_FnRhsStart;
        }

      //
      // Define/Shadow: (see 'Frame')
      //

      protected:
        // define tries to add a new symbol to this context
        bool define(Defn* new_defn) {
            if (pdm::DEBUG) {
                assert(!is_placeholder() && "Placeholder contexts can only be shadowed.");
            }

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
        static Context* shadow(Context* parent_context, ContextKind context_kind, Frame* frame) {
            return new Context(context_kind, frame, parent_context);
        }

        // link adds a frame to query *after* any defined symbols
        void link(Frame* link_frame) {
            m_opt_link = link_frame;
            m_opt_link_filter_prefix = "";
        }
        void link(Frame* link_frame, std::string&& opt_filter_prefix) {
            link(link_frame);
            m_opt_link_filter_prefix = std::move(opt_filter_prefix);
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