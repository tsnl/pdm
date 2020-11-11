; ModuleID = 'hub-test'
source_filename = "hub-test"

@literal_string = internal constant [12 x i8] c"hello, world"

declare i8* @malloc(i64 %0)

declare i32 @puts(i8* %0)

define i32 @main() {
entry:
  %chain_result = alloca i32
  %"let:s" = alloca i8*
  store i8* getelementptr inbounds ([12 x i8], [12 x i8]* @literal_string, i32 0, i64 0), i8** %"let:s"
  %"let:r" = alloca i32
  %actual_0_0_loaded = load i8*, i8** %"let:s"
  %call_value = call i32 @puts(i8* %actual_0_0_loaded)
  store i32 %call_value, i32* %"let:r"
  %intl = alloca i32
  store i32 0, i32* %intl
  %chain_result_loaded = load i32, i32* %intl
  store i32 %chain_result_loaded, i32* %chain_result
  %cast_ui = alloca i32
  %cast_ui_input_loaded = load i32, i32* %chain_result
  %loaded_for_return = load i32, i32* %chain_result
  ret i32 %loaded_for_return
}