/*
    variadic template: khi 1 hàm nhận số lượng đối số ko xác định và chưa rõ kiểu dữ liệu
*/
#include <iostream>
using namespace std;

template<typename type>
//hàm đệ quy 1 giá trị
type sum(type value){
    return value;
}
//hàm đệ quy 2 giá trị trở lên
template<typename type,typename...Args>
auto sum(type first,Args... args){
    return first + sum(args...);
}
int main(){
    cout << "sum of int: " << sum(1,2,3,4,5) << endl;
    cout << "sum of float: " << sum(12.3,2.12,3.3,4.5,5.9) << endl;
    cout << "sum of int and float: " << sum(1,2,3,4.7,5.5) << endl;
    return 0;
}

