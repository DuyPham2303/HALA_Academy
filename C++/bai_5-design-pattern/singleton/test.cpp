#include <iostream>
using namespace std;

/* Singleton : mẫu thiết kế đảm bảo 1 class chỉ được phép tạo ra 1 object duy nhất -
              -> tránh tạo ra nhiều object (Khi tạo ra các bản copy để truy cập dữ liệu từ object gốc)-> tốn RAM
    + vÍ DỤ 
    - Khởi tạo cấu hình GPIO,Timer,Uart, khi cần truy cập và log ra thông tin hoặc dùng lại cấu hình cho nhiều ngoại vi 
        -> cần tạo ra bản sao (Tốn RAM) 

    + Giải pháp 
    - singleTon cho phép khởi tạo 1 object duy nhất cho class và có địa chỉ cố định 
        -> chia sẻ chung cho tất cả các object khai báo từ class đó

    + Các thành phần
    - private constructor 
        + đảm bảo không ai có thể khởi tạo đối tượng bên ngoài class 
        + Sử dụng 1 hàm khởi tạo gián tiếp bên trong class để gọi ra constructor 
    - static property
        + đối tượng tĩnh duy nhất 
        + đảm bảo chỉ cho phép tạo ra 1 đối tượng từ class
    - static method
        + phương thức cho phép truy cập bất kỳ dâu thông qua tên class
*/

class GPIO
{
private:
    GPIO()  /* Private constructor */
    {
        //cách 1 : gọi method xử lý cấu hình -> chạy duy nhất 1 lần
        uartInit(); // chuấ cấu hình thông số cấu hình
    }
    void uartInit()
    {
        cout << "UART is initialized" << endl;
        /* 
            detail implementation 
        */
    }
    static GPIO *instance; // trỏ đến object duy nhất
public:
    static GPIO *getInstance()  /* static Instance */
    { // method để khởi tạo object
        if (instance == nullptr)
        {
            //cấp phát vùng nhớ cho instance quản lý
            instance = new GPIO(); 

            //cách 2:  gọi trưc tiếp method cấu hình
            instance->uartInit();  
        }
        return instance;
    }
};
GPIO *GPIO::instance = nullptr; // cấp phát địa chỉ cho static property

int main()
{
    GPIO::getInstance(); // gọi hàm trả về địa chỉ của obkect đã tạo

    GPIO::getInstance();//trả về địa chỉ của object được khởi tạo ở lần đầu gọi
    return 0;
}