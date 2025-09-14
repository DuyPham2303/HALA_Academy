#include "lcd1.hpp"
#include "lcd2.hpp"
/* 
    Giả sử phát triển driver cho 1 lcd ta có thể đóng gói các đối tượng liên quan đến việc định nghĩa 1 LCD thành 1 namespace chứa
    + class bao hàm method,properties -> liên quan đến việc cấu hình, tương tác với phần cưng
    + hàm trừu tượng chức năng : hiển thị chuỗi, ký tự, dịch chuỗi 
    => Nếu vậy thì sẽ không tách biệt rõ nhiệm vụ từng layer. Giải pháp tách thành 2 namespace cùng tên  -> gọi ở nhiều file khác nhau
*/
int main(){
    LCD::lcd lcd1(12,32,"my lcd1");
    LCD::lcd lcd2(11,22,"my lcd2");
    LCD::lcd lcd3(18,42,"my lcd3");
    LCD::lcd lcd4(12,12,"my lcd4");

    LCD::displayInfo(&lcd1);
    LCD::displayInfo(&lcd3);
    LCD::displayInfo(&lcd2);
    LCD::displayInfo(&lcd4);

    LCD::totalLCD();
    return 0;
}