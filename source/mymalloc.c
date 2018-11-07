#include "mymalloc.h"

#define MALLOC_BUFFER_SIZE 30000
static char malloc_buffer[MALLOC_BUFFER_SIZE];
static size_t mbuffer_idx;

/* dumb malloc replacement without possibility to free. that's
   enough for us here */
void *my_malloc(size_t size)
{
    char *ret = &malloc_buffer[mbuffer_idx];

    if (mbuffer_idx + size > MALLOC_BUFFER_SIZE) {
        return NULL;
    }
    mbuffer_idx += size;
    return ret;
}

void my_free(void *foo)
{
    foo = foo;
}

