/*
 * Chức năng chính:
 * - Khởi tạo mảng 4 cửa, gán actuator (Door_Init)
 * - Vòng lặp menu cho phép:
 *    + Xem trạng thái cửa: truy cập statusUnion/status/byte
 *    + Thao tác actuator: gọi open/close/lock/unlock
 *    + Packing trạng thái vào frame: packDoorStatus
 *    + Unpacking frame: unpackDoorStatus
 *    + Kiểm tra parity, đảo bit: checkParity, reverseBits
 *    + Thao tác advanced pointer: pointerDemo
 *    + In log kết quả ra màn hình
 */
#include "door.h"
#include "Menu.h"
#include "Keyboard.h"
#include "utils.h"
#include "can_frame.h"

void LogStatus(Door* doors);
void UpdateStatus(Door *door);
void HandleFrame(Door *door,CANFrame_t* frame);
void CheckBits(Door* door);
void TestPointer(Door* door);

int main()
{
    //Khai báo mảng 4 cửa
    Door door[N_DOORS];
    //khai báo frame xử lý dữ liệu 
    CANFrame_t frame;

    //Khởi tạo trạng thái ban đầu 
    for (int i = 0; i < 4; i++)
    {
        openDoor(&door[i]);
        closeDoor(&door[i]);
        unlockDoor(&door[i]);
        lockDoor(&door[i]);
        Door_Init(&door[i], openDoor, closeDoor, lockDoor, unlockDoor);
    }
    while(1){
        PRINT_MENU("Xem trạng thái cửa",
                "Điều khiển cửa",
                "Packing/Unpacking trạng thái vào Frame",
                //"Kiểm tra parity và đảo bit",
                //"test pointer nâng cao",
                "thoát");
        int option = UI_InputChoice("Nhập lựa chọn:");
        if(option == 4){
            break;
        }
        HANDLE_OPTION(option,
                        CASE_OPTION(1,LogStatus(door))
                        CASE_OPTION(2,UpdateStatus(door))
                        CASE_OPTION(3,HandleFrame(door,&frame))
                        //CASE_OPTION(5,CheckBits(door))
                        //CASE_OPTION(6,TestPointer(door))
                    );
    }
    UI_ShowMessage("Đã thoát chương trình");
}
void LogStatus(Door* doors)
{   
   for(int i = 0 ; i < N_DOORS ;i++){
        printf("Door[%d]\tbyte : %02X\tisopen : %d\tislocked: %u\n",i,
            doors[i].statusUnion.byte,
            doors[i].statusUnion.status.isOpen,
            doors[i].statusUnion.status.isLocked);
   }
   
}
void UpdateStatus(Door* door){
    PRINT_MENU("Door 0","Door 1","Door 2","Door 3");
    input:
    int index = UI_InputChoice("Chọn cửa cần cập nhật trạng thái:");
    if(index > 4){
        UI_ShowMessage("Vui lòng chọn cửa [0...4]");
        goto input;
    }
    PRINT_MENU("Mở cửa","Đóng cửa","Mở khóa cửa","Khóa cửa");
    int option = UI_InputChoice("Chọn trạng thái:");
    HANDLE_OPTION(option,
                  CASE_OPTION(1,openDoor(&door[index - 1]))
                  CASE_OPTION(2,closeDoor(&door[index - 1]))
                  CASE_OPTION(3,unlockDoor(&door[index - 1]))
                  CASE_OPTION(4,lockDoor(&door[index - 1]))
                );
}
void HandleFrame(Door *door,CANFrame_t* pframe){
    PRINT_MENU("Đóng gói frame dữ liệu","Gỡ gói frame dữ liệu");
    int option = UI_InputChoice("Nhập lựa chọn:");
    HANDLE_OPTION(option,
                CASE_OPTION(1,packDoorStatus(door,pframe))
                CASE_OPTION(2,unpackDoorStatus(pframe,door))
            );
}