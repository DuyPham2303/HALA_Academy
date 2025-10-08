#include <pthread.h>
#include <stdio.h>
#include <stdatomic.h>

//int counter = 0;

_Atomic int counter = 0;  //từ khóa có sẵn trong chuẩn C11

//atomic_int count = 0;    //typedef được định nghĩa trong <stdatomic.h>
/* 
    t1 : load(100) -> write(100++) -> store (101)
    t1 : load(100) -> write(100++) -> store (101)
*/
void* increment(void* arg) {
    for (int i = 0; i < 100000; ++i)
        counter++;
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("Expected = 200000, Actual = %d\n", counter);
}
