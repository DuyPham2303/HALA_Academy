#include <stdio.h>

// program counter

int main()
{
    while (1)
    {
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (i == 3 && j == 4)
                {
                    printf("break\n");
                    goto exit_loop;
                }
                else
                {
                    printf("i = %d,j = %d\n", i, j);
                }
            }
        }
    }
exit_loop:
    printf("exit loop\n");
    return 0;
}