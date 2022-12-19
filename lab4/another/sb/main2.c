#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

sem_t semaphore;
static int counter = 0;

void *worker1(void *args) {
    int i;
    int local;
    for (int i = 0; i < 100; i++) {
        sem_wait(&semaphore);
        local = counter;
        printf("worker 1 - %d\n", local);
        local++;
        counter = local;
        usleep(10000);
        sem_post(&semaphore);
    }
}

void *worker2(void *args) {
    int i;
    int local;
    for (int i = 0; i < 100; i++) {
        sem_wait(&semaphore);
        local = counter;
        printf("worker 2 - %d\n", local);
        local--;
        counter = local;
        usleep(10000);
        sem_post(&semaphore);
    }
}

int main() {
    pthread_t thread1;
    pthread_t thread2;

    sem_init(&semaphore, 0, 1);

    pthread_create(&thread1, NULL, worker1, NULL);
    pthread_create(&thread2, NULL, worker2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    sem_destroy(&semaphore);
    printf("== %d", counter);
}