; ModuleID = '/Users/nti/Workshop/Pandemonium/pdm.master/sandbox/emit-test-1.pd'
source_filename = "/Users/nti/Workshop/Pandemonium/pdm.master/sandbox/emit-test-1.pd"

define i32 @"lambda @ /Users/nti/Workshop/Pandemonium/pdm.master/sandbox/emit-test-1.pd:5:5-8:6"(i32 %0, i32* %1) {
fn_entry_point:
  %"dim[arg-in]:x" = alloca i32
  store i32 %0, i32* %"dim[arg-in]:x"
  %"dim[arg-inout]:y" = alloca i32*
  store i32* %1, i32** %"dim[arg-inout]:y"
  %"dim[var]:omega" = alloca i32
  store i32 24, i32* %"dim[var]:omega"
  %"loaded:omega" = load i32, i32* %"dim[var]:omega"
  ret i32 %"loaded:omega"
}
