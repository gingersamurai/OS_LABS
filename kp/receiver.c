#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>


char *shared_string;
int first = 1;
int stat_id;

void init_shared_memory();

void init_sigaction();

void write_output_handler(int sig);


int main() {
    init_shared_memory();
    
    init_sigaction();
    while (1);
}


void init_shared_memory() {
    int shared_memory_fd = open("shmobj", O_RDWR, 0777);
    ftruncate(shared_memory_fd, getpagesize());
    shared_string = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, shared_memory_fd, 0);
}

void init_sigaction() {
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = write_output_handler;
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR2);
    sigaddset(&set, SIGUSR1);
    act.sa_mask = set;
    sigaction(SIGUSR1, &act, 0);
}

void write_output_handler(int sig) {
    if (first) {
        stat_id = atoi(shared_string);
        first = 0;
        kill(getppid(), SIGUSR2);
        return;
    }
    printf("received:\t[%s]\n", shared_string);
    kill(getppid(), SIGUSR2);
    kill(stat_id, SIGUSR2);
}

