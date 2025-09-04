                                                            /* VOID FUNCTION */
#include <stdio.h>
#include <stdint.h>
int main()
{
    double c = 765656.65653;
    float d = 23.54;
    int e = 21;
    char f = 'e';
    char str[] = "hello world";


    // void* ptr = &d;
    // ptr = &f;
    // printf("*ptr = %c",*(char*)ptr);

    void *ph[] = {&c, &d, &e, &f,str};

    printf("c = %lf\n", *((double *)ph[0]));
    printf("d = %.2f\n", *((float *)ph[1]));
    printf("e = %d\n", *((int *)ph[2]));
    printf("f = %c\n", *((char *)ph[3]));

    for(int i = 0 ; i < sizeof(str) ; i++){
        printf("%c",*((char*)ph[4] + i));
    }
    return 0;
}