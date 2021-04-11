; ModuleID = '/Users/nti/Workshop/Pandemonium/pdm.llvm-emitter-transplant/sandbox/emit-test-1.pd'
source_filename = "/Users/nti/Workshop/Pandemonium/pdm.llvm-emitter-transplant/sandbox/emit-test-1.pd"

define half @pdm_builtin_f16_multiply(half %0, half %1) {
builtin-inline-fn-implementation:
  %return-value = fmul half %0, %1
  ret half %return-value
}

define half @pdm_builtin_f16_divide(half %0, half %1) {
builtin-inline-fn-implementation:
  %return-value = fdiv half %0, %1
  ret half %return-value
}

define half @pdm_builtin_f16_modulo(half %0, half %1) {
builtin-inline-fn-implementation:
  %return-value = frem half %0, %1
  ret half %return-value
}

define half @pdm_builtin_f16_add(half %0, half %1) {
builtin-inline-fn-implementation:
  %return-value = fadd half %0, %1
  ret half %return-value
}

define half @pdm_builtin_f16_subtract(half %0, half %1) {
builtin-inline-fn-implementation:
  %return-value = fsub half %0, %1
  ret half %return-value
}

define float @pdm_builtin_f32_multiply(float %0, float %1) {
builtin-inline-fn-implementation:
  %return-value = fmul float %0, %1
  ret float %return-value
}

define float @pdm_builtin_f32_divide(float %0, float %1) {
builtin-inline-fn-implementation:
  %return-value = fdiv float %0, %1
  ret float %return-value
}

define float @pdm_builtin_f32_modulo(float %0, float %1) {
builtin-inline-fn-implementation:
  %return-value = frem float %0, %1
  ret float %return-value
}

define float @pdm_builtin_f32_add(float %0, float %1) {
builtin-inline-fn-implementation:
  %return-value = fadd float %0, %1
  ret float %return-value
}

define float @pdm_builtin_f32_subtract(float %0, float %1) {
builtin-inline-fn-implementation:
  %return-value = fsub float %0, %1
  ret float %return-value
}

define double @pdm_builtin_f64_multiply(double %0, double %1) {
builtin-inline-fn-implementation:
  %return-value = fmul double %0, %1
  ret double %return-value
}

define double @pdm_builtin_f64_divide(double %0, double %1) {
builtin-inline-fn-implementation:
  %return-value = fdiv double %0, %1
  ret double %return-value
}

define double @pdm_builtin_f64_modulo(double %0, double %1) {
builtin-inline-fn-implementation:
  %return-value = frem double %0, %1
  ret double %return-value
}

define double @pdm_builtin_f64_add(double %0, double %1) {
builtin-inline-fn-implementation:
  %return-value = fadd double %0, %1
  ret double %return-value
}

define double @pdm_builtin_f64_subtract(double %0, double %1) {
builtin-inline-fn-implementation:
  %return-value = fsub double %0, %1
  ret double %return-value
}

define i8 @pdm_builtin_i8_multiply(i8 %0, i8 %1) {
builtin-inline-fn-implementation:
  %return-value = mul i8 %0, %1
  ret i8 %return-value
}

define i8 @pdm_builtin_i8_divide(i8 %0, i8 %1) {
builtin-inline-fn-implementation:
  %return-value = sdiv i8 %0, %1
  ret i8 %return-value
}

define i8 @pdm_builtin_i8_modulo(i8 %0, i8 %1) {
builtin-inline-fn-implementation:
  %return-value = srem i8 %0, %1
  ret i8 %return-value
}

define i8 @pdm_builtin_i8_add(i8 %0, i8 %1) {
builtin-inline-fn-implementation:
  %return-value = add i8 %0, %1
  ret i8 %return-value
}

define i8 @pdm_builtin_i8_subtract(i8 %0, i8 %1) {
builtin-inline-fn-implementation:
  %return-value = sub i8 %0, %1
  ret i8 %return-value
}

define i8 @pdm_builtin_i8_and(i8 %0, i8 %1) {
builtin-inline-fn-implementation:
  %return-value = and i8 %0, %1
  ret i8 %return-value
}

define i8 @pdm_builtin_i8_xor(i8 %0, i8 %1) {
builtin-inline-fn-implementation:
  %return-value = xor i8 %0, %1
  ret i8 %return-value
}

define i8 @pdm_builtin_i8_or(i8 %0, i8 %1) {
builtin-inline-fn-implementation:
  %return-value = or i8 %0, %1
  ret i8 %return-value
}

define i16 @pdm_builtin_i16_multiply(i16 %0, i16 %1) {
builtin-inline-fn-implementation:
  %return-value = mul i16 %0, %1
  ret i16 %return-value
}

define i16 @pdm_builtin_i16_divide(i16 %0, i16 %1) {
builtin-inline-fn-implementation:
  %return-value = sdiv i16 %0, %1
  ret i16 %return-value
}

define i16 @pdm_builtin_i16_modulo(i16 %0, i16 %1) {
builtin-inline-fn-implementation:
  %return-value = srem i16 %0, %1
  ret i16 %return-value
}

define i16 @pdm_builtin_i16_add(i16 %0, i16 %1) {
builtin-inline-fn-implementation:
  %return-value = add i16 %0, %1
  ret i16 %return-value
}

define i16 @pdm_builtin_i16_subtract(i16 %0, i16 %1) {
builtin-inline-fn-implementation:
  %return-value = sub i16 %0, %1
  ret i16 %return-value
}

define i16 @pdm_builtin_i16_and(i16 %0, i16 %1) {
builtin-inline-fn-implementation:
  %return-value = and i16 %0, %1
  ret i16 %return-value
}

define i16 @pdm_builtin_i16_xor(i16 %0, i16 %1) {
builtin-inline-fn-implementation:
  %return-value = xor i16 %0, %1
  ret i16 %return-value
}

define i16 @pdm_builtin_i16_or(i16 %0, i16 %1) {
builtin-inline-fn-implementation:
  %return-value = or i16 %0, %1
  ret i16 %return-value
}

define i32 @pdm_builtin_i32_multiply(i32 %0, i32 %1) {
builtin-inline-fn-implementation:
  %return-value = mul i32 %0, %1
  ret i32 %return-value
}

define i32 @pdm_builtin_i32_divide(i32 %0, i32 %1) {
builtin-inline-fn-implementation:
  %return-value = sdiv i32 %0, %1
  ret i32 %return-value
}

define i32 @pdm_builtin_i32_modulo(i32 %0, i32 %1) {
builtin-inline-fn-implementation:
  %return-value = srem i32 %0, %1
  ret i32 %return-value
}

define i32 @pdm_builtin_i32_add(i32 %0, i32 %1) {
builtin-inline-fn-implementation:
  %return-value = add i32 %0, %1
  ret i32 %return-value
}

define i32 @pdm_builtin_i32_subtract(i32 %0, i32 %1) {
builtin-inline-fn-implementation:
  %return-value = sub i32 %0, %1
  ret i32 %return-value
}

define i32 @pdm_builtin_i32_and(i32 %0, i32 %1) {
builtin-inline-fn-implementation:
  %return-value = and i32 %0, %1
  ret i32 %return-value
}

define i32 @pdm_builtin_i32_xor(i32 %0, i32 %1) {
builtin-inline-fn-implementation:
  %return-value = xor i32 %0, %1
  ret i32 %return-value
}

define i32 @pdm_builtin_i32_or(i32 %0, i32 %1) {
builtin-inline-fn-implementation:
  %return-value = or i32 %0, %1
  ret i32 %return-value
}

define i64 @pdm_builtin_i64_multiply(i64 %0, i64 %1) {
builtin-inline-fn-implementation:
  %return-value = mul i64 %0, %1
  ret i64 %return-value
}

define i64 @pdm_builtin_i64_divide(i64 %0, i64 %1) {
builtin-inline-fn-implementation:
  %return-value = sdiv i64 %0, %1
  ret i64 %return-value
}

define i64 @pdm_builtin_i64_modulo(i64 %0, i64 %1) {
builtin-inline-fn-implementation:
  %return-value = srem i64 %0, %1
  ret i64 %return-value
}

define i64 @pdm_builtin_i64_add(i64 %0, i64 %1) {
builtin-inline-fn-implementation:
  %return-value = add i64 %0, %1
  ret i64 %return-value
}

define i64 @pdm_builtin_i64_subtract(i64 %0, i64 %1) {
builtin-inline-fn-implementation:
  %return-value = sub i64 %0, %1
  ret i64 %return-value
}

define i64 @pdm_builtin_i64_and(i64 %0, i64 %1) {
builtin-inline-fn-implementation:
  %return-value = and i64 %0, %1
  ret i64 %return-value
}

define i64 @pdm_builtin_i64_xor(i64 %0, i64 %1) {
builtin-inline-fn-implementation:
  %return-value = xor i64 %0, %1
  ret i64 %return-value
}

define i64 @pdm_builtin_i64_or(i64 %0, i64 %1) {
builtin-inline-fn-implementation:
  %return-value = or i64 %0, %1
  ret i64 %return-value
}

define i128 @pdm_builtin_i128_multiply(i128 %0, i128 %1) {
builtin-inline-fn-implementation:
  %return-value = mul i128 %0, %1
  ret i128 %return-value
}

define i128 @pdm_builtin_i128_divide(i128 %0, i128 %1) {
builtin-inline-fn-implementation:
  %return-value = sdiv i128 %0, %1
  ret i128 %return-value
}

define i128 @pdm_builtin_i128_modulo(i128 %0, i128 %1) {
builtin-inline-fn-implementation:
  %return-value = srem i128 %0, %1
  ret i128 %return-value
}

define i128 @pdm_builtin_i128_add(i128 %0, i128 %1) {
builtin-inline-fn-implementation:
  %return-value = add i128 %0, %1
  ret i128 %return-value
}

define i128 @pdm_builtin_i128_subtract(i128 %0, i128 %1) {
builtin-inline-fn-implementation:
  %return-value = sub i128 %0, %1
  ret i128 %return-value
}

define i128 @pdm_builtin_i128_and(i128 %0, i128 %1) {
builtin-inline-fn-implementation:
  %return-value = and i128 %0, %1
  ret i128 %return-value
}

define i128 @pdm_builtin_i128_xor(i128 %0, i128 %1) {
builtin-inline-fn-implementation:
  %return-value = xor i128 %0, %1
  ret i128 %return-value
}

define i128 @pdm_builtin_i128_or(i128 %0, i128 %1) {
builtin-inline-fn-implementation:
  %return-value = or i128 %0, %1
  ret i128 %return-value
}

define i8 @pdm_builtin_u1_multiply(i8 %0, i8 %1) {
builtin-inline-fn-implementation:
  %return-value = mul i8 %0, %1
  ret i8 %return-value
}

define i8 @pdm_builtin_u1_divide(i8 %0, i8 %1) {
builtin-inline-fn-implementation:
  %return-value = udiv i8 %0, %1
  ret i8 %return-value
}

define i8 @pdm_builtin_u1_modulo(i8 %0, i8 %1) {
builtin-inline-fn-implementation:
  %return-value = urem i8 %0, %1
  ret i8 %return-value
}

define i8 @pdm_builtin_u1_add(i8 %0, i8 %1) {
builtin-inline-fn-implementation:
  %return-value = add i8 %0, %1
  ret i8 %return-value
}

define i8 @pdm_builtin_u1_subtract(i8 %0, i8 %1) {
builtin-inline-fn-implementation:
  %return-value = sub i8 %0, %1
  ret i8 %return-value
}

define i8 @pdm_builtin_u1_and(i8 %0, i8 %1) {
builtin-inline-fn-implementation:
  %return-value = and i8 %0, %1
  ret i8 %return-value
}

define i8 @pdm_builtin_u1_xor(i8 %0, i8 %1) {
builtin-inline-fn-implementation:
  %return-value = xor i8 %0, %1
  ret i8 %return-value
}

define i8 @pdm_builtin_u1_or(i8 %0, i8 %1) {
builtin-inline-fn-implementation:
  %return-value = or i8 %0, %1
  ret i8 %return-value
}

define i8 @pdm_builtin_u8_multiply(i8 %0, i8 %1) {
builtin-inline-fn-implementation:
  %return-value = mul i8 %0, %1
  ret i8 %return-value
}

define i8 @pdm_builtin_u8_divide(i8 %0, i8 %1) {
builtin-inline-fn-implementation:
  %return-value = udiv i8 %0, %1
  ret i8 %return-value
}

define i8 @pdm_builtin_u8_modulo(i8 %0, i8 %1) {
builtin-inline-fn-implementation:
  %return-value = urem i8 %0, %1
  ret i8 %return-value
}

define i8 @pdm_builtin_u8_add(i8 %0, i8 %1) {
builtin-inline-fn-implementation:
  %return-value = add i8 %0, %1
  ret i8 %return-value
}

define i8 @pdm_builtin_u8_subtract(i8 %0, i8 %1) {
builtin-inline-fn-implementation:
  %return-value = sub i8 %0, %1
  ret i8 %return-value
}

define i8 @pdm_builtin_u8_and(i8 %0, i8 %1) {
builtin-inline-fn-implementation:
  %return-value = and i8 %0, %1
  ret i8 %return-value
}

define i8 @pdm_builtin_u8_xor(i8 %0, i8 %1) {
builtin-inline-fn-implementation:
  %return-value = xor i8 %0, %1
  ret i8 %return-value
}

define i8 @pdm_builtin_u8_or(i8 %0, i8 %1) {
builtin-inline-fn-implementation:
  %return-value = or i8 %0, %1
  ret i8 %return-value
}

define i16 @pdm_builtin_u16_multiply(i16 %0, i16 %1) {
builtin-inline-fn-implementation:
  %return-value = mul i16 %0, %1
  ret i16 %return-value
}

define i16 @pdm_builtin_u16_divide(i16 %0, i16 %1) {
builtin-inline-fn-implementation:
  %return-value = udiv i16 %0, %1
  ret i16 %return-value
}

define i16 @pdm_builtin_u16_modulo(i16 %0, i16 %1) {
builtin-inline-fn-implementation:
  %return-value = urem i16 %0, %1
  ret i16 %return-value
}

define i16 @pdm_builtin_u16_add(i16 %0, i16 %1) {
builtin-inline-fn-implementation:
  %return-value = add i16 %0, %1
  ret i16 %return-value
}

define i16 @pdm_builtin_u16_subtract(i16 %0, i16 %1) {
builtin-inline-fn-implementation:
  %return-value = sub i16 %0, %1
  ret i16 %return-value
}

define i16 @pdm_builtin_u16_and(i16 %0, i16 %1) {
builtin-inline-fn-implementation:
  %return-value = and i16 %0, %1
  ret i16 %return-value
}

define i16 @pdm_builtin_u16_xor(i16 %0, i16 %1) {
builtin-inline-fn-implementation:
  %return-value = xor i16 %0, %1
  ret i16 %return-value
}

define i16 @pdm_builtin_u16_or(i16 %0, i16 %1) {
builtin-inline-fn-implementation:
  %return-value = or i16 %0, %1
  ret i16 %return-value
}

define i32 @pdm_builtin_u32_multiply(i32 %0, i32 %1) {
builtin-inline-fn-implementation:
  %return-value = mul i32 %0, %1
  ret i32 %return-value
}

define i32 @pdm_builtin_u32_divide(i32 %0, i32 %1) {
builtin-inline-fn-implementation:
  %return-value = udiv i32 %0, %1
  ret i32 %return-value
}

define i32 @pdm_builtin_u32_modulo(i32 %0, i32 %1) {
builtin-inline-fn-implementation:
  %return-value = urem i32 %0, %1
  ret i32 %return-value
}

define i32 @pdm_builtin_u32_add(i32 %0, i32 %1) {
builtin-inline-fn-implementation:
  %return-value = add i32 %0, %1
  ret i32 %return-value
}

define i32 @pdm_builtin_u32_subtract(i32 %0, i32 %1) {
builtin-inline-fn-implementation:
  %return-value = sub i32 %0, %1
  ret i32 %return-value
}

define i32 @pdm_builtin_u32_and(i32 %0, i32 %1) {
builtin-inline-fn-implementation:
  %return-value = and i32 %0, %1
  ret i32 %return-value
}

define i32 @pdm_builtin_u32_xor(i32 %0, i32 %1) {
builtin-inline-fn-implementation:
  %return-value = xor i32 %0, %1
  ret i32 %return-value
}

define i32 @pdm_builtin_u32_or(i32 %0, i32 %1) {
builtin-inline-fn-implementation:
  %return-value = or i32 %0, %1
  ret i32 %return-value
}

define i64 @pdm_builtin_u64_multiply(i64 %0, i64 %1) {
builtin-inline-fn-implementation:
  %return-value = mul i64 %0, %1
  ret i64 %return-value
}

define i64 @pdm_builtin_u64_divide(i64 %0, i64 %1) {
builtin-inline-fn-implementation:
  %return-value = udiv i64 %0, %1
  ret i64 %return-value
}

define i64 @pdm_builtin_u64_modulo(i64 %0, i64 %1) {
builtin-inline-fn-implementation:
  %return-value = urem i64 %0, %1
  ret i64 %return-value
}

define i64 @pdm_builtin_u64_add(i64 %0, i64 %1) {
builtin-inline-fn-implementation:
  %return-value = add i64 %0, %1
  ret i64 %return-value
}

define i64 @pdm_builtin_u64_subtract(i64 %0, i64 %1) {
builtin-inline-fn-implementation:
  %return-value = sub i64 %0, %1
  ret i64 %return-value
}

define i64 @pdm_builtin_u64_and(i64 %0, i64 %1) {
builtin-inline-fn-implementation:
  %return-value = and i64 %0, %1
  ret i64 %return-value
}

define i64 @pdm_builtin_u64_xor(i64 %0, i64 %1) {
builtin-inline-fn-implementation:
  %return-value = xor i64 %0, %1
  ret i64 %return-value
}

define i64 @pdm_builtin_u64_or(i64 %0, i64 %1) {
builtin-inline-fn-implementation:
  %return-value = or i64 %0, %1
  ret i64 %return-value
}

define i128 @pdm_builtin_u128_multiply(i128 %0, i128 %1) {
builtin-inline-fn-implementation:
  %return-value = mul i128 %0, %1
  ret i128 %return-value
}

define i128 @pdm_builtin_u128_divide(i128 %0, i128 %1) {
builtin-inline-fn-implementation:
  %return-value = udiv i128 %0, %1
  ret i128 %return-value
}

define i128 @pdm_builtin_u128_modulo(i128 %0, i128 %1) {
builtin-inline-fn-implementation:
  %return-value = urem i128 %0, %1
  ret i128 %return-value
}

define i128 @pdm_builtin_u128_add(i128 %0, i128 %1) {
builtin-inline-fn-implementation:
  %return-value = add i128 %0, %1
  ret i128 %return-value
}

define i128 @pdm_builtin_u128_subtract(i128 %0, i128 %1) {
builtin-inline-fn-implementation:
  %return-value = sub i128 %0, %1
  ret i128 %return-value
}

define i128 @pdm_builtin_u128_and(i128 %0, i128 %1) {
builtin-inline-fn-implementation:
  %return-value = and i128 %0, %1
  ret i128 %return-value
}

define i128 @pdm_builtin_u128_xor(i128 %0, i128 %1) {
builtin-inline-fn-implementation:
  %return-value = xor i128 %0, %1
  ret i128 %return-value
}

define i128 @pdm_builtin_u128_or(i128 %0, i128 %1) {
builtin-inline-fn-implementation:
  %return-value = or i128 %0, %1
  ret i128 %return-value
}

define i32 @"root_$_entry_point_$_entry_point_without_args"() {
fn_entry_point:
  ret i32 0
}

define i32 @"root_$_module_$_test1"(i32 %0, i32* %1) {
fn_entry_point:
  %"dim-ptr[arg-in]:x" = alloca i32, align 4
  store i32 %0, i32* %"dim-ptr[arg-in]:x", align 4
  %"loaded:x" = load i32, i32* %"dim-ptr[arg-in]:x", align 4
  %"dim-ptr[var]:variable" = alloca i32, align 4
  store i32 %"loaded:x", i32* %"dim-ptr[var]:variable", align 4
  store i32 42, i32* %"dim-ptr[var]:variable", align 4
  store i32 21, i32* %1, align 4
  %"loaded:y" = load i32, i32* %1, align 4
  ret i32 %"loaded:y"
}

define i32 @"root_$_module_$_main"() {
fn_entry_point:
  %"dim-ptr[var]:foo" = alloca i64, align 8
  store i64 0, i64* %"dim-ptr[var]:foo", align 4
  %"dim-ptr[var]:baz" = alloca i64, align 8
  store i64 1, i64* %"dim-ptr[var]:baz", align 4
  %"dim-ptr[var]:bar" = alloca i32, align 4
  store i32 10, i32* %"dim-ptr[var]:bar", align 4
  %"loaded:bar" = load i32, i32* %"dim-ptr[var]:bar", align 4
  ret i32 %"loaded:bar"
}
