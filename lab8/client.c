#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>

#include "utils.h"

volatile bool should_close = false;


void signal_handler(int signum) {
    should_close = true;
}


void generate_random_string(char *buffer, int length) {
    for (int i = 0; i < length; i++) {
        buffer[i] = 'a' + rand() % 26;
    }
    buffer[length] = '\0';
}


int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <number_of_users>\n", argv[0]);
        return -1;
    }

    int number_of_users = atoi(argv[1]);

    // Random seed
    srand(time(NULL));

    // Open shared memory
    int memory_fd = shm_open(SHARED_MEMORY_DESCRIPTOR_NAME, O_RDWR, S_IRUSR | S_IWUSR);
    if (memory_fd < 0)
        perror("shm_open");

    // Map shared memory in this process's space
    memory_map_t *memory_map = mmap(NULL, sizeof(memory_map_t), PROT_READ | PROT_WRITE, MAP_SHARED, memory_fd, 0);
    if (memory_map == MAP_FAILED) {
        perror("mmap");
    }

    // Define buffer
    char user_buffer[MAX_PRINTER_BUFFER_SIZE] = {0};

    // Register signal handler
    for (int sig = 1; sig < SIGRTMAX; sig++) {
        signal(sig, signal_handler);
    }

    // spawn users
    for (int i = 0; i < number_of_users; i++) {
        pid_t user_pid = fork();

        if (user_pid < 0) {
            perror("fork");
            return -1;
        } else if (user_pid == 0) {
            while (!should_close) {
                generate_random_string(user_buffer, 10);

                int printer_index = -1;
                for (int j = 0; j < memory_map->number_of_printers; j++) {
                    int val;
                    sem_getvalue(&memory_map->printers[j].printer_semaphore, &val);
                    if (val > 0) {
                        printer_index = j;
                        break;
                    }
                }

                if (printer_index == -1)
                    printer_index = rand() % memory_map->number_of_printers;

                if (sem_wait(&memory_map->printers[printer_index].printer_semaphore) < 0)
                    perror("sem_wait");

                memcpy(memory_map->printers[printer_index].printer_buffer, user_buffer, MAX_PRINTER_BUFFER_SIZE);
                memory_map->printers[printer_index].printer_buffer_size = strlen(user_buffer);

                memory_map->printers[printer_index].printer_state = PRINTING;

                printf("User %d is printing on printer %d\n", i, printer_index);

                sleep(rand() % 3 + 1);
            }
            return 0;
        }
    }

    // Wait for all children to finish
    while (wait(NULL) > 0) {};

    // Clean up
    munmap(memory_map, sizeof(memory_map_t));

    return 0;
}