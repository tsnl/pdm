; ModuleID = '/Users/nti/Workshop/Pandemonium/pdm.llvm-emitter-transplant/sandbox/emit-bug-1.pd'
source_filename = "/Users/nti/Workshop/Pandemonium/pdm.llvm-emitter-transplant/sandbox/emit-bug-1.pd"

define i32 @"lambda @ /Users/nti/Workshop/Pandemonium/pdm.llvm-emitter-transplant/sandbox/emit-bug-1.pd:2:5-6:6"(i32 %0, i32* %1) {
fn_entry_point:
  %"dim[arg-in]:x" = alloca i32, align 4
  store i32 %0, i32* %"dim[arg-in]:x", align 4
  %"dim[arg-inout]:y" = alloca i32*, align 8
  store i32* %1, i32** %"dim[arg-inout]:y", align 8
  %"loaded:x" = load i32, i32* %"dim[arg-in]:x", align 4
  %"dim[var]:variable" = alloca i64, align 8
  store i32 %"loaded:x", i64* %"dim[var]:variable", align 4
  %"loaded:x1" = load i32, i32* %"dim[arg-in]:x", align 4
  ret i32 %"loaded:x1"
}
