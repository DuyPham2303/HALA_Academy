#include <stdint.h>
#include <stdio.h>

typedef struct Info
{
    //lần 1 (8 byte) (0x00 - 0x07) 
    /* 
        - 1 byte : status (byte 0)
        - 3 padding byte  (byte 1 - 3)
        - byte 4 : flags + mode + error 
        - 3 byte padding
    */
    char status;            // 1 byte
    unsigned int flags : 4; // bit field 4 bit
    unsigned int mode : 3;  // bit field 3 bit
    unsigned int error : 1; // bit field 1 bit
    // lần 2 (8 byte) (0x08 - 0x0f)
    int *ptr;               // con trỏ 4 hoặc 8 byte tùy hệ thống
    // lần 3 (8 byte) (0x10 - 0x17)
    /* 
       -  5 byte : label[0] - label[4]
       -  3 byte padding
    */
    char label[5];          // mảng 5 byte
    // lần 4 (8 byte) (0x18)
    double value;           // 8 byte
} Info;

int main()
{ 
     printf("sizeof(Info)          = %zu\n", sizeof(Info));
     printf("offset of (status)    = %zu\n", offsetof(Info, status));
     printf("offset of (ptr)       = %zu\n", offsetof(Info, ptr));
     printf("offset of (label)     = %zu\n", offsetof(Info, label));
     printf("offset of (value)     = %zu\n", offsetof(Info, value)); 
}