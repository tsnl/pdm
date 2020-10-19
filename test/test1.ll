; ModuleID = 'hub-test'
source_filename = "hub-test"

define i8 @answer() {
entry:
  %stack = alloca i8
  store i8 42, i8* %stack
  %loaded_for_return = load i8, i8* %stack
  ret i8 %loaded_for_return
}

define i64 @question() {
entry:
  %chain_result = alloca i64
  %fortytwo = call i8 @answer()
  store i8 %fortytwo, i64* %chain_result
  %loaded_for_return = load i64, i64* %chain_result
  ret i64 %loaded_for_return
}