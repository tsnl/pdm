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
            case FrameKind::Package: return "Package";
        }
        if (DEBUG) {
            assert(0 && "NotImplemented: invalid FrameKind.");
        }
        return nullptr;
    }

    void Frame::print(printer::Printer* p) const {
        printer::print_c_str(p, "Frame ");
        printer::print_c_str(p, frame_kind_as_text(kind()));
        printer::print_c_str(p, " at ");
        printer::print_uint_hex(p, reinterpret_cast<u64>(this));
        printer::print_c_str(p, " {");
        printer::print_newline_indent(p);
        {
            printer::print_c_str(p, "Contexts:");
            printer::print_newline_indent(p);
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
                        printer::print_newline(p);
                    }
                    ctx_stack.pop();
                }
            }
            printer::print_newline_exdent(p);

            // newline spacer
            // printer::print_newline(p);

            // child frames:
            printer::print_c_str(p, "Sub-frames: (");
            printer::print_uint_dec(p, m_child_frames.size());
            printer::print_c_str(p, ") ...");
            if (m_child_frames.empty()) {
                // printer::print_newline(p);
            } else {
                printer::print_newline(p);

                int child_frame_count = m_child_frames.size();
                for (int index = 0; index < child_frame_count; index++) {
                    Frame* frame = m_child_frames[index];
                    frame->print(p);
                    if (index+1 != child_frame_count) {
                        printer::print_newline(p);
                    }
                }
            }
        }
        printer::print_newline_exdent(p);
        printer::print_c_str(p, "}");
    }

}
