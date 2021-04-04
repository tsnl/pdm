# Introduction

This book specifies the PDM programming language. Thus, all subsequent references to **PDM** are short for **the PDM programming language.** Furthermore, **PDMC** is short for **the PDM compiler**.

PDM lets you write **type-safe code** once **that runs fast anywhere.** This means native performance, in a browser or mobile sandbox, on Windows, in a Docker container, or from within Microsoft Excel.

How? Every software tool in existence was created by a human trying to most efficiently represent some load, store, arithmetic, and control/code-navigation instructions all CPUs uniformly support. This means that in PDM, you write **code that checks, then transforms data, in terms every modern computer understands**, leaving few platform-dependent blanks to be filled by the compiler. Note that to PDMC, data refers to anything represented by a finite sequence of 1s and 0s.

# A Peek

```
# imports...
import std from "https://github.com/tsnl/pdm/stdlib" type "git/remote/branch=v0";
import print from "./printer.pdm";

# module definitions
mod fibonacci {

    anonymous_fn fib (n S32) -> S32 = {
        # fib_naive(n)
        fib_faster(n, 1, 0, 1);
    }
    
    anonymous_fn fib_naive (n S32) -> S32 = {
        if (n == 0 or n == 1) then (1)
        else {
            fib(n-1) + fib(n-2)
        }
    };

    anonymous_fn fib_faster (n S32, i S32, xp S32, x S32) -> S32 = {
        # i tracks current index
        # xp precedes x
        if (n == 0) then {
            0
        } else {
            if (i == n) then {
                x
            } else {
                # note that x, xp, and i remain unchanged in outer 
                # scopes.
                # they are just shadowed here.
                let (x, xp) = (x + xp, x);
                let i = i+1;
                fib_faster (n, )
            }
        }
    };
};
```

# Chapter List

[Chapter 1 - Basic Expressions (10 mins)]("01-basic-exps.md")
- What is an expression?
- What does 'evaluation' mean?
- What does 'representation' mean?
- What is a literal?
- How do I represent...
  - an integer?
  - a rational number?
  - a string of bytes?
- What is a function?
  - What is a call?
  - What is a unary operator?
  - What is a binary operator?

[Chapter 2 - Basic Types (10 mins)]("02-basic-types.md")
- What is a platform?
- What is a type?
- How do I represent the type of...
  - an integer?
  - a rational number?
  - a string of bytes?
  - a function?
- How do I represent a relation between types?
  - What is subtyping? What is supertyping?
  - What is type equality?

[Chapter 3 - Chains, Statements, and Definitions]("03-chains.md")
- What is a statement?
  - How to... evaluate and store an expression (eg. `let a = b`)
  - How to... evaluate and discard an expression
  - How to... define a constant or a function
  - How to... define a module
- What is time? (No, seriously)
- What is a chain?
  - What is shadowing?
- What is an if-then-else?
- What is a short-circuiting binary operator?

[Chapter 4 - Templates]("04-templates.md")
- What is a typeclass?
- What is a template?
  - How do I represent a pointer?
  - How do I represent a mutable monad?
  - How do I define a template function?
- Misc.
  - Why can't I create templates in chains?
  - Why can't I create module templates?
