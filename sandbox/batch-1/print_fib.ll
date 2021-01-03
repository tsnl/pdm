; ModuleID = 'hub-test'
source_filename = "hub-test"

@literal_string = internal constant [11 x i8] c"fibonacci(\00"
@literal_string.1 = internal constant [5 x i8] c") = \00"
@literal_string.2 = internal constant [25 x i8] c"FIBONACCI PRINTER until \00"

declare i8* @malloc(i64 %0)

declare i32 @puts(i8* %0)

declare void @print_string(i8* %0)

declare void @print_s32(i32 %0)

declare void @println()

define i32 @fib(i32 %0) {
entry:
  %"arg:0-n" = alloca i32
  store i32 %0, i32* %"arg:0-n"
  %chain_result = alloca i32
  br label %ite_entry_bb

ite_entry_bb:                                     ; preds = %entry
  %intl = alloca i32
  store i32 0, i32* %intl
  %bop_ltarg_loaded = load i32, i32* %"arg:0-n"
  %bop_rtarg_loaded = load i32, i32* %intl
  %bop_res = alloca i1
  %bop_ueq_loaded = icmp eq i32 %bop_ltarg_loaded, %bop_rtarg_loaded
  store i1 %bop_ueq_loaded, i1* %bop_res
  %ite_cond_loaded = load i1, i1* %bop_res
  br i1 %ite_cond_loaded, label %ite_true_bb, label %ite_false_bb

ite_true_bb:                                      ; preds = %ite_entry_bb
  %chain_result1 = alloca i32
  %intl2 = alloca i32
  store i32 0, i32* %intl2
  %chain_result_loaded = load i32, i32* %intl2
  store i32 %chain_result_loaded, i32* %chain_result1
  %if_true_loaded = load i32, i32* %chain_result1
  br label %ite_landing_bb

ite_false_bb:                                     ; preds = %ite_entry_bb
  %chain_result3 = alloca i32
  br label %ite_entry_bb4

ite_landing_bb:                                   ; preds = %ite_landing_bb7, %ite_true_bb
  %ite_result_loaded37 = phi i32 [ %if_true_loaded, %ite_true_bb ], [ %if_false_loaded36, %ite_landing_bb7 ]
  %ite_result38 = alloca i32
  store i32 %ite_result_loaded37, i32* %ite_result38
  %chain_result_loaded39 = load i32, i32* %ite_result38
  store i32 %chain_result_loaded39, i32* %chain_result
  %cast_si = alloca i32
  %cast_si_input_loaded = load i32, i32* %chain_result
  store i32 %cast_si_input_loaded, i32* %cast_si
  %loaded_for_return = load i32, i32* %cast_si
  ret i32 %loaded_for_return

ite_entry_bb4:                                    ; preds = %ite_false_bb
  %intl8 = alloca i32
  store i32 1, i32* %intl8
  %bop_ltarg_loaded9 = load i32, i32* %"arg:0-n"
  %bop_rtarg_loaded10 = load i32, i32* %intl8
  %bop_res11 = alloca i1
  %bop_ueq_loaded12 = icmp eq i32 %bop_ltarg_loaded9, %bop_rtarg_loaded10
  store i1 %bop_ueq_loaded12, i1* %bop_res11
  %ite_cond_loaded13 = load i1, i1* %bop_res11
  br i1 %ite_cond_loaded13, label %ite_true_bb5, label %ite_false_bb6

ite_true_bb5:                                     ; preds = %ite_entry_bb4
  %chain_result14 = alloca i32
  %intl15 = alloca i32
  store i32 1, i32* %intl15
  %chain_result_loaded16 = load i32, i32* %intl15
  store i32 %chain_result_loaded16, i32* %chain_result14
  %if_true_loaded17 = load i32, i32* %chain_result14
  br label %ite_landing_bb7

ite_false_bb6:                                    ; preds = %ite_entry_bb4
  %chain_result18 = alloca i32
  %call_res = alloca i32
  %intl19 = alloca i32
  store i32 1, i32* %intl19
  %bop_ltarg_loaded20 = load i32, i32* %"arg:0-n"
  %bop_rtarg_loaded21 = load i32, i32* %intl19
  %bop_res22 = alloca i32
  %bop_ssubtract_loaded = sub i32 %bop_ltarg_loaded20, %bop_rtarg_loaded21
  store i32 %bop_ssubtract_loaded, i32* %bop_res22
  %actual_0_0_loaded = load i32, i32* %bop_res22
  %call_value = call i32 @fib(i32 %actual_0_0_loaded)
  store i32 %call_value, i32* %call_res
  %call_res23 = alloca i32
  %intl24 = alloca i32
  store i32 2, i32* %intl24
  %bop_ltarg_loaded25 = load i32, i32* %"arg:0-n"
  %bop_rtarg_loaded26 = load i32, i32* %intl24
  %bop_res27 = alloca i32
  %bop_ssubtract_loaded28 = sub i32 %bop_ltarg_loaded25, %bop_rtarg_loaded26
  store i32 %bop_ssubtract_loaded28, i32* %bop_res27
  %actual_0_0_loaded29 = load i32, i32* %bop_res27
  %call_value30 = call i32 @fib(i32 %actual_0_0_loaded29)
  store i32 %call_value30, i32* %call_res23
  %bop_ltarg_loaded31 = load i32, i32* %call_res
  %bop_rtarg_loaded32 = load i32, i32* %call_res23
  %bop_res33 = alloca i32
  %bop_sadd_loaded = add i32 %bop_ltarg_loaded31, %bop_rtarg_loaded32
  store i32 %bop_sadd_loaded, i32* %bop_res33
  %chain_result_loaded34 = load i32, i32* %bop_res33
  store i32 %chain_result_loaded34, i32* %chain_result18
  %if_false_loaded = load i32, i32* %chain_result18
  br label %ite_landing_bb7

ite_landing_bb7:                                  ; preds = %ite_false_bb6, %ite_true_bb5
  %ite_result_loaded = phi i32 [ %if_true_loaded17, %ite_true_bb5 ], [ %if_false_loaded, %ite_false_bb6 ]
  %ite_result = alloca i32
  store i32 %ite_result_loaded, i32* %ite_result
  %chain_result_loaded35 = load i32, i32* %ite_result
  store i32 %chain_result_loaded35, i32* %chain_result3
  %if_false_loaded36 = load i32, i32* %chain_result3
  br label %ite_landing_bb
}

define void @print_fibonacci_table_until(i32 %0, i1 %1) {
entry:
  %"arg:0-n" = alloca i32
  store i32 %0, i32* %"arg:0-n"
  %"arg:1-ascend_not_descend" = alloca i1
  store i1 %1, i1* %"arg:1-ascend_not_descend"
  %"let:result" = alloca i32
  %actual_0_0_loaded = load i32, i32* %"arg:0-n"
  %call_value = call i32 @fib(i32 %actual_0_0_loaded)
  store i32 %call_value, i32* %"let:result"
  br label %ite_entry_bb

ite_entry_bb:                                     ; preds = %entry
  %intl = alloca i32
  store i32 0, i32* %intl
  %bop_ltarg_loaded = load i32, i32* %"arg:0-n"
  %bop_rtarg_loaded = load i32, i32* %intl
  %bop_res = alloca i1
  %bop_uneq_loaded = icmp ne i32 %bop_ltarg_loaded, %bop_rtarg_loaded
  store i1 %bop_uneq_loaded, i1* %bop_res
  %ite_cond_loaded = load i1, i1* %bop_res
  br i1 %ite_cond_loaded, label %ite_true_bb, label %ite_false_bb

ite_true_bb:                                      ; preds = %ite_entry_bb
  br label %ite_entry_bb1

ite_false_bb:                                     ; preds = %ite_entry_bb
  br label %ite_landing_bb

ite_landing_bb:                                   ; preds = %ite_false_bb, %ite_landing_bb22
  ret void

ite_entry_bb1:                                    ; preds = %ite_true_bb
  %ite_cond_loaded5 = load i1, i1* %"arg:1-ascend_not_descend"
  br i1 %ite_cond_loaded5, label %ite_true_bb2, label %ite_false_bb3

ite_true_bb2:                                     ; preds = %ite_entry_bb1
  %intl6 = alloca i32
  store i32 1, i32* %intl6
  %bop_ltarg_loaded7 = load i32, i32* %"arg:0-n"
  %bop_rtarg_loaded8 = load i32, i32* %intl6
  %bop_res9 = alloca i32
  %bop_ssubtract_loaded = sub i32 %bop_ltarg_loaded7, %bop_rtarg_loaded8
  store i32 %bop_ssubtract_loaded, i32* %bop_res9
  %actual_0_0_loaded10 = load i32, i32* %bop_res9
  %intl11 = alloca i32
  store i32 1, i32* %intl11
  %cast_ui = alloca i1
  %cast_ui_input_loaded = load i32, i32* %intl11
  %cast_utrunc = trunc i32 %cast_ui_input_loaded to i1
  store i1 %cast_utrunc, i1* %cast_ui
  %actual_1_1_loaded = load i1, i1* %cast_ui
  call void @print_fibonacci_table_until(i32 %actual_0_0_loaded10, i1 %actual_1_1_loaded)
  br label %ite_landing_bb4

ite_false_bb3:                                    ; preds = %ite_entry_bb1
  br label %ite_landing_bb4

ite_landing_bb4:                                  ; preds = %ite_false_bb3, %ite_true_bb2
  %stringliteral = alloca i8*
  store i8* getelementptr inbounds ([11 x i8], [11 x i8]* @literal_string, i32 0, i64 0), i8** %stringliteral
  %actual_0_0_loaded12 = load i8*, i8** %stringliteral
  call void @print_string(i8* %actual_0_0_loaded12)
  %actual_0_0_loaded13 = load i32, i32* %"arg:0-n"
  call void @print_s32(i32 %actual_0_0_loaded13)
  %stringliteral14 = alloca i8*
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @literal_string.1, i32 0, i64 0), i8** %stringliteral14
  %actual_0_0_loaded15 = load i8*, i8** %stringliteral14
  call void @print_string(i8* %actual_0_0_loaded15)
  %call_res = alloca i32
  %actual_0_0_loaded16 = load i32, i32* %"arg:0-n"
  %call_value17 = call i32 @fib(i32 %actual_0_0_loaded16)
  store i32 %call_value17, i32* %call_res
  %actual_0_0_loaded18 = load i32, i32* %call_res
  call void @print_s32(i32 %actual_0_0_loaded18)
  call void @println()
  br label %ite_entry_bb19

ite_entry_bb19:                                   ; preds = %ite_landing_bb4
  %uop_res = alloca i1
  %uop_not_arg_loaded = load i1, i1* %"arg:1-ascend_not_descend"
  %uop_not_res_loaded = xor i1 %uop_not_arg_loaded, true
  store i1 %uop_not_res_loaded, i1* %uop_res
  %ite_cond_loaded23 = load i1, i1* %uop_res
  br i1 %ite_cond_loaded23, label %ite_true_bb20, label %ite_false_bb21

ite_true_bb20:                                    ; preds = %ite_entry_bb19
  %intl24 = alloca i32
  store i32 1, i32* %intl24
  %bop_ltarg_loaded25 = load i32, i32* %"arg:0-n"
  %bop_rtarg_loaded26 = load i32, i32* %intl24
  %bop_res27 = alloca i32
  %bop_ssubtract_loaded28 = sub i32 %bop_ltarg_loaded25, %bop_rtarg_loaded26
  store i32 %bop_ssubtract_loaded28, i32* %bop_res27
  %actual_0_0_loaded29 = load i32, i32* %bop_res27
  %intl30 = alloca i32
  store i32 0, i32* %intl30
  %cast_ui31 = alloca i1
  %cast_ui_input_loaded32 = load i32, i32* %intl30
  %cast_utrunc33 = trunc i32 %cast_ui_input_loaded32 to i1
  store i1 %cast_utrunc33, i1* %cast_ui31
  %actual_1_1_loaded34 = load i1, i1* %cast_ui31
  call void @print_fibonacci_table_until(i32 %actual_0_0_loaded29, i1 %actual_1_1_loaded34)
  br label %ite_landing_bb22

ite_false_bb21:                                   ; preds = %ite_entry_bb19
  br label %ite_landing_bb22

ite_landing_bb22:                                 ; preds = %ite_false_bb21, %ite_true_bb20
  br label %ite_landing_bb
}

define i32 @main() {
entry:
  %chain_result = alloca i32
  %"let:n" = alloca i32
  store i32 40, i32* %"let:n"
  %stringliteral = alloca i8*
  store i8* getelementptr inbounds ([25 x i8], [25 x i8]* @literal_string.2, i32 0, i64 0), i8** %stringliteral
  %actual_0_0_loaded = load i8*, i8** %stringliteral
  call void @print_string(i8* %actual_0_0_loaded)
  %actual_0_0_loaded1 = load i32, i32* %"let:n"
  call void @print_s32(i32 %actual_0_0_loaded1)
  call void @println()
  %actual_0_0_loaded2 = load i32, i32* %"let:n"
  %intl = alloca i32
  store i32 1, i32* %intl
  %cast_ui = alloca i1
  %cast_ui_input_loaded = load i32, i32* %intl
  %cast_utrunc = trunc i32 %cast_ui_input_loaded to i1
  store i1 %cast_utrunc, i1* %cast_ui
  %actual_1_1_loaded = load i1, i1* %cast_ui
  call void @print_fibonacci_table_until(i32 %actual_0_0_loaded2, i1 %actual_1_1_loaded)
  %intl3 = alloca i32
  store i32 0, i32* %intl3
  %chain_result_loaded = load i32, i32* %intl3
  store i32 %chain_result_loaded, i32* %chain_result
  %cast_si = alloca i32
  %cast_si_input_loaded = load i32, i32* %chain_result
  store i32 %cast_si_input_loaded, i32* %cast_si
  %loaded_for_return = load i32, i32* %cast_si
  ret i32 %loaded_for_return
}