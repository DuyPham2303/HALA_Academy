#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <unistd.h>

_Atomic int accountA = 100;
_Atomic int accountB = 100;

void* transfer1(void* arg) {
    for (int i = 0; i < 100000; i++) {
        int money = 1;

        // rút từ A
        int oldA = atomic_fetch_sub(&accountA, money);
        // printf("[account A before] : %d\n"
        //        "[account A after]  : %d",oldA,atomic_load(&accountA));
        // nạp vào B
        int oldB = atomic_fetch_add(&accountB, money);
    }
    return NULL;
}

void* transfer2(void* arg) {
    for (int i = 0; i < 100000; i++) {
        int money = 1;

        // rút từ B
        int oldB = atomic_fetch_sub(&accountB, money);
        // nạp vào A
        int oldA = atomic_fetch_add(&accountA, money);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, transfer1, NULL);
    pthread_create(&t2, NULL, transfer2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Account A = %d\n", atomic_load(&accountA));
    printf("Account B = %d\n", atomic_load(&accountB));
    printf("Total = %d\n", atomic_load(&accountA) + atomic_load(&accountB));
    return 0;
}
