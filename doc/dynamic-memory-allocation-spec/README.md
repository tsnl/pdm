Since references to data cannot be stored in structures or in closures,

escape analysis for allocated memory is restricted to the stack, which is well understood.

**Can we statically insert 'delete' calls such that memory is garbage-collected ahead of time?**
- trade-off between 'if de-allocated then de-allocate' and wasting memory

Unfortunately, doesn't work, consider assigning a `Buf` to an `inout` parameter.
- memory must persist to outside stack frame.

Consider pushing to a vector that resizes.
- must relinquish old buffer and allocate a new, larger one

**Instead, use reference counting for 'Buf' instances!**
- no risk of cycles since structs cannot contain references, so elements in a Buf cannot point to this Buf or others
- maximum count closely related to maximum stack-length-- trimmable aot
- **need to bake in inc-ref and dec-ref calls**
