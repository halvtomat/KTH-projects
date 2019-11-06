#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

    int pid = getpid();

    long *heap = (unsigned long*)calloc(54, sizeof(unsigned long));

    printf("heap[2]:        0x%lx\n", heap[2]);
    printf("heap[1]:        0x%lx\n", heap[1]);
    printf("heap[0]:        0x%lx\n", heap[0]);
    printf("heap[-1]:       0x%lx\n", heap[-1]);
    printf("heap[-2]:       0x%lx\n", heap[-2]);

    free(heap);

    printf("heap[2]:        0x%lx\n", heap[2]);
    printf("heap[1]:        0x%lx\n", heap[1]);
    printf("heap[0]:        0x%lx\n", heap[0]);
    printf("heap[-1]:       0x%lx\n", heap[-1]);
    printf("heap[-2]:       0x%lx\n", heap[-2]);

    back:

        printf("\n\n /proc/&d/maps \n\n", pid);
        char command[50];
        sprintf(command, "cat /proc/%d/maps", pid);
        system(command);

        return 0;
}