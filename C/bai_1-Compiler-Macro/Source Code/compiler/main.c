#include<stdio.h> 
//ví dụ 1 : macro
#define SIZE 5

int size = 5;

//int arr1[size]; //compiler ko tìm thấy giá trị cụ thể của size -> chỉ biết size là biến ko phải hằng số

int arr2[SIZE]; //compiler mở rộng SIZE và tìm thấy giá trị thay 

//macro vs biến hoặc hàm

//ví dụ 2: macro 
#define A 123
#define CREATE_FUNCTION(name,STR) \
void name(){            \
    printf(STR);    \
}

CREATE_FUNCTION(func1,"this is function 1\n");
CREATE_FUNCTION(func2,"this is function 2\n");
CREATE_FUNCTION(func3,"this is function 3\n");

//chỉ thị biên dịch có điều kiện : #ifndef #ifdef #endif #error #if #elif #else

/* #ifdef SIZE
    #define SIZE
#endif //được dùng để kết thúc việc xử lý các chỉ thị khác
 */
//thiết kế mã lỗi tiền xử lý bằng chỉ thị #error

#ifndef EX_H
    #error "ex.h chua duoc dinh nghia"
#endif

#define SQUARE(X) ((X) * (X))

int square(int x){
    return (x*x);
}

int main(){
    int result = square(3);
    int result1 = SQUARE(2+1);
    func1();
    print1();
    return 0;
    A;
}








