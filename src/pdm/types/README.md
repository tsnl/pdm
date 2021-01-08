# Types

## Upshot

This module lets users...
1. create types
2. create type and typeclass variables (with TypeVar, ClassVar resp.)
3. create relations and assume or test them. 
4. use assumed relations to solve and check type and typeclass variables.

## Overview

This module is used to infer and check the all typing in an input program.
Users do this by instantiating `Var`s, and apply `Rule`s to them.
This module then solves each Var by examining constraints for any inconsistencies.

This module supports two kinds of variables: `ClassVar` and `TypeVar`.
- Use `TypeVar` to solve for one unique type in a context.
  - Use `Type`, subclass of `TypeVar`, for constant types with frozen soln.
    Need to generate/maintain appropriate constraints for these constants.
- Use `ClassVar` to solve for or constrain many types in a context.

## Usage

All typing can be viewed as a special case of a template function, since...
- value operators are typechecked just like value functions-- as N-ary operators
- value calls are a special case of template calls without any type arguments
- For a template function,
  - each value arg gets a `TypeVar`, since the value is of one valid type.
  - each type arg gets a `ClassVar`, since the type is in one valid class.

**In short, create a `ClassVar` for only type-TArgs (incl. typeclass candidate) and `TypeVar`s everywhere else!**

## Implementation

Under the hood, both TVs and CVs actually track sets of types (i.e. dynamic typeclasses),
and may thus be related between each other.
For example, input programs may include templates, which are like functions that may also accept **type arguments.**
Each formal type argument is assigned a CV, that is then exempt from finding a unique solution while solving all Vars.
Like a bed of clay against a key, the CV accepts constraints that form an imprint unique to that formal argument's use.
Then, actual argument TVs may subclass the formal CV, such that the proxy's constraints are checked for each actual type argument.

To solve, treat each `Var` (class or type) as a node in a graph.
- to solve each `TypeVar`, need to solve and compare all super and sub TVs using 'visited' bit to avoid cycles.
  - TV solution exclusively based on 'Soln' comparison
- to apply each `ClassVar`, 
  - (CV-TV) need to check all `TypeVar` solutions against constraints, or 
  - (CV-CV) `Constraints` against `Constraints`

There are two different typer operators:
- `assume(rule)` adds the rule to the system, assuming it is true. All errors deferred until type solution.
- `test(rule)` checks if the rule is True, False, or Invalid. The latter indicates a typing error.

## Solution

1.  Propagates and equalizes Constraint sets iteratively
    flowing from supervars to subvars
2.  Iterates through assumed constraints to determine a solution
    constructively.
    1.  consider kind-constraints to select one kind.
    2.  check and use kind-dependent-constraints to construct an IntervalSet
    