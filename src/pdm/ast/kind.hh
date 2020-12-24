#ifndef INCLUDED_PDM_AST_KIND_HH
#define INCLUDED_PDM_AST_KIND_HH

namespace pdm::ast {

    enum class Kind {
        // scripts:
        Script, 
        
        // statements:
        BuiltinTypeStmt,    // non-syntactic
        DiscardStmt,
        ConstStmt,
        LetStmt,
        VarStmt,
        SetStmt,
        FnStmt,
        TypeStmt,
        EnumStmt,
        TypeclassStmt,
        ModStmt,
        LinkStmt,
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
        DotIndexExp, DotNameExp,
        UnaryExp, BinaryExp,
        VCallExp, TCallExp,
        TypeQueryExp,

        // patterns:
        VPattern,       // used in def() and struct-typespec; top-mut types prohibited!
        TPattern,       // used in def<>/[], type<>/[], class<>/[]4
        LPattern,       // used in let, lambda, match

        // typespecs:
        IdTypespec,
        MutTypespec, PtrTypespec,
        FnTypespec, TCallTypespec,
        DotNameTypespec_TypePrefix, DotNameTypespec_ModPrefix,
        TupleTypespec, StructTypespec,
    };

    // dependencies: 
    // - visitor.hh

}   // namespace pdm::ast

#endif  // INCLUDED_PDM_AST_KIND_HH