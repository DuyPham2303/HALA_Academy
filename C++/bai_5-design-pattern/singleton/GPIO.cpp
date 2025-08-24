#include <iostream>
void gpioInit();

void gpioSetPin(int pin, bool value);

void gpioReadPin(int pin);

class GpioManager{
    private:
        GpioManager();
        static GpioManager* instance;
        void init(){
            gpioInit();
        }
    public:
        static GpioManager *getInstace(){
            if(!instance){
                instance = new GpioManager(); // 0xc8
                instance->init();
                // bổ sung thêm tính năng
            }
            return instance;
        }
        void setPin(int pin, bool value){
            gpioSetPin(pin, value);
        }
        void readPin(int pin){
            gpioReadPin(pin);
        }
};

class PORTx{
    private:
        PORTx();
        static PORTx* instance;
        void init(){
            //gpioInit();
        }
    public:
        static PORTx *getInstace(){
            if(!instance){
                instance = new PORTx();
                instance->init();
            }
            return instance;
        }
};


GpioManager* GpioManager::instance = nullptr; // 0xc8 : địa chỉ cố định

int main(int argc, char const *argv[])
{
    GpioManager* gpioManager = GpioManager::getInstace();

    gpioManager->setPin();

    gpioManager->readPin();

    GpioManager* gpioManager2 = GpioManager::getInstace();

    return 0;
}







