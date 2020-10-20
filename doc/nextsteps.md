We must implement (in order) ...
- monomorphic inline functions for basic operations (operator_plus_f32 _ _, operator_minus_u32 _)
- overloads (incl. for operator_* functions, like operator_plus, operator_minus, operator_lessThan, ...)
- typeclasses (a la Haskell) and templates (including potential values.)
  - eg1:
    ```
    def tuple [K:IsAny,N:I64] () -> {
        # ...
    };
    ```
  - eg2:
    ```
    class Hashable [U:IsUInt] {
        val hash (it:Self) -> U;
    };

    def hash [U:IsUInt] (it:U32) -> {
        # ...
    }

    def hash [U:IsUInt] (it:U64) -> {
        # ...
    }

    # ...
    ```

We must also implement...
- 'extern' statements mirroring 'def' statements
- 'val' statements mirroring 'def' statements
- using '->' as a 'def' separator rather than '='
- 'enum' statements as the only way to denote an enum type
- '{...}' for tuple patterns, '(it)' for singletons.
- rename 'S..' to 'I..'