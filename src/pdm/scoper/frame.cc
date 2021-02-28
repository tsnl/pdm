#include "frame.hh"
#include <stack>

namespace pdm::scoper {
    
    char const* frame_kind_as_text(FrameKind frame_kind) {
        switch (frame_kind)
        {
            case FrameKind::Root: return "Root";
            case FrameKind::Script: return "Script";
            case FrameKind::ScriptFieldRhs: return "ScriptFieldRhs";
            case FrameKind::ModModFieldRhs: return "ModModFieldRhs";
            case FrameKind::ModuleBody: return "ModuleBody";
            case FrameKind::ValueModFieldRhs: return "ValueModFieldRhs";
            case FrameKind::TypeModFieldRhs: return "TypeModFieldRhs";
            case FrameKind::EnumTypeSpecBody: return "EnumTypeSpecBodyRhs";
            case FrameKind::ClassModFieldRhs: return "ClassModFieldRhs";
            case FrameKind::LPattern: return "LPattern";
            case FrameKind::VPattern: return "VPattern";
            case FrameKind::TPattern: return "TPattern";
            case FrameKind::Chain: return "Chain";
        }
        return nullptr;
    }

    void Frame::print(printer::Printer& p) const {
        p.print_c_str("Frame ");
        p.print_c_str(frame_kind_as_text(kind()));
        p.print_c_str(" at ");
        p.print_uint_hex(reinterpret_cast<u64>(this));
        p.print_c_str(" {");
        p.print_newline_indent();
        {
            p.print_c_str("Contexts:");
            p.print_newline_indent();
            {
                // reading all contexts into a stack...
                std::stack<Context*> ctx_stack;
                Context* ctx = last_context();
                for (;;) {
                    ctx_stack.push(ctx);
                    if (ctx == first_context()) {
                        break;
                    } else {
                        ctx = ctx->opt_parent_context();
                    }
                }

                // ...then popping to print in reverse order:
                while (!ctx_stack.empty()) {
                    ctx = ctx_stack.top();
                    ctx->print(p);
                    if (ctx_stack.size() > 1) {
                        p.print_newline();
                    }
                    ctx_stack.pop();
                }
            }
            p.print_newline_exdent();

            // newline spacer
            // p.print_newline();

            // child frames:
            p.print_c_str("Subframes: (");
            p.print_uint_dec(m_child_frames.size());
            p.print_c_str(") ...");
            if (m_child_frames.empty()) {
                // p.print_newline();
            } else {
                p.print_newline();

                int child_frame_count = m_child_frames.size();
                for (int index = 0; index < child_frame_count; index++) {
                    Frame* frame = m_child_frames[index];
                    frame->print(p);
                    if (index+1 != child_frame_count) {
                        p.print_newline();
                    }
                }
            }
        }
        p.print_newline_exdent();
        p.print_c_str("}");
    }

}
