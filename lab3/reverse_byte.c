#include <stdio.h>
#include <time.h>

void reverse_by_byte(char *input_file_name, char *output_file_name) {
    FILE *input_file = fopen(input_file_name, "rb");
    FILE *output_file = fopen(output_file_name, "wb");
    char buffer;
    int i = -1;

    while (fseek(input_file, i--, SEEK_END) == 0) {
        fread(&buffer, sizeof(char), 1, input_file);
        fwrite(&buffer, sizeof(char), 1, output_file);
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

    reverse_by_byte(args[1], args[2]);

    clock_gettime(CLOCK_REALTIME, &end);

    int execution_time = end.tv_nsec - start.tv_nsec;
    printf("Execution time - reverse_by_byte(): %i nanoseconds\n", execution_time);

    return 0;
}