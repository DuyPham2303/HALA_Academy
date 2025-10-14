#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <future>
using namespace std;
atomic<int> sharedcnt(0); // shared variable used among multi-thread
mutex key;                // permission mechanism to access shared resources among multi-thread

void delay_ms(uint32_t time) {
    this_thread::sleep_for(chrono::milliseconds(time));
}
int asyn_read() {
    for (int i = 0; i < 30; i++) {
        unique_lock<mutex> unilock(key);
        //lock_guard<mutex> glock(key);
        cout << "read sensor data\tevent count: " << sharedcnt++ << endl;
        unilock.unlock();
        delay_ms(250);
    }

    int sensor_data = rand() % 100;
    cout << "done read data" << endl;
    return sensor_data;
}

int main() {
    //store returned data at heap 
    future<int> unique_result = async(launch::async, asyn_read);   //does not allow other thread to access result      

    for (int i = 0; i < 5; i++) {
        unique_lock<mutex> unilock(key);
        cout << "main\tevent count: " << sharedcnt++ << endl;
        unilock.unlock();
        delay_ms(1000);
    }
    cout << "data has been successfully processes : " << unique_result.get() << endl;

    return 0;
}