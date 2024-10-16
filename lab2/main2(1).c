#include <stdio.h>
#include <dlfcn.h>

int main() {
    void *lib_collatz = dlopen("./libcollatz.so", RTLD_LAZY);
    if (!lib_collatz) {
        printf("Error");
        return 0;
    }

    int (*lib_test_collatz_convergence)(int, int);
    lib_test_collatz_convergence = dlsym(lib_collatz, "test_collatz_convergence");
    if (dlerror() != 0) {
        printf("Error");
        return 0;
    }

    int max_iter = 10;

    int numbers[] = {7, 20, 28, 36};
    int n = 4;

    for (int i = 0; i < n; i++) {
        int iterations = lib_test_collatz_convergence(numbers[i], max_iter);
        if (iterations != -1) {
            printf("Number %d converges to 1 within %d iterations.\n", numbers[i], iterations);
        } else {
            printf("Number %d does not converge to 1 within %d iterations.\n", numbers[i], max_iter);
        }
    }

    dlclose(lib_collatz);
    return 0;
}