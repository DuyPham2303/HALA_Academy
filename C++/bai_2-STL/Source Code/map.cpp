/*
    + key là const -> ko cho phép thay đổi
    + không cho phép trùng key
        * khai báo ban đầu nhiều cặp -> nếu trùng key -> chỉ giữ lại cặp đầu tiên
        + khai báo từng cặp -> nếu trùng key -> giữ lại cặp cuối
        + tự động sắp theo giá trị key (tăng dần)
 */
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <string.h>
using namespace std;
template <typename T1, typename T2>
class Pair
{
public:
    T1 key;
    T2 value;
};
int main()
{
    Pair<string, int> pair[3] = {
        {.key = "Duy solo", .value = 21},
        {.key = "Hoang Trinh", .value = 22},
        {.key = "Tan Tung", .value = 21},
    };

    /* KEY AND VALUE ARE STRING */
    map<string, string> mp = {
        {"duy pham", "23 tuoi"},
        {"duy pham", "25 tuoi"},
        {"duy pham", "27 tuoi"},
        {"Minh thong", "23 tuoi"},
        {"Minh toan", "22 tuoi"},
    }; // locate at stack

    for(const auto i : mp)
        cout << i.first << "\t" << i.second << endl;
    // locate at heap
    mp["Ten:"] = "Tan Tung";
    mp["Ten:"] = "Duy Pham"; // this will be printed out except the above -> the last one with similar key
    mp["MSSV"] = "17146011";

    // cách 1
    for (auto item : mp)
        cout << "key: " << item.first << ", value:" << item.second << endl;
    // cách 2
    for (const auto &[key, value] : mp)
        cout << "key : " << key << ", value: " << value << endl;
    /* KEY IS INTEGER AND VALUE IS STRING */
    map<int, string> mp1;
    string name_list[] = {"Cao Duy", "Tan Tung", "Le Hoang", "Anh Tuan", "Quang Nhat"};
    // add value to map./map
    for (int i = 0; i < sizeof(name_list) / sizeof(name_list[0]); i++)
        mp1[i] = string(name_list[i]);

    mp1.erase(1); // xóa cặp key-value (phần tử trong map ở vị trí bất kỳ)
    mp1.insert(
        {3, "Tan Tung"}
    );
    // print map
    map<int, string>::iterator it;
    for (it = mp1.begin(); it != mp1.end(); it++)
        cout << "key: " << (*it).first << "\tvalue: " << (*it).second << endl;
}