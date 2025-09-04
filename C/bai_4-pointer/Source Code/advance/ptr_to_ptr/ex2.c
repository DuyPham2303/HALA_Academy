#include <stdio.h>
#include <string.h>
char* str[] = {"hello" , "123", "double" , "12.21"};
int main(){ 
    char** p = str; 
    
    char arr[] = "hello";
    //in ra từng chuỗi trong mảng 
    while(*p){
        static int i = 0;
        printf("%s\taddress:0x%p\n",*p,p); //truy xuất đến phần tử trong mảng 
        p+=1;              //di chuyển đế phần tử tiếp theo 
    }

    //in ra các ký tự của phần tử trong mảng 
    // str[2] -> "double" 
    // *p -> 'd'
    *p = str[1];
    while(**p != '\0'){
        printf("%c",**p);
        (*p)++; // sai *p++ ->  //cach 2 : (*p)+=1
    }

    //sự khác biệt giữa sizeof và strlen 
    printf("sizeof len : %d\n",sizeof(arr));
    printf("strlen len : %d",strlen(str[0]));

    //kiểm tra ký tự kết thúc mảng ký tự 
    for(int i = 0 ; i < sizeof(arr) ; i++){
        printf("index[%d]:%d\n",i,arr[i]);
    }

    return 0;
}