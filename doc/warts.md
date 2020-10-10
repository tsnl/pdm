# TODO now
- PARSER/AST
  
  - keyword-less 'def' (if args provided), 'let' (if no args provided), or 'typedef' (if type ID)

  - patterns
    - add support for single ID patterns
    - undo multi-LHS to one RHS in patterns, even in typespecs

  - typespecs
    - implement typespecs as separate from expressions
      - implement `x[a]` postfix template calls.
    - allow typespecs as expressions. can easily be determined by FIRST typeID.
    - works very well with postfix syntax for templates (see below)

  - calls
    - keep postfix call syntax for templates, keep sequential unary style for values.
    - postfix square bracket call => template instantiation (typefunc call)
    - sequential call => value call
    - best of both worlds compromise
    - great shape to annotated patterns, even with extensive nesting, without external parens

  - chains
    - add explicit return/yield statement terminators.
    - exploit this to identify IDs as patterns in assignment off the bat.

  - change lambda sigil from unary '%' to keyword 'fun'
    - each 'fun' only accepts one argument, and this can be reused in 'match' statements without recurrent 'fun' sigils

  - implement 'enum' and tagged unions.
  - implement 'match' statements

  - change 'CHECK' to ':: <cond>'

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