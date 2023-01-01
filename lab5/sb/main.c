#include <dlfcn.h>
#include <stdio.h>

void (*hello_message)(const char *name);

int init_library() {
    void *hdl = dlopen("./libhello.so", RTLD_LAZY);
    if (!hdl) {
        return 0;
    }
    
    hello_message = (void (*)(const char*))dlsym(hdl, "hello_message");
    if (!hello_message) {
        return 0;
    }

    return 1;
}

int main() {
    if (init_library()) {
        hello_message("Nazim");
    } else {
        printf("error");
    }
}