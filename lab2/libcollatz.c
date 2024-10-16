int collatz_conjecture(int input) {
    if (input % 2 == 0) {
        return input / 2;
    }

    return 3 * input + 1;
}

int test_collatz_convergence(int input, int max_iter) {
    for (int index = 0; index < max_iter; index++) {
        input = collatz_conjecture(input);
        if (input == 1) {
            return index + 1;
        }
    }

    return -1;
}
