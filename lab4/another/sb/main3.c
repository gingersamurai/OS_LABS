#define _CRT_SECURE_NO_WARNINGS
#define _CRT_RAND_S
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
 
#ifdef _WIN32
    #include <conio.h>
    #include <Windows.h>
    #define Sleep(x) Sleep(x)
    #define wait() _getch()
#else
    #include <unistd.h>
    #define Sleep(x) sleep(x)
    #define wait() scanf("1")
#endif
 
sem_t semaphore1;
sem_t semaphore2;
 
static int counter = 0;
 
void* waiter(void* args) {
    Sleep(3000);
    sem_wait(&semaphore2);
    printf("waiter work!");
}
 
void* signaler1(void* args) {
    Sleep(1500);
    sem_post(&semaphore1);
    printf("signaler1 work!");
}
 
void* signaler2(void* args) {
    Sleep(2500);
    sem_wait(&semaphore1);
    sem_post(&semaphore2);
    printf("signaler2 work!");
}
 
void main() {
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
 
    sem_init(&semaphore1, 0, 0);
    sem_init(&semaphore2, 0, 0);
     
    pthread_create(&thread1, NULL, waiter, NULL);
    pthread_create(&thread2, NULL, signaler1, NULL);
    pthread_create(&thread3, NULL, signaler2, NULL);
 
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
 
    sem_destroy(&semaphore1);
    sem_destroy(&semaphore2);
}