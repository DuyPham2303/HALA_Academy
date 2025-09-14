#ifndef _LCD2_HPP
#define _LCD2_HPP

namespace LCD{
    void displayInfo(lcd* mylcd){
        cout << "********"<< endl;
        cout << "name lcd : " << mylcd->get_name() << endl;
        cout << "row : " << mylcd->get_row() << endl;
        cout << "col : " << mylcd->get_col() << endl; 
        cout << "********"<< endl;
    }
    void totalLCD(){
        cout << "total : " << lcd::count << endl;
    }
}

#endif

