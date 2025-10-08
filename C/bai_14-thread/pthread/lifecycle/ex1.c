#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// void* worker(void* arg) {
//     int* result = malloc(sizeof(int));
//     *result = 42;  // giá trị giả định
//     printf("Worker: done, result = %d\n", *result);
//     pthread_exit(result); // trả kết quả về cho join() và dừng luồng hiện tại
// }

void* worker(void* arg) {
    for(int i = 0 ; i < 5 ; i++){
        printf("worker : counts %d\n",i);
        sleep(1);
    }
    printf("worker : done\n");
    pthread_exit(NULL); // trả kết quả về cho join() và dừng luồng hiện tại
}


int main() {
    pthread_t t;

    pthread_create(&t, NULL, worker, NULL);

    /*join chờ thread kết thúc */
    // void* retval;
    //pthread_join(t, &retval);
    // int* result = (int*)retval;
    // printf("Main: got result = %d\n", *result);
    // free(result);

    /* demo detach chạy độc lập */
    pthread_detach(t);
    for(int i = 0 ; i < 15 ; i++){
        printf("[thread main] : is counting %d\n",i);
        usleep(500000);
    }
    printf("[thread main] : done");
    return 0;
}
