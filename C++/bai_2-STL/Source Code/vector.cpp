#include <iostream>
#include <vector>
using namespace std;
/* 
    vector -> template class : khởi tạo vùng nhớ động (tự động quy định datatype thống qua <>)
        + 2 cách khởi tạo : có/ko toán tử = 
        + vector<int> arr{n}  -> cấp phát n phần tử
        + vector<int> arr{n,i}-> cấp phát n phền tử có giá trị i
        + vector<int> arr{a,b,c....,n} -> cấp phát số lượng phần tử có giá trị tương ứng 
        + hàm thao tác trên vector
            * begin() -> trả về địa chỉ của phần tử đầu
            * end()   -> trả về địa chỉ sau phần tử cuối 
            * pushback() -> thêm phần tử vào cuối 
            * insert()   -> thêm phần tử ở vị trí bất kỳ
            * popback()  -> xóa phần tử ở cuối
            * erase()    -> xóa vị trí bất kỳ
    Ứng dụng : 
        + cần truy cập nhanh và ngẫu nhiên
        + Lưu trữ vùng nhớ có kích thước cố định
    Hạn chế :
        + Không phù hợp lưu trữ dữ liệu động -> tốn tgian điều chỉnh -> do các địa chỉ liền kề
*/
int main()
{
    vector<int>::iterator it;
    vector<int> arr = {2, 5, 1, 5, 6};  // hoặc arr - {1,2,3,4,5}
    cout << "before" << endl;
    for (int i = 0; i < arr.size(); i++)
        cout << "element: " << arr[i] << endl;

    cout << "begin: " <<  *(arr.begin())  << endl;
    return 0;
    arr.at(2) = 10; // change value 

    arr.resize(8);  // realloc memory 

    arr.insert(arr.begin(), 12); //push new element to the front of vector

    arr.push_back(18); // push new element to the end of vector   

    arr.erase(arr.begin()); //delete begin element of vector

    cout << "after" << endl;
    for (int i = 0; i < arr.size(); i++)
        cout << "element: " << arr[i] << endl;

    vector<char> vec = {'d','u','y','s','o','l','o'};

    //cach 1: cách thông thường để duyệt qua từng phần tử
    for(int i = 0 ; i < vec.size() ; i++) // size() -> return total stored elements
        cout << vec.at(i);
    cout << endl;
    //cach 2: sử dụng based-range for loop
    for(auto i : vec) // auto i -> return value of element with exact data type  
        cout << i;
    cout << endl;
    //cach 3: sử dụng iterator
    vector<char> :: iterator it1; 
    for(it1 = vec.begin() ; it1 != vec.end() ; it1++) //it -> loop throught each element 
        cout << *it1;
    cout << endl;

    return 0;
}