#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
/* 
    //dạng 1 
    [capture](params list) -> return type
    {
        //function body
    }

    //dạng 2 
    [capture](params list)
    {
        //function body
    }

    [capture] : biến toàn cục bên ngoài để sử dụng khi định nghĩa lambda
    [=]       : cho phép sử dụng biến truyền vào ở dạng tham trị
    [&]       : ho phép sử dụng biến truyền vào ở dạng tham trị

*/
int main()
{
    
    //sử dụng trực tiếp định nghĩa lambda
    cout << []
    cout << "sum: " << [](int a,float b){return a+b;}(3,5) << endl;
    //sử dụng thông qua khai báo lambda
    auto sum = [](int a,int b){return a + b;};
    cout << "sum: " << sum(3,5) << endl;

    //truyền biến toàn cục sử dụng trong lambda
    int a = 21, b = 31;
    
    //ví dụ 1
    auto sum1 = [a,&b](){ 
        b += a;
        return b;
    };
    cout << "sum1 = " << sum1() << endl;
    
    //ví dụ 2
    auto lambda = [=]() 
    {       
            int c = a + b;
            cout << "c = " << c << endl; };
    lambda(); 
    return 0;
}