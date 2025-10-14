#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdatomic.h>
#include <pthread.h>
#define ALARM  2
atomic_int data = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// Thread worker: làm 1 việc rồi dừng



void cleanup_mutex(void *arg) {
    pthread_mutex_t *mtx = (pthread_mutex_t *)arg;
    pthread_mutex_unlock(mtx);
    printf("Mutex unlocked by cleanup handler\n");
}

void *task_thread(void *arg) {
    pthread_mutex_lock(&lock);


    
void pthread_cleanup_push(void (*routine)(void *), void *arg);




    pthread_cleanup_push(cleanup_mutex, &lock);
    ...
    // thực hiện công việc chính
    ...
    pthread_cleanup_pop(1);
}



void cleanup_worker(void* arg){
    printf("%s done reclaim resources\n",(char*)arg);
    pthread_mutex_destroy(&mutex);
}

void* worker_thread(void* arg) {
    //đăng ký hàm cleanup sẽ được gọi khi luồng thực hiện xong
    pthread_cleanup_push(cleanup_worker,"Clean up Worker thread");

    //truy cập data và xử lý dữ liệu
    pthread_mutex_lock(&mutex);
    int id = *((int*)arg);
    printf("[Worker %d] Bắt đầu xử lý...\n", id);
    atomic_load(&data);
    int result = data * 2; 
    printf("[Worker %d] : result -> %d\tHoàn thành, thoát!\n", id,result);
    //bỏ truy cập data, cho phép các luồng khác sử dụng
    pthread_mutex_unlock(&mutex);

    pthread_cleanup_pop(1); //gọi hàm cleanup để thu hồi tài nguyên 

    //pthread_exit(NULL);
    return NULL;  // kết thúc thread
}
// Thread scheduler: tạo worker theo lịch
void* scheduler_thread(void* arg) {
    int counter = 0;
    int limit = 0;
    while (limit < 10) {
        static int alarmCnt = 0;
        if(alarmCnt < ALARM){
            printf("[Scheduler] : %d seconds \n",alarmCnt++);
        }
        else{
            pthread_t tid;
            counter++;
            int* id = malloc(sizeof(int));
            *id = counter; // truyền ID để phân biệt worker

            if (pthread_create(&tid, NULL, worker_thread, id) != 0) {
                perror("pthread_create worker failed");
                free(id);
                continue;
            }

            // DETACH: không cần join, thread tự thu dọn khi kết thúc
            //scheduler_thread không cẩn quan tâm đến kết quả xử lý 
            //-> ko cần chờ -> thực thi xong tự thu hồi ko cần báo về luồng chính
            pthread_detach(tid);   
            alarmCnt = 0;
            free(id);
            printf("[Scheduler] Đã tạo worker %d\n", counter);
            limit = counter;
        }
        sleep(1); // giả lập báo thức/alarm mỗi 5 giây
    }
    printf("[Os Scheduler] : Terminater\n");
    return NULL;
}

int main() {
    pthread_t sched;
    if (pthread_create(&sched, NULL, scheduler_thread, NULL) != 0) {
        perror("pthread_create scheduler failed");
        return 1;
    }
    
    // main thread chạy vô tận
    //pthread_detach(sched);
    for(int i = 0 ; i < 50 ; i++){
        int temp = rand() % 100;
        atomic_store(&data,temp);
        printf("[Main OS] : sensor read\t%d\n",data);
        usleep(500000);
    }

    pthread_join(sched,NULL);

    printf("[Main Os] : Terminated\n");

    return 0;
}
