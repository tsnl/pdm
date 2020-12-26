#include "kind.hh"

namespace pdm::ast {
    static char kind_as_cstr_table[][(int)Kind::__Count] = {
        "Script",
        
        "BuiltinTypeStmt",
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

    char const* kind_as_cstr(Kind kind) {
        return kind_as_cstr_table[(int)kind];
    }
}
