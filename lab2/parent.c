#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>



int main() {
    char filename[100];
    scanf("%s", filename);
    int file = open(filename, O_WRONLY | O_CREAT, 0777);
    int pipe1[2];  // p -> c
    int pipe2[2];  // c -> p
    if (pipe(pipe1) == -1) return 1;
    if (pipe(pipe2) == -1) return 1;

    if (file == -1) {
        return 1;
    }

    int pid = fork();
    if (pid == 0) {
        // child

        // redirect stdout to file
        dup2(file, STDOUT_FILENO);
        close(file);
        // redirect stdin
        dup2(pipe1[0], STDIN_FILENO);
        close(pipe1[0]);
        // redirect stderr to pipe2
        dup2(pipe2[1], STDERR_FILENO);
        close(pipe2[1]);
        

        int exec_res = execl("./build/child", "./build/child", NULL);
        if (exec_res == -1) {
            printf("Could not execute\n");
            return 2;
        }
    } else {
        // parent
        FILE *logfile = fopen("parlog", "a");


        dup2(pipe2[0], STDOUT_FILENO);
        close(pipe2[0]);

        char * string_iterator;
        unsigned long int length = 0;
        while (getline(&string_iterator, &length, stdin) != -1) {
            fprintf(logfile, "PARENT transmitted: [%s]\n", string_iterator);
            write(pipe1[1], string_iterator, strlen(string_iterator));
        }
        fclose(logfile);
    }
}
