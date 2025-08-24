#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
bool isEven(int n){
    return n % 2 == 0;
}
int main(){

    vector<int> v = {1,3,5,7,2,9,12,54,16,60};
    int find = 54;
    for(auto val : v)
        cout << val << " ";
    cout << endl;
    auto find_erase = [find](int x){/* if(find == x)  */return x == find;};
    //auto find_erase = [](int x){return x == 54;};
    auto it = remove_if(v.begin(),v.end(),find_erase); //Trả về địa chỉ trỏ đến giá trị cần xóa
    v.erase(it,v.end());
    cout << "after erase" << endl;
    for(auto i : v)
        cout << i << " ";
    cout << endl;
    return 0;
}