#include <iostream>
using namespace std;
/*
    - Single Responsibility Principle : quy định 1 class chỉ nên quản lý 1 tính năng, nhằm mục đích
        + giảm thiểu sự phức tạp
        + Dễ dàng kiểm tra và xử lý lỗi, khi chia nhỏ hệ thống ra thành các module
    - Ví dụ: ta có 1 hệ thống điều khiển động cơ gồm 3 tác vụ
        + đọc data
        + xử lý data
        + truyền data (có thể nhiều kiểu -> uart,spi,i2c,can)
        => nếu gộp cả 3 hành vi vào 1 class như bên dưới sẽ khó quản lý (nếu sau này mở rộng thêm tính năng)

*/
class SpeedSensor
{
public:
    double getSpeed()
    {
        // đọc dữ liệu cảm biến
        return 80.5;
    }

    void controlEngine(double speed)
    {
        if (speed > 100)
        {
            cout << "Giảm tốc độ động cơ" << endl;
        }
    }
};
/*
    - Hướng giải quyết là chia hệ thống thành các class đảm nhiệm từng hành vi, giúp
        + dễ dàng mở rộng tính năng mới có liên quan đến mỗi hành vi
        + ví dụ :
        - EngineController có thể mở rộng thêm adjust các thuộc tính khác (Torque,current,voltage)
        - SpeedSensor có thể mổ trộng thêm
            * các method đọc nhiều loại sensor khác nhau
            * các method hiệu chỉnh data đọc từ sensor để lọc nhiễu
*/
class SpeedSensor
{
public:
    double getSpeed() { return 40; }
};
class EngineController
{
public:
    void adjustSpeed(double speed)
    {
        if (speed <= 40)
        {
            cout << "Tăng tốc độ động cơ" << endl;
        }
        else if (speed >= 100)
        {
            cout << "Giảm tốc độ động cơ" << endl;
        }
    }
};
int main()
{
    SpeedSensor speedSensor;
    double speed = speedSensor.getSpeed();
    EngineController engine;
    engine.adjustSpeed(speed);
    return 0;
}

