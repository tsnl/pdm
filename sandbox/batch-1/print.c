#include <stdio.h>
#include <stdint.h>

void print_string(char const* string) {
    printf("%s", string);
}

void print_s32(int32_t s32) {
    printf("%d", s32);
}

void print_f32(float f32) {
    printf("%f", f32);
}

void print_line() {
    printf("\n");
}
