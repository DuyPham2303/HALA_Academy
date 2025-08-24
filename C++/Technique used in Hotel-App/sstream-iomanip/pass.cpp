#include <iostream>
#include <cstdlib> // Cần cho hàm rand và srand
#include <ctime>   // Cần cho hàm time nếu muốn tạo seed ngẫu nhiên
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
void check_similar(vector<std::string> &pass)
{
    vector<string>::iterator it1, it2;
    bool similar = false;

    for (it1 = pass.begin(); it1 != pass.end(); it1++)
    {
        for (it2 = pass.begin(); it2 != it1; it2++)
        {
            if (*it1 == *it2)
                similar == true;
            cout << "pass : " << *it2 << " is repeat" << endl;
            break;
        }
    }
    if (similar == false)
        cout << "no pass is conccurent";
}
/* int main()
{
    vector<string> pass_list;
    srand(time(0));
    string pass = "";
    int num_pass = 10;
    while (num_pass)
    {
        for (int i = 0; i < 6; i++)
        {
            int ran = rand() % 10;
            pass += to_string(ran);
        }
        pass_list.push_back(pass);
        cout << "pass: " << pass << endl;
        pass = "";
        num_pass--;
    }
    check_similar(pass_list);
    return 0;
} */