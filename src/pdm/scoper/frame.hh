#ifndef INCLUDED_PDM_SCOPER_FRAME_HH
#define INCLUDED_PDM_SCOPER_FRAME_HH

#include <vector>
#include <cassert>

#include "pdm/ast/stmt/stmt.hh"
#include "pdm/scoper/context.hh"
#include "pdm/typer/typer.hh"

namespace pdm::scoper {

    enum class FrameKind {
        Root,
        Script,
        Module,
        FnRhs,
    };

    // Frame is a sequence of Contexts, s.t. each predecessor is successor's parent
    // last_context->parent->parent... = first_context
    // - denote a 'scope' of definitions
    // - used by links
    class Frame {
      private:
        typer::Typer*       m_typer;
        FrameKind           m_kind;
        Frame*              m_parent_frame;
        std::vector<Frame*> m_child_frames;
        Context*            m_first_context;
        Context*            m_last_context;

      protected:
        // primary constructor: called by all other constructors
        Frame(FrameKind kind, Frame* parent_frame, typer::Typer* typer)
        : m_typer(typer),
          m_kind(kind),
          m_parent_frame(parent_frame),
          m_first_context(nullptr),
          m_last_context(nullptr) {
            // if non-null parent, updating:
            Context* parent_last_ctx = nullptr;
            if (m_parent_frame) {
                m_parent_frame->m_child_frames.push_back(this);
                parent_last_ctx = m_parent_frame->last_context();
            }

            // creating a new Context for this frame based on the frame kind:
            ContextKind child_ctx_kind = select_child_ctx_kind();
            m_first_context = new Context(child_ctx_kind, this, parent_last_ctx);
            m_last_context = m_first_context;

            // thus, every 'Frame' always has a non-nullptr 'first' and 'last' context.
            // all done!
        }
    
      public:
        Frame(FrameKind kind, Frame* parent_frame)
        : Frame(kind, parent_frame, parent_frame->typer()) {}

      public:
        typer::Typer* typer() const {
            return m_typer;
        }
        Frame* parent_frame() const {
            return m_parent_frame;
        }
        std::vector<Frame*> const& child_frames() const {
            return m_child_frames;
        }
        Context* first_context() const {
            return m_first_context;
        }
        Context* last_context() const {
            return m_last_context;
        }

      private:
        ContextKind select_child_ctx_kind() const { 
            switch (m_kind) {
                case FrameKind::Root: return ContextKind::RootDefs;
                case FrameKind::Script: return ContextKind::ScriptDefs;
                case FrameKind::Module: return ContextKind::ModuleDefs;
                case FrameKind::FnRhs: return ContextKind::PH_FnRhsStart;
            }
        }

      public:
        // push a new context in this frame 
        Context* shadow(ContextKind new_context_kind) {
            Context* parent_context = last_context();
            // assert(parent_context != nullptr);
            // note that paren_context may be nullptr, and 'shadow' still works.
            m_last_context = Context::shadow(parent_context, new_context_kind, this);

            if (m_first_context == nullptr) {
                m_first_context = m_last_context;
            }
            
            return m_last_context;
        }

        // define a symbol in the topmost Defn
        bool define(scoper::Defn* defn) {
            return m_last_context->define(defn);
        }
    };

}

#endif  // INCLUDED_PDM_SCOPER_FRAME_HH
