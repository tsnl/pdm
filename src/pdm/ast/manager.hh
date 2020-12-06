#ifndef INCLUDED_PDM_AST_MANAGER_HH
#define INCLUDED_PDM_AST_MANAGER_HH

#include "node.hh"
#include "node.script.hh"

namespace pdm::ast {

    class Manager {
      public:

    };

    // Script, 
        
    // ModuleStmt,
    // TypeclassStmt, EnumStmt, TypeStmt, DefStmt, LetStmt,

    // UnitExp, 
    // IntExp, FloatExp, StringExp,
    // IdExp, TIdExp,
    // ParenExp,
    // TupleExp, ArrayExp, StructExp, ChainExp,
    // LambdaExp, 
    // IfExp, MatchExp,
    // DotIndexExp, DotNameExp,
    // UnaryExp, BinaryExp,
    // VCallExp, TCallExp,
    // CastExp,

    // VPattern,       // used in def() and struct-typespec; top-mut types prohibited!
    // TPattern,       // used in def<>/[], type<>/[], class<>/[]4
    // LPattern,       // used in let, lambda, match

    // IdTypespec,
    // MutTypespec, PtrTypespec,
    // TCallTypespec,
    // DotNameTypespec,
    // StructTypespec,


}   // namespace pdm::ast

#endif  // INCLUDED_PDM_AST_MANAGER_HH
