#include <iostream>
using namespace std;
/* - Dạng template chuyên biệt hóa : cho phép tùy chỉnh hành vi/định nghĩa 1 template 
    + có nghĩa là 1 template có thể áp dụng cho nhiều hàm cùng tên (khác kiểu param,return)
    + cú pháp : template <>
   - KHI NÀO ÁP DỤNG ?
    + khi 1 hàm thực thi 1 chức năng tổng quát nhưng có logic xử lý khác nhau tùy thuộc vào datatype của param truyền vào
    + so sánh số/ký tự khác so với 1 chuỗi ký tự/chuỗi -> cùng xử lý thông qua hàm có tên IsEqual() chẳng hạn
*/
// Template tổng quát -> chỉ áp dụng cho hàm có tên định nghĩa tương ứng với duy nhất 1 phiên bản định nghĩa/triển khai hàm 
template <typename T>
void display(T value){
    cout << "Generic: " << value << endl;
}

// Chuyên biệt hóa toàn phần cho kiểu `int` -> cung cấp cách xử lý/hành vi tương ứng cho kiểu int
template <>
void display<int>(int value){
    cout << "Specialized for int: " << value << endl;
}

// Chuyên biệt hóa toàn phần cho kiểu `char*` -> cung cấp cách xử lý/hành vi tương ứng cho kiểu char
template <>
void display<char*>(char* value){
    cout << "Specialized for string: " << value << endl;
}

//chuyên biệt hóa bán phần (ko áp dụng cho hàm) -> triển khai như này có đúng ko ?
template<typename T>
T display<int>(int value){
    return value;
}

int main(){
    display(42);        // Sử dụng chuyên biệt hóa cho int
    display(3.14);      // Sử dụng template tổng quát
    display("Hello");   // Sử dụng chuyên biệt hóa cho char*
    //int val = display(23); //ko thể áp dụng partial specialization cho hàm 
    return 0;
}

