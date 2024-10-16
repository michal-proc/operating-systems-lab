#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

// === SANTA === //

pthread_mutex_t santa_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t santa_cond = PTHREAD_COND_INITIALIZER;

pthread_t santa_thread;

// === REINDEER === //

pthread_mutex_t reindeer_mutexes[9] = {
        PTHREAD_MUTEX_INITIALIZER,
        PTHREAD_MUTEX_INITIALIZER,
        PTHREAD_MUTEX_INITIALIZER,
        PTHREAD_MUTEX_INITIALIZER,
        PTHREAD_MUTEX_INITIALIZER,
        PTHREAD_MUTEX_INITIALIZER,
        PTHREAD_MUTEX_INITIALIZER,
        PTHREAD_MUTEX_INITIALIZER,
        PTHREAD_MUTEX_INITIALIZER
};

int reindeer_back_count = 0;
pthread_mutex_t reindeer_back_mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_t reindeer_threads[9];

// === THREAD HANDLERS === //

void *santa_thread_handler(void *arg) {
    for (int i = 0; i < 4; i++) {
        pthread_cond_wait(&santa_cond, &santa_mutex);
        printf("Mikołaj: budzę się\n");

        printf("Mikołaj: dostarczam zabawki\n");

        sleep(rand() % 3 + 2);

        for (int j = 0; j < 9; j++) {
            pthread_mutex_unlock(&reindeer_mutexes[j]);
        }

        printf("Mikołaj: zasypiam\n");
    }

    for (int j = 0; j < 9; j++) {
        pthread_cancel(reindeer_threads[j]);
    }
}

void *reindeer_thread_handler(void *arg) {
    int reindeer_id = *(int *) arg - 1;
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    pthread_mutex_lock(&reindeer_mutexes[reindeer_id]);
    while (1) {
        sleep(rand() % 6 + 5);

        pthread_mutex_lock(&reindeer_back_mutex);
        reindeer_back_count++;

        if (reindeer_back_count == 9) {
            printf("Renifer: budzę Mikołaja, %d\n", reindeer_id);
            pthread_cond_signal(&santa_cond);
            reindeer_back_count = 0;
        } else {
            printf("Renifer: czeka %d reniferów, %d\n", reindeer_back_count, reindeer_id);
        }

        pthread_mutex_unlock(&reindeer_back_mutex);

        pthread_mutex_lock(&reindeer_mutexes[reindeer_id]);

        printf("Renifer: lecę na wakacje, %d\n", reindeer_id);
    }
}

// === MAIN === //

int main() {
    // Random seed
    srand(time(NULL));

    int reindeer_ids[9];

    pthread_create(&santa_thread, NULL, santa_thread_handler, NULL);
    for (int i = 0; i < 9; i++) {
        reindeer_ids[i] = i + 1;
        pthread_create(&reindeer_threads[i], NULL, reindeer_thread_handler, &reindeer_ids[i]);
    }

    pthread_join(santa_thread, NULL);
    for (int i = 0; i < 9; i++) {
        pthread_join(reindeer_threads[i], NULL);
    }

    return 0;
}