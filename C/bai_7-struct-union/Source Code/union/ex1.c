#include <stdio.h>
#include <stdint.h>
union Data
{
    // cấp phát 16 byte: 0x00 - 0x0f
    uint8_t a;     // 1 byte + 15 padding
    uint16_t b[5]; // 10 byte + 6 padding
    uint32_t c;    // 4 byte + 12 padding
    double d;      // 8 byte + 8 padding
};

int main()
{
    sizeof(union Data);
    union Data dt;
    printf("address of a: %p\n", &dt.a);
    printf("address of b: %p\n", &dt.b);
    printf("address of c: %p\n", &dt.c);
    printf("address of d: %p\n", &dt.d);
}
