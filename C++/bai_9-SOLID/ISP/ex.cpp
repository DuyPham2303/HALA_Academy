#include <iostream>
using namespace std;
/* 
    Interface Segregation Principle : 
    - Quy định 1 hệ thống nên chia thành nhiều base class tương ứng với chức năng/nhiệm vụ xử lý khi được kế
    thừa lại từ class con 
    -> tránh việc chỉ triển khai 1 base class duy nhất 
    -> dẫn đến nhiều class con khác nhiệm vụ/hành vi lại truy cập đến các method không liên quan đến nó
    + Ví dụ ta triển khai 1 base class duy nhất để mô tả hành vi của 1 phương tiện di chuyển
        - lái xe
        - đổ xăng
        - chở hàng hóa
    => các class con như bike,car,motor khi kế thừa từ base class trên sẽ không có nhu cầu sử dụng toàn bộ 
    -> dẫn đến có khả năng truy cập ào các method ko liên quan để sử dụng -> sai hành vi hệ thống

*/
class IVehicle
{
public:
    virtual void drive() = 0;     // phương tiện có thể lái
    virtual void refuel() = 0;    // tiếp nhiên liệu
    virtual void loadCargo() = 0; // chở hàng hóa
};

class Bike : public IVehicle
{
public:
    void drive() override
    {
        cout << "Lái xe đạp" << endl;
    }

    void refuel() override {} // Không cần thiết với xe đạp (có thể ghi đè cách triển khai -> sai hành vi, bản chất của class con hiện tại)
    void loadCargo() override {}
};

/* 
    Hướng giải quyết đó là đối với mỗi phương tiện cụ thể (deprived class) sẽ được triển khai 1 abstract class tương ứng để cung
    cấp hành vi mong muốn cho phương tiện đó 

*/
// Interface cho phương tiện có thể lái
class IDriveable
{
public:
    virtual void drive() = 0;
};

// Interface cho phương tiện có thể lái
class IFuelable
{
public:
    virtual void refuel() = 0;
};

// Interface cho phương tiện có thể lái
class ICargo
{
public:
    virtual void loadCargo() = 0;
};

// Xe ô tô
class Car : public IDriveable, public IFuelable, public ICargo
{
public:
    void drive() override { cout << "Lái ô tô" << endl; }

    void refuel() override { cout << "Đổ xăng" << endl; }

    void loadCargo() override { cout << "Chở hàng" << endl; }
};

// xe đạp
class Bike : public IDriveable, public ICargo
{
public:
    void drive() override { cout << "Lái xe đạp" << endl; }

    void loadCargo() override { cout << "Chở hàng" << endl; }
};
