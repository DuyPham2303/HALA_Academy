#include <iostream>
#include <string>
using namespace std;

/*
    - OOP
    + encapsulation : quá trình đóng gói dữ liệu, ân đi thuộc tính hệ thống thông qua (private/protected)
        -> Giấu đi việc truy cập trực tiếp các biến

    + abstraction :  trừu tượng đi quá trình xử lý logic, thuật toán
        -> Giấu đi phần triển khai cụ thể, truy cập thông qua API

    + Inheritance : khả năng tái sử dụng tài nguyên của lớp có sẵn, và chỉ việc mở rộng thểm các chức năng mới
        - 4 loại : sử dụng với cú pháp <deprived class> : <scope> <base class>
            - public : lớp con kế thừa tất cả đặc điểm từ base
            - private : lớp con chỉ kế thừa tài nguyên private từ base
            - protected : chuyển toàn bộ đặc điểm của base sang proteced cho class con kế thừa
            - đa kế thừa : 1 class kết thừa từ nhiều class
        - overloading : khả năng 1 class con mở rộng 1 method từ base class
    + Polymorphism : khả năng 1 method có thể có nhiều phiên bản/cách triển khai khác nhau, dựa trên đối tượng hiện tại mà nó đang trỏ tới
                     thông qua lớp cơ sở
        - down/up casting : éo kiểu để truy cập method của kiểu class mong muốn, thông thường base -> deprived (1 base truy cập nhiều deprived)
        - virtual function : 
            + hàm ảo cho phép ghi đè định nghĩa từ deprived class
            + dùng override để phân biệt với nạp chông hàm 

        - overloading vs overriding
        - pure virtual function
            + luôn gán = 0, và ko chứa definition
            + cần định nghĩa ở deprived class
            + trở thàn abstract class (chứa 1 pure virtal function) -> ko cho phép tạo object 
        - Abstract Class
        - Interface : chỉ chứa pure virtual function (ko có tù khóa để phân biệt)
*/

class Person
{
private:
    int age;
    string name;
    bool verifyString();
    bool verifyNumber();

public:
    Person(string name, int age);
    void printInfo(); 
    // hàm ảo cho phép lớp con ghi đè cách triển khai, khi gọi thông qua object của base class
    virtual void Info()
    {
        if (verifyNumber())
            cout << "age : " << age << endl;
        else
        {
            cout << "Tuổi không hợp lệ" << endl;
        }
        if (verifyString())
            cout << "name : " << name << endl;
        else
        {
            cout << "tên không hợp lệ" << endl;
        }
    }
    virtual void behaviour() = 0;
};
void Person::printInfo()
{
    if (verifyNumber())
        cout << "age : " << age << endl;
    else
    {
        cout << "Tuổi không hợp lệ" << endl;
    }
    if (verifyString())
        cout << "name : " << name << endl;
    else
    {
        cout << "tên không hợp lệ" << endl;
    }
}
bool Person::verifyNumber()
{
    if (age < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}
bool Person::verifyString()
{
    for (int i = 0; i < name.length(); i++)
    {
        if (name[i] >= static_cast<char>(65) && name[i] <= static_cast<char>(122) || name[i] == ' ')
        {
            continue;
        }
        else
            return false;
    }
    return true;
}
Person::Person(string name, int age)
{
    this->age = age;
    this->name = name;
}

class Student : public Person
{
private:
    float gpa;
    string major;

public:
    Student(string name, int age, string major, float gpa) : Person(name, age), major(major), gpa(gpa) {}
    void printInfo()  // overloading function -> mở rộng method của base class
    {
        cout << "Thông tin SINH VIÊN" << endl;
        Person::printInfo();
        cout << "major : " << major << endl;
        cout << "gpa : " << gpa << endl;
    }
    void behaviour(){
        cout << "do homework" << endl;
    }

    // từ khóa override giúp phân biệt với overloading function
    void Info() override    //ghi đè method của base class
    { 
         cout << "Thông tin SINH VIÊN" << endl;
         cout << "major : " << major << endl;
         cout << "gpa : " << gpa << endl;
     }
};
class Teacher : public Person
{
private:
    string position;
    int id;

public:
    Teacher(string name, int age, string position, int id) : Person(name, age), position(position), id(id) {}
    void printInfo()
    {
        cout << "***Thông tin GIÁO VIÊN" << endl;
        Person::printInfo();
        cout << "position : " << position << endl;
        cout << "id : " << id << endl;
    }
    void Info() override
    {
        cout << "***Thông tin GIÁO VIÊN" << endl;
        Person::printInfo();
        cout << "position : " << position << endl;
        cout << "id : " << id << endl;
    }
    void behaviour(){
        cout << "correct homework" << endl;
    }
};

int main()
{
    // Person object1("Duy Pham",23);
    // object1.printInfo();

    Student st1("Linh Anh", 23, "mechatronics engineer", 8.2);
    Teacher Tc1("Duy Pham", 24, "C program", 21);

    // quản lý nhiều deprived class thông qua con trỏ của lớp cơ sở
    Person *p; // con trỏ tới nhiều object khác nhau để truy cập các phiên bản method
    /*
        - thông tin in ra sẽ gọi ra method dựa trên kiểu dữ liệu của con trỏ p
        - dù các thuộc tính tương ứng với các đối tượng khởi tạo từ deprived class vẫn gọi đúng
        - method của đối tượng được gọi thuộc về chính con trỏ của lớp cơ sở
        => cần ép kiểu từ base -> deprived (up casting)
    */
    p = &st1;
    ((Student *)p)->printInfo();
    p = &Tc1;
    ((Teacher *)p)->printInfo();
    // đa hình runtime
    /*
        - tự động xác định phiên bản khác nhau của cùng 1 hàm dựa trên đối tượng đang được trỏ tới
        - chỉ áp dụng cho hàm ảo kế thừa bởi lớp con (không cần ép kiểu như ví dụ trên)
    */
    cout << "----------------------------" << endl;
    p = &st1;
    p->Info();
    p->behaviour();
    p = &Tc1;
    p->Info();
    p->behaviour();
    
    return 0;
}