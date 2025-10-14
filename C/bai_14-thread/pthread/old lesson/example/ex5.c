// build: gcc -std=c11 -O2 -pthread demo_atomic_cleanup.c -o demo
#include <stdatomic.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// ====== Mailbox đơn giản: ISR/Sensor viết, App đọc ======
typedef struct {
    unsigned seq;     // số thứ tự mẫu
    int      value;   // giá trị đo (giả lập)
} SensorMsg;

static SensorMsg   g_mailbox;
static atomic_bool g_has_msg = ATOMIC_VAR_INIT(false);  // cờ có mẫu mới
static atomic_bool g_running = ATOMIC_VAR_INIT(true);   // cờ chạy hệ thống

static pthread_mutex_t g_m = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  g_cv = PTHREAD_COND_INITIALIZER;

// Cleanup handler: đảm bảo luôn unlock nếu thread bị hủy.
static void unlock_mutex(void *pm) {
    pthread_mutex_t *m = (pthread_mutex_t*)pm;
    pthread_mutex_unlock(m);
}

// Giả lập luồng “Sensor/ISR”: định kỳ tạo mẫu và báo cờ
void* SensorThread(void* arg) {
    (void)arg;
    unsigned seq = 0;
    //kiểm tra trạng thái luồng qua biến g_running
    while (atomic_load_explicit(&g_running, memory_order_acquire)) {
        // Giả lập đo đạc
        SensorMsg tmp = { .seq = ++seq, .value = (int)(seq * 10) };

        // Ghi vào mailbox (dưới mutex để tránh app đọc cùng lúc)
        pthread_mutex_lock(&g_m);
        g_mailbox = tmp; // ghi dữ liệu trước
        // Báo có mẫu (release: đảm bảo dữ liệu đã sẵn sàng)
        atomic_store_explicit(&g_has_msg, true, memory_order_release);
        pthread_cond_signal(&g_cv);
        pthread_mutex_unlock(&g_m);

        usleep(80 * 1000); // 80ms
    }
    printf("cancelled SensorThread\n");
    return NULL;
}

// Luồng ứng dụng đọc và xử lý mẫu. Dùng cleanup để unlock an toàn khi bị hủy.
void* AppThread(void* arg) {
    (void)arg;

    pthread_mutex_lock(&g_m);
    // Đăng ký cleanup để nếu thread bị cancel tại cond_wait, mutex vẫn được unlock.
    pthread_cleanup_push(unlock_mutex, &g_m);

    while (atomic_load_explicit(&g_running, memory_order_acquire)) {
        // Chờ có mẫu (cancellation point): nếu bị cancel, handler sẽ unlock.
        while (!atomic_load_explicit(&g_has_msg, memory_order_acquire)) {
            pthread_cond_wait(&g_cv, &g_m);
            if (!atomic_load_explicit(&g_running, memory_order_acquire))
                break;
        }
        if (!atomic_load_explicit(&g_running, memory_order_acquire))
            break;

        // Lấy snapshot mailbox
        SensorMsg local = g_mailbox;
        // Reset cờ (đã nhận) — có thể dùng exchange để “nhận 1 lần”
        atomic_store_explicit(&g_has_msg, false, memory_order_release);

        // Có thể tạm thời thả lock để xử lý nặng bên ngoài (giảm tắc nghẽn)
        pthread_mutex_unlock(&g_m);

        // ==== Xử lý mẫu (phần thời gian thực/ứng dụng) ====
        printf("[APP] seq=%u, value=%d\n", local.seq, local.value);
        // ==================================================

        // Lấy lại lock để quay vòng chờ tiếp
        pthread_mutex_lock(&g_m);
    }
    printf("cancelled AppThread\n");
    // pop và THỰC THI cleanup (execute=1) để bảo đảm mutex mở khi thoát bình thường
    pthread_cleanup_pop(1);
    return NULL;
}

int main(void) {
    pthread_t th_sensor, th_app;
    pthread_create(&th_sensor, NULL, SensorThread, NULL);
    pthread_create(&th_app, NULL, AppThread, NULL);

    // Chạy thử 1.2 giây rồi “shutdown” (giả lập hệ nhúng dừng dịch vụ)
    //usleep(1200 * 1000);
    for(;;);
    
    // Yêu cầu dừng hệ thống 
    //-> sẽ thực hiện khi terminated đột ngột, tự động thu hồi tài nguyên
    //-> gọi unlock mutex nếu mutex đang bị locked
    atomic_store_explicit(&g_running, false, memory_order_release);
   
    // Đánh thức app nếu nó đang chờ
    pthread_mutex_lock(&g_m);
    pthread_cond_broadcast(&g_cv);
    pthread_mutex_unlock(&g_m);

   
    // Hủy app thread (minh họa trường hợp bị cancel giữa wait/giữa lock)
    pthread_cancel(th_app);


    pthread_join(th_app, NULL);
    pthread_join(th_sensor, NULL);
    
    return 0;
}
