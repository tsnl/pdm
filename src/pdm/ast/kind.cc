#include "kind.hh"

namespace pdm::ast {
    static char kind_as_cstr_table[][(int)Kind::__Count] = {
        "Script",
        
        "BuiltinStmt",
        "DiscardStmt",
        "ConstStmt",
        "LetStmt",
        "VarStmt",
        "SetStmt",
        "FnStmt",
        "TypeStmt",
        "EnumStmt",
        "TypeclassStmt",
        "ModStmt",
        "LinkStmt",
        "ImportStmt",
        "UsingStmt",

        "UnitExp",
        "IntExp", "FloatExp", "StringExp",
        "IdExp",
        "ParenExp",
        "ArrayExp", "TupleExp", "StructExp", "ChainExp",
        "LambdaExp",
        "IfExp",
        "DotIndexExp", "DotNameExp",
        "UnaryExp", "BinaryExp",
        "VCallExp", "TCallExp",
        "TypeQueryExp",

        "VPattern",
        "TPattern",
        "LPattern",

        "IdTypespec",
        "PtrTypespec",
        "FnTypespec", "TCallTypespec",
        "DotNameTypespec_TypePrefix", "DotNameTypespec_ModPrefix",
        "TupleTypespec", "StructTypespec"
    };

    char const* kind_as_text(Kind kind) {
        return kind_as_cstr_table[(int)kind];
    }

    bool is_aux_kind(Kind kind) {
        return (
            kind == Kind::Aux_LPatternField ||
            kind == Kind::Aux_VPatternField ||
            kind == Kind::Aux_TPatternField
        );
    }

    bool is_pattern_kind(Kind kind) {
        return (
            kind == Kind::LPattern ||
            kind == Kind::VPattern ||
            kind == Kind::TPattern
        );
    }
}
