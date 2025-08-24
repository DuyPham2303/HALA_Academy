/*
map also has it own iterator like list and vector
key: any data-type
+ must be distinguished
+ if simlar -> only accept the last one
+ auto self-arrange when print out
value: any data-type
 */
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <string.h>
using namespace std;
int main()
{
/* KEY AND VALUE ARE STRING */
    map<string, string> mp; // locate at stack
    

    // locate at heap
    mp["Ten:"] = "Tan Tung";
    mp["Ten:"] = "Duy Pham"; // this will be printed out except the above -> the last one with similar key
    mp["MSSV"] = "17146011";
    mp["3"] = "123";
    mp["5"] = "456";
    mp["1"] = "789";
    mp["2"] = "159";
    mp["4"] = "168";
    for (auto item : mp)
        cout << "key: " << item.first << ", value:" << item.second << endl;
/* KEY IS INTEGER AND VALUE IS STRING */
    map<int, string> mp1;
    char* name_list[] = {"Cao Duy","Tan Tung","Le Hoang","Anh Tuan","Quang Nhat"};
    //add value to map./map
    for(int i = 0 ; i < sizeof(name_list) / sizeof(name_list[0]) ; i++)
       mp1[i] = string(name_list[i]);

    mp1.erase(1);
    //print map
    map<int, string>::iterator it;
    for (it = mp1.begin(); it != mp1.end(); it++)
        cout << "key: " << (*it).first << "\tvalue: " << (*it).second << endl;
}