#include <stdio.h>

int check(char *current_string) {
    if (current_string[0] >= 65 && current_string[0] <= 90) {
        return 1;
    } else {
        return 2;
    }
}



int main() {
    FILE *logfile = fopen("log", "a");

    char *string_iterator;
    unsigned long int length = 0;
    while (getline(&string_iterator, &length, stdin) != -1) {
        fprintf(logfile, "CHILD received: [%s]\n", string_iterator);
        if (check(string_iterator) == 1) {
            printf("%s", string_iterator);
        } else {
            fprintf(stderr, "%sstarts from lower\n", string_iterator);
        }
    }
    fclose(logfile);
}