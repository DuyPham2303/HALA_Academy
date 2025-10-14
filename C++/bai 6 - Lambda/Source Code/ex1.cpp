#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
     int d = 3;
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
     cout << "outside lambda d = " << d << endl; 
}