# Eg1

## Table of Contents
- [Eg1](#eg1)
  - [Table of Contents](#table-of-contents)
  - [Packages and Headers](#packages-and-headers)
    - [Param Header](#param-header)
    - [Import Header](#import-header)
    - [Export Header](#export-header)
  - [Definitions](#definitions)
    - [Patterns (`[...]`) and Lambdas (`[...] {...}`)](#patterns--and-lambdas--)
    - [Function application](#function-application)
    - [Long expressions](#long-expressions)
    - [Tuples & Structs](#tuples--structs)
  - [Notes](#notes)

## Packages and Headers

A **package** refers to a document and all its dependencies, which include
**subpackages**. 

Each new Pandemonium document specifies a new package.

### Param Header

Params are used to specify file-level parameters for the importer to fill in
while importing this package.

```
%param {
    testPkgPath: String
}
```

> TL;DR: `%param` allows a module to be customized at compile-time.

### Import Header

Imports allows a Pandemonium package to access resources via the compiler.
These resources include:
- Source code
- Data assets
- Build server status
and can be accessed via ordinary functions.

Local pandemonium files can be imported using the builtin `loadPkg` function.

> TL;DR: `import`-ed values are computed and baked at compile-time.
> TL;DR: beware circular dependencies between `%param` and `%import`

```
import {
    testPkg: loadPkg<testPkgPath>
}
```

### Export Header

When a Pandemonium document is loaded with `loadPkg`, the result is defined by the module's
`export` header.

```
export {
    main: main_v4
}
```

## Definitions

- Order independent, provided code behaves as predicted (infinite recursion should be blocked)
  - Module-level symbols are defined before template args or bind-RHSes.
- No semicolons required between definitions.
- Each definition is a bind statement.

### Patterns (`[...]`) and Lambdas (`[...] {...}`)
- The foundation of all pattern-matching: function definitions, lambdas, match expressions, polymorphism
- **Like a struct,** consists of fields.
  - RHS of typespec fields is evaluated in type context.
  - Labels cannot be omitted.
- **Unlike a struct,**
  - Multiple labels can be assigned to the same field (for concision)
    - This is vital for resolving chain-struct ambiguity
- **Type polymorphism** patterns can be provided to single-ID bind statements to implement type-polymorphism.
  - Actual args are evaluated in type context (see below), even when called in value contexts.
- **Evaluations in type contexts** is a little different.
  - A value with a function type in value context denotes its image type (aka return type) when used in type contexts.
  - Only type function applications are allowed in type contexts (associated with 'bind' statements). 
    - This is just type-polymorphism at work.
- To implement a `lambda`, just write a pattern followed by a body in a value context. No arrows or return types required.
- `lambda`s are used in match expressions to implement match arms.
- Match any pattern with the `[...]` pattern. These holes can never be solved-for, use a template parameter and BE SPECIFIC.
  -  E.g.: `[...] {print "Invalid option"; 0}`
- Can be chained for currying.

### Function application
- Syntactically, generic and value parameter application looks identical.
  - BE SPECIFIC: cannot omit generic parameters, this always feeds the compiler a bit more info and makes monomorphization straightforward.
- This is just a functional-style pairwise application.
  - This style encourages currying, which our lambdas neatly support.
  - Always left-associative to enable currying

### Long expressions
- Long expressions always go between parentheses. These include tuples.

### Tuples & Structs
- Tuples are structs with indices that go 0, 1, 2, ...
- Structs are tuples with keys that can be named by symbol
- Both are equivalent, can be desugared
  - Namedtuple (struct) is a subtype of tuple.
  - Just push a struct field with a SYM_NULL name-- separation of policy and implementation.
- Multiple labels **CANNOT** be assigned to the same field (for concision) (unlike patterns)
  - This is vital for resolving chain-struct ambiguity in 2 look-ahead tokens

```
main_v4: (args: Slice[String]) -> {
    status = testPkg.Main();
    if status == 0 then {
        eprint("Test failed: " + testModule.testName);
    };
    return status;
}
```

## Notes

1. Markdown **should not** be source code.
   I flirted with the idea of just using Markdown as source code, but...
    - documentation introduces too much noise
    - several parts (Table of Contents, named links to functions) should be automatically generated

2. Export headers are our gateway to interfaces
   If we can allow the user to abstractly specify an export header, we have 'module-interfaces' as a feature.
    - An easy way to do this? Subfunc loadPkg and add assertions.
    - **Making sense of assertions at compile time is a key differentiator.**