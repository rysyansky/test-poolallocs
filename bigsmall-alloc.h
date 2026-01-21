#pragma once

void small_allocator_init();
void big_allocator_init();
void* small_malloc();
void* big_malloc();
void bigsmall_free(void*);