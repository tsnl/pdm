#ifndef INCLUDED_PDM_SCOPER_FRAME_HH
#define INCLUDED_PDM_SCOPER_FRAME_HH

#include <vector>
#include <cassert>

#include "pdm/ast/stmt/stmt.hh"
#include "pdm/scoper/context.hh"
#include "pdm/types/manager.hh"
#include "pdm/printer/printer.hh"


namespace pdm::scoper {

    enum class FrameKind {
        Root,
        Script, ScriptFieldRhs,
        ModModFieldRhs, ValueModFieldRhs, TypeModFieldRhs, EnumTypeSpecBody, ClassModFieldRhs,
        LPattern, VPattern, TPattern,
        Chain
    };

    char const* frame_kind_as_text(FrameKind frame_kind);

    // Frame is a sequence of Contexts, s.t. each predecessor is successor's parent
    // last_context->parent->parent... = first_context
    // - denote a 'scope' of definitions
    // - used by links
    class Frame {
      private:
        types::Manager*       m_typer;
        FrameKind           m_kind;
        Frame*              m_parent_frame;
        std::vector<Frame*> m_child_frames;
        Context*            m_first_context;
        Context*            m_last_context;

      protected:
        // primary constructor: called by all other constructors
        Frame(FrameKind kind, Frame* parent_frame, types::Manager* typer)
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
        FrameKind kind() const {
            return m_kind;
        }
        types::Manager* typer() const {
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
                case FrameKind::ScriptFieldRhs: return ContextKind::ModuleDefs;
                case FrameKind::ModModFieldRhs: return ContextKind::ModuleDefs;
                case FrameKind::ValueModFieldRhs: return ContextKind::ChainStart;
                case FrameKind::Chain: return ContextKind::ChainStart;
                case FrameKind::LPattern: return ContextKind::LPatternDefs;
                case FrameKind::VPattern: return ContextKind::VPatternDefs;
                case FrameKind::TPattern: return ContextKind::TPatternDefs;

                // unclear if actually useful:
                case FrameKind::TypeModFieldRhs: return ContextKind::TypeRhsStart;
                case FrameKind::EnumTypeSpecBody: return ContextKind::EnumRhsStart;
                case FrameKind::ClassModFieldRhs: return ContextKind::TypeclassRhsStart;
            }
        }

      public:
        // push a new context in this frame 
        Context* shadow(ContextKind new_context_kind) {
            Context* parent_context = last_context();
            return m_last_context = Context::shadow(parent_context, new_context_kind, this);
        }

        // define a symbol in the topmost Defn
        bool define(scoper::Defn defn) {
            return m_last_context->define(defn);
        }

      public:
        void print(printer::Printer& p) const;
    };

}

#endif  // INCLUDED_PDM_SCOPER_FRAME_HH
