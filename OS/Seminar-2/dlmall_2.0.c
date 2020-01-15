/*
In this version a single 4 byte pointer is used in the free list (flist), 
the 4 most significant bytes of the next pointer in the head struct
are removed before assigning, this makes the "pointer" a regular 32bit int.
Every time the pointer is needed the 4 bytes are re-instated.
Because of the removal of "prev"-pointer, the free-list is now a singular linked list.
These changes reduce overhead by 12 bytes, but have speed penalties.

I wanted to get my total overhead down to just 8 bytes and realised the free 
and bfree was using 2 bytes each but just utilizing 1 bit each, this 
is outrageous. I also realised the size and bsize didn't utilize
the 3 least significant bits (because of the 8 byte alignment).
Now free and bfree are just the LSB in size and bsize.
Finally 8 byte total overhead.

I tried the best-fit and first-fit approaches in this code,
currently the first-fit approach is in use and best-fit
is commented away.
When running benchmarks, best-fit was 125 times as slow
as first fit.

Benchmarks show that this "improved" version is about 50 times slower than
the non "improved" one and 100 times slower than built-in malloc when running
a random-size request benchmark.
When running a fixed-size request benchmark, this version was 135% faster than the 
non improved one and 25% faster than built-in malloc.
This version of malloc would be well suited in a machine that requires high memory-efficiency
and/or makes similarly sized memory requests.
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

To translate back to the full 64bit address, use function NEXT.

*/
static uint32_t ADRS(struct head *block){
    uint32_t i = (uint64_t)block - (uint64_t)arena;
    return (uint32_t)i;
}

//Checks if the free-list is sane
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

//Split a block (detached from free-list) into two where the first one is gonna be used and the second will be free
static struct head *split(struct head *block, int size){
    int rsize = (block->size & 0xFFFE ) - (HEAD + size);
    block->size = size;
    struct head *splt = after(block);
    splt->size = rsize;
    splt->size |= 0x1;  //free = 1;
    after(splt)->bsize = splt->size; //Bfree = 1;
    return splt;
}

//Create new arena 
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
    new->bsize = FALSE; //Bfree = 0;
    new->size  = size;
    new->size |= 0x1;   //Free = 1;
    
    struct head *sentinel = after(new);

    sentinel->bsize = size; //Bfree = 0;
    sentinel->size  = 0;    //Free = 0;

    arena = (struct head*)new;
    return new;
}

//Detach from free-list
static void detach(struct head *block){
    uint16_t adrs = ADRS(block);
    if(block->next == adrs){        //If this is the only block in the free-list
        flist = NULL;               //remove this block and return;
        return;
    } 
    if(flist == block) flist = NEXT(block);     //If thiss is the first block, make the next block the first block
    struct head *bef = flist;
    while(bef->next != adrs) bef = NEXT(bef);   //Find the block before this one by circling the free-list
    bef->next = block->next;                    //Set the "next" of the block before to be the block after

}

//Inserts block into free-list
static void insert(struct head *block){
    if(flist != NULL){
        uint16_t adrs = ADRS(flist);
        struct head *last = flist;
        while(last->next != adrs) last = NEXT(last);//Find the last block in the free-list
        last->next = ADRS(block);                   //Set last->next to be block
        block->next = adrs;                         //Set block->next to be the current first block
    }
    else block->next = ADRS(block); //If the free-list is empty, block->next is block

    flist = block;                  //Set Block as first in the free-list
}


static int adjust(int request){
    return (int)((request/ALIGN + 1) * ALIGN);
}

//Finds an appropriate block for the request
static struct head *find(int size){
    if(flist == NULL) insert(new());    //If free-list is empty, create and insert new arena
    struct head *current = flist;
    //FIRST-FIT APPROACH
    
    while(size > (current->size & 0xFFFE )){
        if(current->next == ADRS(flist)) return NULL;   //If we haven't found a big enough block but the next block is the first block,
        current = NEXT(current);                        //there is no big enough block
    }
    
    /*
    //BEST-FIT APPROACH
    struct head *best_fit = NULL;
    while(1){
        if(size < (current->size & 0xFFFE )){
            if(best_fit == NULL) best_fit = current;
            else if((current->size & 0xFFFE ) < (best_fit->size & 0xFFFE )) best_fit = current;
        }
        if(current->next == ADRS(flist)){
            if(best_fit == NULL) return NULL;
            current = best_fit;
            break;
        }
        current = NEXT(current);
    }*/

    detach(current);
    if((current->size & 0xFFFE ) >= size + (HEAD + ALIGN))insert(split(current, size)); //If current block is big enough to fit                                                                            
    current->size &= 0xFFFE;        //Free = 0;                                         //the requested block + a free block, split it
    after(current)->bsize &= 0xFFFE;//Bfree = 0;
    return current;
}

//Merges a newly freed block with free neighbors
static struct head *merge(struct head *block){
    struct head *aft = after(block);
    if(block->bsize & 0x1){             //Check if Bfree = 1
        struct head *bef = before(block);
        detach(bef);
        int nsize = (block->size & 0xFFFE ) + (bef->size & 0xFFFE ) + HEAD; //Calculate new size of merged block
        bef->size = nsize;                                                  //Sets bef to new size, WARNING THIS SETS FREE TO 0
        block = bef;                                                        //Sets block to bef because block is now a part of bef
    }
    if(aft->size & 0x1){  
        detach(aft);
        int nsize = (block->size & 0xFFFE ) + (aft->size & 0xFFFE ) + HEAD; //Calculate new size of merged block
        block->size = nsize;                                                //Sets block to new size, WARNING THIS SETS FREE TO 0
    }
    aft = after(block);             //Get the new after (if we merged with the previus after aft is no longer valid)
    block->size |= 0x1;             //Free = 1;
    aft->bsize = block->size;       //Bfree = 1;
    return block;
}

//
void *dalloc2(size_t request){
    if(request <= 0){
        return NULL;
    }
    int size = adjust(request);
    struct head *block = find(size); 
    if(block == NULL){
        fprintf(stderr,"Failed to find large enough block\n");
        return NULL;
    }else{
        return HIDE(block);
    }
}

//
void dfree2(void *memory){
    if(memory != NULL){
        struct head *block = MAGIC(memory);
        block = merge(block);
        insert(block);
    }
    return;
}