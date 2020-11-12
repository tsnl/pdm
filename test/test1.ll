; ModuleID = 'hub-test'
source_filename = "hub-test"

@literal_string = internal constant [14 x i8] c"(x1,y1) = {x=\00"
@literal_string.1 = internal constant [4 x i8] c",y=\00"
@literal_string.2 = internal constant [2 x i8] c"}\00"
@literal_string.3 = internal constant [14 x i8] c"(x2,y2) = {x=\00"
@literal_string.4 = internal constant [4 x i8] c",y=\00"
@literal_string.5 = internal constant [2 x i8] c"}\00"
@literal_string.6 = internal constant [23 x i8] c"subtract_s32(x1,y1) = \00"
@literal_string.7 = internal constant [23 x i8] c"subtract_s32(x2,y2) = \00"
@literal_string.8 = internal constant [18 x i8] c"add_s32(x1,y1) = \00"
@literal_string.9 = internal constant [18 x i8] c"add_s32(x2,y2) = \00"
@literal_string.10 = internal constant [20 x i8] c"dot(x1,y1,x2,y2) = \00"

declare i8* @malloc(i64 %0)

declare i32 @puts(i8* %0)

declare void @print_string(i8* %0)

declare void @print_s32(i32 %0)

declare void @print_f32(float %0)

declare void @println()

define i32 @add_s32(i32 %0, i32 %1) {
entry:
  %"arg:0-x" = alloca i32
  store i32 %0, i32* %"arg:0-x"
  %"arg:1-y" = alloca i32
  store i32 %1, i32* %"arg:1-y"
  %chain_result = alloca i32
  %bop_ltarg_loaded = load i32, i32* %"arg:0-x"
  %bop_rtarg_loaded = load i32, i32* %"arg:1-y"
  %bop_res = alloca i32
  %bop_sadd_loaded = add i32 %bop_ltarg_loaded, %bop_rtarg_loaded
  store i32 %bop_sadd_loaded, i32* %bop_res
  %chain_result_loaded = load i32, i32* %bop_res
  store i32 %chain_result_loaded, i32* %chain_result
  %cast_si = alloca i32
  %cast_si_input_loaded = load i32, i32* %chain_result
  store i32 %cast_si_input_loaded, i32* %cast_si
  %loaded_for_return = load i32, i32* %cast_si
  ret i32 %loaded_for_return
}

define i32 @subtract_s32(i32 %0, i32 %1) {
entry:
  %"arg:0-x" = alloca i32
  store i32 %0, i32* %"arg:0-x"
  %"arg:1-y" = alloca i32
  store i32 %1, i32* %"arg:1-y"
  %chain_result = alloca i32
  %bop_ltarg_loaded = load i32, i32* %"arg:0-x"
  %bop_rtarg_loaded = load i32, i32* %"arg:1-y"
  %bop_res = alloca i32
  %bop_ssubtract_loaded = sub i32 %bop_ltarg_loaded, %bop_rtarg_loaded
  store i32 %bop_ssubtract_loaded, i32* %bop_res
  %chain_result_loaded = load i32, i32* %bop_res
  store i32 %chain_result_loaded, i32* %chain_result
  %cast_si = alloca i32
  %cast_si_input_loaded = load i32, i32* %chain_result
  store i32 %cast_si_input_loaded, i32* %cast_si
  %loaded_for_return = load i32, i32* %cast_si
  ret i32 %loaded_for_return
}

define i32 @dot_s32(i32 %0, i32 %1, i32 %2, i32 %3) {
entry:
  %"arg:0-x1" = alloca i32
  store i32 %0, i32* %"arg:0-x1"
  %"arg:1-y1" = alloca i32
  store i32 %1, i32* %"arg:1-y1"
  %"arg:2-x2" = alloca i32
  store i32 %2, i32* %"arg:2-x2"
  %"arg:3-y2" = alloca i32
  store i32 %3, i32* %"arg:3-y2"
  %chain_result = alloca i32
  %bop_ltarg_loaded = load i32, i32* %"arg:0-x1"
  %bop_rtarg_loaded = load i32, i32* %"arg:2-x2"
  %bop_res = alloca i32
  %bop_smul_loaded = mul i32 %bop_ltarg_loaded, %bop_rtarg_loaded
  store i32 %bop_smul_loaded, i32* %bop_res
  %bop_ltarg_loaded1 = load i32, i32* %"arg:1-y1"
  %bop_rtarg_loaded2 = load i32, i32* %"arg:3-y2"
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
  %"let:x1" = alloca i32
  store i32 42, i32* %"let:x1"
  %"let:y1" = alloca i32
  store i32 56, i32* %"let:y1"
  %"let:x2" = alloca i32
  store i32 0, i32* %"let:x2"
  %"let:y2" = alloca i32
  store i32 64, i32* %"let:y2"
  %stringliteral = alloca i8*
  store i8* getelementptr inbounds ([14 x i8], [14 x i8]* @literal_string, i32 0, i64 0), i8** %stringliteral
  %actual_0_0_loaded = load i8*, i8** %stringliteral
  call void @print_string(i8* %actual_0_0_loaded)
  %actual_0_0_loaded1 = load i32, i32* %"let:x1"
  call void @print_s32(i32 %actual_0_0_loaded1)
  %stringliteral2 = alloca i8*
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @literal_string.1, i32 0, i64 0), i8** %stringliteral2
  %actual_0_0_loaded3 = load i8*, i8** %stringliteral2
  call void @print_string(i8* %actual_0_0_loaded3)
  %actual_0_0_loaded4 = load i32, i32* %"let:y1"
  call void @print_s32(i32 %actual_0_0_loaded4)
  %stringliteral5 = alloca i8*
  store i8* getelementptr inbounds ([2 x i8], [2 x i8]* @literal_string.2, i32 0, i64 0), i8** %stringliteral5
  %actual_0_0_loaded6 = load i8*, i8** %stringliteral5
  call void @print_string(i8* %actual_0_0_loaded6)
  call void @println()
  %stringliteral7 = alloca i8*
  store i8* getelementptr inbounds ([14 x i8], [14 x i8]* @literal_string.3, i32 0, i64 0), i8** %stringliteral7
  %actual_0_0_loaded8 = load i8*, i8** %stringliteral7
  call void @print_string(i8* %actual_0_0_loaded8)
  %actual_0_0_loaded9 = load i32, i32* %"let:x2"
  call void @print_s32(i32 %actual_0_0_loaded9)
  %stringliteral10 = alloca i8*
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @literal_string.4, i32 0, i64 0), i8** %stringliteral10
  %actual_0_0_loaded11 = load i8*, i8** %stringliteral10
  call void @print_string(i8* %actual_0_0_loaded11)
  %actual_0_0_loaded12 = load i32, i32* %"let:y2"
  call void @print_s32(i32 %actual_0_0_loaded12)
  %stringliteral13 = alloca i8*
  store i8* getelementptr inbounds ([2 x i8], [2 x i8]* @literal_string.5, i32 0, i64 0), i8** %stringliteral13
  %actual_0_0_loaded14 = load i8*, i8** %stringliteral13
  call void @print_string(i8* %actual_0_0_loaded14)
  call void @println()
  %stringliteral15 = alloca i8*
  store i8* getelementptr inbounds ([23 x i8], [23 x i8]* @literal_string.6, i32 0, i64 0), i8** %stringliteral15
  %actual_0_0_loaded16 = load i8*, i8** %stringliteral15
  call void @print_string(i8* %actual_0_0_loaded16)
  %call_res = alloca i32
  %actual_0_0_loaded17 = load i32, i32* %"let:x1"
  %actual_1_1_loaded = load i32, i32* %"let:y1"
  %call_value = call i32 @subtract_s32(i32 %actual_0_0_loaded17, i32 %actual_1_1_loaded)
  store i32 %call_value, i32* %call_res
  %actual_0_0_loaded18 = load i32, i32* %call_res
  call void @print_s32(i32 %actual_0_0_loaded18)
  call void @println()
  %stringliteral19 = alloca i8*
  store i8* getelementptr inbounds ([23 x i8], [23 x i8]* @literal_string.7, i32 0, i64 0), i8** %stringliteral19
  %actual_0_0_loaded20 = load i8*, i8** %stringliteral19
  call void @print_string(i8* %actual_0_0_loaded20)
  %call_res21 = alloca i32
  %actual_0_0_loaded22 = load i32, i32* %"let:x2"
  %actual_1_1_loaded23 = load i32, i32* %"let:y2"
  %call_value24 = call i32 @subtract_s32(i32 %actual_0_0_loaded22, i32 %actual_1_1_loaded23)
  store i32 %call_value24, i32* %call_res21
  %actual_0_0_loaded25 = load i32, i32* %call_res21
  call void @print_s32(i32 %actual_0_0_loaded25)
  call void @println()
  %stringliteral26 = alloca i8*
  store i8* getelementptr inbounds ([18 x i8], [18 x i8]* @literal_string.8, i32 0, i64 0), i8** %stringliteral26
  %actual_0_0_loaded27 = load i8*, i8** %stringliteral26
  call void @print_string(i8* %actual_0_0_loaded27)
  %call_res28 = alloca i32
  %actual_0_0_loaded29 = load i32, i32* %"let:x1"
  %actual_1_1_loaded30 = load i32, i32* %"let:y1"
  %call_value31 = call i32 @add_s32(i32 %actual_0_0_loaded29, i32 %actual_1_1_loaded30)
  store i32 %call_value31, i32* %call_res28
  %actual_0_0_loaded32 = load i32, i32* %call_res28
  call void @print_s32(i32 %actual_0_0_loaded32)
  call void @println()
  %stringliteral33 = alloca i8*
  store i8* getelementptr inbounds ([18 x i8], [18 x i8]* @literal_string.9, i32 0, i64 0), i8** %stringliteral33
  %actual_0_0_loaded34 = load i8*, i8** %stringliteral33
  call void @print_string(i8* %actual_0_0_loaded34)
  %call_res35 = alloca i32
  %actual_0_0_loaded36 = load i32, i32* %"let:x2"
  %actual_1_1_loaded37 = load i32, i32* %"let:y2"
  %call_value38 = call i32 @add_s32(i32 %actual_0_0_loaded36, i32 %actual_1_1_loaded37)
  store i32 %call_value38, i32* %call_res35
  %actual_0_0_loaded39 = load i32, i32* %call_res35
  call void @print_s32(i32 %actual_0_0_loaded39)
  call void @println()
  %stringliteral40 = alloca i8*
  store i8* getelementptr inbounds ([20 x i8], [20 x i8]* @literal_string.10, i32 0, i64 0), i8** %stringliteral40
  %actual_0_0_loaded41 = load i8*, i8** %stringliteral40
  call void @print_string(i8* %actual_0_0_loaded41)
  %call_res42 = alloca i32
  %actual_0_0_loaded43 = load i32, i32* %"let:x1"
  %actual_1_1_loaded44 = load i32, i32* %"let:y1"
  %actual_2_2_loaded = load i32, i32* %"let:x2"
  %actual_3_3_loaded = load i32, i32* %"let:y2"
  %call_value45 = call i32 @dot_s32(i32 %actual_0_0_loaded43, i32 %actual_1_1_loaded44, i32 %actual_2_2_loaded, i32 %actual_3_3_loaded)
  store i32 %call_value45, i32* %call_res42
  %actual_0_0_loaded46 = load i32, i32* %call_res42
  call void @print_s32(i32 %actual_0_0_loaded46)
  call void @println()
  %intl = alloca i32
  store i32 0, i32* %intl
  %chain_result_loaded = load i32, i32* %intl
  store i32 %chain_result_loaded, i32* %chain_result
  %cast_si = alloca i32
  %cast_si_input_loaded = load i32, i32* %chain_result
  store i32 %cast_si_input_loaded, i32* %cast_si
  %loaded_for_return = load i32, i32* %cast_si
  ret i32 %loaded_for_return
}