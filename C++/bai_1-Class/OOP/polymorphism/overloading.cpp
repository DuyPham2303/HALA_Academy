#include <iostream>
#include <string>
using namespace std;
class Phanso{
    private:
        int mauso;
        int tuso;
    public:
        Phanso(int mauso = 0,int tuso = 0){
            this->mauso = mauso;
            this->tuso = tuso;
        }
        Phanso operator + (Phanso other){
            Phanso ketqua;
            ketqua.mauso = this->mauso * other.tuso + this->tuso * other.mauso;
            ketqua.tuso = this->tuso * other.tuso;
            return ketqua;

        }
        void display(Phanso a, Phanso b,Phanso ketqua){
            cout << a.mauso << "/" << a.tuso << " + " << b.mauso << "/" << b.tuso << " = " << ketqua.mauso << "/" << ketqua.tuso << endl;
        }
};
class tinh_toan
{
public:
    /*Overloading method*/
    int tong(int a, int b)
    {
        return a + b;
    }
    double tong(double a, double b)
    {
        return a + b;
    }
    int tong(double a, double b, double c, double d)
    {
        return (int)a + b + c + d;
    }
};
int main(){
    Phanso ps1(23,21);
    Phanso ps2(2,3);
    Phanso ps3 = ps1 + ps2;
    ps3.display(ps1,ps2,ps3);
    return 0;
}