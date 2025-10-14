#include <iostream>
#include <memory>
using namespace std;
class Sensor
{
private:
    float value1;
    float value2;

public:
    /*cach 2*/
    Sensor(float init1 = 23.21, float init2 = 12.21)
    { // : value1(init1) , value2(init2){}
        value1 = init1;
        value2 = init2;
    }
    ~Sensor()
    {
        cout << "call destructor" << endl;
    }
    float getValue1()
    {
        return value1;
    }
    float getValue2()
    {
        return value2;
    }
    void setValue1(float value1)
    {
        this->value1 = value1;
    }
    void display()
    {
        cout << "sensor1 value: " << getValue1() << endl;
        cout << "sensor2 value: " << getValue2() << endl;
    }
};
int main()
{
    unique_ptr<Sensor> uptr = make_unique<Sensor>(10); // return heap memory to be managed by bother uptr and its raw pointer
    cout<< "default data" << endl;
    uptr->display(); // cach 2 : (*uptr).display();
    uptr->getValue1();
    uptr->getValue2();


    // get data -> trả về raw nhưng vẫn còn quyền sở hữu
    cout << "get data" << endl;
    Sensor *rawptr = uptr.get();
    rawptr->setValue1(100.21);
    rawptr->display();

    // release -> giải phóng raw pointer và object
    cout << "release" << endl;
    rawptr->setValue1(89.23);
    rawptr = uptr.release();
    rawptr->display();
    delete rawptr; // tự giải phóng do unique_ptr đã được thu hồi

    // reset: thu hồi object và cho phép quản lý đối tượng mới
    cout << "reset" << endl;
    uptr.reset(new Sensor(20));
    uptr->display();

    // move: chuyển quyền sở hữu
    cout << "move" << endl;
    unique_ptr<Sensor> uptr2 = move(uptr);
    uptr2->display();
}