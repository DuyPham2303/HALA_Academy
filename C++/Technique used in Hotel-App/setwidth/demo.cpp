#include <iostream>
#include <iomanip> // Thư viện để định dạng đầu ra

using namespace std;
int main() {
    // Tiêu đề
    cout << left  << setw(15) << "Name"
              << setw(10) << "Age"
              << setw(15) << "Address"
              << setw(10) << "Salary" 
              << endl;

    // Dòng kẻ ngang
    cout << setfill('-') << setw(50) << "-" << endl;

    // Reset fill về mặc định (space)
    cout << setfill(' ');

    // Dữ liệu
    cout << left  << setw(15) << "Alice"
              << setw(10) << 25
              << setw(15) << "New York"
              << setw(10) << 5000.50 
              << endl;

    cout << left  << setw(15) << "Bob"
              << setw(10) << 30
              << setw(15) << "San Francisco"
              << setw(10) << 7000.75 
              << endl;

    cout << left  << setw(15) << "Charlie"
              << setw(10) << 22
              << setw(15) << "Los Angeles"
              << setw(10) << 6500.80 
              << endl;

    return 0;
}
