#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


// Dành cho dữ liệu nhỏ
int16_t Temp_ReadNow(void); 

// Dành cho dữ liệu phức tạp hoặc gọi xuống API ở layer bên dưới để truy cập dữ liệu
void Sensor_Read(int* data);

// Hằng số dùng cho quá trình tính toán
extern const double pi;  

