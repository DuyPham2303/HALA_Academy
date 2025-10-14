#include "alarm.h"


/* ****************************************************************************************
 * QUẢN LÝ ALARM (mức ms)
 * **************************************************************************************** */
typedef struct
{
    uint8_t id;        /* Alarm ID (theo Os_Cfg.h) */
    TickType start_ms; /* Trễ khởi động (ms) */
    TickType cycle_ms; /* Chu kỳ (ms); 0 = one-shot */
    pthread_t thread;  /* Thread POSIX đại diện cho Alarm */
    atomic_int active; /* 1 = đang hoạt động; 0 = dừng */
} OsAlarmCtl;

static OsAlarmCtl s_alarm[ALARM_COUNT] =
    {
        [Alarm_10ms] = {.id = Alarm_10ms},
        [Alarm_100ms] = {.id = Alarm_100ms},
        [Alarm_500ms] = {.id = Alarm_500ms},
};

static void *OS_AlarmThread(void *arg)
{
    OsAlarmCtl *const a = (OsAlarmCtl *)arg; // con trỏ đến block chứa cấu hình báo thức cho task chạy theo chu kỳ
    atomic_store(&a->active, 1);             // set trạng thái bắt đầu chạy

    /* Trễ khởi động một lần (nếu có) */
    if (a->start_ms > 0u)
    {
        OS_SleepMs(a->start_ms); // nạp thời gian bắt đầu xử lý vào bộ đếm
    }

    /* Vòng kích hoạt chu kỳ */
    while (atomic_load(&a->active)) // kiểm tra trạng thái của báo thức liên tục
    {
        /* Ánh xạ alarm → task chu kỳ tương ứng */
        switch (a->id)
        {
        case Alarm_10ms:
            //(void)ActivateTask(Task_10ms_ID);
            //(void)ActivateTask(Task_Can_ID);
            break;
        case Alarm_100ms:
            //(void)ActivateTask(Task_100ms_ID);
            break;
        case Alarm_500ms:
            (void)ActivateTask(Task_10ms_ID);
            (void)ActivateTask(Task_Can_ID);
        default:
            /* Không hỗ trợ alarm khác trong bản tối giản */
            break;
        }

        /* One-shot: thoát vòng nếu cycle_ms == 0 */
        if (a->cycle_ms == 0u)
        {
            break;
        }
        OS_SleepMs(a->cycle_ms); // thời gian lặp
    }

    atomic_store(&a->active, 0); // reset trạng thái báo thức
    return NULL;
}

StatusType SetRelAlarm(uint8_t alarmId, TickType start_ms, TickType cycle_ms)
{
    // kiểm tra Alarm_ID có hợp lệ dựa trên enum trong Os_Cfg.h
    if (alarmId >= ALARM_COUNT)
    {
        return E_OS_ID;
    }

    // con trỏ tới thông tin cấu hình alarm trong bảng ánh xạ loại báo thức cho task chạy theo chu kỳ
    OsAlarmCtl *const a = &s_alarm[alarmId];

    // cấu hình thời gian lặp lại báo thức cho task (chỉ gán 1 lần)
    a->start_ms = start_ms;
    a->cycle_ms = cycle_ms;

    // khởi tạo luồng chạy cho task chạy theo báo thức
    const int rc = pthread_create(&a->thread, NULL, OS_AlarmThread, a);
    if (rc != 0)
    {
        perror("[OS] pthread_create (alarm)");
        return E_OS_STATE;
    }

    /* Alarm cũng detach để tự thu dọn */
    (void)pthread_detach(a->thread); // Luồng Alarm chạy trên nền -> ko cần join để báo kết quả về hàm khởi tạo nó
    return E_OK;
}