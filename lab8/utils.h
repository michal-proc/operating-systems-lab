#ifndef PRINTERS_UTILS
#define PRINTERS_UTILS

#include <semaphore.h>

#define SHARED_MEMORY_DESCRIPTOR_NAME "shared_memory"

#define MAX_PRINTERS 256
#define MAX_PRINTER_BUFFER_SIZE 256

typedef enum {
    WAITING = 0,
    PRINTING = 1
} printer_state_t;

typedef struct {
    sem_t printer_semaphore;
    char printer_buffer[MAX_PRINTER_BUFFER_SIZE];
    size_t printer_buffer_size;
    printer_state_t printer_state;
} printer_t;

typedef struct {
    sem_t queue_semaphore;
    printer_t printers[MAX_PRINTERS];
    int number_of_printers;
} memory_map_t;

#endif