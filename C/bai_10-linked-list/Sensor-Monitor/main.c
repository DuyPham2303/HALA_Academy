#include "sensor.h"
int main() {
    Sensor* sensorList = NULL;

    addSensor(&sensorList, TEMP_SENSOR, 36.5);
    addSensor(&sensorList, SPEED_SENSOR, 101.2);
    addSensor(&sensorList, VOLTAGE_SENSOR, 75.0);

    printSensors(sensorList);

    updateSensor(sensorList,VOLTAGE_SENSOR,95);
    printf("\nSau cập nhật:\n");
    printSensors(sensorList);

    deleteSensor(&sensorList, SPEED_SENSOR);
    printf("\nSau xoá:\n");
    printSensors(sensorList);

    freeSensors(&sensorList);

    printSensors(sensorList);

    //Mô phỏng quản lý thông tin cảm biến
    /* 
        Menu 
        1) Hiển thị các cảm biến đã thêm vào list
        2) Thêm cảm biến mới vào list 
        3) xóa cảm biến khỏi list
        4) Thoát -> xóa toàn bộ cảm biến
        5) Chạy mô phỏng cảm biến 
            - tạo biến running == 1 -> chạy trong while loop
            - gọi hàm updateSensor
            - Gọi hàm rand() để sinh số ngẫu nhiên 
            - tạo delay mô phỏng thay đổi dữ liệu theo tgian 
            - gán running == 0 
                -> break khỏi while loop 
                -> dừng mô phỏng
                -> return Menu
    */
    return 0;
}
