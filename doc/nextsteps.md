We must implement (in order) ...
1. monomorphic inline functions for basic operations (operator_plus_f32 _ _, operator_minus_u32 _)
2. overloads (incl. for operator_* functions, like operator_plus, operator_minus, operator_lessThan, ...)
3. (1) typeclasses (a la Haskell) and (2) templates (including values)
  - eg1:
    ```
    def Array[T:IsAny,N:I64] -> {
        # ...
    };
    ```
  - eg2:
    ```
    class IsHashable[U:IsUInt] {
        val hash it:Self -> U;
    };

    def hash[U:IsUInt] it:U32 -> {
        # ...
    };

    def hash[U:IsUInt] it:U64 -> {
        # ...
    };

    def Dict[K:IsHashable[U64],V:IsAny] -> {
        # ...
    };

    # ...
    ```

We must also implement...
- 'extern' statements mirroring 'def' statements
- 'val' statements mirroring 'def' statements
- using '->' as a 'def' separator rather than '='
- 'enum' statements as the only way to denote an enum type
- '{...}' for tuple patterns, '(it)' for singletons.
- rename 'S..' to 'I..'