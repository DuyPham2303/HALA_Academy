#ifndef MANAGER_HPP
#define MANAGER_HPP
#include "EmployeeManager.hpp" 
#include "Menu.hpp"
#include "UI.hpp"
class Manager{
public:
    // Hiển thị menu quản lý chính
    void showManagementMenu();
private:
    EmployeeManager  employeeManager;
    // Các phương thức để quản lý từng phần
    void manageEmployees();  // Quản lý nhân viên
    void manageRooms();      // Quản lý phòng
    void manageServices();   // Quản lý dịch vụ

    // Các phương thức cụ thể cho từng hành động
    void addEmployee();      // Thêm nhân viên
    void editEmployee();     // Sửa thông tin nhân viên
    void deleteEmployee();   // Xóa nhân viên
    void listEmployees();    // Liệt kê nhân viên
    void setWorkShift();  // set ca lam
    void TableSchedule();    // hien thi thoi gian lam viec

    void addRoom();          // Thêm phòng
    void editRoom();         // Sửa thông tin phòng
    void deleteRoom();       // Xóa phòng
    void listRooms();        // Liệt kê phòng

    void addService();       // Thêm dịch vụ
    void editService();      // Sửa thông tin dịch vụ
    void deleteService();    // Xóa dịch vụ
    void listServices();     // Liệt kê dịch vụ
};
#endif // MANAGER_HPP
