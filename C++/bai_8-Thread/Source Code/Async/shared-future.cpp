/* #include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <future>
#include <condition_variable>
using namespace std;
atomic<int> sharedcnt(0); // shared variable used among multi-thread
atomic<int> sensor_data(0);
mutex key;                // permission mechanism to access shared resources among multi-thread

void delay_ms(uint32_t time) {
    this_thread::sleep_for(chrono::milliseconds(time));
}
void mutex_lockunique(int it, int thread_id)
{
    while (sharedcnt < it)
    {
        unique_lock<mutex> unilock(key);
        cout << "thread " << thread_id << ": " << sharedcnt++ << endl;
        delay_ms(300);
    }
}
void process_AsynSharedData(int id, shared_future<int> shared_data) {
    unique_lock<mutex> unilock(key);
    cout << "device " << id << " after process data: " << shared_data.get() << endl;
    unilock.unlock();
}
int read_AsynSharedData() {
    unique_lock<mutex> unilock(key);
    cout << "reading sensor..."<< endl;
    unilock.unlock();
    delay_ms(8000);
    cout << "done read data" << endl;
    sensor_data = rand() % 100;
    return sensor_data;
}
int main() {
    //store returned data at heap 
    shared_future<int> shared_result = async(launch::async, read_AsynSharedData).share();  // allow multi-thread to access result             

    thread shared_t1(process_AsynSharedData, 1, shared_result);
    thread shared_t2(process_AsynSharedData, 2, shared_result);

    for (int i = 0; i < 12 ; i++) {
        cout << "main execute -> event count:" << i << endl;
        delay_ms(1000);
    }
    shared_t1.join();
    shared_t2.join();
	return 0;
} */