#include <stdint.h>
#include <printf.h>

extern uint64_t fibonacci(uint64_t x);

int main() {
    uint64_t n = 1024;
    uint64_t result = fibonacci(n);
    printf("fibonacci(%llu) = %llu\n", n,result);
    return 0;
}