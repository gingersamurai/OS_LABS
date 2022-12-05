#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main() {
    int *array;
    int length;
    printf("enter lenght of array: ");
    scanf("%d", &length);
    array = (int *)malloc(sizeof(int) * length);

    printf("enter elements of array:\n");
    for (int index = 0; index < length; index++) {
        scanf("%d", &array[index]);
    }

    int threads_count;
    printf("enter count of threads: ");
    scanf("%d", &threads_count);


    printf("result:\n");
    for (int index = 0; index < length; index++) {
        printf("%d ", array[index]);
    }
    printf("\n");
}