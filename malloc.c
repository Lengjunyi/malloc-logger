
#define _GNU_SOURCE

#include <malloc.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/mman.h>

void *malloc(size_t size) {
    static void *(*real_malloc)(size_t);
    static bool loading = false;
    fprintf(stderr, "%ld %d\n", size, loading);

    if (loading) {
        return mmap(NULL, size, PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS, 0, 0);;
    }
    else if (!real_malloc) {
        loading = true;
        real_malloc = (void * (*)(size_t))dlsym(RTLD_NEXT, "malloc");
        fprintf(stderr, "returning from dlsym\n");
        loading = false;
    }
    
    return (*real_malloc)(size);
}

