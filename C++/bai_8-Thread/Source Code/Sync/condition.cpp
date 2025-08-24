/* #include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <condition_variable>
using namespace std;
atomic<int> sharedcnt(0); // shared variable used among multi-thread
atomic<int> sensor_data(0);
mutex key;                // permission mechanism to access shared resources among multi-thread
condition_variable notification;
bool IsdataRcv = false;

void delay_ms(uint32_t time) {
    this_thread::sleep_for(chrono::milliseconds(time));
}

void sensor_read() {
    while (1) {
        //wait a bit
        delay_ms(200);
        //lock shared resource to get sensor data
        unique_lock<mutex> unilock(key);
        //read data
        sensor_data = rand() % 100;
        //update action status and print out behaviour
        IsdataRcv = true;
        cout << "done read data" << endl;
        //lock shared resources 
        unilock.unlock();
        //fire notification to execute action with received data
        notification.notify_one();
    }
}
void process_data() {
    while (1) {
        //delay a bit
        delay_ms(200);
        //unlock resources to proces data
        unique_lock<mutex> unilock(key);
        //wait until other thread fire notification
        notification.wait(unilock, []() {return IsdataRcv;});
        //reset read status and execute action -> print out notification
        cout << "data: " << sensor_data << endl;
        IsdataRcv = false;
        //unlock data when done processed
        unilock.unlock();
    }
}

int main() {
    thread thread_read(sensor_read);
    thread thread_process(process_data);

    thread_read.join();
    thread_process.join();
	return 0;
} */