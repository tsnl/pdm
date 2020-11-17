#include <stdio.h>
#include <stdint.h>

void print___string(char const* string) {
    printf("%s", string);
}

void print___s32(int32_t s32) {
    printf("%d", s32);
}

void print___f32(float f32) {
    printf("%f", f32);
}

void print___line() {
    printf("\n");
}
