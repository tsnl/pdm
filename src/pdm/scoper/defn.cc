#include "defn.hh"

namespace pdm::scoper {
    char const* defn_kind_as_text(DefnKind defn_kind) {
        switch (defn_kind)
        {
            case DefnKind::BuiltinType: return "BuiltinType";
            case DefnKind::Module: return "Module";
            case DefnKind::ImportModule: return "ImportModule";
            case DefnKind::Const: return "Const";
            case DefnKind::Val: return "Val";
            case DefnKind::Var: return "Var";
            case DefnKind::Type: return "Type";
            case DefnKind::Enum: return "Enum";
            case DefnKind::Typeclass: return "Typeclass";
            case DefnKind::Using: return "Using";
            case DefnKind::Import: return "Import";
            case DefnKind::ExternObject: return "ExternObject";
            case DefnKind::FormalVArg: return "FormalVArg";
            case DefnKind::FormalTArg: return "FormalTArg";
        }
        return nullptr;
    }

    void Defn::print(printer::Printer& p) const {
        p.print_intstr(name());
        p.print_cstr(":");
        p.print_cstr(defn_kind_as_text(kind()));
    }
}