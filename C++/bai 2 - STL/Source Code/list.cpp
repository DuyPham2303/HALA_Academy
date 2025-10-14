#include <iostream>
#include <list>
using namespace std;
/* 
    begin() -> địa chỉ node đầu
    end()   -> địa chỉ sau node cuối
    rbegin() -> địa chỉ node cuối
    rend()   -> địa chỉ trước node đầu

    list<int>::iterator it;             //con trỏ duyệt từ node đầu -> cuối (it++)
    list<int>::reverse_iterator rit;    //con trỏ duyệt từ node cưới -> đầu (rit++)

    Ứng dụng : 
    - lưu trữ vùng nhớ động, thay đổi kích thước linh hoạt
    - dễ dàng thao tác thêm/xóa dữ liệu mới
    Hạn chế :
    - không thích hợp truy cập ngẫu nhiên -> tốn gian -> yêu cầu lặp qua từng node

*/
int main()
{
    cout << "add node and print" << endl;
    list<int> lst;
    for (int i = 0; i < 5; i++)
        lst.push_back(i + 1);  

    list<int>::iterator it;
    cout << "print values of list" << endl;
    for (auto item : lst)
        cout << "node " << item << endl;  

    cout << "last node" << endl;
    it = lst.end();
    cout << "address: " << &(*it) << " value: " << *it << endl;

    cout << "address and value of node" << endl;
    for (it = lst.begin(); it != lst.end(); it++)
        cout << "add: " << &(*it) << ", node " << *it << endl;

    // traverse through each node

    cout << "add node at certein position" << endl;
    for (it = lst.begin(); it != lst.end(); it++)
    {
        static int i = 0;
        if (i == 2)
        {
            lst.insert(it, 12); // insert at node 2
        }
        i++; // count each node
    }

    cout << "print list after adding new node" << endl;
    for (it = lst.begin(); it != lst.end(); it++)
        cout << "add: " << &(*it) << ", node " << *it << endl;

    
    cout << "print reverse list" << endl;
    list<int>::reverse_iterator rit;
    for(rit = lst.rbegin() ; rit != lst.rend() ; rit++)
        cout << "add: " << &(*rit) << ", node " << *rit << endl;

    return 0;

                                            /*  delete node */
    /* cach 1 */
    for (it = lst.begin(); it != lst.end(); it++)
    {
        static int i = 0;
        if (i == 3)
        {
            it = lst.erase(it); // update new it after delete
        }
        i++;
    }

    /* cach 2 */
    
    // it = lst.begin();

    // advance(it,3); // Di chuyển iterator tới phần tử thứ 3 (giá trị 30)

    // lst.erase(it); 
   
    for (auto value : lst)
        cout << "value " << value << endl;

    // delete onode based on condition
    cout << "print list after delete node > 2" << endl;
    lst.remove_if([](int value)
                  { return value > 2; });
    for (auto value : lst)
        cout << "value " << value << endl;

    return 0;
}