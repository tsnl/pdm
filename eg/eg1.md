# Eg1

## Table of Contents
- [Eg1](#eg1)
  - [Table of Contents](#table-of-contents)
  - [Packages and Headers](#packages-and-headers)
    - [Param Header](#param-header)
    - [Import Header](#import-header)
    - [Export Header](#export-header)
  - [Definitions](#definitions)
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

```
main_v4: (args Slice[String]) -> {
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