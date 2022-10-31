#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int p1[2];  // c -> p
    int p2[2];  // p -> c
    if (pipe(p1) == -1) return 1;
    if (pipe(p2) == -1) return 1;

    int pid = fork();
    if (pid == -1) return 2;
    if (pid == 0) {
        // child process
        close(p1[0]);
        close(p2[1]);
        int x;
        if (read(p2[0], &x, sizeof(x)) == -1) return 3;
        x *= 4;
        if (write(p1[1], &x, sizeof(x)) == -1) return 4;
        close(p1[1]);
        close(p2[0]);
    } else {
        // Parent process
        close(p1[1]);
        close(p2[0]);
        srand(time(NULL));
        int y = rand() % 10;
        printf("start from %d\n", y);
        if (write(p2[1], &y, sizeof(y)) == -1) return 5;
        if (read(p1[0], &y, sizeof(y)) == -1) return 6;
        printf("Result is %d\n", y);
        close(p1[0]);
        close(p2[1]);
    }
    close(p1[0]);
    close(p1[1]);
}