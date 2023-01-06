#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main() {
    time_t t1, t2;
    time(&t1);
    usleep(1000000);
    time(&t2);
    printf("%f", difftime(t2, t1));
}