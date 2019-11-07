#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(){

    int pid = fork();

    if(pid == 0){
        int fd = open("quotes.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        dup2(fd, 1);
        close(fd);
        execl("boba", "boba", NULL);
        printf("this only happens on failure\n");
    } else{
        wait(NULL);
    }
    return 0;
}