; ModuleID = '/Users/nti/Workshop/Pandemonium/pdm.llvm-emitter-transplant/sandbox/emit-test-1.pd'
source_filename = "/Users/nti/Workshop/Pandemonium/pdm.llvm-emitter-transplant/sandbox/emit-test-1.pd"

define void @"root_$_entry_point_$_line_1"(i32 %0, i32 %1, i32 %2, i32* %3) {
fn_entry_point:
  %"dim-ptr[arg-in]:m" = alloca i32, align 4
  store i32 %0, i32* %"dim-ptr[arg-in]:m", align 4
  %"dim-ptr[arg-in]:c" = alloca i32, align 4
  store i32 %1, i32* %"dim-ptr[arg-in]:c", align 4
  %"dim-ptr[arg-in]:x" = alloca i32, align 4
  store i32 %2, i32* %"dim-ptr[arg-in]:x", align 4
  %"loaded:m" = load i32, i32* %"dim-ptr[arg-in]:m", align 4
  %"loaded:x" = load i32, i32* %"dim-ptr[arg-in]:x", align 4
  %i_mul_res = mul i32 %"loaded:m", %"loaded:x"
  %"loaded:c" = load i32, i32* %"dim-ptr[arg-in]:c", align 4
  %i_add_res = add i32 %i_mul_res, %"loaded:c"
  store i32 %i_add_res, i32* %3, align 4
  ret void
}

define i32 @"root_$_entry_point_$_main"() {
fn_entry_point:
  %"dim-ptr[var]:m" = alloca i32, align 4
  store i32 2, i32* %"dim-ptr[var]:m", align 4
  %"dim-ptr[var]:c" = alloca i32, align 4
  store i32 12, i32* %"dim-ptr[var]:c", align 4
  %"dim-ptr[var]:x1" = alloca i32, align 4
  store i32 15, i32* %"dim-ptr[var]:x1", align 4
  %"dim-ptr[var]:y1" = alloca i32, align 4
  store i32 0, i32* %"dim-ptr[var]:y1", align 4
  %"loaded:m" = load i32, i32* %"dim-ptr[var]:m", align 4
  %"loaded:c" = load i32, i32* %"dim-ptr[var]:c", align 4
  %"loaded:x1" = load i32, i32* %"dim-ptr[var]:x1", align 4
  call void @"root_$_entry_point_$_line_1"(i32 %"loaded:m", i32 %"loaded:c", i32 %"loaded:x1", i32* %"dim-ptr[var]:y1")
  %"loaded:y1" = load i32, i32* %"dim-ptr[var]:y1", align 4
  ret i32 %"loaded:y1"
}
