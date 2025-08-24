#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int sensor_data = 0;
int data_ready = 0;

void* sensor_thread(void* arg) {
    while (1) {
        sleep(1); // giả lập thời gian đọc cảm biến
        int new_data = rand() % 100;

        pthread_mutex_lock(&lock);
        sensor_data = new_data;
        data_ready = 1;
        printf("Sensor: Dữ liệu mới = %d\n", sensor_data);
        pthread_cond_signal(&cond); // báo có dữ liệu mới
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void* processor_thread(void* arg) {
    while (1) {
        pthread_mutex_lock(&lock);
        while (!data_ready) {
            pthread_cond_wait(&cond, &lock); // chờ dữ liệu
        }
        printf("Processor: Xử lý dữ liệu = %d\n", sensor_data);
        data_ready = 0; // đánh dấu đã xử lý
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, sensor_thread, NULL);
    pthread_create(&t2, NULL, processor_thread, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
