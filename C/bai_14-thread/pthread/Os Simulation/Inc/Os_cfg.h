#ifndef CFG_H
#define CFG_H

/* =====================================================================================
 * 1) TASK IDs
 * -------------------------------------------------------------------------------------
 *  Thứ tự & số lượng Task của hệ. ID dùng để gọi ActivateTask(...)
 *  và (với Extended Task) GetEvent/SetEvent/ClearEvent(...)
 * ===================================================================================== */
typedef enum {
    TASK_ID_Sensor,
    TASK_ID_EngineControl,   
    TASK_ID_Actuator,        
    TASK_ID_Diagnostic,     
    ID_ISR_CAN_RX,
    TASK_ID_Max
}TaskIDType;

/* GIÁ TRỊ QUY ĐỔI */
/* 
    dec 	hex	    bin
    1	0x01	1 << 0
    2	0x02	1 << 1
    4	0x04	1 << 2
    8	0x08	1 << 3
    16	0x10	1 << 4
    32	0x20	1 << 5
    64	0x40	1 << 6
    128	0x80	1 << 7 
*/

/* =====================================================================================
 * 2) EVENT MASKS cho Extended Task
 * -------------------------------------------------------------------------------------
 *  Chỉ Task_Com sử dụng trong mô phỏng:
 *    - EV_RX : có dữ liệu nhận (RX) cần xử lý
 *    - EV_TX : có yêu cầu truyền (TX) cần xử lý
 * ===================================================================================== */
#define EV_DataReady          ((EventMaskType)0x0004u)
#define EV_ControlCmdReady    ((EventMaskType)0x0008u)
#define EV_TriggerError       ((EventMaskType)0x0010u)



/* =====================================================================================
 * 3) ALARM IDs (đơn vị mili-giây trong mô phỏng)
 * -------------------------------------------------------------------------------------
 *  Mỗi Alarm sẽ được Os_Posix.c tạo một thread “ngủ” theo start_ms/cycle_ms
 *  và tới hạn sẽ ActivateTask() Task chu kỳ tương ứng.
 * ===================================================================================== */
typedef enum
{
    Alarm_10ms = 0,    /* Kích Task_10ms mỗi 10 ms (sau start_ms) */
    Alarm_100ms,       /* Kích Task_100ms mỗi 100 ms (sau start_ms) */
    Alarm_500ms,
    ALARM_COUNT        /* Số lượng Alarm (luôn để cuối cùng)        */
}AlarmIDType;

#endif