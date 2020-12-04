#ifndef INCLUDED_PDM_AST_KIND_HH
#define INCLUDED_PDM_AST_KIND_HH

namespace pdm::ast {

    enum class Kind {
        Script, 
        
        ModuleStmt,
        ClassStmt, EnumStmt, TypeStmt, DefStmt, LetStmt,

        UnitExp, 
        IntExp, FloatExp, StringExp,
        VIdExp, TIdExp,
        ParenExp,
        TupleExp, ArrayExp, StructExp, ChainExp,
        LambdaExp, 
        IfExp, MatchExp,
        DotIndexExp, DotNameExp,
        UnaryExp, BinaryExp,
        VCallExp, TCallExp,
        CastExp,
        VPattern,       // used in def() and struct-typespec; top-mut types prohibited!
        TPattern,       // used in def<>/[], type<>/[], class<>/[]4
        LPattern        // used in let, lambda, match
    };

    // dependencies: 
    // - visitor.hh

}   // namespace pdm::ast

#endif  // INCLUDED_PDM_AST_KIND_HH