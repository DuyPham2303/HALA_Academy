#include "Os.h"
#include "stdlib.h"
#include <stdbool.h>
#include <stdatomic.h>

atomic_int sensor_data = 0;

void* task_sensor(void* arg) {
        //read sensor random 

        //Set event to activate Task_control 

}

// TASK_Control
void* task_control(void* arg) {

    //wait triggered event from task_sensor
   
    // Giả lập phát hiện lỗi ngẫu nhiên
    bool has_error = rand() % 5 == 0;

    //set event đến task_diagnotic nếu có lỗi

    //tính toán output signal -> set event đến task_actuator 

    //clear event từ task_sensor

}

// TASK_Actuator
void* task_actuator(void* arg) {
   //wait triggered event from task_control

   //output signal to actuator 

   //clear event từ task_control
}

// TASK_Diagnostic
void* task_diagnostic(void* arg) {
  
}

// ISR_CAN_RX (mô phỏng)
void* isr_can_rx(void* arg) {
    
}
