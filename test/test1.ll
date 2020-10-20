; ModuleID = 'hub-test'
source_filename = "hub-test"

define i64 @answer() {
entry:
  %chain_result = alloca i64
  %call_alloca = alloca i64
  %call_value = call i64 @answer_helper()
  store i64 %call_value, i64* %call_alloca
  %loaded_for_return = load i64, i64* %call_alloca
  ret i64 %loaded_for_return
}

define i64 @answer_helper() {
entry:
  %chain_result = alloca i64
  %stack = alloca i8
  store i8 42, i8* %stack
  %cast_si = alloca i64
  %cast_si_input_loaded = load i8, i8* %stack
  %cast_sext = sext i8 %cast_si_input_loaded to i64
  store i64 %cast_sext, i64* %cast_si
  %loaded_for_return = load i64, i64* %cast_si
  ret i64 %loaded_for_return
}