#include <iostream>
#include <vector>
#include <map>
using namespace std;

class student
{
    private:
        int age;
        string name;
        string id;

    public:
        student() : name("unset name"), age(0), id("unset id") {}
        student(string _name, int _age, string _id) : name(_name), age(_age), id(_id) {}
        string getName() const { return name; }
        string getId() const { return id; }
        int getAge() const { return age; }
        void printInfo(){
            cout << getName() << "\t" << getAge() << endl;
        }
};

int main()
{
    vector<student> list_student = 
    {
        student{"Duysolo", 23, "ID02"},
        student{"Hoang Anh", 22, "ID05"},
        student{"Hoang Trinh", 21, "ID01"},
        student{"Hoang Bao", 26, "ID03"},
        student{"Hoang Pham", 22, "ID08"}
    };

    //lưu trữ cặp key-value sắp xếp theo thứ tự key
    map<string,student> sortIdlist;

    //sắp xếp theo thứ tự
    for(const auto& info : list_student){
        sortIdlist[info.getId()] = info;    //gán value cho từng cặp key-value 
    }

    for(auto&[id,info] : sortIdlist){
        cout << id << "\t";
        info.printInfo();
        cout << endl;
    }
    
}