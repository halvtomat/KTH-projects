/*
In this version 4 byte pointers are used in the free list (flist), 
the 4 most significant bytes of the next & prev pointers in the head struct
then every time the pointers are used the 4 bytes are re-instated.
Overhead of free blocks reduced by 8 bytes.

A new struct "taken" wich is usedinstead of "head" on blocks that
are not free (hence taken).
Taken doesn't have the prev and next pointers because it will never
be in the free list.
Overhead of taken blocks reduced by another 8 bytes.

I tried the best-fit, worst-fit and first-fit approaches in this code,
currently the first-fit approach is in use and best and worst-fit
is commented away.
When running benchmarks, best-fit was more than twice as slow
as first fit, worst-fit was more than 4 times as slow.

Benchmarks show that this "improved" version is about 18% slower than
the non "improved" one.
The real improvement is the much lower overhead, this version would be
more suited for a machine with a small memory.
*/

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
    uint16_t bsize; //  2 bytes, the size of block before LSB = Bfree
    uint16_t size;  //  2 bytes, the size (max 2^16 i.e. 64Ki byte) LSB = Free
    uint32_t next;  //  4 bytes pointer
};

static struct head *arena = NULL;

static struct head *flist = NULL;

struct taken {
    uint16_t bfree; //  2 bytes, the status of block before
    uint16_t bsize; //  2 bytes, the size of block before
    uint16_t free;  //  2 bytes, the status of the block
    uint16_t size;  //  2 bytes, the size (max 2^16 i.e. 64Ki byte)
};

/*
NEXT is used to translate the 32bit addresses created by ADRS
to reduce overhead, into the full 64bit address it represents.
*/
static struct head* NEXT(struct head *block){
    char *p = (char *)arena + block->next;
    return (struct head*)p;
}

/*
ADRS compresses the "real" 64bit address of the head pointer 
to a 32bit pointer consisting of the 32 least significant bits.
The heap will never grow beyond a 32bit address-space so the 
most significant bits will always be the same.

This buys us 8 bytes in terms of reduced overhead 
for the head struct.

To translate back to the full 64bit address, use functions NEXT & PREV.

*/
static uint32_t ADRS(struct head *block){
    uint32_t i = (uint64_t)block - (uint64_t)arena;
    return (uint32_t)i;
}

void sanity2(){
    if(flist == NULL) return;
    struct head *current = flist;
    int n = 0;
    while(1){
        printf("Block %d info:\n\tadrs: %p\n\tbfre: %d\n\tbsiz: %d\n\tfree: %d\n\tsize: %d\n\tnext: %p\n\n"
        ,++n,current,current->bsize & 0x1,current->bsize & 0xFFFE,current->size & 0x1,current->size & 0xFFFE,NEXT(current));

        if(current->size & 0x1 == FALSE){
            printf("Occupied heap-space in freelist at %p\n",current);
            return;
        }
        if((current->size & 0xFFFE )%ALIGN != 0){ 
            printf("Size of heap-block is unaligned at %p\n",current);
            return;
        }
        if((current->size & 0xFFFE ) == 0){ 
            printf("Size of heap-block is zero at %p\n",current);
            return;
        }
        if(current->bsize & 0x1){
            printf("Block %d before is free but not merged\n",n);
            return;
        }
        //if(n >= 10) break;
        if(current->next != ADRS(flist)) current = NEXT(current);
        else break;
    };
    printf("Sanitycheck completed\n");
    return;
}


static struct head *after(struct head *block){
    return (struct head*)(HIDE(block) + (block->size & 0xFFFE ));
}

static struct head *before(struct head *block){
    char *p = (char *)block - HEAD - (block->bsize & 0xFFFE);
    return (struct head*)p;
}

static struct head *split(struct head *block, int size){
    int rsize = (block->size & 0xFFFE ) - (HEAD + size);
    block->size = (block->size & 0x1) | size;
    block->size &= 0xFFFE; //free = 0;

    struct head *splt = after(block);
    splt->bsize &= 0xFFFE; //bfree = 0;
    splt->size |= 0x1;  //free = 1;
    splt->bsize = block->size;
    splt->size = (splt->size & 0x1) | rsize;

    after(splt)->bsize = splt->size;

    return splt;
}

static struct head *new(){
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
    uint16_t size = ARENA - 2*HEAD;
    new->bsize = FALSE;
    new->size  = size;
    new->size |= 0x1;
    
    struct head *sentinel = after(new);

    sentinel->bsize = new->size;
    sentinel->size  = 0;

    arena = (struct head*)new;
    return new;
}



static void detach(struct head *block){
    uint16_t adrs = ADRS(block);
    if(block->next != adrs){
        if(flist == block) flist = NEXT(block);
        struct head *bef = flist;
        while(bef->next != adrs) bef = NEXT(bef);
        bef->next = block->next;
    }else{
        flist = NULL;
    }
}

static void insert(struct head *block){
    if(flist != NULL){
        uint16_t adrs = ADRS(flist);
        struct head *last = flist;
        while(last->next != adrs) last = NEXT(last);
        last->next = ADRS(block);
        block->next = adrs;
    }
    else{
        block->next = ADRS(block);
    }
    flist = block;
}


static int adjust(int request){
    return (int)((request/ALIGN + 1) * ALIGN);
}

static struct head *find(int size){
    if(flist == NULL){
        insert(new());
    }
    struct head *current = flist;

    
    //FIRST-FIT APPROACH
    while(size > (current->size & 0xFFFE )){
        if(current->next == ADRS(flist)) return NULL;
        current = NEXT(current);
    }
    
    
    /*
    //BEST-FIT APPROACH
    struct head *best_fit = NULL;
    while(1){
        if(size < current->size){
            if(best_fit == NULL) best_fit = current;
            else if(current->size < best_fit->size) best_fit = current;
        }
        if(current->next == ADRS(flist)){
            if(best_fit == NULL) return NULL;
            current = best_fit;
            break;
        }
        current = NEXT(current);
    }
    */
    /*
    //WORST-FIT APPROACH
    struct head *worst_fit = NULL;
    while(1){
        if(size < current->size){
            if(worst_fit == NULL) worst_fit = current;
            else if(current->size > worst_fit->size) worst_fit = current;
        }
        if(current->next == ADRS(flist)){
            if(worst_fit == NULL) return NULL;
            current = worst_fit;
            break;
        }
        current = NEXT(current);
    }
    */
    detach(current);
    if((current->size & 0xFFFE ) >= size + (HEAD + ALIGN)){
        insert(split(current, size));
    }else{
        current->size &= 0xFFFE;
        after(current)->bsize &= 0xFFFE;
    }
    return current;
}

static struct head *merge(struct head *block){
    struct head *aft = after(block);
    if(block->bsize & 0x1){
        struct head *bef = before(block);
        detach(bef);
        int nsize = (block->size & 0xFFFE ) + (bef->size & 0xFFFE ) + HEAD;
        bef->size = (bef->size & 0x1) | nsize;
        block = bef;
    }
    if(aft->size & 0x1){  
        detach(aft);
        int nsize = (block->size & 0xFFFE ) + (aft->size & 0xFFFE ) + HEAD;
        block->size = (block->size & 0x1) | nsize;
    }
    aft = after(block);
    aft->bsize = block->size;
    block->size |= 0x1;
    return block;
}

void *dalloc2(size_t request){
    if(request <= 0){
        return NULL;
    }
    int size = adjust(request);
    struct head *taken = find(size); //TODO: FIX TAKEN TO ACCTUALLY BE USED
    if(taken == NULL){
        fprintf(stderr,"Failed to find large enough block\n");
        return NULL;
    }else{
        return HIDE(taken); //TODO: HIDE HIDES TO MUCH
    }
}

void dfree2(void *memory){
    if(memory != NULL){
        struct head *block = MAGIC(memory);
        block = merge(block);
        insert(block);
    }
    return;
}

