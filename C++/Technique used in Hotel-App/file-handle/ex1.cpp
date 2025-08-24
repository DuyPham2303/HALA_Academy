/* ghi file */
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <ctime>
#define PATH "..//database//file.csv"
using namespace std;
typedef map<int,int> sensor_data;

void writefile(vector<sensor_data>& data_list){
    //ofstream outFile(PATH);  // Mở file để ghi
    fstream outFile(PATH,ios::out);
    if (!outFile.is_open()) {
        cout << "Unable to open file for writing!" << endl;
        return;
    }

    outFile << "toc do\tnhiet do" << endl;
    for(auto& list : data_list){
        for(auto& value : list){
            outFile << to_string(value.first) +","+ to_string(value.second) + "," << endl;
        }
    }
    outFile.close();  // Đóng file sau khi ghi
    cout << "Data written to file successfully!" << endl;
}
void readfile(vector<sensor_data>& data_list){
    ifstream inFile(PATH);  // Mở file để đọc
    if (!inFile.is_open()) {
        cout << "Unable to open file for reading!" << endl;
        return;
    }

    string line;

    getline(inFile,line);

    while (getline(inFile, line)) {  // Đọc từng dòng
        cout << line << endl;
        stringstream ss(line);
        string token;
        
        getline(ss,token,',');
        int speed = stoi(token);

        getline(ss,token,',');
        int temp = stoi(token);

        sensor_data data;
        data[speed] = temp;

        data_list.push_back(data);
    }

    inFile.close();  // Đóng file sau khi đọc
}
#define SPEED 0
#define TEMP  1
int main() {
   srand(time(0));
   vector<sensor_data> list;

   int total = 10;
   auto GenerateRandomvalue = [&,total](){
        for(int i = 0 ; i < total ; i++){
            int temp =  (30 + rand() % 70);
            int speed = (30 + rand() % 300);
            sensor_data data;
            data[speed] = temp;
            list.push_back(data);
        }
   };

    GenerateRandomvalue();

    writefile(list);
    readfile(list);
    return 0;
}
