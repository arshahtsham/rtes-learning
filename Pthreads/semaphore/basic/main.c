#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

#define THREAD_NUM 4

sem_t semaphore;

void* routine(void* args) {
    sem_wait(&semaphore);
    sleep(1);
    printf("Hello from thread %d\n", *(int*)args);
    sem_post(&semaphore);
    free(args);
}

int main (){

    pthread_t th[THREAD_NUM];
    sem_init(&semaphore, 0, 2);

    for (int i = 0; i < THREAD_NUM ; i++)
    {
        int* a = malloc(sizeof(int));
        *a = i;
        pthread_create(&th[i], NULL, &routine, a);
    }
    

    for (int i = 0; i < THREAD_NUM ; i++)
    {
        pthread_join(th[i], NULL);
    }
    sem_destroy(&semaphore);
    return 0;

}