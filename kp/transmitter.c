#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>


char *shared_string;
int first = 1;
int receiver_id;
int stat_id;


void init_shared_memory();

void init_sigaction();

int my_getline(char *desc);

void send_message_handler(int sig);


int main() {
    init_shared_memory();
    
    receiver_id = fork();
    if (receiver_id > 0) {
        // transmitter (parent)

        stat_id = fork();
        if (stat_id == 0) {
            // stat (child);
            int estatus = execl("./build/stat", "./build/stat", NULL);
        }
        kill(stat_id, SIGINT);
        init_sigaction();
        raise(SIGUSR2);
        while (1);
    } else {
        // receiver (child)

        execl("./build/receiver", "./build/receiver", NULL);
    }
}


void init_shared_memory() {
    int shared_memory_fd = open("shmobj", O_CREAT | O_RDWR, 0777);
    ftruncate(shared_memory_fd, getpagesize());
    shared_string = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, shared_memory_fd, 0);
    for (int i = 0; i < getpagesize(); i++) {
        shared_string[i] = '\0';
    }

}

void init_sigaction() {
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = send_message_handler;
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR2);
    sigaddset(&set, SIGUSR1);
    act.sa_mask = set;
    sigaction(SIGUSR2, &act, 0);
}

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

void send_message_handler(int sig) {
    int status;
    if (first) {
        usleep(100000);
        sprintf(shared_string, "%d", stat_id);
        status = 0;
        printf("send id = %s\n", shared_string);
        first = 0;
    }
    else {
        printf("enter string: ");
        status = my_getline(shared_string);
    }
    if (status == -1) {
        kill(stat_id, SIGINT);
        kill(receiver_id, SIGKILL);
        wait(NULL);
        munmap(shared_string, getpagesize());
        exit(0);
    }
    kill(receiver_id, SIGUSR1);
    kill(stat_id, SIGUSR1);
}

