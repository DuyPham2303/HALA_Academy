#include "utils.h"
#include <stdio.h>

uint8_t checkParity(uint8_t byte){
    uint8_t bitmask = 1;
    uint8_t count = 0;
    for(int i = 0 ; i < 8 ;i++){
        if(bitmask & byte) count++;
        else{
            bitmask <<= 1 ;
        }
    }
    return (count % 2) ? 1 : 0;
}
uint8_t reverseBits(uint8_t byte){
    /* 
        0b 1010 1010 (byte)
           0000 0001 (bitmask)
        0b 0000 0001 (reverse)
           
    */
    uint8_t bitmask = 1;
    uint8_t reverse = 0;
    for(int i = 0 ; i < 8 ; i++){
        reverse <<= 1; //dịch trái để đẩy bit đầu về cuối
        if(byte & bitmask){
            reverse |= 1; //set bit 1
        }
        bitmask <<= 1;  //dịch trái để kiểm tra các bit 
    }  
    return reverse;
}
void pointerDemo(Door* doors){
    //kiểm tra dữ liệu có khác NULL
    if(!doors){
       printf("Con trỏ tới doors không hợp lệ");
        return;
    }
    //ptr to ptr : trỏ từng cửa để xử lý
    Door* current = &doors[0];  //con trỏ tới đầu mảng doors
    Door** p = &current;        //con trỏ tới con trỏ quản lý địa chỉ của từng cửa
    for(int i = 0 ; i < N_DOORS ; i++){
        *p = &doors[i]; //lặp qua từng địa chỉ của từng cửa thông qua con trỏ 2 cấp
        printf("cửa thứ [%d] : open : %d\tislock : %d\n",i,
            (*p)->statusUnion.status.isOpen,
            (*p)->statusUnion.status.isLocked);
    }

    //khai báo mảng thô chứa dữ liệu đóng gói
    uint8_t packFrame[N_DOORS] = {0};

    //trỏ tới mảng thô chứa kiểu dữ liệu cần đóng gói
    void* pFrame = packFrame;

    //thực hiện ép về kiểu dữ liệu cần đóng gói thông qua con trỏ void* 
    for(int i = 0 ; i < N_DOORS ; i++){
        //copy byte dữ liệu của từng cửa vào mảng thô qua con trỏ void*
       ((uint8_t*)pFrame)[i] = doors[i].statusUnion.byte; 
    }

    printf("packed Frame\ndoor[0]:%02X\ndoor[1]:%02X\ndoor[2]:%02X\ndoor[3]:%02X\n",
                    packFrame[0],packFrame[1],packFrame[2],packFrame[3]);
    //ptr to const : read data safely

    //đọc về dữ liệu bằng cách ép kiểu con trỏ void* về kiểu tương ứng
    const uint8_t* unpackFrame = (const uint8_t*)pFrame;

    //truy cập gói dữ liệu đã đọc về của từng cửa
    printf("unpacked Frame\ndoor[0]:%02X\ndoor[1]:%02X\ndoor[2]:%02X\ndoor[3]:%02X\n",
                    unpackFrame[0],unpackFrame[1],unpackFrame[2],unpackFrame[3]);

    //const ptr : truy cập vùng địa chỉ cố định để thao tác dữ liệu 1 cách an toàn
    // Door* const fixed = &doors[0];  // thao tác cố định trên vùng nhớ của cửa trỏ đến
    // fixed->lock;
    // fixed->close;
}