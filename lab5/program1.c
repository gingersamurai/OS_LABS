#include <stdio.h>
#include "mymath.h"

int main() {
    while (1) {
        int command;
        printf("enter command: ");
        scanf("%d", &command);
        if (command == 1) {
            printf("enter length of row: ");
            int k;
            scanf("%d", &k);
            printf("result: %f\n", get_pi(k));
        } else if (command == 2) {
            printf("enter value of x: ");
            int x;
            scanf("%d", &x);
            printf("result: %f\n", get_e(x));
        } else {
            break;
        }
    }
}