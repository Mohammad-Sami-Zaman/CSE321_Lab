#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

struct shared_m {
    char sel[100];
    int b;
};

int main() {
    int share_m_id = shmget(IPC_PRIVATE, sizeof(struct shared_m), IPC_CREAT | 0666);
    struct shared_m *sh_m = (struct shared_m *)shmat(share_m_id, NULL, 0);

    printf("Please give Input From Options:\n");
    printf("1.Type c for Check Balance  \n2. Type a for Add  Money \n3. Type w for Withdraw  Money \n");
    scanf(" %s", (*sh_m).sel);
    (*sh_m).b = 1000;

    printf("Your selected:  %s\n", (*sh_m).sel);
    
    int fd[2];
    pipe(fd);

    pid_t pid = fork();
    if (pid < 0){
    	printf("Fork Failed can not proceed");
    }
    else if (pid > 0) {
        wait(NULL);
        char buffer[100];
        close(fd[1]);
        read(fd[0], buffer, sizeof(buffer));
        printf("%s", buffer);
        close(fd[0]);
        shmdt(sh_m);
        shmctl(share_m_id, IPC_RMID, NULL);
    } 
    else if (pid == 0) {        
        if (strcmp((*sh_m).sel, "c") == 0) {
        	printf("Your current balance is: %d\n", (*sh_m).b);
        } 
        
        else if (strcmp((*sh_m).sel, "a") == 0) {
            int add_money;
            printf("Enter amount to be added:\n");
            scanf("%d", &add_money);
            if (add_money <= 0) {
            	printf("Adding failed, Invalid amount\n");
            } 
            else {
            	(*sh_m).b = (*sh_m).b + add_money;
                printf("Balance added successfully\n");
                printf("Updated balance after addition: %d\n", (*sh_m).b);
                }
        } 
        
        else if (strcmp((*sh_m).sel, "w") == 0) {
            int withdraw;
            printf("Enter amount to be withdrawn:\n");
            scanf("%d", &withdraw);
            if (withdraw <= 0 && withdraw >= (*sh_m).b) {
            	printf("Failed to withdraw, Invalid amount\n");   
            } 
            else {
            	(*sh_m).b = (*sh_m).b - withdraw;
                printf("Balance withdrawn successfully\n");
                printf("Updated balance after withdrawal: %d\n", (*sh_m).b);
            }
        } 
        
        else {printf("Invalid selection\n");}
        char reply[] = "Thank you for using\n";
        write(fd[1], reply, strlen(reply) + 1);
        close(fd[1]);
        shmdt(sh_m);
        exit(0);
    }

    return 0;
}

















































