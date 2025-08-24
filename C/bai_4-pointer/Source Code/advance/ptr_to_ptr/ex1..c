                                                            /* DOUBLE POINTER */
#include <stdio.h>
#include <stdint.h>
void single_ptr(const char *ptr)
{
    ptr += 4; //"o world"
    printf("inside: %s\n", ptr); 
}
void double_ptr(const char **ptr)
{
    /* ptr -> address of ptr
    *ptr -> dereference to string "hello world" pointed by ptr
    **ptr -> derefernce to the first character in string "hello world" */
    (*ptr) += 4; //&str
}

int main()
{
    const char *str = "hello world";
    double_ptr(&str);
    printf("%s",str);
    return 0;
}