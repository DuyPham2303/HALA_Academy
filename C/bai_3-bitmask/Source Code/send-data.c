#include <stdio.h>
#include <stdint.h>
void send_data_Msb2Lsb(uint8_t data_tx, uint8_t *data_rx)
{
    // mặt nạ để kiểm tra từng bit truyền đi từ MSB đến LSB
    uint8_t mask = 0x80; // 0b 1000 000

    // giả sử dữ liệu truyền đi là 8 bit
    for (uint8_t i = 0; i < 8; i++)
    {
        *data_rx <<= 1; // dịch trái để nhận bit tiếp theo

        // kiểm tra nếu là bit hiện tại là 0 thì bỏ qua
        if (data_tx & mask)
        {
            *data_rx |= 1; // đọc về bit 1
        }
        mask >>= 1; // dịch mask để truyền bit tiếp theo
    }
}
void send_data_Lsb2Msb(uint8_t data_tx, uint8_t *data_rx)
{
    // mặt nạ để kiểm tra từng bit truyền đi từ LSB đến MSB
    uint8_t mask = 0x01; // 0b 1000 000

    // giả sử dữ liệu truyền đi là 8 bit
    for (uint8_t i = 0; i < 8; i++)
    {
        // kiểm tra nếu là bit hiện tại là 0 thì bỏ qua
        if (data_tx & mask)
        {
            *data_rx |= mask;
        }

        mask <<= 1; // dịch mask để truyền bit tiếp theo
    }
}
void SwapNumber(int* a,int* b){ 
    /* int *temp = *a;
    *a = *b;
    *b = *temp; */
    
    //cach 2
/* 
    a : 0b 1010 0111
    ^
    b : 0b 1100 0100
    ^
    a1: 0b 0110 0111
    ^
    b1: 0b 1010 0111

    a : 0b 1100 0100
*/

    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b; 
}
int main()
{
    /* uint8_t data_rx = 0;

    send_data_Lsb2Msb(230,&data_rx);
    printf("data_rx = %d\n", data_rx);

    send_data_Msb2Lsb(135,&data_rx);
    printf("data_rx = %d\n", data_rx); */

    int a = 23,b = 10;
    SwapNumber(&a,&b);
    printf("a = %d , b = %d",a,b);
}