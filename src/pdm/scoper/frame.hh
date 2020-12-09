#ifndef INCLUDED_PDM_SCOPER_FRAME_HH
#define INCLUDED_PDM_SCOPER_FRAME_HH

#include <vector>

#include "pdm/ast/stmt/stmt.hh"
#include "pdm/scoper/context.hh"
#include "pdm/typer/typer.hh"

namespace pdm::scoper {

    enum class FrameKind {
        Root,
    };

    // Frame is a sequence of consecutively nested contexts.
    // last_context->parent->parent... = first_context
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
            if (m_parent_frame) {
                m_parent_frame->m_child_frames.push_back(this);
            }
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

        Context* opt_last_context() const {
            if (m_last_context) {
                return m_last_context;
            }
            if (m_parent_frame) {
                return m_parent_frame->opt_last_context();
            }
            return nullptr;
        }

        void append_new_context(scoper::Defn* defn) {
            // allocating a new context:
            Context* parent_context = opt_last_context();
            Context* new_context = new Context(this, parent_context, defn);

            // updating first/last ptrs:
            if (m_first_context == nullptr) {
                m_first_context = new_context;
            }
            m_last_context = new_context;
        }
    };

}

#endif  // INCLUDED_PDM_SCOPER_FRAME_HH
