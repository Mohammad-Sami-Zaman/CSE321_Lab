#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
    
    pid_t pid, pid2;

    int count = 0;
    
    for (int i = 0; i<3; i++){

        pid = fork();
        count = count + 1;
        if (pid == 0){
            
            if (getpid() % 2 != 0){
            count = count + 2;
            pid2 = fork();
            }
            else{
            	count = count + 1;
            }
            
        }   
         }
printf("%d\n", count); 
return 0;
}

























