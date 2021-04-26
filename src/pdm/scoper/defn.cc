#include "defn.hh"

namespace pdm::scoper {
    char const* defn_kind_as_text(DefnKind defn_kind) {
        switch (defn_kind)
        {
            case DefnKind::BuiltinType: return "BuiltinType";
            case DefnKind::BuiltinClass: return "BuiltinClass";
            case DefnKind::Module: return "Mod";
            case DefnKind::ImportModule: return "ImportModule";
            case DefnKind::Const: return "Const";
            case DefnKind::Val: return "Val";
            case DefnKind::Var: return "Var";
            case DefnKind::Type: return "Type";
            case DefnKind::Enum: return "Enum";
            case DefnKind::Typeclass: return "Typeclass";
            case DefnKind::TypeclassCandidate: return "TypeclassCandidate";
            case DefnKind::Using: return "Using";
            case DefnKind::Import: return "Import";
            case DefnKind::Package_ExternModule: return "Package_ExternModule";
            case DefnKind::Package_ImportBundleModule: return "Package_ImportBundleModule";
            case DefnKind::FormalVArg: return "FormalVArg";
            case DefnKind::FormalTArg: return "FormalTArg";
            case DefnKind::NO_DEF_FnTypeSpecFormalVArg: return "NO_DEF_FnTypeSpecFormalVArg";
        }
        return nullptr;
    }

    void Defn::print(printer::Printer* p) const {
        printer::print_int_str(p, name());
        printer::print_c_str(p, ":");
        printer::print_c_str(p, defn_kind_as_text(kind()));
    }
}