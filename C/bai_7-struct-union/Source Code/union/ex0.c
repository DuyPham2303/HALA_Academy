#include <stdio.h>
#include <stdint.h>

/*
    - truy cập thông qua tên biến (.) và con trỏ (->)
    - data alingment : member cấp phát có address chia hết cho data type
    - padding byte : byte đệm thêm vào để đảm bảo data alignment
    - size = members size + padding (nếu có)
    Union
    - size = member (max) + padding (nếu có)
    - members share chung memory
*/

typedef union
{
    // cấp phát 4 byte : 0x00 - 0x03
    uint8_t a;  // 1 byte -> 3 padding byte
    uint32_t b; // 4 byte -> 0 padding byte
    uint16_t c; // 2 byte -> 2 padding byte
} data;
int main()
{
    sizeof(data);
    //0x00      0x01      0x02      0x03
    //01011001  00000000  00000001  00000000

    data dt;
    //dt.a = 28;    //00011100
    //dt.b = 70000;  //00000000 00000000 00000000 10000001
    dt.c = 500;    //00000000 01011001

    //0001 00010001 01110000
    printf("value of a : %d\n", dt.a); 
    printf("value of b : %d\n", dt.b);
    printf("value of c : %d\n", dt.c);
}