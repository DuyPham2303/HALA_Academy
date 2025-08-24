/********************************************************
 *******************
 * @file utils.h
 * @brief Định nghĩa các hàm  Quản lý trạng thái và actuator của cửa xe 
 * @details File này chứa phần định nghĩa các hàm Door_Init,openDoor,closeDoor,lockdoor,unlockDoor
 * @version 1.0
 * @date 2024-09-11
 * @author HALA Academy
 * @website https://hala.edu.vn/
 *********************************************************
 ******************/
#ifndef DOOR_H
#define DOOR_H

#include <stdint.h>

#define N_DOORS 4

/**
 * @brief Trạng thái 1 cửa xe, sử dụng bitfield để tiết kiệm bộ nhớ.
 * - isOpen:    1 nếu cửa đang mở, 0 nếu đóng
 * - isLocked:  1 nếu cửa bị khóa
 * - hasWindow: 1 nếu kính đang mở
 * - reserved:  Dự phòng
 */
typedef struct {
    uint8_t isOpen    : 1;
    uint8_t isLocked  : 1;
    uint8_t hasWindow : 1;
    uint8_t reserved  : 5;
} DoorStatus_t;

/**
 * @brief Union đóng gói trạng thái của cửa để thao tác dưới dạng byte.
 */
typedef union {
    DoorStatus_t status; //set trạng thái cửa 
    uint8_t      byte;   //dữ liệu thực tế được đóng gói
} DoorStatusUnion_t;

struct Door;
/**
 * @brief Con trỏ hàm actuator, nhận vào địa chỉ struct Door cần thao tác.
 */
typedef void (*ActuatorFunc)(struct Door*);

/**
 * @brief Struct quản lý đầy đủ 1 cửa xe, bao gồm trạng thái và 4 hàm actuator.
 */
typedef struct Door {
    DoorStatusUnion_t statusUnion;
    ActuatorFunc open;
    ActuatorFunc close;
    ActuatorFunc lock;
    ActuatorFunc unlock;
} Door;


/**
 * @brief Khởi tạo 1 cửa, gán các hàm actuator và reset trạng thái về mặc định.
 * @param d      Con trỏ tới cửa cần khởi tạo
 * @param open   Hàm actuator mở cửa
 * @param close  Hàm actuator đóng cửa
 * @param lock   Hàm actuator khóa cửa
 * @param unlock Hàm actuator mở khóa cửa
 */
void Door_Init(Door* d, ActuatorFunc open, ActuatorFunc close, ActuatorFunc lock, ActuatorFunc unlock);

/**
 * @brief Actuator mở cửa (set isOpen = 1).
 * @param d Con trỏ tới cửa
 */
void openDoor(Door* d);

/**
 * @brief Actuator đóng cửa (set isOpen = 0).
 */
void closeDoor(Door* d);

/**
 * @brief Actuator khóa cửa (set isLocked = 1).
 */
void lockDoor(Door* d);

/**
 * @brief Actuator mở khóa cửa (set isLocked = 0).
 */
void unlockDoor(Door* d);

#endif // DOOR_H