#include <iostream>
#include <string>

using namespace std;

//Product : class tổng quát mô tả các sensor
class Sensor{
    public:
        virtual void readData() = 0;
};

//concrete product : lớp con cụ thể kế thừa Product
class TemperatureSensor : public Sensor{
    public:
        void readData() override {
            cout<<"reading temp data: " <<endl;
        }
};

//concrete product : lớp con cụ thể kế thừa Product
class HumiditySensor : public Sensor{
    public:
        void readData() override {
            cout<<"reading humidity data: " <<endl;
        }
};

//Creator class : lớp khởi tạo tổng quát 
class SensorFactory{
    public:
        //overloading method được ghi đè ở các concrete creator
        static Sensor* createSensor(){
            cout << "Uninitialized Sensor" << endl;
            return nullptr;
        }
};

//concrete creator
class TempCreator : public SensorFactory{
    public:     
        static Sensor* createSensor(){
            cout << "Temp sensor has been created" << endl;
            return new TemperatureSensor;
        }
};
class HumiCreator : public SensorFactory{
    public:
        static Sensor* createSensor(){
            cout << "Humi sensor has been created" << endl;
            return new HumiditySensor;
        }
};

int main(int argc, char const *argv[])
{
    Sensor* sensor = TempCreator::createSensor();
    sensor->readData();

    sensor = HumiCreator::createSensor();
    sensor->readData();
    return 0;
}

