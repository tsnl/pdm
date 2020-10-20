#include <stdint.h>
#include <stdio.h>

// extern uint64_t fibonacci(uint64_t x);
extern int64_t answer();

int main() {
    // uint64_t n = 100;
    // uint64_t result = fibonacci(n);
    int64_t received_answer = answer();
    printf("answer() = %ld\n",received_answer);
    return 0;
}