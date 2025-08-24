#include <iostream>
#include <list>
using namespace std;
int main()
{
    cout << "add node and print" << endl;
    list<int> lst;
    for (int i = 0; i < 5; i++)
        lst.push_back(i + 1);
    list<int>::iterator it;

    cout << "print values of list" << endl;
    auto i = 0;
    for (auto item : lst)
        cout << "node " << i++ << ":" << item << endl;

    cout << "last node" << endl;
    it = lst.end();
    cout << "address: " << &(*it) << " value: " << *it << endl;

    i = 0;
    cout << "address and value of node" << endl;
    for (it = lst.begin(); it != lst.end(); it++)
        cout << "add: " << &(*it) << ", node" << i++ << ":" << *it << endl;

    // traverse through each node

    cout << "add node at certein position" << endl;
    for (it = lst.begin(); it != lst.end(); it++)
    {
        if (i == 2)
        {
            lst.insert(it, 12); // insert at node 2
        }
        i++; // count each node
    }

    i = 0;
    cout << "print list after adding new node" << endl;
    for (it = lst.begin(); it != lst.end(); it++)
        cout << "add: " << &(*it) << ", node:" << i++ << " " << *it << endl;

    i = 0;

    // return 0;
    //  delete node
    /* cach 1 */
    for (it = lst.begin(); it != lst.end(); it++)
    {
        if (i == 3)
        {
            it = lst.erase(it); // update new it after delete
        }
        i++;
    }
    /* cach 2 */
    /*
    it = lst.begin();

    advance(it,3); // Di chuyển iterator tới phần tử thứ 3 (giá trị 30)

    lst.erase(it); */

    cout << "print list after deleting node at index " << i << endl;
    i = 0;
    for (auto value : lst)
        cout << "value " << i++ << ": " << value << endl;

    // delete onode based on condition
    cout << "print list after delete node > 2" << endl;
    lst.remove_if([](int value)
                  { return value > 2; });
    i = 0;
    for (auto value : lst)
        cout << "value " << i++ << ": " << value << endl;

    return 0;
}