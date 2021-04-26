April 17, 2021

## Overview

> Vacation: 
> the practice of taking time to work on things other than the
> compiler to test the language

For the past few days, I have worked on and thrown away a different
prototype while trying to figure out what video-game ideas are feasible.
I use code to think, so even though nothing persists, I have still learned
a lot from this process.

A few language changes I believe I should make:
1. Export C headers if desired as a part of the build process.
2. Allow the user to override a default module-name separator, with a simple
   post-check to ensure the mapping is surjective.
3. Packages: see [On Packages](#on-packages) below

A few language features I can't wait to use:
1. modules! especially once we have 'using' to truncate full names
2. C interop-- I'm curious to see what I can do with just integers
    - note that pointers can be translated into UInt64s

## On Packages

### Understanding Go Packages

In tinkering with build systems for the compiler, LLVM, and other projects,
I have learned an enormous amount about how installations work.

Compilers & build-tools search for headers, libraries, and other files in well-defined 
paths at a system level by default.
c.f. `/usr/local/*` 

When we build projects as nested subdirectories of trees, we risk duplicating projects
that could be shared/dynamically linked, creating unnecessary duplication upon static
linking **for multiple targets.**

This resulted in a cloned and installed LLVM dependency adding ~60GB to the repository
size, and repeated testing likely ruined my expensive SSD. :(

Thus,
- our blind-side so far has been focussing on creating 1 target at a time
- since we target different platforms, we need a way to share dependencies when 
  executing on different operating systems.

This is the advantage of `golang`'s flat package system.
- we need to *flatten the target tree* into an ordered list of targets

### Encapsulation

We need a way to guarantee that some files cannot be imported from a package
so the user can use shorter (private-only) names in that module/script.

IDEA: use an `exports.pd` file, like an `exports.h` header.
- don't want `pub`-- instead rely on file-level organization.

