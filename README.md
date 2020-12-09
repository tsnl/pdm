# The PDM Programming Language SDK

Work in progress.

## Overview

The PDM Programming language aims to **bridge the gap between static and interpreted programming languages.**
It augments a C-like foundation with compile-time analysis (templates) and evaluation (constexprs), and
uses this toolset to construct a Python-esque programming environment. By providing high-level features
as libraries for a low-level language, 
**PDM eases development by supporting quick and dirty modules and bit-level bulwarks in the same type system.**

Since the gaps between C-land and Python-land are filled in by the compiler ahead of time (AoT), a
programmer has the power to choose whether to strictly or loosely specify their code as needed.

Furthermore, as projects evolve, costly rewrites can be avoided since...
1. Since PDM is AoT compiled, unnecessary runtime checks can be elided in favor of static checks, thereby 
   reducing the baseline demand for highly specified (and thus performant) code.
2. Duck-typed implementations can always be rewritten behind a well-typed interface. 

Lastly, PDM naturally links with existing C (and thus subsets of C++) code. By supporting the de jure standard
in ABIs with `link "C"` statements, PDM simplifies dependency management and allows users to 
**use C libraries (even templates) out of the box.** This is possible using Clang's excellent, highly modular C/C++ parser,
and the fact that PDM's type system accommodates C's (with some caveats with respect to non-discriminated unions).
Support for C++ libraries is currently not planned.

## Summary

This repository currently builds...
1. `pc`: An old (but functional) C compiler implementation for a subset of the language. Just validates a program 
   and then prints LLVM IR to stdout. The benchmark for performance.
2. `[lib]pdm`: A library that compilers, interpreters, and editor tools can share. Written in OO-C++. WIP.
3. `pdm_cli`: An eventual CLI frontend, currently just console tests for `pdm`. WIP.
After building, try running `$ ./pc <file>` or `$ ./pdm_cli`.

This repository contains...
1. `src`: source code for `pc` (`src/pdm_old_c`), `libpdm` (`src/pdm`), `pdm_cli` (`src/pdm_cli`)
2. `dep`: dependency submodules
3. `eg`: a list of aspirational examples; where we're going.
4. `test`: a list of compilable examples; where we are (with `pc`)
5. `doc`: mostly incomprehensible text files the author uses to try and stay organized, or PDFs the author finds useful/interesting. Will eventually contain documentation.

For the latest updates, see my latest commits.


## How to Build

1. Clone this repository using 'git', ensuring you clone submodules.
1. Run `src/pdm_old_c/bison-build.sh` in that working directory to build C parser.
1. Use 'CMake' to configure the project, `cmake .`
   - Note 'CMakeLists.txt' contains some hardcoded paths for LLVM development on macOS.
   - In due time, LLVM (and Clang) will be built and linked from source, so no CMake configuration
     should be required to compile a 'sensible default build' on desktop.
2. Use 'CMake' to build the project, `cmake --build .`


## Project Horizon

1. Implementing a standard library (modelled off of Rust and C++), with
   1. Optional, selective reference counting GC (`shared_ptr` or `Rc`/`Arc`)
   2. Language-wide support for hashing (standardized but flexible `Hashable` typeclass)
   3. Collections for different scales, like `SlotMap<K,V>` or `Deque<T>` to organize
      chunks of contiguous, stable memory, but also `Vec<T>` for smaller/throwaway 
      computation
   4. Excellent UTF-8 and UTF-32 support (as well as natural interop between characters in either set)
   5. IPC batteries included (files, sockets, )
2. Implementing an LSP server for PDM (so VSCode integration is first class) 
3. Implementing a WebGPU (proposal, likely Obsidian) wrapper (in WebGL and OpenGL/Vulkan)

## Contact Me

If you have any questions or would like to contribute, please email me at: [tsnl21009@gmail.com](mailto:tsnl21009@gmail.com).
