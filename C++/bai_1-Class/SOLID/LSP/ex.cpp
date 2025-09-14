#include <iostream>
using namespace std;
/* 
    Liskov Substitution Principle : quy định 1 lớp con không được phép thay đổi hành vi khi kế thừa từ lớp cha 
    + ví dụ ta có 1 class car quản lý các tính năng trên xe hơi như 
     - đổ xăng
     - lái xe
     - dừng xe 
     => 1 class ElectricCar kế thừa class trên, nhưng xe điện thì sẽ không đổ xăng, 
     mặc dù method lái xe,dừng xe có thể dùng lại. Nhưng nó có thể thay đổi method đổ xăng thành sạc pin để phù hợp -> hành vi lớp cha bị thay đổi

*/
class Car{
    public:
        virtual void refuel(){
            cout << "Đổ xăng" << endl;
        }
};
   
class ElectricCar : public Car{
    public:
        void refuel() override{
            // Xe điện không thể đổ xăng
            cout << "Xe điện không dùng xăng!" << endl;
        }
};
/* 
    Hướng giải quyết là tạo 1 class tổng quát đại diện cho phương tiện 
    + Triển khai các class con tương ứng với mỗi loại xe, và truy cập vào method từ base class -> cung cấp cách thức xử lý thực tế

*/
class Vehicle
{
    public:
        virtual void rechargeOrRefuel() = 0;
};
   
class GasCar : public Vehicle
{
    public:
        void rechargeOrRefuel() override
        {
            cout << "Đổ xăng" << endl;
        }
};

class ElectricCar : public Vehicle
{
    public:
        void rechargeOrRefuel() override
        {
            cout << "Sạc pin" << endl;
        }
};
   
int main()
{
    Vehicle* v1 = new GasCar();
    v1->rechargeOrRefuel();
   
    Vehicle* v2 = new ElectricCar();
    v2->rechargeOrRefuel();
    return 0;
}

