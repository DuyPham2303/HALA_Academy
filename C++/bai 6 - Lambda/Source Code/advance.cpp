#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;
// Hàm nhận callback
void handleInterrupt(const function<void()> &callback)
{
    cout << "Interrupt occurred!" << endl;
    callback();
}

int main()
{
    /* EXAMPLE 1 */
    int ledState = 1;
    //lambda function
    handleInterrupt([&ledState](){
    ledState = !ledState; // Đổi trạng thái LED
       cout << "LED State: " << ledState <<endl; 
    });

     /* EXAMPLE 2 */
    vector<int> sensorData = {10, 20, 15, 30};
    // Lọc dữ liệu cảm biến lớn hơn 15
    auto count = count_if(sensorData.begin(), sensorData.end(), [](int val)
                          { return val > 5; });

    cout << "Number of values > 15: " << count << endl; // Output: 2

    return 0;
}
