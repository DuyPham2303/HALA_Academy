#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    /*  int d = 3;
     int e = 2;
     class
     {
     public:
         void operator()(int x)
         {
             cout << x << endl;
         }
     } sth;
     vector<int> v{1, 2, 3, 5, 6};
     for_each(v.begin(), v.end(), [=](int x){
         if(x % d == 0) cout << x << " is divisible by "<< d << endl;
         else cout << x << " is not divisible by " << d << endl;
         //d += 21;
         cout << "inside lambda:" << d << endl;
     });
     e+=1;
     cout << "outside lambda d = " << d << endl; */
    /* sử dụng ()*/ 
    //cach 1
    
    cout << "sum: " << [](int a,float b){return a+b;}(3,5) << endl;
    //cach 2 
    auto sum = [](int a,int b){return a + b;};
    cout << "sum: " << sum(3,5) << endl;

    /* sử dụng [] */
    int a = 21, b = 31;
    //example 1
    auto sum1 = [a,&b](){ 
        b += a;
        return b;
    };
    cout << "sum1 = " << sum1() << endl;
    //example 2
    auto lambda = [=]() 
    {       
            int c = a + b;
            cout << "c = " << c << endl; };
    lambda(); 
    return 0;
}