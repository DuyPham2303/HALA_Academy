/* 
    compile : gcc -g -pthread main.c -o main
 */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t lock;
int count = 0;
void *task1(void* data)
{
    static int i = 0;
    while(1)
    {
        printf("count task1: %d\n", i++);
        sleep(1);
    }
}

void *task2(void* data)
{
    static int i = 0;
    while(1)
    {
        printf("count task2: %d\n", i++);
        sleep(3);
    }
}

void* display(void* a)
{
    static int i = 0;
    while(i++ < 20)
    {
        pthread_mutex_lock(&lock);
        printf("%s:%d\n", (char*)a,count++);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
}

int main(int argc, char const *argv[])
{   
    const char *str = "duy pham";
    const char *ptr = "Hello world";
    //pthread_mutex_init(&lock,NULL);
    pthread_t t1; // luồng 1
    pthread_t t2; // luồng 2
    pthread_t t3;
    //pthread_t t3; // luồng 3
    
    pthread_create(&t1, NULL, task1, NULL);
    pthread_create(&t2, NULL, task2, NULL);
    //pthread_create(&t3, NULL, display,(void*)ptr);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    //pthread_join(t3,NULL);

    //printf("final count: %d",count);
    //pthread_mutex_destroy(&lock);
    /* 
    while(1)
    {
        printf("Hello world\n");
    } */
    return 0;
}