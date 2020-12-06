#ifndef INCLUDED_PDM_AST_KIND_HH
#define INCLUDED_PDM_AST_KIND_HH

namespace pdm::ast {

    enum class Kind {
        Script, 
        
        ModuleStmt,
        TypeclassStmt, EnumStmt, TypeStmt, DefStmt, LetStmt,

        UnitExp, 
        IntExp, FloatExp, StringExp,
        IdExp,
        ParenExp,
        TupleExp, ArrayExp, StructExp, ChainExp,
        LambdaExp, 
        IfExp,
        DotIndexExp, DotNameExp,
        UnaryExp, BinaryExp,
        VCallExp, TCallExp,

        VPattern,       // used in def() and struct-typespec; top-mut types prohibited!
        TPattern,       // used in def<>/[], type<>/[], class<>/[]4
        LPattern,       // used in let, lambda, match

        IdTypespec,
        MutTypespec, PtrTypespec,
        TCallTypespec,
        DotNameTypespec,
        StructTypespec,
    };

    // dependencies: 
    // - visitor.hh

}   // namespace pdm::ast

#endif  // INCLUDED_PDM_AST_KIND_HH