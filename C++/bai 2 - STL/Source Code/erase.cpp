#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Person {
    string name;
    int age;
};

int main() {
    vector<map<int, Person>> people = {
        {{1, {"Alice", 25}}, {2, {"Bob", 30}}},
        {{3, {"Charlie", 35}}, {4, {"David", 40}}},
        {{5, {"Eve", 45}}, {6, {"Frank", 50}}}
    };

    // Xóa map chứa Person có tuổi = 35
    people.erase(remove_if(people.begin(), people.end(), [](const map<int, Person>& m) {
        return any_of(m.begin(), m.end(), [](const pair<int, Person>& p) {
            return p.second.age == 35;
        });
    }), people.end());

    // In lại danh sách sau khi xóa
    cout << "Remaining people after deletion:\n";
    for (const auto& m : people) {

       /*  for (const auto& [key, person] : m) {
            cout << key << ": " << person.name << " (" << person.age << ")\n";
        } */
       for(const auto& value : m){
            cout << value.first << ": " << value.second << endl;
       }
        cout << endl;
    }

    return 0;
}
