#include <stdio.h>
#include <stdarg.h>

// xác định số phần tử của array
/*
    + Size toàn bộ array : sizeof(array)
    + Size phần tử đầu : sizeof(array[0])
    => số phần tử = sizeof(array) / sizeof([0])
*/
// Macro variadic -> dùng cho những macro function ko xác định số lượng input

#define SUM(...)                  \
    int arr[] = {__VA_ARGS__, 0}; \
    int i = 0;                    \
    int tong = 0;                 \
    while (arr[i] != 0)           \
    {                             \
        tong += arr[i++];           \
    }                             \
    printf("tong:%d\n", tong);

int main(){
    SUM(1,2,3,4);
    return 0;
}

