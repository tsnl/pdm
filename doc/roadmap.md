# Roadmap

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

- a new 'struct' statement is required since struct typespecs were
  removed due to grammar conflicts.
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
    * AstXTemplate tracks...
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
                2. prime monomorph
                    using def's scope as base scope to preserve symbols
                3. type monomorph
                    but do not typecheck
                4. monomorphID := add result to table for future lookups
            3. (extra typing) add monomorph type as soln to metavar
            4. return monomorphID
            this is done to ensure monomorphs are only generated for
            concrete types.
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
