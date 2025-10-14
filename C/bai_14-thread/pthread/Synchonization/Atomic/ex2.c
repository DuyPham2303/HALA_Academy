#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

atomic_int data_ready = 0;
int shared_data = 0;
/* 
    - MÔ phỏng cơ chế quản lý cờ trạng thái 
    - sử dụng store/load để ghi/đọc trạng thái của cờ -> quyết định khi nào kiểm tra dữ liệu
*/
void* producer(void* arg) {
    for(int i = 0 ; i < 10 ; i++){
        shared_data = rand() % 50;  //mô phỏng data ngẫu nhiên
        //đánh dấu trạng thái có data
        atomic_store(&data_ready, 1);  // Ghi flag atomically
        printf("Producer: data sẵn sàng!\n");
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    while(1){
        printf("Consumer: đợi dữ liệu...\n");
        while (atomic_load(&data_ready) == 0) { // Đọc flag atomically
            // Có thể thêm sleep nhỏ để giảm CPU
            //printf("checking dataReady\n");
            usleep(1000);
        }
        printf("Consumer: nhận được data = %d\n", shared_data);

        //reset flag để đợi tín hiệu mới
        atomic_store(&data_ready, 0);  // Ghi flag atomically
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t t1, t2;
    pthread_create(&t1, NULL, producer, NULL);
    pthread_create(&t2, NULL, consumer, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}
