#include "Os.h"

#include <pthread.h>   /* pthread_t, mutex, condvar */
#include <stdatomic.h> /* atomic_int cho cờ “đang chạy” */
#include <unistd.h>    /* sleep/usleep/pause */
#include <time.h>      /* nanosleep */
#include <stdio.h>     /* printf, perror */
#include <string.h>    /* memset (nếu cần) */
#include <signal.h>    /* _exit trên POSIX */
#include <errno.h>     /* errno cho log lỗi */


/*  - 
    - LifeCycle : StartOs , ShutdownOs 
    - Task      : ActivateTask, TerminateTask
    - TaskListConfig : task config table, block quản lý thông tin task
*/

/* ****************************************************************************************
 * TIỆN ÍCH THỜI GIAN
 * **************************************************************************************** */
static void OS_SleepMs(uint32_t ms)
{
    struct timespec ts;
    ts.tv_sec = (time_t)(ms / 1000u);
    ts.tv_nsec = (long)((ms % 1000u) * 1000000L);
    (void)nanosleep(&ts, NULL);
}

/* ****************************************************************************************
 * QUẢN LÝ TASK (Task Control)
 * **************************************************************************************** */
typedef struct
{
    pthread_t thread;     /* Thread POSIX đại diện cho Task */
    pthread_mutex_t mtx;  /* Mutex bảo vệ event mask */
    pthread_cond_t cv;    /* Condition variable để WaitEvent thức dậy */
    EventMaskType events; /* Bitmask Event đang được set */
    atomic_int running;   /* 0 = chưa chạy/đã kết thúc ; 1 = đang chạy */
    const char *name;     /* Tên để in log */
    void (*entry)(void);  /* Con trỏ vào thân TASK() do ứng dụng định nghĩa */
} OsTaskCtl;

/* Bảng ánh xạ ID → entry function (do Os_Cfg.h công bố ID) */
static OsTaskCtl s_task[TASK_COUNT] =
    {
        [InitTask_ID] = {.entry = InitTask, .name = "InitTask"},
        [Task_10ms_ID] = {.entry = Task_10ms, .name = "Task_10ms"},
        [Task_100ms_ID] = {.entry = Task_100ms, .name = "Task_100ms"},
        [Task_Com_ID] = {.entry = Task_Com, .name = "Task_Com"},
        [Task_Can_ID] = {.entry = Task_Can, .name = "Task_Can"},
};


StatusType StartOS(uint8_t appMode)
{
    (void)appMode;

    /* Reset trạng thái các Task */
    for (int i = 0; i < TASK_COUNT; ++i)
    {
        s_task[i].thread = (pthread_t)0;
        // mặc định các bit đều được reset -> chưa có task nào được set
        s_task[i].events = 0u;
        // Khai báo trạng thái ban đầu của từng task -> mỗi task sẽ sử dụng 1 biến running để xác định trạng thái đang chạy/dừng
        (void)atomic_exchange(&s_task[i].running, 0);
        /* Mutex/cond sẽ được init lại khi ActivateTask */
    }

    /* Reset trạng thái các Alarm */
    for (int i = 0; i < ALARM_COUNT; ++i)
    {
        s_alarm[i].thread = (pthread_t)0;
        s_alarm[i].start_ms = 0u;
        s_alarm[i].cycle_ms = 0u;
        (void)atomic_exchange(&s_alarm[i].active, 0);
    }

    /* Hook khởi động (app có thể in log) */
    StartupHook();

    /* Autostart: InitTask */
    (void)ActivateTask(InitTask_ID);

    /* Khởi tạo sẵn và đợi event để xử lý*/
    (void)ActivateTask(Task_Com_ID);

    /* Vòng “idle” giữ process sống trong mô phỏng */
    for (;;)
    {
        sleep(1);
    }
    /* Unreachable */
}