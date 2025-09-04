#include <stdio.h>

// Macro nối chuỗi ##
#define CREATE_VAR(name) \
    int int_##name;      \
    double double_##name;  \
    float float_##name; \

// Macro chuẩn hóa chuỗi từ text #
#define CREATE_STRING(str) printf(#str)

int main()
{
    CREATE_VAR(sensor);
    CREATE_STRING(asdwadw);
}