#ifndef LIN_ALLOC_H
#define LIN_ALLOC_H
// Libraries
#include <stddef.h>

/// Block is 16MiB in size by default if not definded otherwise
#ifndef blocksize
#define blocksize 16777216
#endif

/// These macros should make using the allocators easier


/// This initializes the macro interface for the linear allocators
#define glob_lin_init() \
    LinAlloc glob_mem = {0}; \
    LinAlloc *cur_mem = &glob_mem;


/// This initializes the macro interface for the linear allocators
#define lin_init() \
    static LinAlloc glob_mem = {0}; \
    static LinAlloc *cur_mem = &glob_mem;


/// create a new allocator to use
#define lin_switch(new_allocator) \
    LinAlloc new_allocator = {0}; \
    cur_mem = &new_allocator;

/// Free used allocator and assign current allocator
/// back
#define lin_free(new_allocator) \
    lfree(&new_allocator);\
    cur_mem = &glob_mem;




/// This struct represents a region of memeory
typedef struct _Block Block;

/// This struct represents a handle to a
/// linear allocator and is passed around as a pointer
/// You have to init it with:
/// ```
/// LinAlloc glob_mem = {0};
/// ```
typedef struct _LinAlloc {
    Block *first;
    Block *current;
} LinAlloc;

/// This function alloctaes a chunk of memory of size
/// in the linear allocator.
void *lalloc(LinAlloc *linear_alloc, size_t size);



/// This function frees all the memory in the linear allocator
void lfree(LinAlloc *linear_alloc);
#endif // LIN_ALLOC_H
