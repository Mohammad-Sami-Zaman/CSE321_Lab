#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int total_stu = 10;       
int wait_chair = 3;       

sem_t stu;                
sem_t s_tutor;            
pthread_mutex_t mutex;

int wait_count = 0;
int serve_count = 0;

void *studentFunc(void *num) {
    int id_stu = *(int *)num;

    pthread_mutex_lock(&mutex);

    if (wait_count >= wait_chair) {
        printf("No chairs remaining in lobby. Student %d Leaving.....\n", id_stu);
        pthread_mutex_unlock(&mutex);
    } 
    else {
        wait_count++;
        printf("Student %d started waiting for consultation\n", id_stu);

        sem_post(&stu);
        pthread_mutex_unlock(&mutex);

        sem_wait(&s_tutor); 

        printf("Student %d is getting consultation\n", id_stu);

        pthread_mutex_lock(&mutex);
        serve_count++;
        printf("Student %d finished getting consultation and left\n", id_stu);
        printf("Number of served students: %d\n", serve_count);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void *tutorFunc(void *arg) {
    while (1) {
        sem_wait(&stu);

        pthread_mutex_lock(&mutex);
        if (serve_count < total_stu) {
            wait_count--;
            printf("A waiting student started getting consultation\n");
            printf("Number of students now waiting: %d\n", wait_count);
            printf("ST giving consultation\n");
            pthread_mutex_unlock(&mutex);

            sem_post(&s_tutor);
        }
        else{
            pthread_mutex_unlock(&mutex);
            break;
        }

        
    }
    return NULL;
}

int main() {
    pthread_t tutorThread;
    pthread_t studentThreads[100];
    int stu_id[100];

    sem_init(&stu, 0, 0);
    sem_init(&s_tutor, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&tutorThread, NULL, tutorFunc, NULL);

    for (int i = 0; i < total_stu; i++) {
        stu_id[i] = i;
        pthread_create(&studentThreads[i], NULL, studentFunc, &stu_id[i]);
    }

    for (int i = 0; i < total_stu; i++) {
        pthread_join(studentThreads[i], NULL);
    }

    pthread_join(tutorThread, NULL);

    printf("All consultations done. Number of served students: %d\n", serve_count);

    sem_destroy(&stu);
    sem_destroy(&s_tutor);
    pthread_mutex_destroy(&mutex);

    return 0;
}

