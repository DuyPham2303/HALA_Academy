#include <iostream>
#include <memory>

using namespace std;
/*
    share pointer is only released as long as no object manage it
 */
void demo_shareptr()
{
    int *ptr = new int(5);
    cout << "dia chi:" << ptr << endl
         << "value:" << *ptr << endl;
    // local function
    {
        int *ptr1 = ptr;
        cout << "dia chi:" << ptr << endl
             << "value:" << *ptr << endl;
        {
            int *ptr2 = ptr1;
            cout << "dia chi:" << ptr << endl
                 << "value:" << *ptr << endl;
        }
    }
}
int main()
{
    shared_ptr<int> sptr1 = make_shared<int>(20);
    shared_ptr<int> sptr2 = sptr1;
    shared_ptr<int> sptr3 = sptr2;

    {
        shared_ptr<int> sptr4 = sptr1;
        cout << "count:" << sptr1.use_count() << endl;
    }
    cout << "count:" << sptr1.use_count() << endl;
    int *raw = sptr1.get();
    cout << "raw: " << *raw << endl;
    shared_ptr<int> a = make_shared<int>(40);
    shared_ptr<int> b = make_shared<int>(50);

    //hoán đổi giá trị object
    a.swap(b); 
    cout << "a: " << *a << endl
         << "b: " << *b << endl;
    //chuyển quyền sở hữu
    a = move(b);
    cout << "a: " << *a << endl
         << "b: " << *b << endl;
    /*
    sptr1.reset(new int(10)); // khác biệt giữa reset bên share vs unique
    cout << "sptr1:" << *sptr1 << endl
         << "sptr2:" << *sptr2 << endl;
     */
    // demo_shareptr();
}