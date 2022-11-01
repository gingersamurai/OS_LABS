#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main() {
    // init pipes
    int parent_to_child[2];
    int child_to_parent[2];
    if (pipe(parent_to_child) == -1) return 1;
    if (pipe(child_to_parent) == -1) return 1;

    printf("enter name of file: ");
    char filename[100];
    scanf("%s", filename);
    int file = open(filename, O_WRONLY | O_CREAT, 0777);

    if (file == -1) {
        return 2;
    }

    int parent_id = fork();
    if (parent_id == 0) {
        // child

        // close useless fd
        close(parent_to_child[1]);
        close(child_to_parent[0]);

        // redirect input
        if (dup2(parent_to_child[0], STDIN_FILENO) == -1) {
            return 2;
        }
        close(parent_to_child[0]);

        // redirect output
        if (dup2(file, STDOUT_FILENO) == -1) {
            return 2;
        }
        close(file);

        // redirect error
        if (dup2(child_to_parent[1], STDERR_FILENO) == -1) {
            return 2;
        }
        close(child_to_parent[1]);

        if (execl("./build/child", "./build/child", NULL) == -1) {
            return 3;
        }

    } else {
        // parent

        // close useless fd
        close(parent_to_child[0]);
        close(child_to_parent[1]);

        int string_count;
        printf("enter count of strings: ");
        scanf("%d", &string_count);
        write(parent_to_child[1], &string_count, sizeof(int));
        for (int iteration = 0; iteration < string_count; ++iteration) {
            int string_len;
            printf("enter size of string: ");
            scanf("%d", &string_len);
            write(parent_to_child[1], &string_len, sizeof(int));

            char current_string[string_len];
            printf("enter string: ");
            scanf("%s", current_string);
            write(parent_to_child[1], current_string,
                  sizeof(current_string) + 1);
        }

        close(parent_to_child[1]);

        wait(NULL);

        char buffer;
        while (read(child_to_parent[0], &buffer, sizeof(char)) > 0) {
            printf("%c", buffer);
        }
        printf("\nDONE\n");
    }
}
