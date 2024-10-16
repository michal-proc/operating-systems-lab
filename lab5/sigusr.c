#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signal) {
    printf("The SIGUSR1 signal has been caught. Number of signal = %d\n", signal);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Missing argument. Usage: %s [none|ignore|handler|mask]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "none") == 0) {
        // Pass. Do not handle signal
    } else if (strcmp(argv[1], "ignore") == 0) {
        signal(SIGUSR1, SIG_IGN);
    } else if (strcmp(argv[1], "handler") == 0) {
        signal(SIGUSR1, signal_handler);
    } else if (strcmp(argv[1], "mask") == 0) {
        sigset_t set;
        sigemptyset(&set);
        sigaddset(&set, SIGUSR1);
        sigprocmask(SIG_SETMASK, &set, NULL);
    } else {
        printf("Undefined argument. Usage: %s [none|ignore|handler|mask]\n", argv[0]);
        return 1;
    }

    printf("Sending SIGUSR1 to self...\n");
    raise(SIGUSR1);

    if (strcmp(argv[1], "mask") == 0) {
        sigset_t pending;
        sigemptyset(&pending);
        sigpending(&pending);
        if (sigismember(&pending, SIGUSR1)) {
            printf("SIGUSR1 is pending.\n");
        } else {
            printf("SIGUSR1 is not pending.\n");
        }
    }

    return 0;
}