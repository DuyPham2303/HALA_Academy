#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

void erase(){
    // Tạo một vector chứa nhiều std::map<int, string>
    vector<map<int, string>> data = {
        {{1, "Apple"}, {2, "Banana"}},
        {{3, "Cherry"}, {4, "Date"}},
        {{5, "Elderberry"}, {6, "Fig"}}
    };
     // Xóa std::map chứa key = 3
    data.erase(remove_if(data.begin(), data.end(), [](const map<int, string>& m) {
        return m.find(3) != m.end();  // Điều kiện xóa: Nếu có key 3
    }), data.end());

    // Kiểm tra danh sách sau khi xóa
    cout << "After deletion, remaining maps contain keys:\n";
    for (const auto& m : data) {
        for (const auto& [key, value] : m) {
            cout << key << " ";
        }
        cout << endl;
    }

}
void find(){
    // Tạo một vector chứa nhiều std::map<int, string>
    vector<map<int, string>> data = {
        {{1, "Apple"}, {2, "Banana"}},
        {{3, "Cherry"}, {4, "Date"}},
        {{5, "Elderberry"}, {6, "Fig"}}
    };
 // Tìm kiếm std::map chứa key = 3
    auto it = find_if(data.begin(), data.end(), [](const map<int, string>& m) {
        return m.find(6) != m.end();  // Kiểm tra xem key 3 có trong map hay không
    });

    if (it != data.end()) {
        cout << "Found a map containing key 3!: " << endl;
        for(const auto& value : (*it))
            cout << value.first << ": " << value.second << endl;
    }   
    else {
        cout << "Key 3 not found in any map." << endl;
    }
}
int main(){
    find();
    return 0;
}
