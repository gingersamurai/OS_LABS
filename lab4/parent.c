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
    int fd = shm_open("testfile", O_RDWR | O_CREAT | O_EXCL, 0600);
    if (fd < 0) {
        perror("shm_open()");
        return 1;
    }

    ftruncate(fd, getpagesize());

    char *mapped_file = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    memset(mapped_file, '\0', getpagesize());
    // mapped_file[0] = 'a';
    strcat(mapped_file, "abcd");
    printf("sended [%s] to: %p\n", mapped_file, mapped_file);
    munmap(mapped_file, getpagesize());
    close(fd);
}