#include <iostream>
using namespace std;

// Singleton -> đảm bảo chỉ có object được tạo ra
class GPIO
{
private:
    GPIO()
    {
        uartInit(); // cach 1
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
    static GPIO *getInstance()
    { // method để khởi tạo object
        if (instance == nullptr)
        {
            instance = new GPIO(); // tạo ra 1 object duy nhất
            //instance->uartinit();  // cach 2
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