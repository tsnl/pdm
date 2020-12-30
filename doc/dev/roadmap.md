# Roadmap

## Dec 29 - WIP (2)

Turns out, templating out is harder than expected.
- Old templater solution (mentioned below) seems inelegant, relies on old TVs which weren't designed to handle templates/kinding.

(_old_) Here's how we can typecheck types without substitution and copying, using only monomorphic TVs and CHA `O:)`:
- for each formal template-arg,
  - if a type arg, 
    - create a PROXY var to represent any type that could be passed.
    - treat PROXY like a regular monomorphic var, accumulating constraints in definition.
    - FIRST check PROXY vs. typeclass-spec in typer!<br/>
      is PROXY a SUBCLASS of the formal typespec? check by **COMPARING \[TYPE\] CONSTRAINTS**
    - SECOND during template instantiation, check actual arg vs. typeclass-spec
      - true/false: type in class or not.
  - otherwise if a value arg,
    - treat value arg exactly like a VCall in-parameter; solved problem.

(_old_) But we can do even better! The following approach **does not need Constraint comparison**, and instead maintains
a most general proxy argument that can then be subtype-compared.
- create a PROXY_ACTUAL_ARG var; treat like a regular monomorphic var, accumulating constraints in function definition.
- **USE** PROXY as SUPERTYPE of all ACTUAL CALLS **BUT DO NOT REQUIRE PROXY TO SOLVE**
  - since PROXY is fixed, it's referentially transparent in this context; imagine duplicating and applying to each subtyping.
  - do not allow any more constraints to be added to proxy during this point, need some kind of `freeze/one-way` mechanism that just
    ignores new constraints [from subtypes] without error after initial constraint set is constructed.
  - if a T :< PROXY, then T may substitute PROXY
    - suppose T depends on PROXY2; since it is also frozen at this point, all OK!
- sit back and let super/subtype solver handle the rest. :)

> Apply this 'proxy-actual-arg' to value arguments.
> 'running' the program symbolically accumulates 'value-constraints'; e.g. <5, >4, etc
> The proxy value is not a unique solution (can refer to many values) and is hence really a type
> But we can still compare the proxy against other numbers using the MOST GENERAL SUBSTITUTION
> So 4 < x < 5, y = 3, y < x = true always since y < 4.
> This is the same thing we're doing here, such that **PROXY is just the MOST GENERAL ACTUAL ARGUMENT**.

> 'freeze' + no-checking is required to handle **disjoint typeclasses.**
> Consider typeclass `Number`, containing `Int__`, `UInt__` and `Float__`.
> Without these two features, the proxy will get 'Kind'-solved as Int or Float, and will produce errors
> for legal substitutions.
> However, 'freeze' lets us reuse this constant 'Var'--
> **Maybe 'freeze' should return an 'PartialSoln' that cannot be solved but can be compared against.**

Now, we can do even better! We can implement the `A subclass B` transparently using the above method.
To typecheck template type arguments, we...
1. compute a set of constraints
2. stick them in a Var with 'Partial' SolnKind, creating the submost supertype of all valid type args
3. check if the actual type argument 'solves'/'substitutes' the formal type argument.


Thus, we can **typecheck templates without expanding them.**
Furthermore, we can port most of the existing C code without much modification.
Much, much less work. Hooray!

**Note** `Constraint`s only apply to types-- not typeclasses, not values.
- Kind-separated constraints: exploit dynamic_cast<InvalidBase*>(v) == nullptr to weed out inapplicable constraints.
- So constraints are...
  - Void:
    - IsVoidConstraint
  - Int, Float
    - IsNumberConstraint
    - IsIntConstraint
    - IsFloatConstraint
    - IsIntWithMinBitWidthConstraint
    - IsIntWithMaxBitWidthConstraint
  - Tuple
    - IsTupleConstraint
    - HasFieldConstraint
  - Array (hard-coded for `.(abc)` access to work)
    - IsArrayConstraint
    - HasSignature          (accepts Var T)
    - HasLength             (accepts Var value)
  - Struct
    - IsStructConstraint
    - HasFieldConstraint    (accepts Var)
  - Enum
    - IsEnumConstraint
    - HasVariantConstraint  (accepts Var)
  - Function
    - IsFunctionConstraint
    - IsCalledConstraint    (accepts Var for args, return type)

## Dec 29 - WIP
I'm too hungry to go on.

Here's what's in-progress-
1. typer.new_polymorphic_var_tv needs formal arg specs
2. finish creating var_tvs in 'scoper'

read `Roadmap Alf` (Dec 29) below for subsequent steps.

## Dec 29 - Latest Roadmap: Codename Alf

1. Scoper polished, documented, and ready to be implemented
   - just store 'Context' lookup for each ID
2. Then, implement 'typer'
   1. flesh out required typer features...
      1. implement 'typer' visitor to create Rules
         - includes looking up stored 'Context' from scoper
         - includes applying rules to stored TVs on ASTNs (see (2))
         - includes determining all template-calls (tcalls)
            - `TCall{Exp|Typespec}` and `VCallExp` may invoke template substitutions
            - i.e., VCallRule with LHS template => 
              1. generate monomorphic metavars to use for substitutions (monomorphic could include singleton i.e. value)
              2. store each generated metavar pack on VCall, so `templater` (see below) can refer
         - note value TVs may or may not map to an ASTN, but are determined like metavars.
      2. implement 'TV' initializers for ASTNs
         - _decided to do this in-scoper_
      3. implement 'typer::dump' to verify
   2. complete `typecheck_all`
      1. implement TV fixed-point solver
      2. amend 'typer::dump' to print solns to verify
3. Then, implement `conster`
   - check each 'const' expression and evaluate
   - since typechecked already, pretty much just type-safe interpretation, e.g.
     - `cif` statements: cond must be constant
       - dead-code elimination **must** be performed AoT for `cif`
       - so `selected_branch` assigned here
     - `extern` statements: extern arg must be constant
     - `const` statements: rhs must be constant
     - builtin `const`-operators: 
       - since functions are pure, can call functions for RHS (compile-time evaluation)
       - note that functions are just `const`-mapped to `lambdas`
   - Thus, `conster` evaluates all constants.
4. Then, implement `templater`
   - use unique values and already constant types to generate finite template substitutions.
   - `TCall{Exp|Typespec}` and `VCallExp` may invoke template substitutions, so for each...
     - use 'TV' solutions to generate template monomorphs from a cache
   - finally, 

## Dec 28 (Part II)

See `eg/eg10.pd`

How does the heap interact with inout/out params?
- 'Ptr' is the only pointer type, is just an integer address.
- `ptr(out value)' gets the pointer to a value.
- `malloc` returns a `Ptr` instance
- `var x from ptr` to create variable from pointer!
  - compare with `fn ... from`

TODO: introduce `var <lpattern> from <ptr_exp>` to load a variable from a pointer.
- raw pointers can unwrap to anything
- eventually provide allocators with static type info so that `ptr_exp` contains static
  info about buffer size.
  - remember: your whole program is finite, and we have access to all source for templatization
TODO (from part I): `cif ... then ... else`

## Dec 28 (Part I)

I made the following changes last night:
- 'let' -> 'val'
- no more pointers, instead 'out' and 'inout' parameters + indices into data structures
  - functional-style pass-by-value
- no classes, just modules-- not even operator overloads.
  - every library is a DSL of some sort.
- build multiple 'output files' that may depend on each other.
  - initially, we just emit WASM and/or LLVM IR + file dependencies.
  - we can then implement integrations for different build systems
    like Bazel, CMake, or Webpack to...
    1. build WASM/IR
    2. link multiple applications respecting dependency order

This produces the following exceptional platform-independent result:
  - This way, we actually build 2 targets for every source file: WASM and LLVM IR.
  - Then, we 'link' WASM to LLVM IR by trusting stdlib to load WASM from the same location.
  - **Thus, LLVM always runs first (for the server), with the option to replicate namespace env**
    **on a browser using WASM version.**
  - Simple to implement initially too!

TODO: introduce 'cif' expressions

Rough notes:
```
Key insight: only write servers, specify JS via DSLs
Best known way: actor model
Given Rust’s ‘dyn’ issue, abstract + class might be the way to go.
Thus, implement...
1. Classes (cf Kotlin with mandatory prefix C++-style visibility specifier labels); notably has primary constructor, multiple abstract inheritance
2. Change ‘let’ to ‘val’
3. CIF: constant if, in honour of kif kroker from futurama 
```

```
With classes, can implement DSL that corresponds to JS; with the right base classes, we can call methods during compile-time (after everything else is built) to build shaders, JS, etc.
Furthermore, this way, native platforms are first class.

Henceforth, assume built in pointer operations are removed. ‘set’ only writes to IDs defined with ‘var’ or var parameters passed with ‘out’ or ‘inout’ prefix (cf .NET)

If we treat class instances as the only and default reference type (for dynamic dispatch),
0. Can pass subclass instance to superclass
1. Can provide cycle-counting GC (bdwgc) (no weak references)
2. Strong value types + functional style + templates should promote fat objects

The goal is to use class instances as whole processes, not lightweight instances.
* but then what about DSLs and operator overloading?
* advantage of Rust ‘impl’: can add features without VT

Without classes, everything is a value type. Use *containers* to wrap all memory management and *typeclasses* to validate interfaces statically rather than dynamically.
Instead of pointers, only ‘in, out, inout’ parameters supported in language. Since a struct can’t store a reference to another datum, must instead store **index** in container/allocator.
Thus, functionality is tied to allocation, promoting modular C-like programming over actor model.

How can we use this model to provide DSL-like functionality?
- just write a module
- to generate JS

The answer always seems to be “just write a module to do X”, which is great, because it’s simple.

So we’re all set for mega features, just need containers (templates) implemented.
```

## Dec 27

We've overshot the Christmas deadline, but work continues regardless.
The key is to push 'linking' away for now, since it is complicated, and hence intimidating.
However, we know how to generate LLVM IR and/or WASM, so I'll **punt on sound dependencies for now**

Thus, **imports are resolved before all else, then 'extern' is const-evaled**

Here's a modified example from eg8:
```
match (__platform) {
    PLATFORM.Llvm -> {
        extern csdl from {
            lang: "c",
            headers: [
                "./include/SDL.h"
            ],
            header_dirs: [
                "./include/"
            ],
            sources: [],
            static_libs: [
                "./dep/lib/SDL2/SDL2_main.lib",
                "./dep/lib/SDL2/SDL2.lib"
            ],
            copied_dynamic_libs: [
                "./dep/bin/SDL2.dll"
            ],
            shared_dynamic_libs: [
                if __operating_system == OS.Win32 then {
                    "OpenGL32.dll"
                } else if __operating_system == OS.Linux then {
                    "OpenGL.so"
                } else {
                    "OpenGL"
                }
            ],
        };
    }
    PLATFORM.Wasm -> {
        extern csdl from {
            lang: "js",
            # ...
        }
    }
}
```

# language-based bindings can then be provided by linking against this external module.
# note that templates can be used, and that multiple symbols can link against the same definition using
# type translation (T const* -> T, T const -> T, etc...)
mod sdl {
    fn init(flags I32) -> I32
    from csdl "SDL_Init";

    type Event from csdl "SDL_Event";
};
```

... in retrospect, maybe just **'linker'**

This simplifies...
- C dependency management: 

  just import a C/C++ header, and we'll read declarations, leave linking for later.


- Output restricted to LLVM and WASM, and just one output module per compilation,
  so whole program optimization performed in PDM-land, and dynamic libs must be 
  **checked against.**
  - add **top-level** `if const (...) then (...) else (...)` to support conditional
    imports.
  - add **PLATFORM** flag to allow selective 'extern' statements
  - 'extern' to JS as well as C, so WASM and LLVM parity is achieved.

This enables the following factorization:
- **libpdm**: core library
- **compiler**:
  1. accepts an entry point `pdm` file
  2. emits ONE .ll file and/or ONE .wasm file-- compiler output
- (pdm.bartender):
  1. accepts input (+ reads `pdm_order_history.json`) to config and link C, C++ 
     libraries, or more generally configure builds, interactively.
     - constantly test configs to check for errors
  2. invokes `pdmc` to produce LLVM IR or WASM output
  3. invokes 3rd party applications like `clang` and `emcc` to produce finished executable.

This enables the following philosophical changes:
- Haxe profits greatly from being a source-to-source language, and it's great at what it does.
- Rather than build on underlying platforms, instead allow such source-compilation to modern-native
  formats: LLVM and WASM.
- Crucially, punting interop with other ecosystems until linking lets us **use 'headers' for typing**
  and _then_ worry about linking.
  
Note this produces the following pattern in directory structures:
- for web, keep native JS code in-tree; for desktop, keep native C code in-tree. 

  One-tree, multi-platform.
  
  parallel implementations in different languages or differentiated modules: all ok!
- bartender is a better tool to specify linking per-platform:


## Dec 23

While porting the grammar, I've made the following revisions. This allows 
the grammar to parse without ambiguity.

Syntax are the tools to access our analysis. Syntax determines how 
powerful the language is.

**NOTE (dec 23)**

**Part 1: how do we interface with C without adopting its type semantics?**
- extern/link statements breaks indentation correlating with namespacing.
- C linking breaks module namespacing, makes it difficult to nest symbols.
- if we use `extern <emodname> <etype>` statement and `link` statement as 
  below, support for guaranteed const 'if' elision will allow custom 'link'
  args per-platform.
      ```
      extern sdl "C" {
          link {
              include: {
                  "SDL2/SDL.h"
              },
              source: {},
              static_libs: {},
              dynamic_libs: {}
          };

          type Event from "SDL_Event";

          fn init (flags U32) -> U32 from "SDL_Init";
      }
      ```
- **IMPORTANT: prefices when emitting**
  each C library can be built to LLVM IR using Clang.
  If we add the emit all PDM with a `_P` prefix, then no linker conflicts
  will occur unless linked C libraries are in conflict (since native PDM symbols
  are additionally prefixed by their full module ancestry).
  See Wikipedia on [Name Mangling](https://en.wikipedia.org/wiki/Name_mangling#Simple_example)
  **Thus, PDM exists in a subset of the global C namespace and are linker-safe.**
- Furthermore, aliased links
- **this need not be supported just yet**, and need not be for some time. However, this allows
  us to perform another, more consequential change.

**Part 2: breaking free**
- **now treat ptr as mut**, makes a lot of sense!
- use `&` as typespec operator, `^` and `*` as value operators => no parser conflicts.
- always pass by value for immut, **enable link** `T` pbv with `T const*` in C ABI (see above).
  - so `f(char const*)` links with `a[n](Array[Char,n])`-- **type-safe re-interpretation of C**
  - so `f(char const*)` also links with `b(Char)`
  - **and 'a,b' now present a factored, type-safe interface written by a human without any**
    **manual definitions!**
- replace `let &x = 42` with `var x = 13` statement
  - `let` stores as rvalue ref; i.e., **cannot take ptr to 'let' IDs** (HENCE will not mutate)
  - `var` stores as lvalue ref; i.e., **can take ptr to 'var' IDs**
  - for the performance-minded,
    - `var` explicitly&always pushes&stores a copy of rhs to the stack.
    - `let` _may_ be pushed (depending on register allocation), but since it has the _opportunity_ 
      to be promoted to register operations, much faster.
    - obviously fat 'let' statements must be stored by pointer, but this depends on pointer width
      and is an implementation detail. e.g. `let x Array[I64,_] = [1,2,3,4,5,6,7,8,9,10]`.
      What matters is that in either case, we offer options for optimization 'var' would not 
      without worrying about immutability.
  - don't need to explain difference between const and immutable to users-- less mental baggage.
  - since `set` lhs accepts a pointer, `var` is its natural counterpart, connoting mutability.
  - 'var' is fundamentally different since it guarantees memory allocation.
    'let' separate from 'var/set' allows the user to do work before storing independent of 
    syntax constraints.
- **suppose you want to pass an immutable ref/ptr rather than a value to an object.**
  - the _C ABI_ (not even the compiler) does it anyway...
  - you introduce aliasing issues which makes optimization worse
  - instead, pass by value and return, or use a mutable reference-- i.e., the standard proposed
    pointers.
  - **FP + pointers makes perfect sense from the CPU's perspective: memory beyond its**
    **state wall, must be accessed by load/store**
- changes made:
  - delete 'mut' monad typespec
  - delete '&x' lpattern variant
  - create 'var' statement
    - create shared base class with 'var', 'let', 'const': 'BindStmt'

**Part 3:** Revised typeclasses
- remove function typeclass fields.
- defer type refinement for the future as an orthogonal feature. we're spoiled for choice in 
  runtime typing options (classical oop (Java), trait/impl, typestates, refinements), so punt.


## Dec 21 (and earlier, mostly stable)

**WIP (dec 21):** Parser WIP
- todo: finish adding compiler hooks so `import(i_path, i_type)` works as in Python, hitting a cache.
- wip: porting old C lexer to C++ (mostly done)
- wip: porting old Bison grammar
  - most old rules updated with C++ types
  - todo: (cleanup) can delete `pdm::parser::` and `pdm::` prefices (added prefix namespace)
  - todo: implement rule handlers (follow 'type clash' warnings from bison grammar on 'bison-build.sh' in `src/pdm/parser`)
  - todo: regularize grammar names to match C++ scheme (much less confusing)
  - todo: add 'const' statements to the grammar
  - todo: add 'type-query' expressions to the grammar
  - todo: add mod-prefix dot typespecs to the grammar
  - todo: add struct-typespecs to the grammar (wip)
  - todo: add ... (probably more I'm missing, ensure 1-1 with C++ ast)
  
- once this is done, will turn attention to scoper, other analysis passes.

**TODO (dec 10)**

- **done:** 'define', 'shadow', 'link': three scoper tools
  - 'link' associates any frame with a context
    - **todo:** check for cycles?
  - 'define': adds to context, 'shadow': pushes new context

- **todo:** parser
  - impl 'reader': port 'source' from c version to C++ (with unicode, without feedback, loc)
  - port 'lexer' to read from 'reader'
  - port 'parser' to read from 'lexer' and construct AST

- **todo:** default-initialize TVs in AST constructor itself.
  - each node has one or more tv attributes.
  - e.g.: each exp has a 'valtype_tv' tv
  - e.g.: each typespec has a 'spectype_tv' tv
  - this allows constraints to be applied on TVs

- **todo:** add pre-scoper pass: 'dependency_dispatcher'
  - accepts string literal args of 'import'{'from','type'}
  - construct dependency graph
  - instantiate ast::Script, push to 'Compiler' where analysis can begin.
- **todo:** implement 'scoper'
  - pass 1: uses ASTN TVs to initialize 'Defns'
    - can add a filter predicate to only lookup symbols with prefix, matching pattern, etc.
  - pass 2: 
    - set 'link' for 'using' or 'import' (requires lookup)
    - create '{V|T}IdLookupRule'...s to bind ID TVs to lookup Defn TVs

- can then use 'typer' to set up constraints, 'solve' to finalize.
- **plan:** include 'templater' in 'typer'?
- **plan:** diff passes for typer

- **done:** create 'Compiler' with following interface:
  - *completed dec 21*
  - call 'import(path:str, type:str)' on entry point path
    - LAZY: if already loaded, return cached.
    - ELSE:
      - create new script
      - run reader + lexer + parser, module_dispatcher, and type_initializer.
        - halt if any fail
        - note that 'module' symbols are resolved by scoper.
      - cache new script
      - importer returns list of other modules to 'load'. call 'load'.
  - call 'typecheck()' to run the typer.
- **plan:**
  - LATER...
    call 'emit_llvm_executable("hello.out")'
    to emit a file using the LLVM backend whose type depends on the extension.
    cf 'emit(Platform::Wasm, "hello.wasm")'
  - LATER...
    call 'execute(ast_script, "test.main")' to immediately execute some loaded   
    code.

**TODO (dec 10)**
- **done:** allow 'Context' to 'define' multiple symbols and 'define_shadowed' when reqd.
- need to update scoper for position-independent 'def',
- for 'ScriptContent' and 'ModuleContent', store symbols in SHARED CONTEXT LL.
  - SharedContexts allow the user to define multiple symbols that are all accessible.
  - lookup in SharedContext is position independent
  - multiple symbols in lpatterns handled and checked for uniq
  - multiple symbols in 'mod' or 'script' content handled and checked for uniq
  - 'define_shadowed' pushes & returns FRESH context, but should only be used for 'chain'
    - use 'Frame' to push 'shadow' chain and then restore to share
    - so a scoper dump mirrors source code in order, similar nesting

**DONE (dec 9)**
- implemented 'feedback' module; truly ready for primer/parser!

**TODO (dec 7)**
- added utf8 string support, see pdm/core/utf8 or pdm/ast/expr/string
* **todo**: implement new `pdm::feedback` module!
  - source-independent
  - just tracks and organizes compiler messages in order received
- to work on parser, lexer must be ported to C++
  - utf8 string builder support can be shimmed out to C
  - but 'source' and 'feedback' have changed
  - doesn't mean most of C code can be preserved (incl. TK_); conservative port
- work on `scoper` may proceed...
  * implemented much of scaffolding
  * **todo**: implement scoper visitor methods
  * **todo**: implement `Defn` subtypes for `using` and `import` statements.
    - requires well-specified `Compiler` interface to request a module.
    - consider providing a metavar and deferring module loading?
- **done** (as of dec 21)

**UPDATED:**
- added 'link', 'import'
- visitor working

**TODO (dec 6)**
- can either work on scoper (old primer) or parser in cpp version next.
- for parser, write wrapper around existing C lexer but write new YACC callbacks.
  - require backward-compatible C bindings for 'Source'
- for scoper (nee primer), subclass and implement 'Visitor', porting logic from C version
  - dedicated 'Symbol' classes! At last!
  - a much more feature-rich symbol table/graph is required
  - tbd after surveying C version
  * module fields (esp types) MUST be resolved at scoping time 
    - so treat the scoper like the typer! detailed traces, even if we don't need them, just
      to keep us honest :)
    - each 'context' is exactly a frontier of all defined/queriable symbols
      - implementation as an **LL-slice** in a graph aside

**New Exprs, Typespecs in C++ Version**
- **todo:** add 'typecheck' exprs (T :: U, T :< U, T >: U where T,U typespecs) (dec 6)
  - done (dec 7)
- **todo:** add support for the following builtins (dec 6):
  - `Fn<A,R>`: the function type (replaced with FuncType dec 7)
  - 'bitcast<T>(v)`: the cast function
  - `I__, U__, F__`
- **todo:** implement 'const' statements
  - done (dec 7)
- **todo:** implement 'typeclass' statements
  - done (dec 7), tentatively

**Warmup: add '&'**
- added unaryTypespec in yacc with '&' prefix
  - todo: add NewAstTMut, mut type
  - todo: lex '&' symbol

**Next:**

- primer: factor into 4 passes
  - pass 1: exclusively for validating arguments
    - 'import' statements 'as' and 'from' strings must be checked
  - pass 2: import dispatch + prime (add to a queue, all resolved before typing/checking/linking)
  - pass 3: earlydef modules and module items
  - pass 4: scoper (currently in primer)
    - note: we don't need a separate pass for 'const'!
      - usually only depends on AST node
      - if ID, const iff refs value template param
      - determination made by AST, so determining VID const = setting defn
  - separate earlydef into its own pass, then push new frames for each module-stmt body (cf emitter), so all functions can access all modules, even imported ones.
  - remove LookupSymbolInFrame, _SetContentFrame based lookup, and use the AST to lookup by name.

- typer
  - implement sub&copy in typer for ad-hoc monomorph templating w/o AST node copy
  - requireSubtyping is too general: write specialized constraint functions and replace calls

see [fixes/wip](##fixes-wip) for bugs and refinement.

see [##modules](modules) for **current sprint.**


## FIXES/WIP

commit 447814a7ddc699e72772fd5ad789e70ef78f31fe

TODO:

- string literals
  * link against 'puts'; maintain C-compatibility through pointers?
  - req length stored AoT
  - see pointers
  - static string literals are CStr (constant/c string), both null-term
    and length-aware
- pointers require a lot of work...
  - fix dereferences; bugs remain
  - see set-statements
- ITEs must be restored
- set statements must be implemented
- struct statements must be implemented
- enum statements must be implemented
- modules and imports
  - allow user to specify (by path) C library files to use for linking
  - rather than source-level interop, compile C to LLVM with Clang,
    then link at LLVM (so we can output JS or binary)
- output executable and/or js/wasm/wasi

NOTE:

- need a plan to implement templates long-term

## TEMPLATES 

commit adbf846c924775010920a7946b44543d61bfd7fa
Author: Nikhil Tony Idiculla <nikhilidiculla@gmail.com>
Date:   Mon Nov 9 00:06:52 2020 -0800

Templates within reach

- implementing post-primer-based check for whether or not an expr is
  const evaluable (for expr targs)

- to resolve templates, insert 'templater' pass after primer before
  typer.
  in AST,
    - add support for
      - AstLazilySubAndCopy, AstSubbedVID, AstSubbedTID
      * AstXTemplate in def, type, struct, enum stmts
    - AstLazilySubAndCopy replaces a def body's AstTIDs and AstVIDs with
      AstSubbedTID and AstSubbedVID resp.
      - implement AstXTemplate manager for defs to share <3
    * AstXTemplate generates monomorphs for concrete types.
      It tracks...
        - all its xcalls (vtcall or ttcall) (registered in templater)
        - table of actualarg equality-classes -> monomorph def
          (for vtemplate) or type (for ttemplate)
          - note: monomorphs are children in AstVisit
        - when xcall has concrete soln in typer (spoilers), it
          messages AstXTemplate via defNode for...
          1. a monomorph ID (monomorphs of fibonacci[T] are fibonacci.1,
              fibonacci.2, ...)
          2. a type solution in return
              - the value CAN be a lambda
              - but also a value e.g. size[T]
              * solution provided by monomorph to xcall's TypingExt
        - when this happens, LazilySubAndCopy...
            1. looks up table; if args encountered already, use cached
                monomorph type and monomorphID
            2. if table miss,
                1. SubAndCopy creates a new **definition** for a monomorph
                    s.t. monomorph is def's AST child
                2. typer SubAndCopy to generate new types with template subs
                3. type monomorph
                    but do not typecheck
                4. monomorphID := add result to table for future lookups
            3. (extra typing) add monomorph type as soln to metavar
            4. return monomorphID
        * LazilySubAndCopy (
            xtemplate,
            xcall,
            actualTemplateArgs: a list of template args,
          ) -> monomorphID

  in templater*,
    for each vtcall,ttcall,
      1. check expr targs are const-evaluable (**only after primer)
      2. store call on defined template, vice-versa

  in typer,
    1. on ttcall,vtcall, defer until args' types solved.
        - vcall* -> targs can be omitted <=> args' types solvable
          use metavars for ttargs and vtargs*,
          match metavars from actual args
        - this would require...
            - a matchCall func to relate targs to vexpr_cl
            - metavars solvable as constant values (Val2Type solns)
    2. once targs are typechecked,
        - const-eval expr args
        - get monomorph ID from template stored by templater
          using now-unique actual args
          * see above first!
          - AstXTemplate primes and types a monomorph s.t. the call is
            typed.
        - store monomorph ID for emitter

  in emitter,
    - for each def,
        - remember to emit all monomorphs, headers too
        - since AST_VLAMBDAs are included children, should work
    - for each xcall,
        - use stored monomorph ID and AstXTemplate to look up monomorph
        - export monomorph value or type in .llvm field


## POINTERS & SLICES

* slices augment pointers and permit 'lea' access.
    !- no pointer arithmetic, just integer arithmetic + 1 lea
* slice bounds is always private <=> release elidable
- add slice type, notated `T[]` (cf `T^`) (cf `T[targ...]`, note that no valid targ seq is empty, even variadic)
- add lea `@` binary operator, s.t. 
  
  `<int> '@' <slice[t]|slice[t]^|array[t]> = (slice.ptr + int) :: <t^>`
  
  - lea + store replaces (a[i] = x)
  - note that array supports '@', not '.1', '.2' syntax
- ensure LEFT-associative, s.t. 
  
    `i @ a @ b = (i @ a) @ b`
  
  => easy double-layer, triple-layer indirection

  ```
  mod slotmap {
      struct SlotMap_TI [T,I] {
          tab_id_ix I[],
          tab_ix_t  T[]
      };
      def ptr [T,I] (sm SlotMap[T,I]) = T^ {
          id @ sm.tab_id_ix @ sm.tab_ix_t
      };
      def get [T,I] (sm SlotMap[T,I]) = T {
          *ptr(sm)
      };
      # ...
  }
  ```
  
  => discourage/flag jagged access, i @ (j @ array_list)

- add a 'u' suffix for unsigned integers.
  
* end result very similar to Go! Array[T,n] copied in block but accessed 
  with array[...] operator's analogue

- use `->` for 'def' statements to line up 'def' with lambdas, connote fn
  definition.
- use binary `->` operator for function typing
  - lpattern and typespec are mutually exclusive, so no conflict between 
    lambda and typespec, though
  - prefixless lambdas may pose other issues, even if primaryExpr


## MODULES

`!!-` pending update to grammar now

* nestable static modules bring the big usability leap over C

* make `:` the unique namespace accessor (like `.`, but static), for enums as well
* change vpatternFields to be Go-style, vstructFields to use `=` (orthogonal with let and set)
- rename `module` statement to `attach`
- implement `mod` statements s.t. each file contains multiple modules.
- implement `:` postfix operation to lookup module fields and enum variants.
- change fields


## LOOPS: long-term, pending working closures

* lambdas map lpattern to body
    ```
    i -> i+1;
    (i,j,k) -> i+j+k;
    ```
* the 'linear-iterator' generates values in [a,b] incrementing by 1 if a <= b, else -1
    ```
    (iter a .. b)
    ```
  an optional 'step' argument can be provided too
    ```
    (iter a .. b step 2)
    ```
  floating point values can also be used
    ```
    (iter a .. b step 2.0)
    ```
* the more complex 'for-iterator' is a shorthand similar to 'for' statements
    ```
    (iter ID = <init-val>; <continue-condition>; <update-rhs>)
    (iter i = 0; i < n; i+1)
    ```
  - ID denotes a value to return upon each iteration.
  - the first statement provides value for first iteration
  - the second expr provides cond for continue
  - the third expr provides rhs expr in terms of previous iter's values
      ```
      for (i = 0; i < n; i = i+1) 
      ```
* for statements can combine iterators & lambdas
    ```
    for parenExpr:Iterator[T] on_iteration:primaryExpr
    for (0 .. 10) i -> { For.continue };
    ```
* for expressions must return either 'For.break' or 'For.continue';
    ```
    For[T]:break(v:T) => returns Opt[T]:some(v)
    otherwise         => returns Opt[T]:none

    def count_primes_until (n S32) = S32 {
        let primes_count = 1;

        for (iter i = 3; i <= n; i+2) i -> {
            let factor = for (iter j = 3; j*j <= n; j+2) j -> {
                if i % j == 0 then {
                    For:break (j)
                } else {
                    For:continue
                }
            };
            match (factor) with {
                Opt:none -> {
                    set &primes_count = primes_count + 1;
                },
                ________ -> {
                    # do nothing
                }
            };
        };

        primes_count
    };
    ```
* generic sequence batching can be an enormously powerful tool.
  - use a for-iterator to iterate over multiple batches, possibly in linked-list form
  - write a function called 'batch[T,n]' that batches Iterator[T] in groups of Array[T,n]
    * can be used to statically batch piecewise routines in 8,16,32,or N groups
    * can be used with const-evaluable platform/heuristic-parameters to dynamically/late 
      tune performance?
  - consider this with an interleaved coroutine implementation?

* match statements & enums (see above)
  - only work with 'enum' args
  - each branch matches an enum tag (with opt pattern)
  - enum opts can only be accessed explicitly with the `:` operator (though actual targs
    may be elided)
  - `Opt[T]` ought be provided as a builtin like `Array[T,n]` and `Tuple[T...]` for 
    usefulness and extensive optimization.
    
    e.g. `Opt[T^]` does not require an additional tag, use `NULL` ptr to verify.
    
    By specifying builtin, allows confident cast to `Opt[T^]` in wrappers.
    
    No downsides?
