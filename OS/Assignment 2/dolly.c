#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){

    int pid = fork();

    if(pid == 0){
        return 42;
    } else{
        int res;
        wait(&res);
        printf("The result was %d\n", WEXITSTATUS(res));
    }

    return 0;
}
