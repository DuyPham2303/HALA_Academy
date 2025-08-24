#include <iostream>
using namespace std;
/*structure of namespace*/
/*
namespace name_of_namespace{
    //var
    //function
    //class
    //struct
}
 */
namespace user
{
    class Point
    {
    private:
        int x;
        int y;

    public:
        Point() = default;
        Point(int x_,int y_) : x(x_), y(y_){};
        void display()
        {
            cout << "x = " << x << endl;
            cout << "y = " << y << endl;
        }
        void setpoint(int x, int y)
        {
            this->x = x;
            this->y = y;
        }
        int get_pointX()
        {
            return this->x;
        }
        int get_pointY()
        {
            return this->y;
        }
    };
    Point point1;
}
namespace A
{
    string name = "Pham Cao Duy";
    void display()
    {
        cout << "name: " << name;
    }
    namespace B
    {
        string name = "Pham Bang Bang";
        void display()
        {
            cout << "name: " << name;
        }
    }

}
namespace C
{
    string name = "Trinh Le Hoang";
    void display()
    {
        cout << "name: " << name;
    }
}
using namespace A::B; // access directly to namespace B via A
using namespace user;
int main()
{
    
    cout << "name: " << name << endl; // name from namespace B
    cout << "name: " << A::name << endl;
    cout << "name: " << C::name << endl;
    //point1.display();
    point1.setpoint(23,41);
    cout << "x: " << point1.get_pointX() << endl
         << "y: " << point1.get_pointY() << endl;
    return 0;
}