Spec revisions

- Lambdas now have a shorter, arrow-less syntax
    (x int) {x*2}
- Templates are now specified anonymously, like lambdas
    [t] (x t) {x * x}
    cube: [t] (x t) {x * x * x}
- Patterns now accept a Go-like type specifier syntax
  - Intentionally different from value bindings, making the 'different context' idea clearer.
  - This leaves (id: value, ...) for named arguments in function calls, so easier to parse and detect errors.
- Updated module binding syntax to be field-like.
  To type mutually recursive functions, we treat all module functions in one binding group to resolve
  the `exports` object.
  This is the same behavior as fields. Syntax has been updated to reflect this similarity.
- List syntax is in limbo.
  - template instantiation is much more frequent than creating a list or slice
  - variadic functions using templates (like C++, Scala List(...)) can address this gap.
- Chains are a {}-bdd sequence of 0 or more statements followed by a tail expr.
- Unions removed for now, can be figured out later. Symbols may suffice?
