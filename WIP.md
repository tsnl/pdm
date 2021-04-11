This rabbit hole is deep and painful.

Disable function calls, unary, and binary calls until casting/conversion is sorted out.
Immense technical debt must be pair before progress can be made.

1.  We need to cast input arguments to an appropriate type in the emitter.
    -   we would like the typer to detect type casts
    -   and insert 'cast' requests at the conversion site
    -   only required at operator calls, e.g. Unary, Binary, VCallExp, TCallExp.
    -   **how do we cast for extern functions?**
    
2.  The type of an extern function is ambiguous, or at least cannot be specified by
    the user in a straightforward way.
    -   updated packages spec
    -   sweeping changes will require rewriting 'SourceNode' classes _again_.
    -   need to parse individual `type_spec`s in PD...
        - suggestion: add the ability to parse a statement too to support an interpreter/debugger

3.  Non-trivial conversion of structures, need `==` defined
    -   starting to look a lot like templates

4.  Since working on the type solver anyway, should factor into 2 parts:
    -   `t`: corresponding to `types/type.hh`
        - a subset of `meta-t` that is used by emitters after template substitution
        - think of algebraic data types and no more, i.e.
          - prime types: Void, Int, Float
          - connectives: 'tuple-,' 'struct-,' , '*' , '+', 
    -   `meta-t`: corresponding to `types/var.hh`
        - introduces 'variables', predicates aka 'classes'
    

## Task 1: Finish exporting HeaderDigest in emitter

see `llvm-emitter`, specifically emitter for Binary Exp

goals: without any casting/conversion in place yet,
- should be able to call cast-less binary exps.
- should be able to call cast-less functions.

## Task 2: Refactor typer to understand casting

- consider emitter bug, where type is promoted for no apparent reason
- generate 'cast' info in the typer,
    - after running the existing typer as a post-pass if required
    
- do not refactor the typer yet.

## Task 3: Implement typing for extern modules

- must promote external json files to first-class modules,
  with ast and visitors
  
- must write parsing, typing pass for extern module as well as script, such that
    - types are read (parsed) from string values in JSON document
    - external dependencies are parsed with LLVM from file paths

- must link symbols, ensure existence, etc etc

- must update 'import' so we can import a json file like a script.

## Task 4: Implement templates (at least for the backend)

- can be modelled off of how we emit builtins (though systems need not intersect)
- goal is to totally specify all requirements of the type solver

## Task 5: Clean up type solver

- now that demands on the type solver are clear, we NEED to rewrite it so we can 
  understand what's going on in it.
  
- the same 'solver' structure may be preserved, but do away with relentless subclassing
  to simplify header interface.
  
- find better names for 'TypeVar', 'ClassVar', etc...
    - you've ignored theory for long enough. Whip out TAPL and identify the formalisms you need.

- goal:
    - report errors using relations rather than failed-invariant incidents, one by one
    - obtain printable DSL that can be used to explain to the user what went wrong and where
    - factor code into multiple more manageable modules so we don't punt on this analysis,
        namely 't' and 'meta-t'