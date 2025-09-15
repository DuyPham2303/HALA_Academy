#include "encap-abstract.cpp"

class ElectricCar : public Car
{
private:
    int batteryCapacity; // Dung lượng pin

public:
    // Constructor
    ElectricCar(string b, string m, int s, int battery) : Car(b, m, s), batteryCapacity(battery) {}

    // Getter và Setter cho batteryCapacity
    int getBatteryCapacity() { return batteryCapacity; }
    void setBatteryCapacity(int battery) { batteryCapacity = battery; }

    // Ghi đè phương thức displayInfo để hiển thị thêm thông tin về pin
    void displayInfo()
    {
        Car::displayInfo();
        cout << "Battery Capacity: " << batteryCapacity << " kWh" << endl;
    }
};
class GasCar : public Car
{
public:
    GasCar(string b, string m, int s) : Car(b, m, s) {}
    void startEngine() override
    {
        cout << "Gas engine started!" << endl;
    }

    void stopEngine() override
    {
        cout << "Gas engine stopped!" << endl;
    }
};
