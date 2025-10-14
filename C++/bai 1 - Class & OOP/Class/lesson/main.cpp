#include <iostream>
#include <stdint.h>
using namespace std;
// class : phiên bản nâng cấp của struct
/*
    - chứa biến,hàm
    - quản lý thông qua access modidier (quyền truy cập)
    - khả năng trừu tượng và mở rộng
    => thích hợp quản lý đối tượng có đặc điểm thay đổi theo thời gian
*/
// basic traits of class
/*
    - biến (properties)
    - hàm (method)
    - đối tượng (object)
    - quyền truy cập private (default)

    + Scope operator
        - sử dụng :: để truy cập method/properties bên ngoài class ko phụ thuộc object
        - sử dụng . hoặc -> để truy cập method/properties thông qua object
        - con trỏ this  (khi tạo ra 1 class, this được khởi tạo cùng lúc đẻ luôn trỏ tới các thành phần thuộc class đó)
*/
// constructor / destructor
/*
    + Hàm tạo : khởi tạo tham số truyền vào cho object
        - luôn được gọi khi khởi tạo 1 object (nếu có)
        - cùng tên với class
        - không có kiểu trả về
        - 2 loại :
            -> non-param
            -> chứa param chưa khởi tạo
            -> chứa param đã khởi tạo
    + Hàm hủy : thu hồi các object đã khởi tạo (LIFO)
        - cùng tên class (chứa ~ để phân biệt với hàm tạo)
        - ko có kiểu trả về
        - được gọi khi program kết thúc (nếu có)
            -> thường dùng để thu hồi các vùng cấp phát động
*/
// static method/properties
/*
    + static properies
        - thuộc tính chia sẻ chung address giữa các object class
        - khởi tạo global thông qua ::
        - truy cập bất cứ đâu (ko phụ thuộc object)
    + static method
        - method chia sẻ ko phụ thuộc object class
        - có thể gọi static properties
        - Không cho phép gọi non-static method/properties

*/
class student
{
public:
    static int count;
    string name;
    float gpa;
    int age;

    void create();
    void printInfo();
    student();
    student(string name, float gpa, int age);    
    static int countTotal();
    ~student();
};

student::student(string name, float gpa, int age)
{
    this->name = name;
    this->gpa = gpa;
    this->age = age;
    this->count++;
    this->printInfo();
}
student::~student()
{
    cout << "thu hồi vùng nhớ lưu trữ đối tượng" << this->name << endl;
}
// định nghĩa method -> toán tử phạm vi :: kèm tên class
void student::create()
{
    name = "Duy";
    gpa = 3.4;
    age = 23;
}
void student::printInfo()
{
    cout << "name:" << name << endl
         << "gpa: " << gpa << endl
         << "age: " << age << endl;
}
int student::countTotal()
{
     return count;
}
// khởi tạo trước khi dùng
int student::count = 0;
int main()
{
    student st1("Duy", 23.2, 12);
    student st2("Linh", 3.2, 22);
    student st3("Thong", 21.2, 32);
    student st4("Anh", 12.2, 14);

    cout << "total: " << student::countTotal() << endl;
    return 0;
}