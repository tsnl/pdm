#include "pdm/scoper/root_frame.hh"
#include "pdm/typer/typer.hh"
#include "pdm/typer/tv.hh"

#include "pdm/ast/stmt/builtin_type.hh"

namespace pdm::scoper {

    RootFrame::RootFrame(typer::Typer* frame_typer)
    : Frame(FrameKind::Root, nullptr, frame_typer) {
        help_append_new_builtin_type_context("Void", typer()->get_void_tv());
        help_append_new_builtin_type_context("String", typer()->get_string_tv());
        help_append_new_builtin_type_context("TypeInfo", typer()->get_type_info_tv());

        help_append_new_builtin_type_context("U1", typer()->get_u1_tv());
        help_append_new_builtin_type_context("U8", typer()->get_u8_tv());
        help_append_new_builtin_type_context("U16", typer()->get_u16_tv());
        help_append_new_builtin_type_context("U32", typer()->get_u32_tv());
        help_append_new_builtin_type_context("U64", typer()->get_u64_tv());
        help_append_new_builtin_type_context("U128", typer()->get_u128_tv());

        help_append_new_builtin_type_context("I8", typer()->get_i8_tv());
        help_append_new_builtin_type_context("I16", typer()->get_i16_tv());
        help_append_new_builtin_type_context("I32", typer()->get_i32_tv());
        help_append_new_builtin_type_context("I64", typer()->get_i64_tv());
        help_append_new_builtin_type_context("I128", typer()->get_i128_tv());

        help_append_new_builtin_type_context("F16", typer()->get_f16_tv());
        help_append_new_builtin_type_context("F32", typer()->get_f32_tv());
        help_append_new_builtin_type_context("F64", typer()->get_f64_tv());
    }

    void RootFrame::help_append_new_builtin_type_context(intern::String name, typer::TV* tv) {
        std::string debug_name = std::string("root_scope.") + std::string(name.content());
        ast::Stmt* stmt = new ast::BuiltinTypeStmt(std::move(debug_name), tv);
        Defn* defn = new Defn(DefnKind::BuiltinType, "U1", stmt, tv);
        append_new_context(defn);
    }

}