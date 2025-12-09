#include <stdio.h>
int* ptr = NULL;
void count(){  
    static int a = 5;   //0x12
    ptr = &a;
    printf("a = %d\n",++a);  
}
int main(){
    count();
    count();
    *ptr = 23;
    count();
    return 0;
}