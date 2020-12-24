**LSP server**

- [see specification here](https://github.com/microsoft/language-server-protocol)

- should we implement an HTTP server for debugging and dynamic reflection (debugging)?



**Debugger**

- LLVM IR needs source references

- See lldb



**Package manager/linker**

​	- you need to be able to link to C code

​		- which is built in like a bajillion different ways

 	- but really the same one way?!

​	- but also this language’s code

​	- and also static resources

​		- because a big part of using an SMT solver

​		- is that we can feed input files to the compiler to optimize with

​		- think images, 3D model files, anything to do with pre-processing files.

​	+ easily accessible to people so they want to use the language

​	+ reproducible on different platforms



**Package composition**

\- Can’t be LLVM IR since it isn’t stable

​	- unless we support different versions of LLVM IR explicitly

\- JVM bytecode

​	- no explicit memory management

​	- no register-level control

\- WebAssembly

​	- no explicit memory management

​	- no register-level control

\- A custom IR. Probably based on S-expressions.

​	- this is just source code.

​	- may require manual obfuscation?

​	- S-expressions are parser-stable, whereas syntax is not



**Checking**

- Typechecking

- Z3 for program verification
  - I’ve never done this part before.

  - Can first be used to check assertions in control-flow
  - But also to synthesize memory allocation and de-allocation calls before code-generation (see below)

-  LLVM IR for output

  - `+` fast
  - `-` extra work to bind to C code, but not really since the LLVM API is awesome at this
  - `+` I already have an LLVM IR implementation in Python, so it’s easier

