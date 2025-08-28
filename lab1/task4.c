#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    if (argc < 2) {
        printf("need some number when compiling the file.\n");
        return -1;
    }
    
    pid_t pid = fork();


    if (pid > 0)
    {
        wait(NULL);
        execv("oe", argv);
        
    }
    else if (pid == 0)
    {
        execv("s", argv);
    }

    return 0;
}




