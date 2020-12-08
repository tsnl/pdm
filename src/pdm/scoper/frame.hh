#ifndef INCLUDED_PDM_SCOPER_FRAME_HH
#define INCLUDED_PDM_SCOPER_FRAME_HH

#include "pdm/scoper/context.hh"
#include "pdm/ast/stmt/stmt.hh"

namespace pdm::scoper {

    enum class FrameKind {

    };

    class Frame {
      private:
        FrameKind m_kind;
        Frame*    m_parent_frame;
        Context*  m_first_context;
        Context*  m_last_context;
      
      public:
        Frame(FrameKind kind, Frame* parent_frame)
        : m_kind(kind),
          m_parent_frame(parent_frame),
          m_first_context(nullptr),
          m_last_context(nullptr) {}
    
      public:
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
