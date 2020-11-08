; ModuleID = 'hub-test'
source_filename = "hub-test"

declare i8* @malloc(i64 %0)

define i32 @double(i32 %0) {
entry:
  %"arg:0-x" = alloca i32
  store i32 %0, i32* %"arg:0-x"
  %chain_result = alloca i32
  %intl = alloca i32
  store i32 2, i32* %intl
  %bop_ltarg_loaded = load i32, i32* %intl
  %bop_rtarg_loaded = load i32, i32* %"arg:0-x"
  %bop_res = alloca i32
  %bop_smul_loaded = mul i32 %bop_ltarg_loaded, %bop_rtarg_loaded
  store i32 %bop_smul_loaded, i32* %bop_res
  %chain_result_loaded = load i32, i32* %bop_res
  store i32 %chain_result_loaded, i32* %chain_result
  %cast_si = alloca i32
  %cast_si_input_loaded = load i32, i32* %chain_result
  store i32 %cast_si_input_loaded, i32* %cast_si
  %loaded_for_return = load i32, i32* %cast_si
  ret i32 %loaded_for_return
}

define i32 @triple(i32 %0) {
entry:
  %"arg:0-x" = alloca i32
  store i32 %0, i32* %"arg:0-x"
  %chain_result = alloca i32
  %intl = alloca i32
  store i32 3, i32* %intl
  %bop_ltarg_loaded = load i32, i32* %intl
  %bop_rtarg_loaded = load i32, i32* %"arg:0-x"
  %bop_res = alloca i32
  %bop_smul_loaded = mul i32 %bop_ltarg_loaded, %bop_rtarg_loaded
  store i32 %bop_smul_loaded, i32* %bop_res
  %chain_result_loaded = load i32, i32* %bop_res
  store i32 %chain_result_loaded, i32* %chain_result
  %cast_si = alloca i32
  %cast_si_input_loaded = load i32, i32* %chain_result
  store i32 %cast_si_input_loaded, i32* %cast_si
  %loaded_for_return = load i32, i32* %cast_si
  ret i32 %loaded_for_return
}

define i32 @dot(i32 %0, i32 %1) {
entry:
  %"arg:0-x" = alloca i32
  store i32 %0, i32* %"arg:0-x"
  %"arg:1-y" = alloca i32
  store i32 %1, i32* %"arg:1-y"
  %chain_result = alloca i32
  %bop_ltarg_loaded = load i32, i32* %"arg:0-x"
  %bop_rtarg_loaded = load i32, i32* %"arg:0-x"
  %bop_res = alloca i32
  %bop_smul_loaded = mul i32 %bop_ltarg_loaded, %bop_rtarg_loaded
  store i32 %bop_smul_loaded, i32* %bop_res
  %bop_ltarg_loaded1 = load i32, i32* %"arg:1-y"
  %bop_rtarg_loaded2 = load i32, i32* %"arg:1-y"
  %bop_res3 = alloca i32
  %bop_smul_loaded4 = mul i32 %bop_ltarg_loaded1, %bop_rtarg_loaded2
  store i32 %bop_smul_loaded4, i32* %bop_res3
  %bop_ltarg_loaded5 = load i32, i32* %bop_res
  %bop_rtarg_loaded6 = load i32, i32* %bop_res3
  %bop_res7 = alloca i32
  %bop_sadd_loaded = add i32 %bop_ltarg_loaded5, %bop_rtarg_loaded6
  store i32 %bop_sadd_loaded, i32* %bop_res7
  %chain_result_loaded = load i32, i32* %bop_res7
  store i32 %chain_result_loaded, i32* %chain_result
  %cast_si = alloca i32
  %cast_si_input_loaded = load i32, i32* %chain_result
  store i32 %cast_si_input_loaded, i32* %cast_si
  %loaded_for_return = load i32, i32* %cast_si
  ret i32 %loaded_for_return
}

define i32 @main() {
entry:
  %chain_result = alloca i32
  %intl = alloca i32
  store i32 1024, i32* %intl
  %"let:bufsize" = alloca i64
  %cast_ui_input_loaded = load i32, i32* %intl
  %cast_uext = zext i32 %cast_ui_input_loaded to i64
  store i64 %cast_uext, i64* %"let:bufsize"
  %"let:buffer" = alloca i8*
  %actual_0_0_loaded = load i64, i64* %"let:bufsize"
  %call_value = call i8* @malloc(i64 %actual_0_0_loaded)
  store i8* %call_value, i8** %"let:buffer"
  %call_alloca = alloca i32
  %intl1 = alloca i32
  store i32 3, i32* %intl1
  %actual_0_0_loaded2 = load i32, i32* %intl1
  %intl3 = alloca i32
  store i32 2, i32* %intl3
  %actual_1_1_loaded = load i32, i32* %intl3
  %call_value4 = call i32 @dot(i32 %actual_0_0_loaded2, i32 %actual_1_1_loaded)
  store i32 %call_value4, i32* %call_alloca
  %chain_result_loaded = load i32, i32* %call_alloca
  store i32 %chain_result_loaded, i32* %chain_result
  %cast_si = alloca i32
  %cast_si_input_loaded = load i32, i32* %chain_result
  store i32 %cast_si_input_loaded, i32* %cast_si
  %loaded_for_return = load i32, i32* %cast_si
  ret i32 %loaded_for_return
}