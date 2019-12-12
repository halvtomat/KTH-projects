#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>
#include <errno.h>

#define __USE_MISC 1

#define TRUE 1
#define FALSE 0

#define HEAD (sizeof(struct head))
#define MIN(size) (((size) > (8))?(size):(8))
#define LIMIT(size) (MIN(0) + HEAD + size)
#define MAGIC(memory) ((struct head*)memory - 1)
#define HIDE(block) (void*)((struct head*)block + 1)
#define ALIGN 8
#define ARENA (64*1024)


struct head {
    uint16_t bfree; //  2 bytes, the status of block before
    uint16_t bsize; //  2 bytes, the size of block before
    uint16_t free;  //  2 bytes, the status of the block
    uint16_t size;  //  2 bytes, the size (max 2^16 i.e. 64Ki byte)
    struct head *next;  //  8 bytes pointer
    struct head *prev;  //  8 bytes pointer
};

struct head *after(struct head *block){
    return (struct head*)(HIDE(block)+block->size);
}

struct head *before(struct head *block){
    return (struct head*)(MAGIC(block) - block->bsize);
}

struct head *split(struct head *block, int size){
    int rsize = block->size - (HEAD + size);
    block->size = size;

    struct head *splt = after(block);
    splt->bfree = block->free;
    splt->bsize = block->size;
    splt->free = TRUE;
    splt->size = rsize;

    struct head *aft = after(splt);
    aft->bsize = splt->size;

    return splt;
}

struct head *arena = NULL;

struct head *new(){
    if(arena != NULL){
        printf("one arena already allocated \n");
        return NULL;
    }
    struct head *new = mmap(NULL, ARENA, PROT_READ | PROT_WRITE, MAP_PRIVATE | 0x20, -1, 0);

    if(new == MAP_FAILED){
        printf("mmap failed: error %d\n", errno);
        return NULL;
    }
    /* make room for head and dummy*/
    uint32_t size = ARENA - 2*HEAD;

    new->bfree = FALSE;
    new->bsize = FALSE;
    new->free  = FALSE;
    new->size  = size;
    
    struct head *sentinel = after(new);

    sentinel->bfree = new->free;
    sentinel->bsize = new->size;
    sentinel->free  = FALSE;
    sentinel->size  = 0;
    arena = (struct head*)new;
    return new;
}

struct head *flist = NULL;

void detach(struct head *block){
    if(block->next != NULL){
        block->next->prev = block->prev;
    }
    if(block->prev != NULL){
        block->prev->next = block->next;
    }else{
        flist = block->next;
    }
}

void insert(struct head *block){
    block->next = flist;
    block->prev = NULL;
    if(flist != NULL){
        flist->prev = block;
    }
    flist = block;
}

int adjust(int request){
    return (int)((request/ALIGN + 1) * ALIGN);
}

struct head *find(int size){
    if(flist == NULL) insert(new());
    struct head *current = flist;
    while(size > current->size){
        if(current->next == NULL) return NULL;
        current = current->next;
    }
    detach(current);
    if(current->size >= size + (HEAD + ALIGN)){
        insert(split(current, size));
    }
    current->free = FALSE;
    after(current)->bfree = FALSE;

    return current;
}

void *dalloc(size_t request){
    if(request <= 0){
        return NULL;
    }
    int size = adjust(request);
    struct head *taken = find(size);
    if(taken == NULL){
        return NULL;
    }else{
        return (struct head*)(taken + HEAD);
    }
}

void dfree(void *memory){
    if(memory != NULL){
        struct head *block = memory - HEAD;

        struct head *aft = after(block);
        block->free = TRUE;
        aft->bfree = TRUE;
        insert(block);
    }
    return;
}

void sanity(){
    if(flist == NULL) return;
    struct head *current = flist;
    while(current->next != NULL){
        if(current->free == FALSE){
            printf("Occupied heap-space in freelist at %p\n",current); 
            return;
        }
        if(current->size%ALIGN != 0){ 
            printf("Size of heap-block is unaligned at %p\n",current); 
            return;
        }
        if(current->next->prev != current){ 
            printf("Prev-pointer of heap-block at %p is faulty\n",current->next); 
            return;
        }

        current = current->next;
    }
    printf("Sanitycheck completed\n");
    return;
}