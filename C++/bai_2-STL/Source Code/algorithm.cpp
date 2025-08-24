#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void test_foreach()
{
    vector<int> vec = {1, 2, 3, 4, 5};
    int sum = 0;
    // Sử dụng for_each để in ra từng phần tử
    auto print = [](int x)
    { cout << x << " "; };
    auto change = [](int &x)
    { x *= 2; };
    auto tong = [&sum](int x)
    { sum += x; };
    for_each(vec.begin(), vec.end(), tong);
    for (auto i : vec)
        cout << i << " " << endl;
    cout << "sum :" << sum;
}
void test_find(int value)
{
    vector<int> vec = {10, 20, 30, 40, 50};

    auto it = find(vec.begin(), vec.end(), value);

    if (it != vec.end())
        cout << "Found: " << *it << endl;

    else
        cout << "Not found" << endl;
}
void test__merge()
{
    vector<int> vec1 = {10, 20, 30};
    vector<int> vec2 = {15, 25, 35};
    vector<int> result(vec1.size() + vec2.size());

    merge(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), result.begin());

    for (int val : result)
    {
        cout << val << " ";
    }
}
void test_sort()
{
    vector<int> vec = {50, 20, 40, 10, 30};
    
    sort(vec.begin(), vec.end(), greater<int>());
    for (int val : vec)
    {
        cout << val << " ";
    }
}
int main()
{
    // test_foreach();
    // test_find(50);
    //test_sort();
    test__merge();
    return 0;
}