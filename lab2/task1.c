#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/wait.h>


int num, seq; 
int fib_arr[41];      
int sea_index[100]; 


void *fibonacci_generate(void *arg) {
    if (num >= 0) fib_arr[0] = 0;
    if (num >= 1) fib_arr[1] = 1;
    
    int i = 2;
    while (i < num + 1){
    
    	fib_arr[i] = fib_arr[i - 1] + fib_arr[i - 2];
    	i = i + 1;
    }

    pthread_exit(NULL);
}


void *search_fibonacci(void *arg) {
	
    int i = 0;
    while (i <= seq - 1){
    	
    	int index = sea_index[i];
        if (index < 0 && index > num) {
            
            printf("result of search #%d = -1\n", i);
        } 
        
        else {
            printf("result of search #%d = %d\n", i + 1, fib_arr[index]);
        }
        i = i+1;
    }
    pthread_exit(NULL);
}	
	
        
int main() {
    pthread_t t1, t2;

    printf("Enter fibonacci sequence number: ");
    scanf("%d", &num);

    printf("How many numbers you are willing to search?: ");
    scanf("%d", &seq);

    for (int i = 0; i <= seq - 1; i++) {
        printf("Enter search %d: ", i + 1);
        scanf("%d", &sea_index[i]);
    }

    pthread_create(&t1, NULL, fibonacci_generate, NULL);
    pthread_join(t1, NULL);

    for (int i = 0; i < num + 1; i++) {
        printf("a[%d] = %d\n", i, fib_arr[i]);
    }

    pthread_create(&t2, NULL, search_fibonacci, NULL);
    pthread_join(t2, NULL);

    return 0;
}





























