#include <stdio.h>
#include <setjmp.h>
#include <assert.h>

jmp_buf buf;
int exception = 0;
int mauso = 0;
int tuso = 1;

#define TRY if((exception = setjmp(buf)) == 0)
#define CATCH(x)  else if (exception == x)
#define THROW(x)   longjmp(buf,x)

float divide(int mauso, int tuso)
{
    if (mauso == 0 && tuso == 0)
    {
        THROW(1);
    }
    else if (mauso == 0)
    {
        THROW(2);
    }
    else
    {
        return (float)tuso / mauso;
    }
}

int main()
{
    assert(mauso != 0 && "mau so phai khac 0");
    float result = (float)tuso / mauso;
    /* TRY
    {
        float result = divide(mauso, tuso);
        printf("result = %.2f", result);
    }
    CATCH(1)
    {
        printf("Biểu thức không hợp lệ\n");
    }
    CATCH(2)
    {
        printf("lỗi chia cho 0\n");
    } */
    return 0;
}

//read sensor : encoder , nhiet do dong co, dien ap, dong dien

//process sensor data : 
/*
    - tinh toc do hien tai
    - kiem tra temp,voltage,current in allow range
*/

//diagnotic : 