#include <iostream>
using namespace std;
class Car
{
private:
    /*ENCAPSULATION  */
    string brand;
    string model;
    int speed;

public:
    /* ABSTRACT */
    virtual void startEngine()
    {
        cout << "base startEngine" << endl;
    }
    virtual void stopEngine()
    {
        cout << "base stopEngine" << endl;
    }

    virtual ~Car() {
        cout << "destructor for " << this->brand << " is called" << endl;
    } // Destructor ảo
    // Constructor
    Car(string b, string m, int s) : brand(b), model(m), speed(s) {}

    // Getter và Setter
    string getBrand() { return brand; }
    void setBrand(string b) { brand = b; }

    string getModel() { return model; }
    void setModel(string m) { model = m; }

    int getSpeed() { return speed; }
    void setSpeed(int s)
    {
        if (s >= 0)
            speed = s;
    }

    // Hiển thị thông tin
    void displayInfo()
    {
        cout << "Brand: " << getBrand() << ", Model: " << getModel()  << ", Speed: " << getSpeed() << " km/h" << endl;
    }
};
