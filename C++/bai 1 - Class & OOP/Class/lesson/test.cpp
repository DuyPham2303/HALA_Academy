#include <iostream>
using namespace std;
class person
{
protected:
    int tuoi;
    string ten;
public:
    person(string ten, int tuoi)
    {
        this->ten = ten;
        this->tuoi = tuoi;
    }
    void printInfo()
    {
        cout << "ten: " << ten << endl;
        cout << "tuoi: " << tuoi << endl;
    }
};
class hocsinh : public person
{
private:
    string lop;
public:
    hocsinh(string ten, int tuoi, string lop) : person(ten, tuoi)
    {
        this->lop = lop;
    }
    void printInfo() 
    {
        cout << "ten: " << ten << endl;
        cout << "tuoi: " << tuoi << endl;
        cout << "lop: " << lop << endl;
    }
};
class sinhvien : public person
{
private:
    string major;
public:
    sinhvien(string ten, int tuoi, string major) : person(ten, tuoi)
    {
        this->major = major;
    }
    void printInfo()
    {
        cout << "ten: " << ten << endl;
        cout << "tuoi: " << tuoi << endl;
        cout << "nganh hoc: " << major << endl;
    }
};
int main()
{
    hocsinh hs1("Trinh Le Hoang",26,"12A1");
    sinhvien sv1("Pham Cao Duy",17,"Mechatronics Engineer");

    hs1.printInfo();
    sv1.printInfo();
}