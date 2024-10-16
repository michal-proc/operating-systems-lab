#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>

double f(double x) {
    return 4.0 / (x * x + 1);
}

void compute_integral(double start, double end, double interval_width, int pipe_fd) {
    double sum = 0.0;
    for (double x = start; x < end; x += interval_width) {
        sum += f(x) * interval_width;
    }
    write(pipe_fd, &sum, sizeof(double));
    close(pipe_fd);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <interval_width> <number_of_processes>\n", argv[0]);
        return EXIT_FAILURE;
    }

    double interval_width = atof(argv[1]);
    int number_of_processes = atoi(argv[2]);

    int pipes[number_of_processes][2];
    pid_t pids[number_of_processes];

    struct timespec start, end;

    clock_gettime(CLOCK_REALTIME, &start);

    for (int i = 0; i < number_of_processes; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            return -1;
        }
    }

    for (int i = 0; i < number_of_processes; i++) {
        double range_start = (double) i / number_of_processes;
        double range_end = (double) (i + 1) / number_of_processes;
        pids[i] = fork();
        if (pids[i] == 0) {
            close(pipes[i][0]); // Close the reading end in the child
            compute_integral(range_start, range_end, interval_width, pipes[i][1]);
            exit(EXIT_SUCCESS);
        } else if (pids[i] < 0) {
            perror("fork");
            return EXIT_FAILURE;
        }
        close(pipes[i][1]); // Close the writing end in the parent
    }

    double result = 0.0, partial_result;
    for (int i = 0; i < number_of_processes; i++) {
        close(pipes[i][1]);
        read(pipes[i][0], &partial_result, sizeof(double));
        result += partial_result;
        close(pipes[i][0]);
    }

    for (int i = 0; i < number_of_processes; i++) {
        wait(NULL);
    }

    clock_gettime(CLOCK_REALTIME, &end);
    int execution_time = end.tv_nsec - start.tv_nsec;

    printf("Integral approximation: %f\n", result);
    printf("Execution time: %i ms\n", execution_time);

    FILE *file = fopen("report.txt", "a");
    if (file != NULL) {
        fprintf(file, "Width: %f, Processes: %d, Result: %f, Time: %i ns\n", interval_width, number_of_processes,
                result,
                execution_time);
        fclose(file);
    } else {
        perror("fopen");
        return -1;
    }

    return 0;
}