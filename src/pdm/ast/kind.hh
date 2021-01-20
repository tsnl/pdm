#ifndef INCLUDED_PDM_AST_KIND_HH
#define INCLUDED_PDM_AST_KIND_HH

namespace pdm::ast {

    enum class Kind {
        // scripts:
        Script, 
        
        // statements:
        BuiltinStmt,    // non-syntactic
        DiscardStmt, ConstStmt, ValStmt, VarStmt, SetStmt,
        ModValStmt, ModTypeStmt, ModEnumStmt, ModTypeclassStmt,
        ModStmt,
        ExternStmt,
        ImportStmt,
        UsingStmt,

        // expressions:
        UnitExp, 
        IntExp, FloatExp, StringExp,
        IdExp,
        ParenExp,
        ArrayExp, TupleExp, StructExp, ChainExp,
        LambdaExp,
        IfExp,
        ModuleDotExp, DotIndexExp, DotNameExp,
        UnaryExp, BinaryExp,
        VCallExp, TCallExp,
        TypeQueryExp,

        // patterns:
        VPattern,       // used in def() and struct-typespec; top-mut types prohibited!
        TPattern,       // used in def<>/[], type<>/[], class<>/[]4
        LPattern,       // used in let, lambda, match

        // typespecs:
        IdSetSpec,
        ParenTypeSpec,
        FnTypeSpec, TCallTypeSpec,
        DotNameTypeSpec_ModPrefix,
        TupleTypeSpec, StructTypeSpec,
        // DotNameTypeSpec_TypePrefix,

        // args:
        TArg, VArg,

        // helpers, don't get own visit methods:
        Aux_VPatternField,
        Aux_TPatternField,
        Aux_LPatternField,

        // total count:
        __Count
    };

    // dependencies (updated when 'Kind' changed)
    // - ast/*/*.hh: add a class corresponding to this Kind
    // - visitor.hh: add a visit method/delegate
    // - kind.cc: update names IN ORDER

    char const* kind_as_text(Kind kind);

    bool is_aux_kind(Kind kind);

    bool is_pattern_kind(Kind kind);

}   // namespace pdm::ast

#endif  // INCLUDED_PDM_AST_KIND_HH
