#include<stdio.h>
#include<stdint.h>

int main(){
    uint16_t sum = 0xabcd;
    uint8_t* px = (uint8_t*)&sum; 
    uint8_t bit_low = *px;  
    uint8_t bit_high = *(px + 1);
    printf("2 bit cao: 0x%x\n2 bit thap: 0x%x",bit_high,bit_low);
    return 0;
}