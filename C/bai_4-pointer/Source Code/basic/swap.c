#include <stdio.h>

//pass by pointer
void swap(int *pa, int *pb) //pa: 0xa0 , pb : 0xa8
{
    int tmp = *pa;   //temp = 23 
    *pa = *pb;       //*a = 12 -> giá trị tại 0x04 =  12
    *pb = tmp;       //*b = 23 -> giá trị tại 0x08 = 23
    //kết thúc hàm
    //thu hồi 0x04 và 0xa8
} 

//pass by value
void swap(int a,int b){ //a: 0xa0 , b : 0xa8
    int tmp = a; //temp = 23 
    a = b;       //a = 12 -> giá trị tại 0xa0 =  12
    b = tmp;     //b = 23 -> giá trị tại 0xa8 =  23
    //kết thúc hàm
    //thu hồi 0x04 và 0xa8
}

int main(){
    int a = 23; // a(0x04) : 23
    int b = 12; // a(0x08) : 12 

    swap(&a,&b); //truyền 0x04 và 0x08

    printf("a:%d\tb:%d\n",a,b); 
    return 0;
}