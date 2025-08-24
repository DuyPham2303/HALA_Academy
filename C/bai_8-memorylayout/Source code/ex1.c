#include <stdio.h>

const int data;

static int static_global = 10;

const char* str1 = "this is str1"; //read-only -> .rdata

char* str2 = "this is str2";

const char str3[] = "this is str3";

char str4[] = "this is str4"; // .data -> read/write

void test(){
    static int static_local = 13;
    printf("this is test\n");
}

int main()
{   
    /* str4[5] = 't';
    printf("%s\n",str4);
    test();
    printf("this is main"); */
}