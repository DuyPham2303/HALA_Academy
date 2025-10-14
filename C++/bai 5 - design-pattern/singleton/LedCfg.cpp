#include <iostream>
#include "LedCfg.hpp"
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

class LedController
{
private:
    GPIO_StructInitTypedef gpioParamCfg;
    vector<GPIOpin_StructConfig *> PinCfgList;
    LedController(GPIO_PORT Port = PORTB, GPIO_Speed speed = Speed_HIGH, GPIO_Mode Mode = OutputMode)
    {
        gpioParamCfg.Port = Port;
        gpioParamCfg.Speed = speed;
        gpioParamCfg.Mode = Mode;
    }
    static LedController *instance;

public:
    static LedController *getInstace()
    {
        if (!instance)
        {
            // cach 1
            instance = new LedController();
        }
        return instance;
    }
    void CfgLog()
    {
        map<GPIO_PORT, string> PortNameMap;
        map<GPIO_Mode, string> ModeNameMap;
        map<GPIO_Speed, string> SpeedNameMap;

        string name_port[] = {"PORT A", "PORT B", "PORT C", "PORT D"};
        string name_mode[] = {"MODE INPUT", "MODE OUTPUT"};
        string name_speed[] = {"SPEED LOW", "SPEED HIGH"};

        PortNameMap[gpioParamCfg.Port] = name_port[gpioParamCfg.Port];
        ModeNameMap[gpioParamCfg.Mode] = name_mode[gpioParamCfg.Mode];
        SpeedNameMap[gpioParamCfg.Speed] = name_speed[gpioParamCfg.Speed];

        cout << PortNameMap[gpioParamCfg.Port] << endl;
        cout << ModeNameMap[gpioParamCfg.Mode] << endl;
        cout << SpeedNameMap[gpioParamCfg.Speed] << endl;
    }
    void setPin(GPIOpin_StructConfig *PinCfg)
    {
        PinCfgList.push_back(PinCfg);
    }
    void readPin(GPIO_Pin pin)
    {
        string name_pin[] = {"pin 0", "pin 1", "pin 2", "pin 3","pin 4","pin 5"};
        string name_state[] = {"IS LOW","IS HIGH","\tSTATE IS UNSET"};
        map<GPIO_Pin,string> NamePinmap;
        map<pinState,string> NameStatemap;
        for (const auto &pinRead : PinCfgList)
        {
            if (pinRead->pin == pin)
            {
               NamePinmap[pinRead->pin] = name_pin[pinRead->pin];
               NameStatemap[pinRead->state] = name_state[pinRead->pin];
               cout << NamePinmap[pinRead->pin] << "\t" << name_state[pinRead->state] << endl;
               return;
            }
        }
        cout << name_pin[pin] << name_state[2] << endl;
    }
};

LedController *LedController::instance = nullptr; // 0xc8 : địa chỉ cố định

int main(int argc, char const *argv[])
{
    LedController *GPIOCfg = LedController::getInstace();

    GPIOCfg->CfgLog();

    GPIOpin_StructConfig pin_0{.pin = GPIO_PIN_0, .state = Pin_HIGH};
    GPIOpin_StructConfig pin_1{.pin = GPIO_PIN_1, .state = Pin_LOW};
    GPIOpin_StructConfig pin_2{.pin = GPIO_PIN_2, .state = Pin_LOW};
    GPIOpin_StructConfig pin_3{.pin = GPIO_PIN_3, .state = Pin_HIGH};

    GPIOCfg->setPin(&pin_2);
    GPIOCfg->setPin(&pin_3);

    GPIOCfg->readPin(GPIO_PIN_0);
    GPIOCfg->readPin(GPIO_PIN_2);
    GPIOCfg->readPin(GPIO_PIN_4);

    return 0;
}
