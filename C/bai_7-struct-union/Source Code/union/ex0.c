#include <stdio.h>
#include <stdint.h>

/* 
    - Review struct: kiểu tự định nghĩa > nhóm nhiều biến từ nhiều datatype
        + data alignment : quy định các member khi cấp phát mem, có address chia hết cho dtype của chính nó
        + padding byte : byte đệm thêm vào để thỏa mãn data alignment
        + size :
            - member có kiểu max
            - members size + padding
    - UNION 
        + Các member share a common memory 
        + size : member chiếm số byte max + padding
*/

typedef union{
    //cấp phát 4 byte
    uint8_t a;  //1 byte -> dư 3 padding
    uint16_t b; //2 byte -> dư 2 padding
    uint32_t c; //4 byte
}data;
int main(){
    sizeof(data); //phụ thuộc member có size max

    data dt;

    //Cách thức tổ chức trên RAM
    /* 
    SƠ ĐỒ BỘ NHỚ TRÊN RAM
    0x03     0x02     0x01     0x00
                               01100100 (a)
                      00000000 10001110 (ghi đè lên a) 
    00000000 00000000 00000000 11010101 (ghi đè len b)
    */
    //cách thức lưu trữ từng byte trên RAM phụ thuộc vào kiểu endian -> quy đổi ra chuỗi binary
    dt.a = 100;  //01100100
    dt.b = 142;  //00000000 10001110
    dt.c = 213;  //00000000 00000000 00000000 11010101

    //giá trị của các member phụ thuộc vào
    /* 
        - kiểu dữ liệu khai báo
        - vị trí sắp xếp 
    */


}