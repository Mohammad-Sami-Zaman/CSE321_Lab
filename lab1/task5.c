#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
    
    pid_t pid, pid2;
    pid = fork();
    
    if(pid == 0){
      printf("I am the child process,my pid %d\n", getpid());
      for (int i = 0; i<3; i++){

        pid2 = fork();
        if (pid2 == 0){
            
            printf("I am the grandchild process,my pid %d\n", getpid());
            return 0;
            }
        }
        
        return 0;
         
    }
    else{
        printf("I am the parent process, my pid %d\n", getpid());
    }
    return 0;
}