#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
sem_t semaphore;

void* threadFunction(void* arg) {
    int threadNum = *(int*)arg;
    printf("Thread %d: Waiting for semaphore...\n", threadNum);
    sem_wait(&semaphore);
    printf("Thread %d: Acquired semaphore!\n", threadNum);
    sleep(1); // Simulate some work
    printf("Thread %d: Releasing semaphore...\n", threadNum);
    sem_post(&semaphore);
    printf("Thread %d: Semaphore released!\n", threadNum);
    return NULL;
}

int main() {
    pthread_t threads[5];
    int threadNums[5];
    sem_init(&semaphore, 0, 2); // Initialize semaphore with a value of 2
    for (int i = 0; i < 5; i++) {
        threadNums[i] = i + 1;
        pthread_create(&threads[i], NULL, threadFunction, &threadNums[i]);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
    sem_destroy(&semaphore); // Clean up semaphore
    return 0;
    
}