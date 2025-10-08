#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


#define NUM_THREADS 5

void* print_log(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < 10; i++) {
        // In nhiều phần nhỏ để dễ thấy log chồng chéo
        printf("[Thread %d] ", id);
        usleep(1000 * (rand() % 50));  // delay ngẫu nhiên
        printf("processing step %d ", i);
        usleep(1000 * (rand() % 50));
        printf("done.\n");  // xuống dòng cuối
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];
    srand(time(NULL));

    for (int i = 0; i < NUM_THREADS; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, print_log, &ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads done.\n");
    return 0;
}
