#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>

#include "utils.h"

volatile bool should_close = false;

void signal_handler(int signum) {
    should_close = true;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <number_of_printers>\n", argv[0]);
        return -1;
    }

    int number_of_printers = atoi(argv[1]);

    // Open shared memory
    int memory_fd = shm_open(SHARED_MEMORY_DESCRIPTOR_NAME, O_CREAT | O_RDWR, 0666);
    if (memory_fd == -1) {
        perror("shm_open");
        return -1;
    }

    // Size of the shared memory object
    size_t shm_size = sizeof(memory_map_t);
    int shm_ftruncate = ftruncate(memory_fd, shm_size);
    if (shm_ftruncate == -1) {
        perror("ftruncate");
        return -1;
    }

    // Map shared memory in this process's space
    memory_map_t *memory_map = mmap(NULL, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, memory_fd, 0);
    if (memory_map == MAP_FAILED) {
        perror("mmap");
        return -1;
    }

    // Prepare data
    memset(memory_map, 0, sizeof(memory_map_t));
    memory_map->number_of_printers = number_of_printers;

    // Register signal handler
    for (int sig = 1; sig < SIGRTMAX; sig++) {
        signal(sig, signal_handler);
    }

    // Handle printers
    for (int i = 0; i < number_of_printers; i++) {
        sem_init(&memory_map->printers[i].printer_semaphore, 1, 1);

        pid_t printer_pid = fork();
        if (printer_pid < 0) {
            perror("fork");
            return -1;
        } else if (printer_pid == 0) {
            while (!should_close) {
                if (memory_map->printers[i].printer_state == PRINTING) {
                    printf("Printer %d - ", i);
                    for (int j = 0; j < memory_map->printers[i].printer_buffer_size; j++) {
                        printf("%c", memory_map->printers[i].printer_buffer[j]);
                        sleep(1);
                    }

                    printf("\n");

                    memory_map->printers[i].printer_state = WAITING;

                    sem_post(&memory_map->printers[i].printer_semaphore);
                }
            }

            return 0;
        }
    }

    // Wait for all children to finish
    while (wait(NULL) > 0) {}

    // Cleanup
    for (int i = 0; i < number_of_printers; i++) {
        sem_destroy(&memory_map->printers[i].printer_semaphore);
    }
    sem_destroy(&memory_map->queue_semaphore);
    munmap(memory_map, sizeof(memory_map_t));
    shm_unlink(SHARED_MEMORY_DESCRIPTOR_NAME);

    return 0;
}