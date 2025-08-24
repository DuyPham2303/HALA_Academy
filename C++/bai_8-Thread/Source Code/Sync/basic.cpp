#include<iostream>
#include<stdint.h>
#include<thread>
#include<chrono> //cung cấp các hàm để tạo delay
using namespace std;
void delay(uint32_t time) {
    this_thread::sleep_for(chrono::milliseconds(time));
}
void task1(uint32_t limit, string str) {
    int i = 0;
    while (i < limit) {
        cout << str << i++ << endl;
        delay(250);
    }
}

int main() {
    thread t1(task1, 70, "thread 1: ");
    thread t2(task1, 50, "thread 2: ");

    //luồng chính phải chờ 2 luồng t1 và t2 thực hiện xong mới chạy -> t1 và t2 sẽ chạy song song
    t2.detach(); //cho phép t1 chạy song song với luồng chính 
    if (t1.joinable()) {
        cout << "luong t1 chua ket thuc";
        t1.join();
    }
    else cout << "luong 1 da ket thuc";

    //vòng lập sau đây thực hiện xong thì các luồng tạo bên trên cũng dừng 
    for (int i = 0; i < 10; i++) {
        cout << "main thread" << endl;
        delay(250);
    }
    t1.join();

}