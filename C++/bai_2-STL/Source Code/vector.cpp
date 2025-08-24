#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<int>::iterator it;
    vector<int> arr = {2, 5, 1, 5, 6};
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

    //cach 1: use traditional for loop 
    for(int i = 0 ; i < vec.size() ; i++) // size() -> return total stored elements
        cout << vec.at(i);
    cout << endl;
    //cach 2: use the advance for loop 
    for(auto i : vec) // auto i -> return value of element with exact data type  
        cout << i;
    cout << endl;
    //cach 3: use pointer 
    vector<char> :: iterator it1; 
    for(it1 = vec.begin() ; it1 != vec.end() ; it1++) //it -> loop throught each element 
        cout << *it1;
    cout << endl;

    return 0;
}