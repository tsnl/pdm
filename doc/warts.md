# TODO now
- PARSER/AST
  - convert AST_STRUCT -> AST_TUPLE, constructed using '(...)' namedtuples with optional fields (so still LL(2))

  - keep postfix call syntax for templates, keep sequential unary style for values.
    - postfix square bracket call => template instantiation (typefunc call)
    - sequential call => value call
    - best of both worlds compromise

  - change lambda syntax back to [...] {...} (curly braces mandatory!)

  - implement 'enum' and tagged unions.
  - implement 'match' statements

  - rename 'CHECK' to 'test <cond> else <error-message>'

  - make type and value patterns separate but uniform
    - inconsistency is confusing
    - e.g. in type func patterns, `a,b: c` => `a: c, b: c`          
      - (the problem)
    - e.g. in type enum patterns, `a,b: c` => `a: ?, b: c`          
      - (use this instead)
      - (note that tails cannot be omitted in function calls, so this would produce an error)
    - e.g. in value namedtuple patterns, `a,b: c` => `?: a, b: c`   
      - (stays the same)

  - replace '&', '|', and '^' with keywords 'and', 'or', and 'xor' resp.

- TYPER
  - rename META -> HOLE
  - implement a better HOLE solver by...
    - adding a 'soln' to each type instance (concrete iff soln = self)
    - selecting a SOLN...
      - if a HOLE has any concrete required supertypes,
        - select the submost concrete required supertype as SOLN
        - require SOLN as a supertype of each required HOLE subtype
      - else if a HOLE has any concrete required subtypes,
        - select the supermost concrete required subtype as SOLN
      - else totally indeterminate, raise an error or ignore

- EMITTER
  - implement lambda emission
  - implement captures (fix)
  - implement tuples
    - call LLVMConstStruct in AST_TUPLE
  - implement calls
    - no destructuring required
    - pass closures
  
# Warts

- Captures not implemented for lambdas
- Match expressions not implemented

# Disabled/pending

- Closures
  - Lambdas & curried 'def'
- Check/assert
- Templates
- Classes

# Deprecated

- Functions as typespecs
- Pointers