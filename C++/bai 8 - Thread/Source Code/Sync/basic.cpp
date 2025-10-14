#include<iostream>
#include<stdint.h>
#include<thread>
#include<chrono> //cung cấp các hàm để tạo delay
using namespace std;

/* 
    join : 1 luồng con sẽ tạo ra phụ thuộc vào luồng chính
        - luồng chính cần đợi luòng phụ kết thúc 
        - có thể lấy kết quả luồng join từ luồng chính
    detach : 1 luồng con được tạo ra và tách khỏi luồng chính
        - luồng con này chạy // với luồng chính
        - khi luồng chính kết thúc trước -> không thể lấy kết quả từ luồng detach 
*/
int count;
void delay(uint32_t time) {
    this_thread::sleep_for(chrono::milliseconds(time));
}
void task1(uint32_t limit, string str,int id) {
    int i = 0; 
    while (i < limit) {
        if(id == 2){
            count++;
        }
        cout << str << i++ << endl;
        delay(250);
    }
}

int main() {
    //thread t1(task1, 10, "thread 1: ",1); 
    thread t2(task1, 30, "thread 2: ",2);

    //luồng chính phải chờ 2 luồng t1 và t2 thực hiện xong mới chạy -> t1 và t2 sẽ chạy song song
    t2.detach();
     //t1.join();

    //vòng lập sau đây thực hiện xong thì các luồng tạo bên trên cũng dừng 
    for (int i = 0; i < 15; i++) {
        cout << "main thread" << endl;
        delay(250);
    }
    cout << "count : " << count;
}