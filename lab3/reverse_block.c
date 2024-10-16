#include <stdio.h>
#include <time.h>

#define BLOCK_SIZE 1024

void reverse_by_block(char *input_file_name, char *output_file_name) {
    FILE *input_file = fopen(input_file_name, "rb");
    FILE *output_file = fopen(output_file_name, "wb");
    char buffer[BLOCK_SIZE];

    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    long offset = -(file_size % BLOCK_SIZE);

    while (fseek(input_file, offset, SEEK_END) == 0) {
        size_t bytes_read = fread(buffer, 1, BLOCK_SIZE, input_file);
        if (bytes_read > 0) {
            for (size_t i = 0; i < bytes_read / 2; i++) {
                char temp = buffer[i];
                buffer[i] = buffer[bytes_read - 1 - i];
                buffer[bytes_read - 1 - i] = temp;
            }
            fseek(input_file, -((long) bytes_read + BLOCK_SIZE), SEEK_CUR);
            fwrite(buffer, sizeof(char), bytes_read, output_file);
        }

        offset -= BLOCK_SIZE;
        if (-offset >= file_size + BLOCK_SIZE) {
            break;
        }
    }

    fclose(input_file);
    fclose(output_file);
}

int main(int argc, char *args[]) {
    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file> \n", args[0]);
        return 1;
    }

    struct timespec start, end;

    clock_gettime(CLOCK_REALTIME, &start);

    reverse_by_block(args[1], args[2]);

    clock_gettime(CLOCK_REALTIME, &end);

    int execution_time = end.tv_nsec - start.tv_nsec;
    printf("Execution time - reverse_by_block(): %i nanoseconds\n", execution_time);

    return 0;
}
