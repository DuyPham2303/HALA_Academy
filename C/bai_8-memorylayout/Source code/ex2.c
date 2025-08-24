#include <stdio.h>
#include <stdlib.h>

typedef struct{
   int x;
   int y;
} Point_Data;

/* static Point_Data p1 = {0,0}; //bss
Point_Data p2;                  
Point_Data p3 = {0, 1};

int a = 0;
int b;

static int global = 0;
static int global_2;

void test(){
   static int local = 0;
   static int local_2;
}
 */
int main(){
    Point_Data* p = malloc(sizeof(Point_Data));
   return 0;
}

