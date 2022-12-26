#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <threads.h>
#include <string.h>
#include <signal.h>
#include <semaphore.h>




int main() {

    // init shared memory string
    int shared_memory_fd = open("shmobj", O_RDWR, 0777);
    ftruncate(shared_memory_fd, getpagesize());
    char *shared_string = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, shared_memory_fd, 0);

    // init semaphores
    sem_t *semp, *semc;
    semp = sem_open("semp", O_CREAT);
    semc = sem_open("semc", O_CREAT);

    while (1) {
        sem_wait(semc);

        if (strlen(shared_string) == 0) {
            fprintf(stderr, "out child\n");
            break;
        }

        if (shared_string[0] >= 65 && shared_string[0] <= 90) {
            printf("%s\n", shared_string);
        } else {
            fprintf(stderr, "error: %s\n", shared_string);
        }

        sem_post(semp);
    }

    sem_close(semp);
    sem_close(semc);



}