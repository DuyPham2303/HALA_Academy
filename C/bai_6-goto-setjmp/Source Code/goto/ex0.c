#include <stdio.h>

/* 
    label1:

    goto lable1;

    label:
        //cau lenh 9
        //cau lenh 10
*/

//Program counter : PC

int main()
{
    int i = 0;             //0x01 
    /* int running = 0;    //0x02 <- PC
    while (running)
    {
        if (i > 5)
        {
            running = 0;
        }
        else
        {
            printf("i = %d\n", i);
            i++;
        }
    } */

    start:
    if (i > 5) goto end;

    printf("i = %d\n", i);
    i++;

    goto start;

    end: 
   
    return 0;
}