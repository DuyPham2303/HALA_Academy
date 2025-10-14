#include <stdio.h>
#include <pthread.h>    //posix thread 
#include <unistd.h>

/* 
    + chạy join trước/sau main thread 
        -> trước main : thread main chờ cho đến khi join xong mới thực hiện
        -> sau main : thread main chạy song song với join
    + chạy detach trước/sau main thread : 
    + kết hợp chạy detach và join
        -> gọi join,detach trước main
        -> gọi join,detach sau main 
*/

int count = 0;

void *task1(void* data)
{
    static int i = 0;
    for(int i = 0 ; i < 10 ; i++)
    {
        printf("count task1: %d\n", i++);
        sleep(1);
    }
    return NULL;
}

void *task2(void* data)
{
    static int i = 0;
    while(1)
    {
        printf("count task2: %d\n", i++);
        sleep(1);
    }
    return NULL;

}

int main(int argc, char const *argv[])
{   
    pthread_t t1;
    pthread_t t2;

    /* DEMO CHẠY SONG SONG CÁC TASK PHỤ VÀ MAIN */
    pthread_create(&t1,NULL,task1,"task 1");
    pthread_create(&t2,NULL,task2,"task 2");

    
    for(int i = 0 ; i < 5 ; i++){
        printf("this is main : %d\n",i);
        sleep(1);
    }

    pthread_detach(t2);
    pthread_join(t1,NULL);
    return 0;
}