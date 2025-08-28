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
    
    char p1 [] = "I am parent";
    char p2 [] = "I am child";
    char p3 [] = "I am grandchild";
    
    if(pid == 0){

    	pid2 = fork();
    	if (pid2 == 0){
    		printf("%s\n", p3);
	}
	else{
		wait(NULL);
		printf("%s\n", p2);
	}
    }
    else{
        wait(NULL);
    	printf("%s\n", p1);
    }
    return 0;
}