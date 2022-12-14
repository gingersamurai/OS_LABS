#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

char *shared_string;


static int cnt_transmitted = 0;
static int cnt_received = 0;


void init_shared_memory();


void init_transmitter_sigaction();

void init_receiver_sigaction();

void init_finish_sigaction();


void transmitter_handle(int sig);

void receiver_handle(int sig);

void finish_handle(int sig);




int main() {
    init_shared_memory();
    
    init_transmitter_sigaction();
    init_receiver_sigaction();
    init_finish_sigaction();

    while (1);
}

void init_shared_memory() {
    int shared_memory_fd = open("shmobj", O_RDWR, 0777);
    ftruncate(shared_memory_fd, getpagesize());
    shared_string = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, shared_memory_fd, 0);

}


void init_transmitter_sigaction() {
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = transmitter_handle;
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR2);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGINT);
    act.sa_mask = set;
    sigaction(SIGUSR1, &act, 0);
}

void init_receiver_sigaction() {
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = receiver_handle;
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR2);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGINT);
    act.sa_mask = set;
    sigaction(SIGUSR2, &act, 0);
}

void init_finish_sigaction() {
    
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = finish_handle;
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR2);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGINT);
    act.sa_mask = set;
    sigaction(SIGINT, &act, 0);
}


void transmitter_handle(int sig) {
    cnt_transmitted += strlen(shared_string);
}

void receiver_handle(int sig) {
    cnt_received += strlen(shared_string);
}

void finish_handle(int sig) {
    printf("result:\n");
    printf("transmitted\t%d\tsymbls\n", cnt_transmitted);
    printf("received\t%d\tsymbls\n", cnt_received);
    exit(0);
}

