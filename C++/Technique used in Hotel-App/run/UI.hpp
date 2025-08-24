#ifndef UI_HPP
#define UI_HPP

#include <string>

class UI {
public:
    // Phương thức hiển thị và lấy dữ liệu đầu vào
    /* 
        Khai báo là static cho phép truy cập trực tiếp thông qua
        tên class mả không cần tạo đối tượng. Bởi vì kết quả của chúng 
        không phụ thuộc trạng thái của bất kỳ object nào 
     */
    static int getUserChoice(const std::string& prompt);        // Lấy lựa chọn từ người dùng
    static void showMessage(const std::string& message);        // Hiển thị thông báo
    static std::string getInputString(const std::string& prompt); // Lấy chuỗi nhập từ người dùng
};

#endif // UI_HPP
