#include <iostream>
#include <string>
using namespace std;

template <typename type1, typename type2>
class Sensor
{
private:
    type1 value1;
    type2 value2;
public:
    /*cach 1*/
    Sensor(type1 init1, type2 init2)
    {
        value1 = init1;
        value2 = init2;
    }
    /*cach 2*/
    // Sensor(type1 init1,type2 init2) : value1(init1) , value2(init2{}
    type1 getValue1()
    {
        return value1;
    }
    type2 getValue2()
    {
        return value2;
    }
    void display()
    {
        cout << "sensor1 value: " << getValue1() << endl;
        cout << "sensor2 value: " << getValue2() << endl;
    }
};
template <typename Arrtype, int size>
class Array
{
private:
    Arrtype arr[size];

public:
    void set(int index, Arrtype value)
    {
        if (index >= 0 && index < size)
            arr[index] = value;
    }
    Arrtype getElement(int index)
    {
        return arr[index];
    }
};
typedef struct dataStruct{
    int a = 0;          //4 byte
    char b = 1;         //1 byte
    unsigned char c = 2;//1 byte    
    char* f;            //4 byte + 2 padding byte
    double d = 21;      //8 byte
    char a =21;         //1 byte + 7 padding byte
};
int main()
{
    dataStruct data1;
    sizeof(data1);

    Sensor<double,double> tempSensor(65.12,40.45); //temp and humi 
    tempSensor.display();

    Sensor<int, int> lightSensor(510, 390); // upper and lower range
    lightSensor.display();

    Sensor<string, float> StateSensor("ON", 3.14);
    StateSensor.display();

    Array<int,5> arr;
    for(int i = 0 ; i < 5 ; i++)
        arr.set(i,i + 2);
    for(int i = 0 ; i < 5 ;i++)
       cout << arr.getElement(i) << " "; 
    return 0;
}