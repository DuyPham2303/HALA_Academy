#include <stdio.h>

/* DATA SEGMENT -> .data*/
int data_a = 121;             

static int data_b = 10;       

const int data_a = 23;        // .rdata

/* BSS SEGMENT -> .bss*/

int bss_a;  

int bss_b = 0;

const int bss_b;        // .rdata

const char* str1 = "this is str1"; // "this is str1" -> .rdata , str1 -> .rdata

char* str2 = "this is str2"; //"this is str2" -> .rdata , str -> .data

const char str3[] = "this is str3"; // "this is str3" (copy of literal string in .rdata) -> .data  

char str4[] = "this is str4"; // .data -> 

void test(){
    static int static_local = 13;
    printf("this is test\n");
}

int main()
{   
    str4[5] = 't';          //wrong -> can't write in read only segment
    printf("%s\n",str4);
    
    //test();
    //printf("this is main");
}