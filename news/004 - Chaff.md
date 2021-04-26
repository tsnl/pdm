**April 21**

cf https://docs.julialang.org/en/v1/manual/metaprogramming/


---

**April 25 **

is something like this possible?
good for concision.
    
```
mod wart {

    let f () Int32 = {
        using bitwise;
    
        val forty [Int16]:Scalar1 = 40u;
        val forty_one [Int16]:Scalar2 = 41u;
        val forty_two [Int16]:Scalar3 = 42u;
    };

};
```

todo: seriously consider RDBMS-style memory management for modules
- benefit of being pure
- and encoding state changes in a robust way over multiple phases (e.g. const-eval, runtime)