[Uncovering the Unknown: Principles of Type Inference](https://www.youtube.com/watch?v=fDTt_uo0F-g)
> "Type reconstruction, not type inference"
> This turns typing into a question of consistency, rather than whether you will hold the compiler's hand.
- Implement _scoping_ as a deferred process.
- Implement typing as a recursive, bottom-up, re-entrant function.
  - This will also allow us to easily cache this type-state down the road.
  - Really easy to implement. **This talk is a gem.**
  - What about recursion? We'll need some way to detect loops, in which case, the most general unification is always equality. (see below)
> Any statically typed compiler will need to check this stuff anyway.
- **start by writing a type-checker, leaving holes for inference**
> In local inference, you always have you annotate your parameter types.
> Languages with local inference can never infer the return type (e.g. fibonacci function, recursion)
- **unbelievably good introduction to global type inference in ML**
> If you don't know, punt.
- Invent 'metavariables' to fill holes, then
- unify metavariables using the constraint set until no metavariables remain
  - Pragmatically
> this algorithm does not handle mutual recursion by punting, and then doing a larger second inference step.
- in a way, you attacked the most general problem possible at the start when devising the CHA system.
- **divergence => return unified by any type, given 'evaluation' model**
- Question about typeclasses in Haskell
  - Rather than determine the arg for sure, we can use a 'copy' (bound by substitution rules) of the formal type signature
  - This is true category typing.
- 40:00
- **BRAIN HURTING IDEA**
  - If we wind up with a typing full of metavariables,
  - we can define the template types ourselves.
  - If we introduce typeclasses (so way way WAY down the road), we can define types in terms of a number of predicates.
  - What if all parametric polymorphs are implicit, thereby nailing the feel of a dynamic PL? Is this too abstract, or still useful?
    - **Why do the two languages need to be different?**
    - You can use typeclasses to loosely define values supported by runtimes like JVM or JS
    - And really strict typeclasses to support native runtimes
  - 42:30
> Damas-Milner gives us structure, not name.
- Thus, type solutions are always in relation to other types or metavariables (implying generics)
- Error message handling strategy for a 0-typed PL:
  - Substitute from a trivial set of types to provide an example
  - Provide UI-based browsing
  - Go all-in on predicates as types? (No)
    - Hard to guarantee a struct is really 'just a struct', prompting over-generalization
    - Modular composition over generality is the goal with this language,
    - so maybe not
    - the current system is really good, but manual generics are a must
- Idea!
  - To deal with interrupted control flow (e.g. return statements)
  - just say we don't obtain any typing information from that branch, because the **timeline** we type for is independent
    - phi nodes create forks in these timelines, enumerating them along with some set-theory range awareness 
    - gives us finer subdivisions of our scoper contexts along specific program execution paths
    - ignoring certain paths in lib A and certain parts in lib B, then guaranteeing the parts are mutually exclusive, let us 'incrementally' verify a program. this is _progression_; -in-A- return -enter-B-context-> caller_context -> ...