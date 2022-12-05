#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct _subarray{
    int *array;
    int left;
    int right;
} subarray;

void swap(int *a, int *b) {
    int buffer = *a;
    *a = *b;
    *b = buffer;
}

void *insertion_sort(void *args) {
    subarray *current_arg = (subarray *) args;
    int *array = current_arg->array;
    int left = current_arg->left;
    int right = current_arg->right;

    
    for (int index = left+1; index <= right; index++) {
        int current_position = index;
        while (array[current_position] < array[current_position - 1]) {
            swap(&array[current_position], &array[current_position - 1]);
            current_position--;
            if (current_position == left) break;
        }
    }

    return 0;
}

void solve(int *array, int length, int threads_count) {
    printf("len: %d\tthr_cnt: %d\n", length, threads_count);
    int run_len = length / threads_count;
    int runs[threads_count][2];
    for (int i = 0; i < threads_count; i++) {
        runs[i][0] = run_len * i;
        runs[i][1] = run_len * (i+1) - 1;
    }
    runs[threads_count - 1][1] = length - 1;

    pthread_t threads[threads_count];
    subarray args[threads_count];
    for (int index = 0; index < threads_count; index++) {
        args[index].array = array;
        args[index].left = runs[index][0];
        args[index].right = runs[index][1];
        printf("[%d, %d]\n", args[index].left, args[index].right);
    }

    for (int index = 0; index < threads_count; index++) {
        int status = pthread_create(&threads[index], NULL, insertion_sort, (void *) &args[index]);
        if (status != 0) {
            exit(1);
        }
    }

    for (int index = 0; index < threads_count; index++) {
        int status_addr;
        int status = pthread_join(threads[index], (void **) &status_addr);
        if (status != 0) {
            exit(2);
        }
    }



}

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
    
    printf("\n");
    for (int index = 0; index < length; index++) {
        printf("%d ", array[index]);
    }
    printf("\n");

    solve(array, length, threads_count);

    printf("result:\n");
    for (int index = 0; index < length; index++) {
        printf("%d ", array[index]);
    }
    printf("\n");
}