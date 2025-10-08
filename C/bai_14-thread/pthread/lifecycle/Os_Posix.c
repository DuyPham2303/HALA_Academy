#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <unistd.h>

/* ==============================
 * CẤU TRÚC TASK CONTROL
 * ============================== */
typedef struct
{
    pthread_t thread;          // Thread POSIX đại diện cho Task
    atomic_int running;        // 1 = đang chạy, 0 = đã dừng
    const char *name;          // Tên Task
    void (*entry)(void);       // Con trỏ tới hàm thân TASK()
} OsTaskCtl;

/* ==============================
 * HÀM TASK GIẢ LẬP
 * ============================== */
void InitTask(void)
{
    printf("[InitTask] Bắt đầu thực thi.\n");
    for (int i = 0; i < 5; ++i)
    {
        printf("[InitTask] Tick %d\n", i);
        sleep(1);
    }
    printf("[InitTask] Kết thúc.\n");
    pthread_exit(NULL);
}

/* ==============================
 * HÀM DỌN DẸP (CLEANUP)
 * ============================== */
static void OS_TaskCleanup(void *arg)
{
    OsTaskCtl *tc = (OsTaskCtl *)arg;
    atomic_store(&tc->running, 0);
    printf("[OS] Task %s đã kết thúc, cleanup hoàn tất.\n", tc->name);
}

/* ==============================
 * HÀM TRAMPOLINE — nơi thread bắt đầu chạy
 * ============================== */
static void *OS_TaskTrampoline(void *arg)
{
    OsTaskCtl *tc = (OsTaskCtl *)arg;
    atomic_store(&tc->running, 1);

    // Đăng ký hàm cleanup để luôn được gọi khi thread kết thúc
    pthread_cleanup_push(OS_TaskCleanup, tc);

    // Gọi vào thân Task thật sự
    tc->entry();

    // Pop cleanup, tham số 1 = thực thi cleanup ngay
    pthread_cleanup_pop(1);
    return NULL;
}

/* ==============================
 * HÀM KÍCH HOẠT TASK (ActivateTask)
 * ============================== */
void ActivateTask(OsTaskCtl *tc)
{
    if (!atomic_load(&tc->running))
    {
        pthread_create(&tc->thread, NULL, OS_TaskTrampoline, tc);
        pthread_detach(tc->thread);
        printf("[OS] Đã kích hoạt %s (detached thread).\n", tc->name);
    }
    else
    {
        printf("[OS] %s đang chạy, bỏ qua.\n", tc->name);
    }
}

/* ==============================
 * MAIN DEMO
 * ============================== */
int main(void)
{
    OsTaskCtl initTask = {.name = "InitTask", .entry = InitTask};

    ActivateTask(&initTask);

    // Main thread giả lập vòng idle của OS
    for (int t = 0; t < 10; ++t)
    {
        printf("[Main] OS đang chạy... (%d)\n", t);
        sleep(1);
    }
    printf("[Main] Thoát chương trình.\n");
    return 0;
}
