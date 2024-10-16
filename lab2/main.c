#include <stdio.h>

extern int collatz_conjecture(int input);

extern int test_collatz_convergence(int input, int max_iter);

int main() {
    int max_iter = 10;

    int numbers[] = {6, 19, 27, 35};
    int n = 4;

    for (int i = 0; i < n; i++) {
        int iterations = test_collatz_convergence(numbers[i], max_iter);
        if (iterations != -1) {
            printf("Number %d converges to 1 within %d iterations.\n", numbers[i], iterations);
        } else {
            printf("Number %d does not converge to 1 within %d iterations.\n", numbers[i], max_iter);
        }
    }

    return 0;
}