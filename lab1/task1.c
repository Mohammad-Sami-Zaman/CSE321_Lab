#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd = open("input1.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);


    char s1[1000][1000];  
    int flag = 1;
    int p = 0;

    while (flag == 1) {
        char inxt[100];
        

        if (strcmp(inxt, "-1") == 0) {
            flag = -1;
        } 
        else {
            printf("Enter string or -1 to end:\n");
            scanf("%s", inxt);
            strcpy(s1[p], inxt);
            write(fd, s1[p], strlen(s1[p]));
            write(fd, "\n", 1);
            p = p + 1;            
        }
    }

    close(fd);
    return 0;
}
