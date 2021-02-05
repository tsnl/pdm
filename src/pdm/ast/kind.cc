#include "kind.hh"

namespace pdm::ast {
    static char kind_as_cstr_table[][(int)Kind::__Count] = {
        "Script",
        
        "BuiltinStmt",
        "DiscardStmt",
        "ConstStmt",
        "ValStmt",
        "VarStmt",
        "SetStmt",
        "ModValStmt",
        "ModTypeStmt",
        "ModEnumStmt",
        "ModTypeclassStmt",
        "ModStmt",
        "ExternStmt",
        "ImportStmt",
        "UsingStmt",

        "UnitExp",
        "IntExp", "FloatExp", "StringExp",
        "IdExp",
        "ParenExp",
        "ArrayExp", "TupleExp", "StructExp", "ChainExp",
        "LambdaExp",
        "IfExp",
        "ModuleDotExp", "DotIndexExp", "DotNameExp",
        "UnaryExp", "BinaryExp",
        "VCallExp", "TCallExp",
        "TypeQueryExp",

        "VPattern",
        "TPattern",
        "LPattern",

        "IdTypeSpec", "IdClassSpec",
        "ParenTypeSpec",
        "FnTypeSpec",
        "TCallTypeSpec", "TCallClassSpec",
        "DotNameTypeSpec_ModPrefix",
        "TupleTypeSpec", "StructTypeSpec"
        // "DotNameTypeSpec_TypePrefix"
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
