# The PDM Programming Language SDK

Work in progress.

## Overview

*Why decide between a compromised web experience and a dedicated native one?*
*Why separate logical dependencies with slow, unnecessary HTTP barriers?*

The PDM Programming language aims to **bridge the gap between static and interpreted programming languages.**
It augments a C-like foundation with compile-time analysis (templates) and evaluation (constexprs), and
uses this toolset to construct a Python-esque programming environment. By providing high-level features
as libraries for a low-level language, 
**PDM eases development by supporting quick and dirty modules and bit-level bulwarks in the same type system.**

Since the gaps between C-land and Python-land are filled in by the compiler ahead of time (AoT), a
programmer has the power to choose whether to strictly or loosely specify their code as needed.
The programmer's options transparently reflect the capabilities of the underlying, practically
standardized hardware. Low-level features like register types, memory addresses, and unsafe memory
operations apply on an abstract computer with basic features expected of many common platforms.

LLVM makes emitting faster code easier, and WebAssembly allows a derivative of that fast code to run in browsers.
WebGPU is an in-development project to bring a standardized GPU API to browsers to succeed WebGL2.
These facts highlight a pattern: complex GUI applications can be 
**written once and run natively and on browsers without performance degradation** in an 
**environment-aware way**. 

Furthermore, as projects evolve, costly rewrites can be avoided since...
1. Since PDM is AoT compiled, unnecessary runtime checks can be elided in favor of static checks, thereby 
   reducing the baseline demand for highly specified (and thus performant) code.
2. It is impossible to write code that does not typecheck, but it is still possible to write potentially incorrect or unsafe code. Thus, key performance metrics can be incrementally improved from a soundly-typed foundation without additional constraints introduced by the compiler.

Lastly, PDM naturally links with existing C (and thus subsets of C++) code. By supporting the de jure standard
in ABIs with `extern` statements, PDM simplifies dependency management and allows users to 
**use C libraries out of the box.** This is possible using Clang's excellent, highly modular C/C++ parser,
and the fact that PDM's type system accommodates C's (with some caveats with respect to non-discriminated unions).
Support for C++ libraries is currently not planned.
Note that support for C libraries implies support for interpreted programming language interop, i.e. compatibility with JS, Python, Lua, etc.

## Summary

This repository currently builds...
1. `pc`: An old (but functional) C compiler implementation for a subset of the language. Just validates a program 
   and then prints LLVM IR to stdout. The benchmark for performance (it's really quick!).
2. `[lib]pdm`: A library that compilers, interpreters, and editor tools can share. Written in OO-C++. **WIP. (does not build, must disable through CMake)**
3. `pdm_sandbox`: An eventual CLI frontend, currently just console tests for `pdm`. **WIP.**
After building, try running `$ ./pdm_sandbox <file>`.

This repository contains...
1. `src`: source code for `pc` (`src/pdm_old_c`), `libpdm` (`src/pdm`), `pdm_sandbox` (`src/pdm_sandbox`)
2. `dep`: dependency submodules
3. `eg`: a list of aspirational examples; where we're going.
4. `test`: a list of compilable examples; where we are (with `pc`)
5. `doc`: mostly incomprehensible text files the author uses to try and stay organized, or PDFs the author finds useful/interesting. Will eventually contain documentation.

For the latest updates, see my latest commits.


## How to Build

Just run `1build.sh` on *nix-based systems.

### Alternative

In all the following examples, `.` refers to the root of this repository.

1. Clone this repository using 'git', ensuring you clone submodules.
2. Use 'CMake' to configure the project, `cmake .`
   - Please set `PDM_LLVM_INSTALL_DIR` to the directory containing an installation of the LLVM library, built.
     Although the LLVM project is a large submodule dependency, CMake integration is difficult since in-source
     builds are disabled for LLVM.

     If you don't have LLVM installed, please follow LLVM's instructions for building your desired version from 
     source. Once you have built this, set `PDM_LLVM_INSTALL_DIR` accordingly.
   
     **To set `PDM_LLVM_INSTALL_DIR`**, simply run `ccmake .` to run the console CMake configuration tool, or 
     `cmake-gui .`.

   - If you've installed LLVM using Homebrew on macOS, your path might look like...
      `/usr/local/Cellar/llvm/10.0.1_1`
3. Use 'CMake' to build the project, `cmake --build .`
   - I recommend running `cmake --build . -j <N>` where `N` is the number of 'jobs' or parallell processes you
     would like to use. On a computer with M cores, set N >= M for optimal results.
     **Example:** `$ cmake --build . -j 4   # on a 2-core MacBook Air with Hyperthreading/SMT`


## Project Horizon

For my rawest updates, please see `doc/roadmap.md`. It's a poor task tracker, but the text-soup helps me view (and factor)
tasks into code-like trees. Why break from what you work with 99% of the time, right?

More human-friendly documentation will follow when implementing tests takes priority over implementing new features, i.e.
when polish is a greater user barrier than absence of features. This point is yet undetermined.

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
