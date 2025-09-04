                                                        /* FUNCTION POINTER */
#include<stdio.h>
void Tong(int a, int b)
{
    printf("%d + %d = %d\n", a, b, a + b);
}
void Hieu(int a, int b)
{
    printf("%d - %d = %d\n", a, b, a - b);
}
void Tich(int a, int b)
{
    printf("%d x %d = %d\n", a, b, a * b);
}
void Thuong(int a, int b)
{
    if (b != 0)
        printf("%d / %d = %.2f\n", a, b, (float)a / b);
    else
        printf("value of b is invalid\n");
}
void Operator(void (*op)(int, int), int a, int b)
{
    op(a, b);
}

int main(){
// function pointer
    // cach 1
    void (*operator)(int, int);

    operator= Tong;
    operator(34, 56);

    operator= Hieu;
    (*operator)(84, 96);

    operator= Tich;
    operator(34, 5);

    operator= Thuong;
    operator(34, 12);
    // cach 2
    
    int a = 23, b = 2;
    Operator(Tong, a, b);
    Operator(Hieu, a, b);
    Operator(Tich, a, b);
    Operator(Thuong, a, b); 
   
    // cach 3 
    
    void (*opeArr[])(int, int) = {Tong, Hieu, Tich, Thuong};
    for (int n = 0; n < 4; n++)
    {
        opeArr[n](a, b);
    }
   
}