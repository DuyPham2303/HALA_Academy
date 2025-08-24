                                                            /* VOID FUNCTION */
#include <stdio.h>
#include <stdint.h>
int main()
{
    double c = 765656.65653;
    float d = 23.54;
    int e = 21;
    char f = 'e';

    /* void* ptr = &d;
    ptr = &f;
    printf("*ptr = %c",*(char*)ptr); */

    void *ph[] = {&c, &d, &e, &f};

    printf("c = %lf\n", *((double *)ph[0]));
    printf("d = %.2f\n", *((float *)ph[1]));
    printf("e = %d\n", *((int *)ph[2]));
    printf("f = %c\n", *((char *)ph[3]));
    return 0;
}