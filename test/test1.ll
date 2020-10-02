; ModuleID = 'testmodule'
source_filename = "testmodule"

define i64 @fibonacci(i64 %0) {
entry:
  br label %ite-entry

ite-entry:                                        ; preds = %entry
  %eq = icmp eq i64 %0, 0
  br i1 %eq, label %ite-true, label %ite-false

ite-true:                                         ; preds = %ite-entry
  br label %ite-landing

ite-false:                                        ; preds = %ite-entry
  br label %ite-entry1

ite-landing:                                      ; preds = %ite-landing4, %ite-true
  %ite-result8 = phi i64 [ 0, %ite-true ], [ %ite-result, %ite-landing4 ]
  ret i64 %ite-result8

ite-entry1:                                       ; preds = %ite-false
  %eq5 = icmp eq i64 %0, 1
  br i1 %eq5, label %ite-true2, label %ite-false3

ite-true2:                                        ; preds = %ite-entry1
  br label %ite-landing4

ite-false3:                                       ; preds = %ite-entry1
  %sub = sub i64 %0, 1
  %call = call i64 @fibonacci(i64 %sub)
  %sub6 = sub i64 %0, 2
  %call7 = call i64 @fibonacci(i64 %sub6)
  %sum = add i64 %call, %call7
  br label %ite-landing4

ite-landing4:                                     ; preds = %ite-false3, %ite-true2
  %ite-result = phi i64 [ 1, %ite-true2 ], [ %sum, %ite-false3 ]
  br label %ite-landing
}