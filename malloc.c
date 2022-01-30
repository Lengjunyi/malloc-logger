
#define _GNU_SOURCE

#include <malloc.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/mman.h>

void *malloc(size_t size) {
    static void *(*real_malloc)(size_t);
    static bool loading = false;
    static size_t total_allocation = 0;

    if (loading) {
        return mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, 0, 0);
    }
    else if (!real_malloc) {
        loading = true;
        real_malloc = (void * (*)(size_t))dlsym(RTLD_NEXT, "malloc");
        loading = false;
    }
    
    total_allocation += size;
    fprintf(stderr, "Total bytes allocated so far: %ld\n", total_allocation);

    return (*real_malloc)(size);
}

