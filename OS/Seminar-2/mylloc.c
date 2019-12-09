#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

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
    return (struct head*)(block + block->size + HEAD)
}