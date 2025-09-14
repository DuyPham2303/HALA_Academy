#ifndef _LCD1_HPP
#define _LCD1_HPP
#include <iostream>
using namespace std;
namespace LCD{
    class lcd{
        private:
            int row;
            int col;
            string name;
        public:
            static int count;
            int get_row(){return row;}
            int get_col(){return col;}
            string get_name(){return name;}
            lcd(const int& _row,const int& _col,const string& name);
            ~lcd();
    };

    lcd::lcd(const int& _row,const int& _col,const string& _name) : row(_row),col(_col),name(_name){
        cout << "initialize LCD " << ++count << endl;
    }
    lcd::~lcd(){
        cout << "delete LCD " << this->name << endl;
    }
    int lcd::count = 0;
}

#endif

