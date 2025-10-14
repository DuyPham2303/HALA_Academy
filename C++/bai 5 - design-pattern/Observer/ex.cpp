#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
/* 
    - cơ chế tự động cập nhập dữ liệu mới và thông báo đến nhiều thiết bị để xử lý hành động, mục đích khác nhau
    Abstract class 
    + Subject : đối tượng máy chủ      -> liên tục kiểm tra dữ liệu mới và thông báo đến cho các observer 
    + Observer: đối tượng đài quan sát -> cập nhật dữ liệu nhận từ subject -> triển khai hành động xử lý tuong ứng  
    concrete class (triển khai cụ thể)
    + concrete Subject : triển khai đối tượng cụ thể bao gồm các hành động
        - quản lý danh sách observers cần thông báo 
        - thêm/xóa observers 
        - kiểm tra/cập nhật dữ liệu mới 
        - thông báo cho observer (gọi cơ chế update từ Abstract class)
    + concrete Observer : các đối tượng observer cụ thể thực hiện
        - nhận dữ liệu từ subject -> triển khai hành động cụ thể (gọi hàm update từ Abstract class Subject)

*/
class Observer {
public:
    //hàm cập nhật dữ liệu tổng quát -> ghi đè cách xử lý dữ liệu bởi các observers khác nhau 
    virtual void update(float temperature, float humidity, float light) = 0;
};

// Subject (SensorManager) holds the state and notifies observers
class SensorManager {
    float temperature;
    float humidity;
    float light;
    vector<Observer*> observers;
protected:
     void notifyObservers() {
        //thông báo đến từng concrete observer 
        for (auto observer : observers) {
            observer->update(temperature, humidity, light); //mỗi obserer nhận thông báo và thực hiện hành động cụ thể
        }
    }
public:
    void registerObserver(Observer& observer) {
        observers.push_back(&observer);
    }

    void removeObserver(Observer* observer) {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void setMeasurements(float temp, float hum, float lightLvl) {
        this->temperature = temp;
        this->humidity = hum;
        this->light = lightLvl;
        notifyObservers();
    }
};

// Display component (an observer)
class Display : public Observer {
public:
    void update(float temperature, float humidity, float light) override {
      cout << "Display: Temperature: " << temperature
                  << ", Humidity: " << humidity
                  << ", Light: " << light << endl;
    }
};

// Logger component (an observer)
class Logger : public Observer {
public:
    void update(float temperature, float humidity, float light) override {
      cout << "Logging data... Temp: " << temperature
                  << ", Humidity: " << humidity
                  << ", Light: " << light << endl;
    }
};

int main() {
    SensorManager sensorManager;

    Display display;
    Logger logger;

    sensorManager.registerObserver(display);
    sensorManager.registerObserver(logger);

    sensorManager.setMeasurements(25.0, 60.0, 700.0); // Simulate sensor data update
    sensorManager.setMeasurements(26.0, 65.0, 800.0); // Another sensor update

    

    return 0;
}


