# Scoper

todo: implement me!

The scoper sets up data-structures to allow IDs to map to Definitions.
It does this by defining, but not reading, all IDs.
These `Defn` instances include fresh `Var` type solutions.

This entails creating `ClassVar`s for template formal arguments,
and `TypeVar`s for everything else.
