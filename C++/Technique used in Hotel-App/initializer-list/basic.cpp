#include <iostream>
#include <initializer_list>
using namespace std;

class MyClass {
private:
    int* arr;
    size_t size;
public:
    MyClass(initializer_list<int> list) { //nhận trực tiếp các giá trị truyền vào 
        size = list.size();   //tự động tính số lượng phần tử
        arr = new int[size];  
        size_t i = 0;
        for (const int& val : list) {
            arr[i++] = val;
        }
    }

    void print() const {
        for (size_t i = 0; i < size; ++i) {
          cout << arr[i] << " ";
        }
      cout << endl;
    }

    ~MyClass() {
        delete[] arr;
    }
};

int main() {
    MyClass obj = {12,23,43,15,41,46,62,22}; // Khởi tạo đối tượng với danh sách các giá trị
    obj.print(); // In ra 1 2 3 4 5
    return 0;
}
