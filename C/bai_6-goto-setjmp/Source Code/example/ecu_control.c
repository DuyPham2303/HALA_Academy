#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf jump_buffer;
typedef enum{
    NO_ERROR,
    ERROR
}SensorStatus;

#define MAX_VALUE 100

int read_sensor_data()
{
    int sensor_value = rand() % 100;

    if (sensor_value > MAX_VALUE)
    {
        printf("Sensor error! Value too high: %d\n", sensor_value);
        longjmp(jump_buffer, ERROR); // nhảy về điểm an toàn
    }

    return sensor_value;
}

void Task_ReadSensor(int *out_data)
{
    printf("Reading sensor...\n");
    *out_data = read_sensor_data();
    printf("Sensor OK: %d\n", *out_data);
}

void Task_Process(int data)
{
    printf("Processing data: %d\n", data);
    // Giả lập xử lý...
}

void Task_Control(int data)
{
    printf("Control actuator based on: %d\n", data);
    // Giả lập điều khiển...
}


int main()
{
    // mô phỏng 5 chu kỳ lặp như embedded loop
    for (int i = 0; i < 5; i++)
    {
        int data;

        if (setjmp(jump_buffer) == ERROR)
        {
            //lần đầu vào, đặt điểm nhảy
            printf("\nLoop Start\n");
        }
        else
        {
            //khi bị lỗi và nhảy về đây
            printf("Jumped back safely after sensor error!\n");
        }

        // vòng lặp main (1 cycle)
        Task_ReadSensor(&data);
        Task_Process(data);
        Task_Control(data);
    }

    printf("\nSystem terminated.\n");
    return 0;
}
