#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <threads.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>




int main(int argc, char **argv) {
    int fd = shm_open("testfile", O_RDWR, 0666);
    if (fd < 0) {
        perror("shm_open()");
        return 1;
    }

    char *mapped_file = mmap(NULL, getpagesize(), PROT_READ, MAP_SHARED, fd, 0);
    
    printf("received [%s] from: %p\n", mapped_file, mapped_file);
    munmap(mapped_file, getpagesize());
    close(fd);
    shm_unlink("testfile");
}