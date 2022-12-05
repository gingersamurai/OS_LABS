#include <stdio.h>


void merge(int *array, int left1, int right1, int left2, int right2) {
    int new_array[right2 - left1 + 1];
    int result_index = 0;
    int index1 = left1;
    int index2 = left2;
    while (1) {
        if (index1 > right1) {
            while (index2 <= right2) {
                new_array[result_index++] = array[index2++];
            }
            break;
        } else if (index2 > right2) {
            while (index1 <= right1) {
                new_array[result_index++] = array[index1++];
            }
            break;
        } else if (array[index1] <= array[index2]) {
            new_array[result_index++] = array[index1++];
        } else if (array[index1] > array[index2]) {
            new_array[result_index++] = array[index2++];
        }
    }

    for (int index = left1; index <= right2; index++) {
        array[index] = new_array[index - left1];
    }
}


int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    merge(arr, 0, 2, 3, 6);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

}