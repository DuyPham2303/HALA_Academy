/*
    + Construtor & destructor
    + pass by value & reference
    + static method and property
*/
#include <iostream>
#include <string>
using namespace std;
class Shape
{
private:
    int ID;
    void rectangle_area()
    {
        cout << "Area " << name << ": " << (float)(width * height);
    }
    void triangle_area()
    {
        cout << "Area " << name << ": " << (float)((width * height) / 2);
    }
public:
    string name;
    uint16_t width;
    uint16_t height;
    void Setter(int ID)
    {
        this->ID = ID;
    }
    int getter()
    {
        return ID;
    }
    Shape(string name, uint8_t h, uint8_t w)
    {
        this->name = name;
        this->height = h;
        this->width = w;
        if (name == "rectangle")
            rectangle_area();
        else if (name == "triangle")
            triangle_area();
        else
            cout << "shape not found";
        cout << endl;
    }
    ~Shape()
    {
        cout << "object " << name << " is free" << endl;
    }
};
class Person
{
private:
    string name;
    int age;
    static int total;

public:
    Person(string name, int age)
    {
        this->name = name;
        this->age = age;
        total += 1;
    }
    static void totalPerson()
    {
        cout << "total Person: " << total << endl;
    }
    int getage()
    {
        return this->age;
    }
    string getname()
    {
        return this->name;
    }
    void printInfo()
    {
        cout << "name: " << this->getname() << endl;
        cout << "age: " << this->getage() << endl;
    }
    ~Person()
    {
        cout << "constructor: " << name << "has been released" << endl;
    }
};


/*PASS BY REFERENCE*/
void write_and_read(int &write_value, int const &compare_value)
{
    if (compare_value > 23)
    {
        write_value += 12;
    }
    else
        write_value -= 12;
}
/* PASS BY VALUE */
int calculate(int write_value)
{
    return write_value += 12;
}
int Person ::total = 0;
int main()
{
    Shape rectan("triangle",23,21);
    return 0;
}