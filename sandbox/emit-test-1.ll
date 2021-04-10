; ModuleID = '/Users/nti/Workshop/Pandemonium/pdm.llvm-emitter-transplant/sandbox/emit-test-1.pd'
source_filename = "/Users/nti/Workshop/Pandemonium/pdm.llvm-emitter-transplant/sandbox/emit-test-1.pd"

define i32 @"lambda @ /Users/nti/Workshop/Pandemonium/pdm.llvm-emitter-transplant/sandbox/emit-test-1.pd:7:5-10:6"() {
fn_entry_point:
  ret i32 0
}

define i32 @"lambda @ /Users/nti/Workshop/Pandemonium/pdm.llvm-emitter-transplant/sandbox/emit-test-1.pd:16:5-21:6"(i32 %0, i32* %1) {
fn_entry_point:
  %"dim-ptr[arg-in]:x" = alloca i32, align 4
  store i32 %0, i32* %"dim-ptr[arg-in]:x", align 4
  %"loaded:x" = load i32, i32* %"dim-ptr[arg-in]:x", align 4
  %"dim-ptr[var]:variable" = alloca i32, align 4
  store i32 %"loaded:x", i32* %"dim-ptr[var]:variable", align 4
  store i32 42, i32* %"dim-ptr[var]:variable", align 4
  store i32 42, i32* %1, align 4
  %"loaded:variable" = load i32, i32* %"dim-ptr[var]:variable", align 4
  ret i32 %"loaded:variable"
}

define i32 @"lambda @ /Users/nti/Workshop/Pandemonium/pdm.llvm-emitter-transplant/sandbox/emit-test-1.pd:23:5-29:6"() {
fn_entry_point:
  %"dim-ptr[var]:foo" = alloca i32, align 4
  store i32 0, i32* %"dim-ptr[var]:foo", align 4
  %"dim-ptr[var]:baz" = alloca i32, align 4
  store i32 1, i32* %"dim-ptr[var]:baz", align 4
  %"loaded:foo" = load i32, i32* %"dim-ptr[var]:foo", align 4
  %returned = call i32 @"lambda @ /Users/nti/Workshop/Pandemonium/pdm.llvm-emitter-transplant/sandbox/emit-test-1.pd:16:5-21:6"(i32 %"loaded:foo", i32* %"dim-ptr[var]:baz")
  %"dim-ptr[var]:bar" = alloca i32, align 4
  store i32 %returned, i32* %"dim-ptr[var]:bar", align 4
  %"loaded:bar" = load i32, i32* %"dim-ptr[var]:bar", align 4
  ret i32 %"loaded:bar"
}
