#include <ncurses.h>
#include <locale.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include <signal.h>

#include "grid.h"

#define min(a, b) (a < b ? a : b)

typedef struct {
    int cell_start;
    int cell_end;

    char **background;
    char **foreground;
} pthread_t_args;

void signal_handler(int signum) {}

void *thread_function(void *arg) {
    pthread_t_args *args = (pthread_t_args *) arg;

    while (true) {
        update_grid(*args->foreground, *args->background);
        pause();
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <number_of_threads>\n", argv[0]);
        return -1;
    }

    int number_of_threads = atoi(argv[1]);

    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);

    srand(time(NULL));
    setlocale(LC_CTYPE, "");
    initscr();

    char *foreground = create_grid();
    char *background = create_grid();
    char *tmp;

    pthread_t threads[number_of_threads];
    pthread_t_args args[number_of_threads];

    int cells_per_thread = (int) ceil(GRID_HEIGHT * GRID_WIDTH / number_of_threads);
    for (int i = 0; i < number_of_threads; i++) {
        args[i].cell_start = i * cells_per_thread;
        args[i].cell_end = min((i + 1) * cells_per_thread, GRID_HEIGHT * GRID_WIDTH);

        args[i].foreground = &foreground;
        args[i].background = &background;

        pthread_create(&threads[i], NULL, thread_function, &args[i]);
    }

    init_grid(foreground);

    while (true) {
        draw_grid(foreground);

        for (int i = 0; i < number_of_threads; i++) {
            pthread_kill(threads[i], SIGUSR1);
        }

        usleep(500000);

        tmp = foreground;
        foreground = background;
        background = tmp;
    }

    endwin(); // End curses mode
    destroy_grid(foreground);
    destroy_grid(background);

    return 0;
}