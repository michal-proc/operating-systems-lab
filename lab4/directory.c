#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int global = 0; // Global variable

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    printf("Program name: %s\n", argv[0]);

    int local = 0; // Local variable

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork()");
        return 1;
    }

    if (pid == 0) {
        printf("\nchild process\n");

        // Increment
        global++;
        local++;

        printf("child pid = %d, parent pid = %d\n", getpid(), getppid());
        printf("child's local = %d, child's global = %d\n", local, global);

        execl("/bin/ls", "ls", argv[1], (char *) NULL);
        perror("execl");
        return EXIT_FAILURE;
    } else {
        int status;
        waitpid(pid, &status, 0);

        printf("\nparent process\n");
        printf("parent pid = %d, child pid = %d\n", getpid(), pid);

        if (WIFEXITED(status)) {
            printf("Child exit code: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child exited with error\n");
        }

        printf("Parent's local = %d, parent's global = %d\n", local, global);
        return WEXITSTATUS(status);
    }
}