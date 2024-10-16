#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <num_of_processes>\n", argv[0]);
        return 1;
    }

    int num_of_precesses = atoi(argv[1]);

    for (int i = 0; i < num_of_precesses; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            printf("Parent PID: %d, Child PID: %d\n", getppid(), getpid());
            exit(EXIT_SUCCESS);
        }
    }

    for (int i = 0; i < num_of_precesses; i++) {
        wait(NULL);
    }

    printf("\nNumber of processes: %d\n", num_of_precesses);

    return 0;
}

