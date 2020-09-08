- SPIN can be used for program verification
- We generate C and Promela from source
  
  Pretty straightforward translation, the goal should be to augment C, not replace it.
  
  We can write Promela to augment the solver.
  - Run `modex` to convert existing C code to Promela.
    - Generating C rather than LLVM IR is the right idea here.
  - Run `spin` to verify process state, generate counterexamples.
  - Propagate counterexample back up to compiler, generate meaningful error message.

- We should experiment with Promela before generating it
  - Try on `moon-river`, the toy raytracer?
  - 
