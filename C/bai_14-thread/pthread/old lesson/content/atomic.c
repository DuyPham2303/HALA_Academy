#include <stdatomic.h>
#include <pthread.h>
#include <stdint.h>
#include <stdbool.h>
/* 
_Atomic int g_counter;            // kiểu ngắn gọn
atomic_int g_flag;                // typedef chuẩn
atomic_uint_least32_t g_seq;      // chọn độ rộng “ít nhất”

 */
static atomic_bool adc_ready = ATOMIC_VAR_INIT(false);
static volatile uint16_t adc_sample; // thanh ghi/buffer phần cứng

// ISR (ngữ cảnh ngắt)
void ADC_IRQHandler(void) {
    adc_sample = ADC->DR;                         // đọc HW register (volatile)
    atomic_store_explicit(&adc_ready, true, memory_order_release);
}

// Task chính
void Task_Process(void) {
    if (atomic_load_explicit(&adc_ready, memory_order_acquire)) {
        // đảm bảo thấy adc_sample mới tương ứng
        uint16_t v = adc_sample;
        // ... xử lý v ...
        atomic_store_explicit(&adc_ready, false, memory_order_release);
    }
}


int main(){

    return 0;
}