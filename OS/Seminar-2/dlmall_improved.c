#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>
#include <errno.h>
#include <stddef.h>

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
    uint32_t next;  //  4 bytes pointer
    uint32_t prev;  //  4 bytes pointer
};

struct head *arena = NULL;

struct taken {
    uint16_t bfree; //  2 bytes, the status of block before
    uint16_t bsize; //  2 bytes, the size of block before
    uint16_t free;  //  2 bytes, the status of the block
    uint16_t size;  //  2 bytes, the size (max 2^16 i.e. 64Ki byte)
};

struct head* NEXT(struct head *block){
    char *p = (char *)arena + block->next;
    return (struct head*)p;
}
struct head* PREV(struct head *block){
    char *p = (char *)arena + block->prev;
    return (struct head*)p;
}

uint32_t ADRS(struct head *block){
    uint32_t i = (uint64_t)block - (uint64_t)arena;
    return (uint32_t)i;
}

struct head *after(struct head *block){
    return (struct head*)(HIDE(block) + block->size);
}

struct head *before(struct head *block){
    char *p = (char *)block - HEAD - block->bsize;
    return (struct head*)p;
}

struct head *split(struct head *block, int size){
    int rsize = block->size - (HEAD + size);
    block->size = size;
    block->free = FALSE;

    struct head *splt = after(block);
    splt->bfree = block->free;
    splt->bsize = block->size;
    splt->free = TRUE;
    splt->size = rsize;
    splt->next = 1;
    splt->prev = 1;

    struct head *aft = after(splt);
    aft->bsize = splt->size;

    return splt;
}

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
    if(block->next != 1 && block->prev != 1){
        NEXT(block)->prev = block->prev;
        PREV(block)->next = block->next;
    }else if(block->next != 1 && block->prev == 1){
        NEXT(block)->prev = 1;
        flist = NEXT(block);
    }else if(block->prev != 1 && block->next == 1){
        PREV(block)->next = 1;
    }else{
        flist = NULL;
    }
    block->next = 1;
    block->prev = 1;
    
}

void insert(struct head *block){
    
    block->next = 1;
    block->prev = 1;
    if(flist != NULL){
        block->next = ADRS(flist);
        flist->prev = ADRS(block);
    }
    flist = block;
}

int adjust(int request){
    return (int)((request/ALIGN + 1) * ALIGN);
}

struct head *find(int size){
    if(flist == NULL){
        insert(new());
    }
    struct head *current = flist;
    while(size > current->size){
        if(current->next == 1) return NULL;
        current = NEXT(current);
    }
    detach(current);
    if(current->size >= size + (HEAD + ALIGN)){
        insert(split(current, size));
    }else{
        current->free = FALSE;
        after(current)->bfree = FALSE;
    }
    return current;
}

struct head *merge(struct head *block){
    struct head *aft = after(block);
    if(block->bfree == TRUE){
        struct head *bef = before(block);
        detach(bef);
        int nsize = block->size + bef->size + HEAD;
        bef->size = nsize;
        block = bef;
    }

    if(aft->free == TRUE){  
        detach(aft);
        int nsize = block->size + aft->size + HEAD;
        struct head *aftaft = after(aft);
        aftaft->bfree = FALSE;
        aftaft->bsize = nsize;
        aft->free = FALSE;
        block->size = nsize;
    }
    block->free = TRUE;
    after(block)->bfree = TRUE;
    after(block)->bsize = block->size;
    return block;
}

void *dalloc(size_t request){
    if(request <= 0){
        return NULL;
    }
    int size = adjust(request);
    struct head *taken = find(size);
    if(taken == NULL){
        fprintf(stderr,"Failed to find large enough block\n");
        return NULL;
    }else{
        return HIDE(taken);
    }
}

void dfree(void *memory){
    if(memory != NULL){
        struct head *block = MAGIC(memory);
        block = merge(block);
        insert(block);
    }
    return;
}

void sanity(){
    if(flist == NULL) return;
    struct head *current = flist;
    int n = 0;
    while(1){
        printf("Block %d info:\n\tadrs: %p\n\tbfre: %d\n\tbsiz: %d\n\tfree: %d\n\tsize: %d\n\tnext: %p\n\tprev: %p\n\n"
        ,++n,current,current->bfree,current->bsize,current->free,current->size,NEXT(current),PREV(current));

        if(current->free == FALSE){
            printf("Occupied heap-space in freelist at %p\n",current);
            return;
        }
        if(current->size%ALIGN != 0){ 
            printf("Size of heap-block is unaligned at %p\n",current);
            return;
        }
        if(current->size == 0){ 
            printf("Size of heap-block is zero at %p\n",current);
            return;
        }
        if(current->next != 1 && PREV(NEXT(current)) != current){ 
            printf("Block %d info:\n\tadrs: %p\n\tbfre: %d\n\tbsiz: %d\n\tfree: %d\n\tsize: %d\n\tnext: %p\n\tprev: %p\n\n"
            ,n+1,NEXT(current),NEXT(current)->bfree,NEXT(current)->bsize,NEXT(current)->free,NEXT(current)->size,NEXT(NEXT(current)),PREV(NEXT(current)));
            printf("Prev-pointer of heap-block %d at %p is faulty\n",n+1,NEXT(current));
            printf("\tPrev pointer: %p\n\tShould be: %p\n",PREV(NEXT(current)),current);
            return;
        }
        if(current->bfree){
            printf("Block %d before is free but not merged\n",n);
            return;
        }
        if(n >= 10) break;
        if(current->next != 1) current = NEXT(current);
        else break;
    };
    printf("Sanitycheck completed\n");
    return;
}