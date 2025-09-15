#include <iostream>
using namespace std;
/* 
    - Open-closed Principle : quy định 1 hệ thống khi đã chạy ổn định thì sẽ không được chỉnh sữa khi thêm new features đảm bảo
        + rủi ro can thiệp và thay đổi trực tiếp mã nguồn, dễ gây lỗi
        + Giảm bớt độ complex, tgian khi trace back vị trí trong code cần chỉnh sửa -> chương trình càng lớn -> thay đổi ko cẩn thận -> lỗi dây chuyền 
    Ví dụ : phát triển 1 hệ thống cảnh báo trên xe hơi, sử dụng 1 class như bên dưới để quản lý thì xảy ra vấn đè
     + cần thêm các phương thức cảnh báo cụ thể như sound,blink led 
        -> can thiệp trực tiếp mã nguồn -> không tối uu -> hệ thống càng lớn -> sửa code trực tiếp -> lỗi dây chuyền

*/
class SpeedAlert
{
    public:
        void sendAlert(double speed)
        {
            if (speed > 100)
            {
                cout << "Cảnh báo: Vượt quá tốc độ!" << endl;
            }
        }
};
/* 
    - Hướng giải quyết như bên dưới giúp hệ thống mở rộng tính năng mới mà ko cần can thiệp mã nuồn ban đầu
    + Yêu cầu triển khai ? hệ thống cần tuân theo SRP -> tách biệt nhiệm vụ các hành vi cụ thể thành class riêng biệt
    + Thiết kế 1 lớp tổng quát (base class) cho phép nhiều lớp con kế thừa và ghi đè cách triển khai 

*/
class Device_Alert{
    public:
        virtual void sendAlert(double speed) = 0;   //hành vi tổng quát -> chưa biết hướng triển khai cụ thể
};
class Sound_Alert : public Device_Alert{
    public:
        void sendAlert(double speed) override{  //triển khai cụ thể cách thức xử lý
            if (speed > 100){
                cout << "Cảnh báo: Vượt quá tốc độ! (Âm thanh)" << endl;
            }
        }
};
class LED_Alert : public Device_Alert{
    public:
        void sendAlert(double speed) override{
            if (speed > 100){
                cout << "Cảnh báo: Vượt quá tốc độ! (Đèn LED)" << endl;
            }
        }
};

void handleSpeedAlert(Device_Alert *alert, double speed){ alert->sendAlert(speed); }
   
int main(){
    Sound_Alert sound;
    LED_Alert led;
    handleSpeedAlert(&sound, 80);
    handleSpeedAlert(&led, 120);
    return 0;
}

