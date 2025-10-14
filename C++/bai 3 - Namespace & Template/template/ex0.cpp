#include <iostream>
using namespace std;
/* 
    - Generic Proggram : phương pháp lập trình tổng quát giúp 
        + tối ưu tgian viết code
        + đơn giản hóa, rút gọn code, tránh việc viết code trùng lặp
        + tăng khả năng tái sử dụng code
    => từ khóa template giúp định nghĩa ra các đối tượng function,class tổng quát
    + cú pháp : template <typename T>
    + giúp viết 1 phiên bản hàm duy nhất xử lý nhiều datatype mà không cần overload (viết nhièu hàm có t6en giống nhau)
    + mỗi template chỉ sử dụng cho 1 loại định nghĩa hàm duy nhất
*/

template <typename Type1 , typename Type2>  //tự suy luận ra kiểu phù hợp dựa trên tham số truyền vào
auto sum(Type1 a, Type2 b){ // từ khóa auto tự ép kiểu trả về phù hợp
    return a + b;
}
template <typename T = int>
T sum1(T a){
    return a * a;
}

int main(){
    //cout << "Sum: " << sum(23.45,21.1) << endl;  //float + float
    //cout << "Sum: " << sum(25,211.13) << endl;  //int + float
    //cout << "Sum: " << sum(25,12) << endl; //int + int

    cout << "sum1 : " << sum1(21.21) << endl; //tự ép lại kiểu mặc định khi gán ở trên template
    cout << "sum1: " << sum1<float>(21.21) << endl; //ép lại kiểu mong muốn

    return 0;
}