/*
    + Inheritance
    + Polymorphism
    + virtual function and pure
*/
#include <iostream>
#include <string>
using namespace std;
class Car
{
private:
    float speed;
    float torque;
    int total;

protected:
    string name;
    string model;

public:
    virtual void behaviour() = 0; // pure virtual function
    virtual void print_info() = 0;
    virtual void function()
    {
        cout << "basic function" << endl;
    }
    Car(string name, string model)
    {
        this->name = name;
        this->model = model;
        this->speed = 0;
        this->torque = 0;
        total = 0;
    }
    void Verify_quantity()
    {
        if (total > 5)
        {
            cout << "meet enough quanity: " << total << endl;
        }
        else
            cout << "do not meet enough quanity: " << total << endl;
    }
    void produce()
    {
        total++;
    }
};
class SUV : public Car
{
public:
    string original;
    SUV(string name, string model, string original) : Car(name, model)
    {
        this->original = original;
    }
    void function()
    {
        cout << "additional SUV function" << endl;
    }
    void behaviour()
    {
        cout << "activate the air bar" << endl;
    }
    void print_info()
    {
        cout << "name: " << name << endl;
        cout << "model: " << model << endl;
        cout << "original: " << original << endl;
    }
};
class Mercedes : public Car
{
public:
    Mercedes(string name, string model) : Car(name, model)
    {
    }
    void function()
    {
        cout << "additional Mercedes function" << endl;
    }
    void behaviour()
    {
        cout << "activate ABS" << endl;
    }
    void print_info()
    {
        cout << "name: " << name << endl;
        cout << "model: " << model << endl;
    }
};
class Instrument
{
public:
    virtual void makesound(){
        cout << "make sound " << endl;
    }
};
class Piano : public Instrument
{
    void makesound()
    {
        cout << "playing the piano" << endl;
    }
};
class guitar : public Instrument
{
    void makesound()
    {
        cout << "playing the guitar" << endl;
    }
};
class Ukelele : public Instrument
{
    void makesound()
    {
        cout << "playing the Ukelele" << endl;
    }
};
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
    virtual void do_task(){
        cout << "doing task" << endl;
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
    void do_task(){
        cout << "do homework" << endl;
    }
};
class sinhvien
{
private:
    string rank;
    float dtb;
public:
    float dtoan;
    float dvan;
    string name;

    sinhvien(string name, float dtoan, float dvan)
    {
        this->name = name;
        this->dtoan = dtoan;
        this->dvan = dvan;
    }
    float tinh_dtb()
    {
        dtb = (dtoan + dvan) / 2;
        return dtb;
    }
    string xep_hang()
    {
        if (dtb >= 8)
            rank = "gioi";
        else if (dtb > 6.5)
            rank = "kha";
        else if (dtb >= 5 && dtb < 6.5)
            rank = "trung binh";
        else
            rank = "yeu";
        return rank;
    }
};
int main()
{
    /* sinhvien sv1("Pham Cao Duy",8.2,8.4);
    cout << "diem trung binh: " << sv1.tinh_dtb() << endl;
    cout << "xep hang: " << sv1.xep_hang();
    hocsinh hs1("Pham Cao Duy",23,"12A1");
    person* p = &hs1;
    p->do_task(); */
    SUV mysuv("my suv", "Model 1", "Viet Nam");
    Mercedes myMer("my mercedes", "model 4");

    for (int i = 0; i < 8; i++)
        mysuv.produce();
    for (int i = 0; i < 4; i++)
        myMer.produce();

    mysuv.Verify_quantity();
    myMer.Verify_quantity();

    
    Car *mycar[] = {&mysuv,&myMer};

    for(int i = 0 ; i < 2 ; i++){
        mycar[i]->print_info();
    }

     /* Instrument *ins[3];
     ins[0] = new Piano();
     ins[1] = new guitar();
     ins[2] = new Ukelele();
     for (int i = 0; i < 3; i++)
     {
         ins[i]->makesound();
     } */
 
    return 0;
}