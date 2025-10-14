#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
/* 
    - Giữ cờ đếm broadcast_count – đại diện cho “phiên dữ liệu hiện tại”.

    - Mỗi worker lưu last_handled riêng của nó.

    - Nếu broadcast_count > last_handled → có dữ liệu mới → worker đọc.

*/
#define MAX_WORKER 3

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int data = 0;
int broadcast_count = 0;  // số lần signaler broadcast

typedef struct {
    int id;               // id đại diện cho mỗi thread worker
    int last_handled;     // worker nhớ mình đã xử lý đến broadcast nào
} worker_info_t;

void* worker(void* arg) {
    worker_info_t* info = (worker_info_t*)arg;
    while (1) {
        pthread_mutex_lock(&mtx);

        //lặp liên tục nếu signaler chưa có thông báo mới -> broadcast_count chưa được update
        while (info->last_handled == broadcast_count) {
            printf("[worker %d] : waiting for new data\n", info->id);
            pthread_cond_wait(&cond, &mtx);
        }

        // Cập nhật trạng thái và xử lý dữ liệu mới
        info->last_handled = broadcast_count;   
        printf("[worker %d] : reading data %d (broadcast %d)\n",
               info->id, data, broadcast_count);
        pthread_mutex_unlock(&mtx);

        usleep(500000); // giả lập thời gian xử lý 0.5s
    }
    return NULL;
}

void* signaler(void* arg) {
    char* nameTask = (char*)arg;
    while (1) {
        pthread_mutex_lock(&mtx);
        data = rand() % 100;
        if (data > 30) {
            broadcast_count++;
            printf("[%s] : broadcast new data = %d (broadcast %d)\n",
                   nameTask, data, broadcast_count);
            pthread_cond_broadcast(&cond);
        } else {
            printf("[%s] : skip broadcast (data=%d)\n", nameTask, data);
        }
        pthread_mutex_unlock(&mtx);

        sleep(1);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t signal_thread;
    pthread_t workers[MAX_WORKER];
    worker_info_t infos[MAX_WORKER];

    pthread_create(&signal_thread, NULL, signaler, "signaler");

    for (int i = 0; i < MAX_WORKER; i++) {
        infos[i].id = i + 1;
        infos[i].last_handled = 0;
        pthread_create(&workers[i], NULL, worker, &infos[i]);
    }

    pthread_join(signal_thread, NULL);
    return 0;
}
