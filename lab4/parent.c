#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <threads.h>
#include <string.h>
#include <signal.h>
#include <semaphore.h>

int my_getline(char *desc) {
    int id = 0;
    char c = getchar();
    while (c != EOF && c != '\n') {
        desc[id++] = c;
        c = getchar();
    }
    desc[id] = '\0';
    if (c == EOF) {
        return -1;
    } else {
        return 0;
    }
}


int main() {
    
    // open resfile
    char filename[100];
    printf("enter name of file: ");
    scanf("%s", filename);
    char buff;
    while((buff = getchar()) != '\n');
    int resultfile_fd = open(filename, O_CREAT | O_WRONLY, 0777);
    
    // init shared memory string
    int shared_memory_fd = open("shmobj", O_CREAT | O_RDWR, 0777);
    ftruncate(shared_memory_fd, getpagesize());
    char *shared_string = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, shared_memory_fd, 0);
    for (int i = 0; i < getpagesize(); i++) {
        shared_string[i] = '\0';
    }

    // init semaphores
    sem_t *semp, *semc;
    semp = sem_open("semp", O_CREAT, 0777, 0);
    semc = sem_open("semc", O_CREAT, 0777, 0);
    int pid = fork();
    if (pid > 0) {
        // parent
        
        while(1) {
            printf("enter string: ");
            int status = my_getline(shared_string);

            if (status == -1) {
                shared_string[0] == '\0';
                sem_post(semc);
                break;

            }
            sem_post(semc);
            sem_wait(semp);
        }
        wait(NULL);

        sem_unlink("semp");
        sem_unlink("semc");
        
        sem_close(semp);
        sem_close(semc);

        munmap(shared_string, getpagesize());

    } else {
        // child
        
        if (dup2(resultfile_fd, STDOUT_FILENO) == -1) {
            return 1;
        }
        close(resultfile_fd);
                
        execl("./build/child", "./build/child", NULL);
    }


}