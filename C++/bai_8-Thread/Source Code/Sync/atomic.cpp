/* #include<iostream>
#include<thread>
#include<mutex>
#include<atomic>
#include<variant>
using namespace std;

int cnt = 0;
atomic<int> sharedcnt(0);
void task(int it){
    while(cnt < it){
        cout << ++cnt << endl;
    }
}
int main(){
    thread t1(task,20);
    thread t2(task,15);

    t1.join();
    t2.join();

} */