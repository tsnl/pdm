#include "kind.hh"

namespace pdm::ast {
    static char kind_as_cstr_table[][(int)Kind::META_Count] = {
        // AUDIT: ensure this lines up with Kind order.
        // generated from 'Kind'-- easily invalidated.
        "Script",
        "ScriptField",
        "ModExp",
        "ValueModField",
        "TypeModField",
        "ClassModField",
        "ModModField",
        "ModAddress",
        "TemplateModAddress",
        "BuiltinStmt",
        "DiscardStmt",
        "ConstStmt",
        "ValStmt",
        "VarStmt",
        "SetStmt",
        "ExternStmt",
        "ImportStmt",
        "UsingStmt",
        "UnitExp",
        "IntExp",
        "FloatExp",
        "StringExp",
        "IdExp",
        "ParenExp",
        "ArrayExp",
        "TupleExp",
        "StructExp",
        "ChainExp",
        "LambdaExp",
        "IfExp",
        "ModuleDotExp",
        "DotIndexExp",
        "DotNameExp",
        "UnaryExp",
        "BinaryExp",
        "VCallExp",
        "TCallExp",
        "TypeQueryExp",
        "VPattern",
        "TPattern",
        "LPattern",
        "IdTypeSpec",
        "FnTypeSpec",
        "DotTypeSpec",
        "TupleTypeSpec",
        "StructTypeSpec",
        "EnumTypeSpec",
        "IdClassSpec",
        "ClassExpClassSpec",
        "TArg",
        "VArg",
        "Aux_VPatternField",
        "Aux_TPatternField",
        "Aux_LPatternField",
        "__Count"
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
