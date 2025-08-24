#include <iostream>
#include <functional>
#include <vector>
#include <initializer_list>
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
    MenuItem(int choice, const string& description, function<void()> action)
        : choice_(choice), description_(description), action_(action) {}

    // Getter cho choice_
    int getChoice() const { return choice_; }

    // Getter cho description_
    string getDescription() const { return description_; }

    // Thực thi hành động của lựa chọn
    void executeAction() const { action_(); }
};

// Lớp Menu quản lý danh sách MenuItem
class Menu {
private:
    vector<MenuItem> menuItems; 
public:
    // Constructor sử dụng initializer_list để khởi tạo danh sách MenuItem
    // lưu từng đề mục vào vector kiểu MenuItem
    Menu(initializer_list<MenuItem> items) : menuItems(items) {} 

    // Hàm hiển thị menu
    void show() const {
        cout << "\nMenu:\n";
        for (const auto& item : menuItems) { //tham chiếu từng đề mục trong menu
            cout << item.getChoice() << ". " << item.getDescription() << '\n';
        }
    }

    // Hàm xử lý lựa chọn của người dùng
    void handleChoice(int choice) const {
        bool found = false;
        for (const auto& item : menuItems) {
            if (item.getChoice() == choice) {
                item.executeAction();
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Lựa chọn không hợp lệ. Vui lòng thử lại.\n";
        }
    }
};

int main() {
    // Tạo một đối tượng Menu với initializer_list chứa các MenuItem
    // khởi tạo trực tiếp các tập giá trị
    //-> không cần phải tạo vector -> tốn vùng nhớ 
    Menu menu = {
        MenuItem(1, "Option 1", option1),
        MenuItem(2, "Option 2", option2),
        MenuItem(3, "Option 3", option3),
        MenuItem(4, "Exit", exitMenu)
    };

    int userChoice = 0;

    // Lặp lại cho đến khi người dùng chọn thoát
    while (true) {
        // Hiển thị menu
        menu.show();
        option:
        // Yêu cầu người dùng nhập lựa chọn
        cout << "Chọn một lựa chọn (1-4): ";
        cin >> userChoice;
        // Xử lý lựa chọn của người dùng
        menu.handleChoice(userChoice);

        // Nếu chọn thoát, thoát khỏi vòng lặp
        if (userChoice == 4) {
            break;
        }
        else goto option;     
    }

    return 0;
}
