#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msg {
    long int type;
    char txt[20];
};

int main() {
    key_t key = 2025;
    int msg_id;
    struct msg message;
    char work_name[20];

    msg_id = msgget(key, 0666 | IPC_CREAT);

    printf("Please enter the workspace name:\n");
    scanf("%s", work_name); 

    if (strcmp(work_name, "cse321") == 0) {
    	struct msg actual_data;
    	int msg_id = msgget((key_t)11, 0666 | IPC_CREAT);
    
    	actual_data.type = 5; 
    	strncpy(actual_data.txt, work_name, sizeof(actual_data.txt) - 1);
    	actual_data.txt[sizeof(actual_data.txt) - 1] = '\0';

    	msgsnd(msg_id, (void *)&actual_data, sizeof(actual_data.txt), 0);
    	printf("Workspace name sent to OTP generator from login: %s\n", actual_data.txt);

		pid_t otp;
    	otp = fork();

    	if (otp > 0) {
        	wait(NULL); 

        	char otp_to_otp[20], mail_to_otp[20];

        	msgrcv(msg_id, (void *)&actual_data, sizeof(actual_data.txt), 10, 0);
        	printf("Login received OTP from OTP generator: %s\n", actual_data.txt);
        	strncpy(otp_to_otp, actual_data.txt, sizeof(otp_to_otp));

        	msgrcv(msg_id, (void *)&actual_data, sizeof(actual_data.txt), 20, 0);
        	printf("Login received OTP from mail: %s\n", actual_data.txt);
        	strncpy(mail_to_otp, actual_data.txt, sizeof(mail_to_otp));

			if (strcmp(otp_to_otp, mail_to_otp) != 0) {
            	printf("OTP Incorrect\n");
        		} 
        	else {
        		printf("OTP Verified\n");
            	}    
        	msgctl(msg_id, IPC_RMID, NULL);
    		
    	return 0;
    	}
  
    	else if (otp == 0) {    	
    		msgrcv(msg_id, (void *)&actual_data, sizeof(actual_data.txt), 5, 0);
        	printf("OTP generator received workspace name from login: %s\n", actual_data.txt);

        	int otp_k = getpid();
        	snprintf(actual_data.txt, sizeof(actual_data.txt), "%d", otp_k);

        
        	actual_data.type = 10;
        	msgsnd(msg_id, (void *)&actual_data, sizeof(actual_data.txt), 0);
        	printf("OTP sent to login from OTP generator: %s\n", actual_data.txt);
        
        	actual_data.type = 15;
        	msgsnd(msg_id, (void *)&actual_data, sizeof(actual_data.txt), 0);
        	printf("OTP sent to mail from OTP generator: %s\n", actual_data.txt);

        	pid_t email;
        	email = fork();

        	if (email > 0) {
        		wait(NULL); 
            	exit(0); 
            	} 
        	else if (email == 0) {
            	msgrcv(msg_id, (void *)&actual_data, sizeof(actual_data.txt), 15, 0);
            	printf("Mail received OTP from OTP generator: %s\n", actual_data.txt);

            
            	actual_data.type = 20;
            	msgsnd(msg_id, (void *)&actual_data, sizeof(actual_data.txt), 0);
            	printf("Mail sent OTP to login: %s\n", actual_data.txt);

            	exit(0);
        		}
			}
}       
    else{
    	printf("Invalid workspace name\n");
        exit(0); 
        }
}
    





