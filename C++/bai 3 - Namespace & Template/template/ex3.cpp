#include <iostream>
using namespace std;

// Template tổng quát cho class -> giúp 1 class chứa nhiều phiên bản method cùng tên nhưng khác cách triển khai/định nghĩa
template <typename T>
class Printer
{
    public:
        static void print(T value)
        {
            cout << "Generic: " << value << endl;
        }
};

// Chuyên biệt hóa cho kiểu `char*`
template <>
class Printer<char*>
{
    public:
        static void print(char* value)
        {
            cout << "String specialization: " << value << endl;
        }
};

// Chuyên biệt hóa cho kiểu `bool`
template <>
class Printer<bool>
{
    public:
        static void print(bool value)
        {
            cout << "Boolean specialization: " << (value ? "true" : "false") << endl;
        }
};

int main()
{
    Printer<int>::print(100);          // Sử dụng template tổng quát
    Printer<double>::print(3.14);      // Sử dụng template tổng quát
    Printer<char*>::print("Hello");    // Sử dụng template chuyên biệt hóa
    Printer<bool>::print(true);        // Sử dụng template chuyên biệt hóa
    return 0;
}

