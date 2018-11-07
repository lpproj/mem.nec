#ifndef MYMALLOC_H
#define MYMALLOC_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

void *my_malloc(size_t size);
void my_free(void *foo);
#define my_calloc(nitems,size) (my_malloc((nitems) * (size)))


#ifdef __cplusplus
}
#endif

#define malloc(s)  my_malloc(s)
#define free(p) my_free(p)
#define calloc(n,s) my_calloc(n,s)

#endif

