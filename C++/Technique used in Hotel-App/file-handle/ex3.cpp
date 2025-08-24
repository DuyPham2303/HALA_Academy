/* 
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    fstream file("example.txt", ios::in | ios::out | ios::app);  // Mở file để đọc, ghi, và thêm nội dung
    if (!file) {
        cout << "Unable to open file!" << endl;
        return 1;
    }

    file << "Adding a new line!" << endl;  // Ghi thêm vào cuối file

    file.seekg(0);  // Đưa con trỏ về đầu file
    string line;
    while (getline(file, line)) {  // Đọc từng dòng
        cout << line << endl;
    }

    file.close();
    return 0;
}
 */