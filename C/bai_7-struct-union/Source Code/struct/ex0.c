#include <stdio.h>
#include <stdint.h>
/*
    - data alignment
    - padding byte
    - size of struct
    - bit field
*/
// sinh vien (int,float,double,char)
/*
    - ten
    - ngay,thang,namsinh
    - mssv
    - nganh hoc
*/

typedef uint8_t sensor_data;
/*
    - thứ tự cấp phát
    - số byte cấp phát trong 1 lần dựa vào thành viên có datatype max
    - size = members + padding byte
*/
typedef struct
{
    double a; // lần 1: 0x00 -> 0x07
    int b;    // lân 2: 0x08 -> 0x0F -> 0x04 -> 0x0f
    int c;
} user;

// double,uint64_t (8 byte) : 0x00,0x08,0x10 (16) ,0x20 (48)
// uint32_t,int32_t,float,int (4 byte) : 0x04,0x08,0x0c (12)
// uint16_t,int16_t (2 byte) : 0x02,0x04,0x06,0x08,0x0a (10)
// uint8_t ,int8_t, char (1 byte)

user user1;
user *p = &user1;

struct data
{
    uint8_t a : 1;
    uint16_t b : 3;
    uint8_t d : 4;
};


int main()
{
    sizeof(struct data);
    printf("address of a: %p\n", &p->a);
    printf("address of b: %p\n", &p->b);
    printf("address of c: %p\n", &p->c);
}