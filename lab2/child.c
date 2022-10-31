#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int check(char *current_string) {
    if (current_string[0] >= 65 && current_string[0] <= 90) {
        return 1;
    } else {
        return 2;
    }
}

int main() {
    int string_len;
    read(STDIN_FILENO, &string_len, sizeof(int));

    char parent_string[string_len];
    scanf("%s", parent_string);
    int res;
    if (check(parent_string) == 1) {
        printf("%s\n", parent_string);
    } else {
        char error_message[23];
        fprintf(stderr, "string [%s] in incorrect\n", parent_string);
    }
}