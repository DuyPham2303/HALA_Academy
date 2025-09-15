/* 
    Dependency Inversion Principle : Quy định 1 hành vi của hệ thống thay vì chỉ gắn liền với 1 đối tượng nhất định -> ta sẽ cho phép 
    hành vi đó có thể gắn liền với nhiều đối tượng khác nhau -> giúp tăng tính mổ rộng, và linh hoạt
    + Ví dụ: ta có 1 method để bật/tắt 1 đối tượng là bóng đèn 
    -> thay vì gắn chặt hành vi này cho 1 thực thể -> cho phép nó gắn với nhiều thực thể 
*/
class LightBulb
{
    public:
        void turnOn() { /* Bật đèn */ }
};

class Switch
{
    private:
        LightBulb bulb;
       
    public:
        void operate() { bulb.turnOn(); }
};    


/* 
    - Hướng giải quyết là tạo 1 class trung gian (abstract class) chứa hành vi bật/tắt mà bất cứ device nào cùng sử dụng được
    => triển khai 1 giao diện tương tác trung gian tách biệt giữa 
        + hành vi bật/tắt 
        + device cụ thể 
    Chỉ gọi ra Hàm xử lý trừu tượng để xử lý mà không cần biết chi tiết hệ thống gọi ra class cụ thể nào
*/
class Device{
    public:
        virtual void turnOn() = 0;
};
class LightBulb : public Device{
    public:
        void turnOn() override { /* Bật đèn */ }
};
class Fan : public Device{
    public:
        void turnOn() override { /* Bật quạt */ }
};
class Switch{
    private:
        Device *device;

    public:
        Switch(Device *d) : device(d){}
        void operate() { device->turnOn(); }
};
   

