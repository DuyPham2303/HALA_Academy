/* #include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    ifstream inFile("data.txt");  // Giả sử file chứa: "Alice,20,85\nBob,22,90"
    if (!inFile) {
        cout << "Unable to open file!" << endl;
        return 1;
    }

    string line;
    while (getline(inFile, line)) {  // Đọc từng dòng
        stringstream ss(line);
        string token;

        while (getline(ss, token, ',')) {  // Tách chuỗi theo dấu phẩy
            cout << token << endl;
        }
    }

    inFile.close();
    return 0;
}
 */