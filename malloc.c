
#define _GNU_SOURCE

#include <malloc.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/mman.h>

void *malloc(size_t size) {
    static void *(*real_malloc)(size_t);
    static size_t total_allocation = 0;

    if (!real_malloc) {
        real_malloc = (void * (*)(size_t))dlsym(RTLD_NEXT, "malloc");
    }
    
    total_allocation += size;
    fprintf(stderr, "Total bytes allocated so far: %ld\n", total_allocation);

    return (*real_malloc)(size);
}

