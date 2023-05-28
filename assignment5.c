#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[100];
    int status;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(pipefd[1]);
        read(pipefd[0], buffer, sizeof(buffer));

        printf("Child process received message: %s\n", buffer);

        close(pipefd[0]);

        exit(EXIT_SUCCESS);
    } else {
        close(pipefd[0]);

        printf("Parent process sending message...\n");

        write(pipefd[1], "Hello from the parent process!", 29);

        close(pipefd[1]);
        wait(&status);

        printf("Parent process exiting.\n");
    }

    return 0;
}

