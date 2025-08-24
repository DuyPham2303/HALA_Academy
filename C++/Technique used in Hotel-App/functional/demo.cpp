#include <iostream>
#include <functional>
#include <vector>
using namespace std;

// Định nghĩa các hành động
void option1() {
   cout << "Bạn đã chọn Option 1.\n";
}

void option2() {
   cout << "Bạn đã chọn Option 2.\n";
}

void option3() {
   cout << "Bạn đã chọn Option 3.\n";
}

void exitMenu() {
   cout << "Thoát chương trình.\n";
}

// Lớp MenuItem mô tả từng lựa chọn trong menu
class MenuItem {
private:
    int choice_; // Số hiệu lựa chọn
   string description_; // Mô tả của lựa chọn
   function<void()> action_; // Hành động khi lựa chọn được chọn
public:
    // Constructor
    MenuItem(int choice, const string& description,function<void()> action)
        : choice_(choice), description_(description), action_(action) {}

    // Getter cho choice_
    int getChoice() const { return choice_; }

    // Getter cho description_
   string getDescription() const { return description_; }

    // Thực thi hành động của lựa chọn
    void executeAction() const { action_(); }
};

int main() {
    // Tạo một danh sách các MenuItem
   vector<MenuItem> menu = {
        MenuItem(1, "Option 1", option1),
        MenuItem(2, "Option 2", option2),
        MenuItem(3, "Option 3", option3),
        MenuItem(4, "Exit", exitMenu)
    };

    int userChoice = 0;

    // Lặp lại cho đến khi người dùng chọn thoát
    while (true) {
        // In ra menu
       cout << "\nMenu:\n";
        for (const auto& item : menu) {
           cout << item.getChoice() << ". " << item.getDescription() << '\n';
        }

        // Yêu cầu người dùng nhập lựa chọn
       cout << "Chọn một lựa chọn (1-4): ";
       cin >> userChoice;

        // Tìm kiếm và thực thi hành động tương ứng
        bool found = false;
        for (const auto& item : menu) {   //item tham chiếu đến từng mục trong menu
        /*   
        kiểm tra lựa chọn có trong đề mục hiện tại không 
        nếu có -> thực hiện hành động cụ thể
        nếu không -> tiếp tục kiểm tra đề mục tiếp theo 
        */
            if (item.getChoice() == userChoice) { 
                item.executeAction();
                found = true;
                break;
            }
        }
        //nếu lựa chọn không có trong menu thực hiện in ra thông báo sau
        if (!found) {
           cout << "Lựa chọn không hợp lệ. Vui lòng thử lại.\n";
        }

        // Nếu chọn thoát, thoát khỏi vòng lặp
        if (userChoice == 4) {
            break;
        }
    }

    return 0;
}
