# Modules

The compiler reads code using the **source**, **lexer**, and **parser** modules. It represents this code using the **AST** module. This module is then used by the **primer**, **scoper**, **typer**, and **checker** modules respectively to generate information for the **emitter**.

1. **Source** provides read-only access to all *source files*: code, assets, anything the user feeds the compiler.

   It provides...

   - a file-reading interface supporting line and column numbers and normalized newlines for text
   - a feedback-tracking mechanism associated with source modules (errors, warnings, information, and debug guides)
   - an interface for tracking source files and locations (line, column, and offset) within them in other modules

2. **AST** is the backbone of the compiler since all subsequent modules use the AST to exchange data. It...

   - tracks enough state to reproduce any AST node
   - tracks state shared by multiple modules per-node
   - tracks source location on a per-node basis for modules to provide feedback

3. **Lexer** constructs a token stream from a code source file. It is used by **parser**

4. **Parser** constructs an AST module from a code source file. The output AST module may be incomplete or invalid, and is thus called the *raw AST*. Specifically,

   - A raw AST node does not tell us if a field is in a tuple, struct, pattern, or module. It does not guarantee that the contents of a tuple, struct, pattern, or module are valid fields in each case.
   - A raw AST node may contain invalid control-flow (e.g. empty 'match' body)

5. **Primer** refines a raw AST into an AST proper (just 'AST'). If the raw AST is invalid, the primer generates feedback describing why.

   - Superficially checks the raw AST to ensure all data is valid.
   - Initializes shared variables for other modules, usually by invoking them
     - see Scoper
     - see Typer
   - Initializes flags per-AST node based on outer-scope properties (IN_FUNC, IN_STRUCT, IN_PATTERN, etc...)
   - Generates feedback and requests termination if node is invalid

5. **Scoper** performs lexical analysis on an AST.
6. **Typer** performs typechecking analysis on an AST.
7. **Checker** performs SMT-based analysis on an AST.
8. **Emitter** converts an AST with the required shared variables populated into LLVM IR.
