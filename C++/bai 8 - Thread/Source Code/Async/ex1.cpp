/* #include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>
#include <ctime>

// Dữ liệu cảm biến giả lập
struct SensorData {
    double speed;
    double fuel;
    double distance;
};

// Hàng đợi dữ liệu cảm biến
std::queue<SensorData> sensorQueue;
std::mutex mtx;
std::condition_variable cv;
bool newDataAvailable = false; // Cờ báo có dữ liệu mới

// Luồng 1: Giả lập cảm biến LiDAR
void sensorThread() {
    int count = 0;
    while (count < 5) { // Giả lập chạy 5 lần
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Giả lập thời gian đo đạc
        double speed = rand() % 100 + 20;
        double fuel = rand() % 10 + 1;
        double distance = rand() % 500 + 100;
        SensorData data = {speed,fuel,distance}; // Giả lập dữ liệu

        {
            std::lock_guard<std::mutex> lock(mtx); // Khóa để cập nhật dữ liệu
            sensorQueue.push(data);
            newDataAvailable = true; // Báo có dữ liệu mới
        }
        
        cv.notify_one(); // Đánh thức luồng xử lý
        count++;
    }
}

// Luồng 2: Xử lý dữ liệu cảm biến khi có dữ liệu mới
void processingThread() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        
        cv.wait(lock, [] { return newDataAvailable; }); // Chờ đến khi có dữ liệu mới
        
        while (!sensorQueue.empty()) {
            SensorData data = sensorQueue.front();
            sensorQueue.pop();
            newDataAvailable = false; // Đánh dấu đã xử lý dữ liệu

            // Xử lý dữ liệu
            std::cout << "[Xử lý] Tốc độ: " << data.speed
                      << " km/h, Nhiên liệu: " << data.fuel
                      << " L, Khoảng cách: " << data.distance << " m\n";
        }

        lock.unlock();
    }
}

int main() {
    std::thread t1(sensorThread);
    std::thread t2(processingThread);

    t1.join();
    t2.detach(); // Luồng xử lý tiếp tục chạy nếu cần

    std::cout << "Chương trình kết thúc!\n";
    return 0;
}
 */