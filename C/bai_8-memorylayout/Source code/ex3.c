#include <stdio.h>

// stack frame :
/*
    - return address
    - tham số
    - biến cục bộ
    - thanh ghi lưu trữ kết quả hoặc trạng thái trước đó của chương trình
    - Call stack: chứa frame của hàm được gọi
*/

int test(int a, int b) //
{
    int c = a + b;
    int d = c + 10;

    const int e = 12;

    int* p = (int*)&e;

    *p = 12;

    printf("e = %d",e);

/*     printf("&b = %p\n", &b);
    printf("&a = %p\n", &a);
    printf("&c = %p\n", &c);
    printf("&d = %p\n", &d); */
    return d;
}

//n ! = n(n - 1)(n - 2)...2*1

//5 ! = 5 * 4 * 3 * 2 *1

int tinhgiaithua(int n){ //n = 1
    if(n == 1){ //1 == 1
        return 1;
    }
    return n * tinhgiaithua(n - 1); //5 * 4 * 3 * 2 * 1
}

//2 * 1
//3 * 2 * 1
//4 * 3 * 2 * 1
//5 * 4 * 3 * 2 * 1
int main()
{
    int n = 5;
    int result = tinhgiaithua(n);
    printf("result = %d",result);
    return 0;
}
