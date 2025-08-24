#include <iostream>
using namespace std;
//function template
template <typename Type1 , typename Type2>
auto sum(Type1 a, Type2 b){
    return a + b;
}
int main(){
    cout << "Sum: " << sum(23.45,21.1) << endl;  //float + float
    cout << "Sum: " << sum(25,211.13) << endl;  //int + float
    cout << "Sum: " << sum(25,12) << endl; //int + int
    return 0;
}