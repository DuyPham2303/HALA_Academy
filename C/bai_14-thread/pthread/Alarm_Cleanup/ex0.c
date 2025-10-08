#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* 
    + pthread_exit() kết thúc thread ngay lập tức
     → không chạy phần sau 
     → cleanup không gọi → rò rỉ vùng nhớ buf.

    + Để cleanup hoạt động, phải pop trước khi exit hoặc đặt cờ đúng cách.

*/
void cleanup(void* arg) {
    printf("Cleaning up memory!\n");
    free(arg);
}

void* worker(void* arg) {
    char* buf = malloc(100);
    pthread_cleanup_push(cleanup, buf);

    printf("Doing something...\n");
    pthread_exit(NULL);  // ❌ cleanup chưa được pop -> bị bỏ qua
    pthread_cleanup_pop(1); // không bao giờ tới đây
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, worker, NULL);
    pthread_join(tid, NULL);
}
