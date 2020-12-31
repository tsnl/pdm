#ifndef INCLUDED_PDM_SCOPER_CONTEXT_HH
#define INCLUDED_PDM_SCOPER_CONTEXT_HH

#include <vector>
#include <deque>
#include <string>

#include "pdm/core/config.hh"
#include "pdm/core/intern.hh"

#include "pdm/ast/stmt/stmt.hh"

#include "pdm/scoper/defn.hh"

namespace pdm::scoper {

    class Frame;

    // ContextKind tells the compiler why a Context was created.
    enum class ContextKind {
        // contexts containing Defns:
        RootDefs,               // contains all primitives, builtins in one context
        ScriptDefs,             // contains all modules in a script in one context  (out)
        ModuleDefs,             // contains all constants/defns in a module in one context (out of order query) [fn,const]
        TPatternDefs,           // contains all defns in a TPattern
        VPatternDefs,           // contains all defns in a VPattern
        LPatternDefs,           // contains all defns in an LPattern
        
        // contexts that should never contain symbols, but help initialize Frames:
        PH_FnRhsStart,          // placeholder: start of fn defn (rhs, incl. targs and vargs).
        PH_TypeRhsStart,        // placeholder: start of type defn (rhs, incl. targs).
        PH_EnumRhsStart,        // placeholder: start of enum defn (rhs, incl. targs).
        PH_TypeclassRhsStart,   // placeholder: start of typeclass defn (rhs, incl. targs).
        PH_ChainStart,          // placeholder: start of chain exp.
        PH_ChainLink,           // placeholder: start of a new statement in a chain (shadowing)
    };

    // Context represents a point in code from where symbols can be looked up.
    // - At each context, some symbols are defined while all others are not.
    // - Defined symbols are either stored on this context or its parents.
    // - Each Context may define multiple symbols, corresponds to one defn statement.
    //   - store on one Context for out-of-order lookup to work.
    //   - store on chained Contexts for shadowing to work.
    // - For 'Using', can also pass a 'linked frame' that is looked up

    // (extra on frames)
    // * a frame is a chain of contexts
    // * when a frame is 'popped' from a frame manager, it means that frame's parent is now
    //   top frame, so multiple contexts are actually popped.
    // * use push_frame/pop_frame when 'Context*' must be restored

    class Context {
        friend Frame;

      private:
        ContextKind      m_kind;
        Frame*           m_frame;
        Context*         m_opt_parent_context;
        Frame*           m_opt_link;
        std::string      m_opt_link_filter_prefix;
        std::deque<Defn> m_defns;

      // protected constructor, intended for 'Frame'
      private:
        Context(ContextKind kind, Frame* frame, Context* opt_parent_context);

      // public property getters:
      public:
        ContextKind kind() {
            return m_kind;
        }
        Context* opt_parent_context() {
            return m_opt_parent_context;
        }
        std::deque<Defn> const& defns() {
            return m_defns;
        }

      private:
        bool is_placeholder() const;

      // define / shadow
      protected:
        // define tries to add a new symbol to this context.
        bool define(Defn new_defn);

        // shadow creates a new child context
        static Context* shadow(Context* parent_context, ContextKind context_kind, Frame* frame);

      // link:
      public:
        // link adds a frame to query *after* any defined symbols
        void link(Frame* link_frame, std::string opt_filter_prefix);

      // lookup:
      public:
        Defn const* lookup(intern::String name);
        Defn const* lookup_until(intern::String name, Context* opt_until_context);

      // private helpers
      protected:
        Defn const* help_lookup_shallow(intern::String name);
        Defn const* help_lookup_link(intern::String name);
        Defn const* help_lookup_parent(intern::String name, Context* opt_until_context);
    };

}

#endif  // INCLUDED_PDM_SCOPER_CONTEXT_HH
