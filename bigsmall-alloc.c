#include <stddef.h>
#include <stdint.h>

/* [SETTINGS] */
#define SMALL_BLOCK         15
#define BIG_BLOCK           180

#define SMALL_COUNT         8
#define BIG_COUNT           4

/* [SYSTEMIC ALIGNMENT MACROS] */
#define ALIGN               sizeof(void*)
#define MIN_NEAR            (ALIGN - 1)
#define BIT_MASK            ~(MIN_NEAR)
#define SYS_ROUND_UP(x)     ((x + MIN_NEAR) & BIT_MASK)

/* [CHUNK STRUCT] */
typedef struct Chunk{
    struct Chunk *next;
}Chunk;

/* [REAL SIZES COUNT] */
#define REAL_SMALL_BLOCK    SYS_ROUND_UP(SMALL_BLOCK)
#define REAL_BIG_BLOCK      SYS_ROUND_UP(BIG_BLOCK)

#define SMALL_CHUNK         SYS_ROUND_UP(sizeof(Chunk) + REAL_SMALL_BLOCK)
#define BIG_CHUNK           SYS_ROUND_UP(sizeof(Chunk) + REAL_BIG_BLOCK)

/* [STATIC POOL VARIABLES] */
static uint8_t small_pool[SMALL_COUNT][SMALL_CHUNK];
static uint8_t big_pool[BIG_COUNT][BIG_CHUNK];

/* [CHUNK HEADS] */
static Chunk* small_free = NULL;
static Chunk* big_free = NULL;

/* [ALLOCATORS] */
void small_allocator_init() {
    for (unsigned int i = 0; i < SMALL_COUNT; i++) {
        Chunk* c = (Chunk*)small_pool[i];
        c->next = small_free;
        small_free = c;
    }
}
void big_allocator_init() {
    for (unsigned int i = 0; i < BIG_COUNT; i++) {
        Chunk* c = (Chunk*)big_pool[i];
        c->next = big_free;
        big_free = c;
    }
}

/* [MALLOCS] */
void* small_malloc() {
    if(!small_free) return NULL;

    Chunk* c = small_free;
    small_free = c->next;

    return c + 1;
}

void* big_malloc() {
    if(!big_free) return NULL;
    
    Chunk* c = big_free;
    big_free = c->next;

    return c + 1;
}

/* [FREEERS] */
void bigsmall_free(void* bs) {
    Chunk* c = ((Chunk*)bs) - 1;

    if ((uint8_t*)c >= (uint8_t*)small_pool && (uint8_t*)c < (uint8_t*)small_pool + sizeof(small_pool)) {
        c->next = small_free;
        small_free = c;
        return;
    }

    if ((uint8_t*)c >= (uint8_t*)big_pool && (uint8_t*)c < (uint8_t*)big_pool + sizeof(big_pool)) {
        c->next = big_free;
        big_free = c;
        return;
    }
}