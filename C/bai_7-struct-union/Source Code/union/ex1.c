#include <stdio.h>
#include <stdint.h>
//lưu trữ member là array ?

typedef union{
    //data alignment -> cấp phát 4 byte 1 lần (do c lớn nhất)
    
    //lần 1 : 4 byte (arr[0] - arr[3])
    //lần 2 : 4 byte (arr[4] - arr[6]) + 1 padding 
    //vùng nhớ mới : 8 byte
    uint8_t a[7]; 
    uint16_t b; //1 byte + 7 padding 
    uint32_t c; //4 byte + 4 padding
}data;

int main(){
    sizeof(data); //8 byte -> phụ thuộc a và padding của nó
}