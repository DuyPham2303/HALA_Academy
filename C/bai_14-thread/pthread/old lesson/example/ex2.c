#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int sensor_data = 0;
int data_ready = 0;

void* sensor_thread(void* arg) {
    while (1) {
        sleep(1); // Giả lập thời gian đọc cảm biến

        pthread_mutex_lock(&lock);
        sensor_data = rand() % 100;  // Giả lập dữ liệu cảm biến
        data_ready = 1;
        printf("[Sensor] Dữ liệu cảm biến: %d\n", sensor_data);
        pthread_cond_signal(&cond);  // Báo cho thread xử lý biết có dữ liệu mới
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void* processing_thread(void* arg) {
    while (1) {
        pthread_mutex_lock(&lock);
        while (!data_ready) {
            pthread_cond_wait(&cond, &lock);  // Chờ đến khi có dữ liệu
        }

        int data = sensor_data;
        data_ready = 0;
        pthread_mutex_unlock(&lock);

        int result = data * data;  // Xử lý: bình phương dữ liệu
        printf("[Processor] Dữ liệu đã xử lý: %d^2 = %d\n", data, result);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t t1, t2;

    pthread_create(&t1, NULL, sensor_thread, NULL);
    pthread_create(&t2, NULL, processing_thread, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
