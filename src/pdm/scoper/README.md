# Scoper

The scoper sets up data-structures to allow IDs to map to Definitions.
It does this by defining, but not reading, all IDs.
These `Defn` instances include fresh `Var` type solutions.

This entails creating `ClassVar`s for template formal arguments,
and `TypeVar`s for everything else.

**TODO:**
- It is possible for 'using' to form an infinite lookup loop.
- Solution:
  - each 'Context' lookup sets a per-thread bit from 'false' to 'true' at the start, and to 'false' upon return.
  - if 'lookup' is called on a node with a 'true' bit, we detect the cycle and exit.