#include <stdio.h>

#include "symbols.h"
#include "interp.h"

int main() {
    Interp* interp = CreateInterp();
    Source* scriptSource = CreateSource("test/test1.hub");
    if (!scriptSource) {
        printf("File not found.\n");
        return 1;
    }

    int result;
    
    result = InterpLoadModuleSource(interp, scriptSource);
    if (!result) {
        printf("Loading failed.\n");
        return 1;
    }
    printf("Loading succeeded.\n");
    
    result = InterpTypecheckModules(interp);
    if (!result) {
        printf("Linking failed.\n");
        return 1;
    }

    result = InterpCompile(interp);
    if (!result) {
        printf("LLVM emission failed.\n");
    }

    // TODO: execute, emit an executable, or just exit after reporting the program's validity.
    DestroyInterp(interp);
    return 0;
}


// TODO: (MAIN)........
// - PARSER/AST
//   - convert AST_STRUCT -> AST_TUPLE, constructed using '(...)' namedtuples with optional fields (so still LL(2))
//     - won't be used for postfix invocation, but orthogonality preserved
//   - remove 'check', will implement better 'test' statement later.
//   - implement 'enum' and tagged unions.
//   - change functions to accept numerous args rather than just 1
//     - update call syntax
//     - even unary functions map 1-tuples to an image.
//
// - TYPER
//   - rename META -> HOLE
//   - implement a better HOLE solver by...
//     - adding a 'soln' to each type instance (concrete iff soln = self)
//     - if a HOLE has any concrete required supertypes,
//       - select the submost concrete required supertype as SOLN
//     - else if a HOLE has any concrete required subtypes,
//       - select the supermost concrete required subtype as SOLN
//     - require SOLN as a supertype of each required HOLE subtype
// 
// - EMITTER
//   - implement lambda emission
//   - implement captures (fix)
//   - implement tuples
//     - call LLVMConstStruct in AST_TUPLE
//   - implement calls
//     - no destructuring required
//     - pass closures
