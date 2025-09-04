                                                            /* DOUBLE POINTER */
#include <stdio.h>
#include <stdint.h>
void single_ptr(const char *ptr)
{
    ptr += 4; 
    printf("inside: %s\n", ptr); 
}
void double_ptr(const char **ptr)
{
    (*ptr) += 4; 
}

int main()
{
    const char *str = "hello world";
    double_ptr(&str);
    printf("%s",str);
    return 0;
}