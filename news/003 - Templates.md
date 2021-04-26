# New Modules

*April 21*

Would be great to finally have templates, be able to turn our existing C-level language into a one-of-a-kind 
systems-level PL.

```
mod dict [Key hash:HASHABLE, Value ANY] {
    let Dict = {
        # todo: implement a hash table
    };
    
    let create () Dict = {
        # todo: initialize a `Dict` instance here.
    };
};
```

&lt;sarcasm&gt;
It's like D, but with fewer features. `D--`? Hopefully not.
&lt;/sarcasm&gt;

## [Rejected] Templates for Package Management

IDEA: pass a `[cfg Config]` arg to `entry_point` 
- `cfg.?` provides information about the target's capabilities.
- `Config` type may vary with versions, consider `CONFIG_V1`, `CONFIG_V2`, ...
- assume functions can be evaluated at compile-time using the `aot (<exp>)` expression.
    - initially emits the 'default' value
    - after compilation, evaluates the 'new' value and replaces the 'default' value with it.
    - evaluation order needs special consideration
    - needs more work, but similar to `#run` in JAI...
- then, we can implement 'conditional imports' by...
    1. allowing imports inside modules instead of just outside (so template args may be bound)
    2. allowing import paths/params to depend on variables
    3. allowing `aot` to determine an import path using a function
    - e.g. a function can map targets to a list of DLLs. import name from (aot dll_names())
      - assuming `dll_names` has bound access to `cfg` object since in the same module as `import`.

We can use this system to load all libraries as shared libraries as interpreted languages load 
- but this leads to worse optimization because whole-program-optimization will not know about dynamic
  dependencies that would otherwise be static
- simplicity in dependency management not worth the trade-off in safety-- 'module not found', now what?
- even if goal is to shift to shared libraries, can still be accomplished with a hybrid of shared/static.

CONCLUSION: This is an overcomplicated solution to a solved problem:
1. all PD code is implicitly platform-independent
2. all external dependencies have different rules in JSON.

## How Templates Work

Naive implementation:
- gather each AST instantiation (TCall)
- perform typing, solve the system (typer supports polymorphic relations)
- perform template instantiation, such that
    1. only values are expanded: ignore types, typeclasses.
    2. constants are recursively evaluated for value terms
       - error if ID is a var, unbound function input
       - must recursively expand 'val' 
       - must support ModAddress lookups
       - must support function calls
         - bound function input may be constant transitively,
         - but this is context-dependent
         - else error: cannot pass non-constant to a function in a constant context
         - can track bound/unbound on an evaluation stack
       - must support chains
       - this snowballs into full constexpr territory and gets gnarly. stub at a point for now.
       - IDEA: can call any function aot using `!` suffix.
         ```
            val hello = scsvdb["./test.csv"]:cell:query!("hello");
            val greetings = scsvdb["./test.csv"]:column[column_id!("Greetings")]:query!();
         ```
    3. group instantiations based on values: so soln type for type args, soln value for value args.
    4. each group of instantiations gets one monomorphic instantiation
        - bound in a module called `$templates`, so non-user-accessible
        - name mangled too
        - but point is we give it a place to export from
    
This is a great idea! Allow any function to be evaluated at run-time with '!' suffix once this is in place.
- can explicitly check that all inputs are constant
- can guarantee that inside function calls, all inputs are aot-computable
- solves 'macro' problem

IDEA: factor AoT into its own interpreter with support for polymorphism
- insert static-interp after typing.
- assemble a list of all AST nodes that require const evaluation
- 'load' all modules into an empty interpreter. then, a naive algorithm would foreach:
    - instantiate the context where the const-exp was called
      - i.e. define all symbols on a stack, be they constant or HOLES (errors waiting to be detected)
      - may depend on bound values
    - evaluate the exp, pushing function frames and all
    - destroy the context
- problems:
  - create and destroy interpreter for each little value
  - unnecessarily re-compute values without reusing, esp. in same context
  - why assume set of expressions is static? instead, compute with BFS
- BFS-based algorithm:
  - create a set of all const-expressions to evaluate.
  - associate each const-expression with an AotExp node.
  - evaluate each AotExp node, such that...
    - if a literal, trivially known
    - if an ID, equal to ID's AotExp node + immediately resolve ID's AotExp node
    - if a static fn call, immediately resolve each arg before resolving fn
  - cache/reuse constant values outside functions-- only use stack frames for static fn calls.
- just store types as values when evaluating TCalls
  - post-typer, can guarantee all substitutions are valid, 
  - but which type to use when `x T` and `T` is a template arg?
  - need to push and pop a frame! but...
  - this means a template is a static fn call that can also accept type values.
- if context becomes an issue, study continuations, and consider a graph of interrupted nodes
    
How do we represent template expansion?
- types must be valid, so all substitutions are good
- want to verify assertions using Z3 next, so an IR would be nice

## CONCLUSION: after the typer

1. Implement an AoT evaluator
   - look up values for ModAddress:vid, only push frames for TCall or static
2. Implement a template expander
3. Implement an Monomorphic IR (MIR) that we can forward to the LLVM emitter.
   - a new 'AST' that contains all information from prior modules + instrumentation & other properties
   - strictly monomorphic, so all template calls have been expanded to a new synthetic node (not parseable).
   - contains properties for const-evaluation
   - contains extra arguments for Z3, like
      - stack pointer/recursion counter/backtrace: used to check against stack overflows
      - must be marked 'aot-only' so the emitter ignores them
4. Implement Z3-based checking on MIR to verify...
    1. no assertions are always false
    2. no recursion above a finite limit occurs (can be 4x a sensible limit)
    3. no loops always infinite
5. Modify the LLVM emitter to emit based on MIR.

New feature: `function!` to call at compile-time.