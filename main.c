#include <stdio.h>
#include <stdint.h>
#include "bigsmall-alloc.h"

int main(void) {
    small_allocator_init();
    big_allocator_init();

    void* x1 = small_malloc();
    void* x2 = small_malloc();
    void* y1 = big_malloc();

    printf("x1 = %p\n", x1);
    printf("x2 = %p\n", x2);
    printf("y1 = %p\n", y1);

    bigsmall_free(x1);
    bigsmall_free(x2);
    bigsmall_free(y1);

    void* x3 = small_malloc();
    printf("x3 = %p\n", x3);
    bigsmall_free(x3);

    return 0;
}