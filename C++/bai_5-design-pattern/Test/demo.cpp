#include<iostream>
#include<vector>
#include<string>
using namespace std;

                                                        /* FACTORY DESIGN */
class sensor{
    public:
    //cơ chế đa hình tại runt-time -> xác định được hàm nào dưới đây được gọi tương ứng bởi lớp con nào
        virtual void sensor_initialize() = 0;
        virtual void display() = 0;
        virtual ~sensor(){
            cout << "destructor for sensor manager is called" << endl;
        };

};
class Tempsensor : public sensor{
    private:
        float temp;
    public:
        Tempsensor(float temp_init = 34.65) : temp(temp_init){}
        void display() override{
            cout << "temp value: " << temp << endl;
        }
        void sensor_initialize() override{
            cout << "temp sensor is initialized succssfully" << endl;
        }
       ~Tempsensor(){
            cout << "destructor for temp sensor is called" << endl;
       }
};
class Lighsensor : public sensor{
    private:
        int intensity;
    public:
        Lighsensor(float intensity_init = 45) : intensity(intensity_init){}
        void display() override{
            cout << "temp value: " << intensity << "%" << endl;
        }
        void sensor_initialize() override{
            cout << "light sensor is initialized successfully" << endl;
        }
        ~Lighsensor(){
            cout << "destructor for light sensor is called" << endl;
        }
};
class Speedsensor : public sensor{
    private:
        int speed;
    public:
        Speedsensor(int speed_init = 78) : speed(speed_init){}
        void display() override{
            cout << "temp value: " << speed << "km/h" << endl;
        }
        void sensor_initialize() override{
            cout << "speed sensor is initialized successfully" << endl;
        }
        ~Speedsensor(){
            cout << "destructor for speed sensor is called" << endl;
       }
};
class SensorFactory{
    public:
        //trả về 1 con trỏ đến lớp dẫn xuất/kế thừa từ sensor 
        static sensor* createSensor(const string& sensortype){
            if(sensortype == "temp sensor")           return new Tempsensor;
            else if(sensortype == "speed sensor")     return new Speedsensor;
            else if(sensortype == "light sensor")     return new Lighsensor;
            else {
                cout << "no sensor found" << endl;
                return NULL;
            }
    }
};
                                                        /* SINGLETON DESIGN */
class GPIO{
    private:
        void uartInit(){
            cout << "uart is Initialized" << endl;
        }
        //private constructor prevents any object outside scope to access directly
        GPIO(){
            uartInit();
        }
        ~GPIO(){
            cout << "Destructor for GPIO is called" << endl;
            if(Instance != NULL){
                delete Instance;
                Instance = NULL;
            }
        }
        //Unique instance for every MCU
        static GPIO* Instance;
        static int count;
    public:
        //method for indirectly create object
        static GPIO* GPIO_Initialize(){
            if(Instance == NULL){
                Instance = new GPIO;
            }
            count++;
            return Instance;
        }
        static int TotalMcu(){
            return count;
        }
};
//Initialize address for object
GPIO* GPIO :: Instance = NULL;
int GPIO::count = 0;
                                                        /* OBSERVER DESIGN */
class Observer{
    public:
        virtual void update(float temp,float humi,int light) = 0;
        //virtual ~Observer();
};
class Subject{
private:
    float temp_update;
    float humi_update;
    int light_update;
    //list of subscriber -> concrete observer
public:
    vector<Observer*> sensor_list;
    Subject(float temp_ = 0,float humi_ = 0,int light_ = 0) : temp_update(temp_),humi_update(humi_),light_update(light_){}
       
    void Subscribe(Observer& newsensor){
        sensor_list.push_back(&newsensor);
    }
    void removeSensor(Observer* removeSensor){
        vector<Observer*>::iterator it;
        for(it = sensor_list.begin() ; it != sensor_list.end() ; it++){
            if(*it == removeSensor)
                sensor_list.erase(it);
                break;
        }
    }
    void setsensor(float temp,float humi,int light){
        this->humi_update = humi;
        this->temp_update = temp;
        this->light_update = light;
        notification();
    }
    void notification(){
        for(auto sensor : sensor_list)
            sensor->update(temp_update,humi_update,light_update);
    }
};
class motor : public Observer{
    public: 
        void update(float temp_update,float humi_update,int light_update) override{
            cout << "temp value: " << temp_update << " celcius,"
                 << "humi value; " << humi_update << "%," 
                 << "light value: "<< light_update << "%" << endl;
            controlMotor(temp_update);
        }
        void controlMotor(float temp){
            if(temp > 50) cout << "speed up motor" << endl;
            else          cout << "slow down motor" << endl;
        }
};
class window : public Observer{
    public:
        void update(float temp_update,float humi_update,int light_update) override{
            cout << "temp value: " << temp_update << " celcius,"
                    << "humi value; " << humi_update << "%," 
                    << "light value: "<< light_update << "%" << endl;
            controlWindow(humi_update);
        }
        void controlWindow(float humi){
            if(humi > 50) cout << "open window" << endl;
            else          cout << "close window" << endl;
        }
};
int main(){
    //demo singleton
    /* GPIO* MCU1 = GPIO::GPIO_Initialize();
    GPIO* MCU2 = GPIO::GPIO_Initialize();
    GPIO* MCU3 = GPIO::GPIO_Initialize();
    GPIO* MCU4=  GPIO::GPIO_Initialize();

    cout << "total MCU: " << GPIO::TotalMcu() << endl;
    cout << "address: " << MCU1 << endl;
    cout << "address: " << MCU2 << endl;
    cout << "address: " << MCU3 << endl;
    cout << "address: " << MCU4 << endl; */
    //demo factory

    sensor* sensor = SensorFactory::createSensor("temp sensor");
    sensor->sensor_initialize();
    sensor->display();

    sensor = SensorFactory::createSensor("light sensor");
    sensor->sensor_initialize();
    sensor->display();

    sensor = SensorFactory::createSensor("speed sensor");
    sensor->sensor_initialize();
    sensor->display(); 
    

    delete sensor;
    //demo observer
   /*  Subject publisher;

    motor motor1;
    window window1;

    publisher.Subscribe(motor1);
    publisher.Subscribe(window1);

    publisher.removeSensor(&motor1);
    publisher.setsensor(65.21,34.11,67);
    publisher.setsensor(12.21,78.11,89); */



    return 0;
}