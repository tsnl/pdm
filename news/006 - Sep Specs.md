**April 25**

Idea:
- separate type specifiers from definition
- keep postfix call, but use ML-style type declaration + access spec
- move all type specification into `typ`

This results in a much more Python-like language, and makes it easier to write 
functional code since lambdas are inferred in type automatically.

Work must be done to make type errors meaningful.
- when no solution can be found, hints can be given to improve typing.
- default types for literals + aggressive global inference (existing)
  should result in defaults always being present that work for data at
  hand.
  
Note:
- have a lot to learn from interpreted languages, idea of interpreting to fixed 
  point and using metaprogramming/reflection to dump.
- if this is the direction we take, just expand templates in the AST for each
  instantiation (inefficient though it may be)
- and rely on a monomorphic type-checker with static typeclasses that are 
  like interpreted functions, and only provide boolean checks
  - should never infer traits of a TV as a result of being in a class
  - need only check this on demand from the user, i.e. upon instantiation
  - typeclass checks go after type checks, verify that consistent solution
    satisfies bounds.
- TLDR: 
  1. write an interpreted, dynamically typed programming language.
  2. use reflection to analyze symbols loaded after an initial phase.
  3. generate C-level code from remaining code or produce a compiler error.
     - the language is special because we guarantee C code can be generated
       unless insufficient information is specified.
- This is better because...
  1. much easier to implement an interp than a compiler
     - can use Python + LLVM MCJIT
     - dynamic typing lets users call templates easily, since types are dynamic and can be passed
     - running code with 100% coverage and recording evaluated types may be as good as performing type inference?
  2. user can modify compilation routines using same reflection handles
  3. can verify 'kind' errors dynamically as used
  4. guaranteed post-compilation step in monomorphic form ensures compatibility
     with C code.
- note dependencies must be 'linked' for each 'pass': for interpreter and the generated executable.

such behavior can be retrofitted on the existing compiler, with some changes to the typer.
in particular, templates must be monomorphized/copied out before the typer, and such that
no type's information can be determined from classes,
so that T :< U or T :< V can work.
**Note** it's easy to check that T satisfies an 'or' condition, but the inverse is
a nightmare because it creates two possible contexts that require simulation.
This philosophy is very similar to expanding and 'interpreting' class dynamically.
While crude, would work so, so easily, that this might be the go.

NOTE: ad-hoc typing using '<exp> as <type>' supported-- not a cast, but a type-check.
- revise: NO (read on)
- on second thoughts, keep existing type specifiers for 'lpattern'-- totally optional
- 'pub' specifier literally exports-- maybe separate 'typ <id> as <type>'
- perhaps this one case of overlap is ok? or is this reproducing C/C++'s header problem?
- better idea: forbid typing in 'let', but allow 'pub/pvt' typing
- what about 'val/var'? Forbid type specs altogether, just like fn-- intentionally 
  categorical, i.e. depends on types of functions...
  - if functions are defined for these types, logic should work
  - can augment with assertions later, but assertions must use functions to type

```
# all module symbols private by default.
# to 'publish', requires a type specifier (that may depend on symbols in the module)
# so each module composes its header and implements its data.

mod bitwise [ScalarType U_INT] {
    pub fibonacci as Fn (x Scalar) Scalar;
    pub vec3 as Fn (x Scalar, y Scalar, z Scalar) Vector3;
    
    let Scalar = ScalarType;
    
    let Vector2 = {
        x Scalar, y Scalar
    };
    let Vector3 = {
        x Scalar, y Scalar, z Scalar
    };
    
    let Vector = enum {
        v1 Scalar,
        v2 Vector2,
        v3 Vector3
    };

    let vec3 (x, y, z) = {
        x = x,
        y = y,
        z = z
    };

    let fibonacci (x) = {
        if (x == 0 or x == 1) {
            x
        } else {
            fibonacci(x - 1) + fibonacci(x - 2)
        }
    };
};

mod entry_point {
    pub main as Fn () Void;

    let main () = {
        val forty_two = create_42();
        0
    };
    
    # private functions need not be typed at all.
    let create_42 () = {
        42u 
    };
    
};

mod complexity {
    # private functions can optionally be typed with the 'pvt' specifier
    pvt create_1 as Fn () Term;
    pvt create_2 as Fn () Term;
    pvt create_3 as Fn () Term;
    pvt create_4 as Fn () Term;
    pvt create_5 as Fn () Term;
    pvt create_6 as Fn () Term;
    
    # IDEA: 'pub', 'pvt', and... 'extern'?
    # use this mechanism and a 'link' statement + a JSON file to...
    # 1. specify sources in JSON
    # 2. specify interface in code, just like for native code.
    extern "./sdl2.pd-extern-lib.json" {
        create_7 as Fn () Int32;
        create_8 as Fn () Int32;
    };
};

```

Idea: simplify the typer
- recently learned about quotient spaces in linear algebra: collapse multiple points to 0
- idea: types are quotient spaces / subsets of classes
- idea: only model classes in the language and otherwise:
  - so just vid and CId
  - some classes are singletons
  - you specify a class from which a value may be at narrowest
- how to pass types to templates?
  - arg type just subtypes the specified formal supertype without classes
  - so with classes, just pass a class (known by formal name) that subclasses the formal superclass
- maybe don't do this...