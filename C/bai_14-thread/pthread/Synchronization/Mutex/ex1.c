#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_THREADS 5
pthread_mutex_t log_mutex;

void* print_log(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&log_mutex);   // 🔒 Bắt đầu vùng in an toàn
        printf("[Thread %d] processing step %d done.\n", id, i);
        pthread_mutex_unlock(&log_mutex); // 🔓 Kết thúc vùng in
        usleep(1000 * (rand() % 100));
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];
    srand(time(NULL));

    pthread_mutex_init(&log_mutex, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, print_log, &ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&log_mutex);
    printf("All threads done.\n");
    return 0;
}
