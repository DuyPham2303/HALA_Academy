/* #include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <functional>
using namespace std;

atomic<int> sharedcnt(0); // shared variable used among multi-thread
mutex key;                // permission mechanism to access shared resources among multi-thread
void delay_ms(uint32_t time)
{
    this_thread::sleep_for(chrono::milliseconds(time));
}
void task(int it)
{
    for (int i = 0; i < it; i++)
    {
        lock_guard<mutex> lock(key);
        cout << ++sharedcnt << endl;
    }
}
void task1(int limit, function<void()> controlFunction)
{
    while (sharedcnt <= limit)
    {
        //LOCK GUARD
         {
             lock_guard<mutex> glock(key);
             controlFunction();
         }
         delay_ms(250);

        //UNIQUE LOCK
        unique_lock<mutex> unilock(key);
        controlFunction();
        unilock.unlock();
        delay_ms(250);
    }
}
int main()
{
    auto controlHMI = []()
    { cout << "task 1 control HMI\tcurrent count:\t" << ++sharedcnt << endl; };
    auto controlSERVO = []()
    { cout << "task 2 control SERVO\tcurrent count:\t" << ++sharedcnt << endl; };
    auto controlLED = []()
    { cout << "task 3 control LED\tcurrent count:\t" << ++sharedcnt << endl; };
    
    thread t1(task1, 20,controlHMI);
    thread t2(task1, 45,controlSERVO);
    thread t3(task1, 60,controlLED);

    t1.join();
    t2.join();
    t3.join();
} */