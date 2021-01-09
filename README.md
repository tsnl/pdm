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
1. `pc`: An old C compiler implementation of the language. Just validates a program 
   and then prints LLVM IR to stdout. The benchmark for performance (it's really quick!).
   Syntax and semantics have changed incompatibly since then.
2. `[lib]pdm`: A library that compilers, interpreters, and editor tools can share. Written in OO-C++. **WIP.**
3. `pdm_sandbox`: An eventual CLI frontend, currently just console tests for `pdm`. **WIP, TRY ME.**
After building, try running `$ ./pdm_sandbox <file>`.

This repository contains...
1. `src`: source code for `pc` (`src/pdm_old_c`), `libpdm` (`src/pdm`), `pdm_sandbox` (`src/pdm_sandbox`)
2. `dep`: dependency submodules
3. `eg`: a list of aspirational examples; where we're going.
4. `test`: a list of compilable examples; where we are (with `pc`)
5. `doc`: mostly incomprehensible text files the author uses to try and stay organized, or PDFs the author finds useful/interesting. Will eventually contain documentation.

For the latest updates, see my latest commits.

## How to Build

**Prerequisites:**

In order to build PDM, you will require:
1. CMake >= 3.16 (can probably be downgraded safely)
2. A C/C++ compiler (I recommend Clang)
3. The `git` command-line utility, and an understanding of how to navigate directories and invoke `git` and `cmake` using the terminal

**Recommended:** If you use Visual Studio Code or another OSS Code derivative, 
1. install the `CMake Tools` Extension via the Visual Studio Code Marketplace. 
2. Use VS Code to open the Workspace located at `/vscode.code-workspace`.
Now, CMake Tools will help you detect installed compiler kits, configure CMake, and even help you build and debug if you so choose.

**Building**

In all the following examples, `.` refers to the root of this repository.
Ensure you have CMake installed.

1. Clone this repository using 'git'. Initialize submodules.

   Assuming we are cloning to the directory 'pdm-0',
    ```
    $ git clone https://github.com/tsnl/pdm pdm-0
    $ cd pdm-0
    $ git submodule update --init --recursive
    ```
2. Use 'CMake' to configure the project, `cmake .`

   This will automatically fetch and compile all required dependencies from scratch.
   This may take upwards of an hour.
   
3. Use 'CMake' to build the project, `cmake --build .`
    -   I recommend running `cmake --build . -j <N>` where `N` is the number of 'jobs' or parallell processes you
        would like to use. On a computer with M cores, set N >= M for optimal results.
        
        **Example:** 
        
        `$ cmake --build . -j 4   # on a 2-core MacBook Air with Hyperthreading/SMT`
    -   Omit the `-j` flag when debugging to ensure C compiler output is in-order.


**Having trouble?**

Please file an issue, and it'll be fixed as soon as possible.


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


## A Taste of PDM

```
# eg/eg10.pdm

mod vector {
    type Vec [T Number, n UInt32] = {
        data Array[T,n]
    };

    fn increment ![T Number, n UInt32] (inout lt Vec[T,n], rt Vec[T,n]) = {
        help_increment[T,n](inout lt, rt);
    };
    fn help_increment [T Number, n UInt32] (inout lt Vec[T,n], rt Vec[T,n]) = {
        # for this to work, need Array subtyping to work correctly
        # s.t. Array[T,n] :< Array[T,m] <=> n < m
        if (n > 0) then {
            set lt.data.(n-1) = lt.data.(n-1) + rt.data.(n-1);
            help_increment[T,n-1](inout lt, rt)
        };
    };

    fn add ![T Number, n UInt32] (lt Vec[T,n], rt Vec[T,n]) -> Vec[T,n] = {
        var sum_vec = lt;
        increment(inout sum_vec, rt);
        sum_vec
    };
}
```

## Try Me!

Once you have built, try running the following command.
First, navigate to the root of this repository (where the 'pdm_sandbox' executable is assumed to be built.)

```
# Input:
$ ./pdm_sandbox sandbox/fib1.pdm
```