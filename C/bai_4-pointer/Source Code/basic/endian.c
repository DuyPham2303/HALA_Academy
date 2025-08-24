#include <stdio.h>

int main()
{
    //Endianness
    unsigned int x = 0x12345678;
    unsigned char*c = (unsigned char*)&x;

    if (*c == 0x78)
    {
        printf("Little Endian\n");
    }
    else
    {
        printf("Big Endian\n");
    } 
    return 0;
}

