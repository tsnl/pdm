# Chapter 02 - Basic Expressions

```
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
```

## What is an Expression?
**To transform data, we must first learn to express it using expressions.** 
We use expressions to first write numbers and pieces of text, then operate on these expressions in a few previously defined ways. 

## What is Evaluation?
**When an expression is evaluated**, it produces a special kind of expression called **a literal** that evaluates to itself; i.e., an expression is a literal if and only if it evaluates to itself.

For example, the expression `(2)` evaluates to the expression `(2)`, i.e. the expression itself.

For example, the expression `(2 + 2)` evaluates to the expression `(4)`. 
So, the expression `(2+2 == 4)` always evaluates to the expression `true`.
However, the expression `(2 + "holiday")` would not evaluate.

If an expression `A` evaluates to `B`, then `A` is called `B`'s **representation.**
Thus, `(2+2)` is a representation of `4` since `(2+2)` evaluates to `4`. 
Furthermore, **expressions that do not evaluate have no representation.**

## Common Representations

**Integers** are represented by...
- (**decimal**) sequences of the digits `0` through `9` => a decimal (base-10) number,
  with optional '_' spacer characters
  - eg. 42, 525_600, 22_420_102_222
- (**hexadecimal**) `0x` followed by sequences of the digits `0` through `9` or `abcdef` or
  `ABCDEF`.
  - e.g. 0x2a (or 42), 0x80520 (or 525_600), 0x3857_9c4e

**Rational numbers** are represented by `(decimal-int) '.' (decimal-int)`.
- eg. 3.14159, 2.71828

Note that it is always better to represent **currency** as an integer number of cents/hundredths since rational number representation may introduce rounding errors.

**Strings of bytes** are represented by characters between pairs of 
`single-quotes'` or `double-quotes"`.

Eg. 1: 
- `"hello, world"` and `'hello, world'` represent the same string.
  
Eg. 2:
- `"he said, \"hello, world!\", using \\"-characters in string literals."`
- represents `he said, "hello, world!", using \" characters in string literals.`
  in UTF-8 encoding.


## What is a Function?

**In PDM, all you write are functions, so they are _very important._**

A function is just a set of relationships mapping inputs to an output.
It is used to compute output expressions from input expressions so one does
not need to rewrite steps to reuse them.

For example, in mathematics, the function `f(x) = x` maps every input
to itself, while `g(x) = 0` maps every input to 0. The function 
`h(x) = f(x) + g(x)` is identical to `f` when `x` is an integer,
rational number, or complex number. (why?)

Since this map is usually quite large, evaluating a function is not easy,
since even addition and multiplication take some time for a computer.
However, functions let less work do more, so even the smartest mathematician
can do more with functions in their pocket than without.

However, functions are so useful that the only way to construct many common 
representations is using functions. 
Thus, this section will **only focus on using functions to represent expressions, not defining functions.**

### Call Expressions

Each function accepts a whole number of arguments (0 or more).
For example, `f() = 0` or `g(x) = 1` or `h(x,y,z) = x+y+z` accept
0, 1, and 3 arguments respectively. 

Each argument is uniquely identified by its position. The 3rd
argument of `h` is represented by the identifier `z`.
