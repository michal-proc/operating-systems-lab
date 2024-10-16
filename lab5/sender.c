#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int signal_received = 0;

void signal_handler(int sig) {
    signal_received = 1;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Missing argument. Usage: %s <catcher_pid> <work_mode>\n", argv[0]);
        return 1;
    }

    int catcher_pid = atoi(argv[1]);
    int work_mode = atoi(argv[2]);

    signal(SIGUSR1, signal_handler);

    union sigval signal_value;
    signal_value.sival_int = work_mode;
    sigqueue(catcher_pid, SIGUSR1, signal_value);

    while (!signal_received) {
        pause();
    }

    return 0;
}
