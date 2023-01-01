#include <stdio.h>
#include <dlfcn.h>

int main() {
    float (*get_pi)(int);
    float (*get_e)(int);

    int curlib = 1;
    void *handler = dlopen("libmymath1.so", RTLD_LAZY);
    get_e = dlsym(handler, "get_e");
    get_pi = dlsym(handler, "get_pi");

    while (1) {
        printf("enter command: ");
        int command;
        scanf("%d", &command);
        if (command == 1) {
            printf("enter value of k: ");
            int k;
            scanf("%d", &k);
            printf("result: %f\n", get_pi(k));
        } else if (command == 2) {
            printf("enter value of x: ");
            int x;
            scanf("%d", &x);
            printf("result: %f\n", get_e(x));
        } else if (command == 0) {
            dlclose(handler);
            if (curlib == 1) {
                handler = dlopen("libmymath2.so", RTLD_LAZY);
            } else {
                handler = dlopen("libmymath1.so", RTLD_LAZY);
            }
            get_e = dlsym(handler, "get_e");
            get_pi = dlsym(handler, "get_pi");
            curlib = 3 - curlib;
        }
    }
}