# Scripts

*Like Python, each source file is designed to be wholly local. If something isn't working, you only check the **script** where the error ocurred.*

A `script` refers to a single source file. It is the modular unit of source code. 

Scripts may use file resources that are **static** or **dynamic**
- static resources: unchanging files always used by a script at a fixed location
  - will be built by the compiler
  - may be optimized by the compiler, bundled with other static resources
  - imported files are a kind of static resource
- dynamic resources: files used by a script that may change during run-time or may not be used.
  - requires use of the VFS to mount, load, open, and check file access

# Packages

When a script is executed, all static resources are added to a package for that script.
This is not a user-oriented feature; packages are ad-hoc bundles of required resources that correspond to an entry point.

```Script -> Package (after pulling in all resources) -> Application/Library```
- Scripts are FS references in terms of the developer's machine
- Packages normalize all these references and shake redundant ones
- Packages are then compiled to scripts

# Example

*The 'dev.app.hub' program below prints `(...)\n\n` to stdout.*
