#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

void test(){
    unordered_map<std::string, int> myMap;
    // Thêm hoặc cập nhật giá trị
    myMap["a"] = 10;  // Thêm key "a" với value 10
    myMap["b"] = 20;  // Thêm key "b" với value 20
    myMap["a"] = 15;  // Cập nhật key "a" với value 15

    // Kiểm tra xem key có tồn tại không
    if (myMap.find("a") != myMap.end()) {
        std::cout << "Key 'a' exists with value: " << myMap["a"] << std::endl;
    }

    // Xóa một phần tử
    myMap.erase("b"); // Xóa key "b"

    // Duyệt qua các phần tử
    for (const auto& pair : myMap) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }
}
void test1(){
    typedef std::unordered_map<std::string, int> myMap;
    vector<myMap> list_mymap;
    vector<string> letter_list = {"a","b","c","d","e","f"};
    int index = 0;
    for(auto& letter : letter_list){
        myMap map;
        map[letter] = index++;
        list_mymap.push_back(map);
    }

    for(auto& mymap : list_mymap){
        if(mymap.find(letter_list[4]) != mymap.end()){
            cout << "value: " << mymap[letter_list[4]];
        }
    }
    
}

int main() {
    test1();
    return 0;
    // Khai báo một unordered_map ánh xạ string -> int
    std::unordered_map<std::string, int> fruitCount;

    // Thêm phần tử vào unordered_map
    fruitCount["apple"] = 5;  // Cặp key-value: "apple" -> 5
    fruitCount["banana"] = 2;

    // In ra giá trị tương ứng với key "apple"
    std::cout << "Apple count: " << fruitCount["apple"] << std::endl;

    // Truy cập một key không tồn tại sẽ tạo key với giá trị mặc định
    std::cout << "Mango count: " << fruitCount["mango"] << std::endl; // 0 (giá trị mặc định của int)



    return 0;
}
