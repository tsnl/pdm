April 25, 2021

## What Went Wrong

Attempted to implement `reduct` system, but ran into issues with 
namespaces.
- if each module has symbols with different names
- we must store each module as a separate constant bunch of symbols
- that may reference each other in function call or extern var form
- this gets very hairy

Furthermore,
- translation into reduct highly wasteful
- need for MORE classes to act as temporary storage while interpreting-- is this reduct too?

## Try Again

Instead, we can interpret the AST itself, and generate monomorphic 
versions linked to call-sites in an emitter.
This further allows type-schemes in the emitter to handle generics,
or some similar system down the road.

Change 1: (scoper) gathering template uses in scoper 
- while handling `ModAddressLookupOrder` in scoper,
- store mai on the instantiated template

Change 2: (scoper) defining formal template args in scoper
- for type args, defn class var
- for value args, defn type var

Change 3a: (typer) typing relations for formal t-args
- specifiers have 'eq' relations set to the defn var
- TODO: calls (uses) need appropriate typing relations set
- TODO: when args are omitted, must be inferred.
- we do not evaluate constants, just set typing relations to ensure 
  computable

TODO: below changes totally incomplete

Change 3b: (scoper) define builtin classes
- INT, SIGNED_INT, UNSIGNED_INT, FLOAT, NUMBER
- requires changing BuiltinStmt

Change 4: (const-eval) evaluate static expressions
- insert a 'const-eval' pass after the typer
- attempt to evaluate each Exp node
- note VCall may be called with '!(...)' args, in which case 
  function can be statically evaluated.
- note '!(...)' syntax better as `[...]` syntax

Change 5: for each tcall use, bake instantiations
- iterate through uses
- unique evaluated value and type should be associated with use
- for each unique use key, can generate and link.

TODO: below technical debt must also eventually be paid once templates are in place:
- arrays
- dynamic lists / vectors


TODO: below features should be implemented 
- for loops
- closures for map, filter, reduce
- type suffixes for literals:
  It injects a lot of information very concisely.
  - 'f' suffix => float, e.g. `24f or 24.0f or 24e3f`
  - 'F' suffix => double, e.g. `42F or 42.0F or 42e3F`
  - 'b' suffix => unsigned 1, e.g. `1b or 0b`
  - 'B' suffix => unsigned 8, e.g. `128B`
  - 'u' suffix => unsigned 32, e.g. `15u`
  - 'U' suffix => unsigned 64, e.g. `32U`
  - 'i' suffix => signed 32, e.g. `15i`
  - no suffix => signed, min width inferrable


Below is a fairly complex example that can be used as a stress test
for template instantiation before implementing/checking type-classes.

```
mod vec [Scalar NUMBER, n Int32] {

    let Vector = [Scalar^n];

    let add (v Vector, w Vector) Vector = {
        val adder = fn (it {Ty,Ty}) Ty {
            it.0 + it.1
        };
        map(adder, zip(v, w))
    };

};

mod entry_point {

    let entry_point () Int32 = {
        # Initializing some vectors...
        # (can't wait for variadic templates)
        val v1 vec[Float32, 3]:Vector = [0f, 0f, 1f];
        val v2 vec[Float32, 3]:Vector = [0f, 1f, 0f];
        val v3 vec[Float32, 3]:Vector = [1f, 0f, 0f];

        # Note omitted template args or type-spec: must infer
        val sum vec:Vector = vec:add(vec:add(v1, v2), v3);
        val double_sum = vec:add(sum, sum);
        
        # checking the result, returning rc:
        val ok = (double_sum == [2, 2, 2]);
        val return_code = {
            if (ok) {
                0        
            } else {
                1
            }
        };
        return_code
    };

};
```

## Extra Note

If we add templates, each module must be pure to instantiate.

This rules out `var` members in modules, which in turn rules out the ECS-style this language may have been
going for. Bad.

As Go adds generics on top of an existing type-tree, this increasingly looks like a futile task.

If we commit to adding templates, we cannot use 'var' mod members.
Instead, rely on functions instantiating and referencing data from the consumer.