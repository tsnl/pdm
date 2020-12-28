#include "pdm/scoper/root_frame.hh"
#include "pdm/typer/typer.hh"
#include "pdm/typer/tv.hh"

#include "pdm/ast/stmt/builtin_type.hh"

namespace pdm::scoper {

    RootFrame::RootFrame(typer::Typer* frame_typer)
    : Frame(FrameKind::Root, nullptr, frame_typer) {
        shadow(ContextKind::Root); {
            help_define_builtin_type("Void", typer()->get_void_tv());
            help_define_builtin_type("String", typer()->get_string_tv());
            help_define_builtin_type("TypeInfo", typer()->get_type_info_tv());

            help_define_builtin_type("Bool", typer()->get_u1_tv());
            help_define_builtin_type("UInt8", typer()->get_u8_tv());
            help_define_builtin_type("UInt16", typer()->get_u16_tv());
            help_define_builtin_type("UInt32", typer()->get_u32_tv());
            help_define_builtin_type("UInt64", typer()->get_u64_tv());
            help_define_builtin_type("UInt128", typer()->get_u128_tv());

            help_define_builtin_type("Int8", typer()->get_i8_tv());
            help_define_builtin_type("Int16", typer()->get_i16_tv());
            help_define_builtin_type("Int32", typer()->get_i32_tv());
            help_define_builtin_type("Int64", typer()->get_i64_tv());
            help_define_builtin_type("Int128", typer()->get_i128_tv());

            help_define_builtin_type("Float16", typer()->get_f16_tv());
            help_define_builtin_type("Float32", typer()->get_f32_tv());
            help_define_builtin_type("Float64", typer()->get_f64_tv());
        }
    }

    void RootFrame::help_define_builtin_type(intern::String name, typer::TV* tv) {
        std::string debug_name = std::string("root_scope.") + std::string(name.content());
        ast::Stmt* stmt = new ast::BuiltinTypeStmt(std::move(debug_name), tv);
        Defn* defn = new Defn(DefnKind::BuiltinType, "U1", stmt, tv);
        define(defn);
    }

}
