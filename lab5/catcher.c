#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int mode_change_requests = 0;
int current_mode = -1;

void signal_handler(int sig, siginfo_t *siginfo, void *context) {
    mode_change_requests++;
    current_mode = (int) siginfo->si_int;
    kill(siginfo->si_pid, SIGUSR1);
}

int main() {
    printf("Catcher PID: %d\n", getpid());

    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = signal_handler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);

    while (1) { // Endless loop, handle signals
        pause();

        switch (current_mode) {
            case 1:
                for (int i = 1; i < 100; i++) {
                    printf("%i, ", i);
                }
                printf("100\n");
                break;
            case 2:
                printf("Number of received requests to change the mode of operation: %d\n", mode_change_requests);
                break;
            case 3:
                printf("Exiting...\n");
                return 0;
        }
    }
}

