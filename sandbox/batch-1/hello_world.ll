; ModuleID = 'hub-test'
source_filename = "hub-test"

declare i8* @malloc(i64 %0)

declare i32 @puts(i8* %0)

define i32 @simple(i32 %0) {
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
  br label %ite_entry_bb2

ite_false_bb:                                     ; preds = %ite_entry_bb
  %chain_result19 = alloca i32
  %intl20 = alloca i32
  store i32 1, i32* %intl20
  %chain_result_loaded21 = load i32, i32* %intl20
  store i32 %chain_result_loaded21, i32* %chain_result19
  %if_false_loaded22 = load i32, i32* %chain_result19
  br label %ite_landing_bb

ite_landing_bb:                                   ; preds = %ite_false_bb, %ite_landing_bb5
  %ite_result_loaded23 = phi i32 [ %if_true_loaded18, %ite_landing_bb5 ], [ %if_false_loaded22, %ite_false_bb ]
  %ite_result24 = alloca i32
  store i32 %ite_result_loaded23, i32* %ite_result24
  %chain_result_loaded25 = load i32, i32* %ite_result24
  store i32 %chain_result_loaded25, i32* %chain_result
  %cast_si = alloca i32
  %cast_si_input_loaded = load i32, i32* %chain_result
  store i32 %cast_si_input_loaded, i32* %cast_si
  %loaded_for_return = load i32, i32* %cast_si
  ret i32 %loaded_for_return

ite_entry_bb2:                                    ; preds = %ite_true_bb
  %intl6 = alloca i32
  store i32 1, i32* %intl6
  %bop_ltarg_loaded7 = load i32, i32* %"arg:0-n"
  %bop_rtarg_loaded8 = load i32, i32* %intl6
  %bop_res9 = alloca i1
  %bop_ueq_loaded10 = icmp eq i32 %bop_ltarg_loaded7, %bop_rtarg_loaded8
  store i1 %bop_ueq_loaded10, i1* %bop_res9
  %ite_cond_loaded11 = load i1, i1* %bop_res9
  br i1 %ite_cond_loaded11, label %ite_true_bb3, label %ite_false_bb4

ite_true_bb3:                                     ; preds = %ite_entry_bb2
  %chain_result12 = alloca i32
  %intl13 = alloca i32
  store i32 1, i32* %intl13
  %chain_result_loaded = load i32, i32* %intl13
  store i32 %chain_result_loaded, i32* %chain_result12
  %if_true_loaded = load i32, i32* %chain_result12
  br label %ite_landing_bb5

ite_false_bb4:                                    ; preds = %ite_entry_bb2
  %chain_result14 = alloca i32
  %intl15 = alloca i32
  store i32 0, i32* %intl15
  %chain_result_loaded16 = load i32, i32* %intl15
  store i32 %chain_result_loaded16, i32* %chain_result14
  %if_false_loaded = load i32, i32* %chain_result14
  br label %ite_landing_bb5

ite_landing_bb5:                                  ; preds = %ite_false_bb4, %ite_true_bb3
  %ite_result_loaded = phi i32 [ %if_true_loaded, %ite_true_bb3 ], [ %if_false_loaded, %ite_false_bb4 ]
  %ite_result = alloca i32
  store i32 %ite_result_loaded, i32* %ite_result
  %chain_result_loaded17 = load i32, i32* %ite_result
  store i32 %chain_result_loaded17, i32* %chain_result1
  %if_true_loaded18 = load i32, i32* %chain_result1
  br label %ite_landing_bb
}