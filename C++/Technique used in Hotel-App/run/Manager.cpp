#include "manager.hpp"
#include <cctype>
#define VALID   SUCCESS
#define INVALID FAIL
vector<string> list_room;
                            /*HIỂN THỊ MENU QUẢN LÝ CHÍNH */
void Manager::showManagementMenu() {
    //tạo các đề mục của menu
    Menu mainMenu("Quản lý khách sạn", {
        {1, "Quản lý nhân viên", [this]() { manageEmployees(); }},
        {2, "Quản lý phòng", [this]() { manageRooms(); }},
        {3, "Dịch vụ", [this]() { manageServices(); }},
        {0, "Quay lại", []() { UI::showMessage("Quay lại menu chính..."); }}
    });

    // Hiển thị menu quản lý chính
    mainMenu.showMenu(); 
}
                                 /*HIỂN THỊ CÁC MENU QUẢN LÝ NHỎ HƠN*/
// Quản lý nhân viên
void Manager::manageEmployees() {
    Menu employeeMenu("Quản lý nhân viên", {
        {1, "Thêm nhân viên", [this]() { addEmployee(); }},
        {2, "Sửa thông tin nhân viên", [this]() { editEmployee(); }},
        {3, "Xóa nhân viên", [this]() { deleteEmployee(); }},
        {4, "Xem danh sách nhân viên", [this]() { listEmployees(); }},
        {5, "Set ca làm cho nhân viên",[this](){setWorkShift();}},
        {6, "Thời gian làm việc",[this](){TableSchedule();}},
        {0, "Quay lại", []() { UI::showMessage("Quay lại menu quản lý..."); }}
    });

    employeeMenu.showMenu();  // Hiển thị menu quản lý nhân viên
}
static bool ValidInfo(const string& name,const string& phoneNumber,const string& position){
    string valid_job[] = {"TV","BV","LT","DB","NV"};
    bool validname = true,validphone = true,validjob = false;
    for(const char& cha : name){
        if(isalpha(cha) == false){
            UI::showMessage("tên không hợp lệ vui lòng nhập lại");
            validname = false;
            break;
        }
    }
    for(const char& digit : phoneNumber){
        if(isdigit(digit) == false){
            UI::showMessage("sdt không hợp lệ vui lòng nhập lại");
            validphone = false;
            break;
        }
    }
    for(const auto& job : valid_job){
        if(job == position){
            validjob = true;
            break;
        }
    }
    if(validjob == false)   
        UI::showMessage("vị trí không hợp lệ vui lòng nhập lại");

    if(validname == false || validphone == false || validjob == false)
        return INVALID;
    else 
        return VALID;
}
void Manager::addEmployee() {
   
    while (true) {
        UI::showMessage("=== Thêm Nhân Viên ===");

        user_input:
        // Nhập thông tin từ người dùng
        std::string name = UI::getInputString("Nhập tên nhân viên: ");
        std::string phoneNumber = UI::getInputString("Nhập số điện thoại (ID): ");
        std::string position = UI::getInputString("Nhập vị trí công việc (Tạp vụ/Bảo vệ/Đầu bếp/Lễ Tân): ");

        if(ValidInfo(name,phoneNumber,position) == INVALID){
            goto user_input;
        }

        // Thêm nhân viên mới vào danh sách
        if(employeeManager.addEmployee(accountList, name, phoneNumber, position) == FAIL){
            UI::showMessage("vui lòng nhập lại thông tin:");
            goto user_input;
        }

        // In ra tên của nhân viên mới
        UI::showMessage("Thêm thành công nhân viên " + name);

        // Tự động đăng ký tài khoản cho nhân viên với mật khẩu mặc định
        UI::showMessage("mật khẩu mặc định : 123456");
        UI::showMessage("----------------------------");
        UI::showMessage("1.Thêm nhân viên khác\n2.hoặc quay lại (0)");
        // Hiển thị tùy chọn để thêm nhân viên khác
        int choice = UI::getUserChoice("vui lòng chọn tính năng");        
        if (choice == 0) {
            break;  // Quay lại nếu người dùng chọn 0
        }
    }
    
}

void Manager::editEmployee() {
    while(1){
        UI::showMessage("Sửa thông tin nhân viên...");
        // Danh sách nhân viên
        employeeManager.listEmployees();

        //nhập thông tin chỉnh sửa
        UI::showMessage("Vui lòng nhập tên của nhân viên muốn sửa thông tin:");
        std::string id = UI::getInputString("Nhập ID: ");
        std::string newname = UI::getInputString("Nhập tên mới: ");
        std::string newposition= UI::getInputString("Nhập công việc mới: ");
    
        //thực hiện cập nhật thông tin nhân viên
        employeeManager.editEmployeeById(id,newname,newposition);

        UI::showMessage("1.Tiếp tục sửa thông tin");
        UI::showMessage("0.Quay lại");
        int choice = UI::getUserChoice("nhập lựa chọn:");
        if(choice == 0)
            break;
    }
}

void Manager::deleteEmployee() {
    while(1){
        UI::showMessage("Xóa nhân viên...");
        employeeManager.listEmployees();
        UI::showMessage("------------------");
        std::string id = UI::getInputString("Nhập ID của nhân viên muốn xóa: ");
        employeeManager.deleteEmployeeById(id);

        UI::showMessage("0.Quay lại");
        option:
        int choice = UI::getUserChoice("Nhấn 0 để quay lại:");
        if(choice == 0){
            UI::showMessage("lựa chọn không hợp lệ, vui lòng nhập lại");
            break;
        }
        else 
            goto option;
            
    }
}

void Manager::listEmployees() {
    while(1){
        UI::showMessage("=== Danh Sách Nhân Viên ===");

        employeeManager.listEmployees();

        UI::showMessage("------------------");
        option:
        int choice = UI::getUserChoice("Quay lai (0):");
        if(choice == 0)
            break;
        else{
            UI::showMessage("Lua chon khong hop le vui long nhap lai");
            goto option;
        }
    }
}

void Manager::setWorkShift(){
    while(1){
        UI::showMessage("Set ca làm nhân viên");
        employeeManager.listEmployees();
        UI::showMessage("-------------------------");
        string id = UI::getInputString("Nhập id của nhân viẹn muốn set ca làm");
        UI::showMessage("Vui lòng nhập ca làm việc trong tuần");
        string workShift = UI::getInputString("Thứ - Buổi:");
        employeeManager.setWorkShift(id,workShift);
        UI::showMessage("-------------------------");
        UI::showMessage("1.Tiếp tục set ca làm việc");
        UI::showMessage("0. Quay lại");
        int choice = UI::getUserChoice("vui lòng chọn tính năng:");
        if(choice == 0)
            break;
    }
}

void Manager::TableSchedule(){
    while(1){
       //employeeManager.TableSchedule();
       int choice = UI::getUserChoice("Chọn 0 để quay lại");
       if(choice == 0)
          break; 
    }

}


// Quản lý phòng
void Manager::manageRooms() {
    Menu roomMenu("Quản lý phòng", {
        {1, "Thêm phòng", [this]() { addRoom(); }},
        {2, "Sửa thông tin phòng", [this]() { editRoom(); }},
        {3, "Xóa phòng", [this]() { deleteRoom(); }},
        {4, "Xem danh sách phòng", [this]() { listRooms(); }},
        {0, "Quay lại", []() { UI::showMessage("Quay lại menu quản lý..."); }}
    });

    roomMenu.showMenu();  // Hiển thị menu quản lý phòng
}
static bool validRoom(const string& room){
    if(room.length() > 3)
        return INVALID;
    else{
        list_room.push_back(room); 
        return VALID;
    }

}
void Manager::addRoom() {
    while(1){
        UI::showMessage("Thêm phòng");
        string room= UI::getInputString("Vui lòng nhập số phòng:");
        //check valid room
        if(validRoom(room) == VALID){
           UI::showMessage("Thêm phòng thành công");
        }
        // Thêm logic thêm phòng ở đây
        UI::showMessage("1.Thêm phòng khác");
        UI::showMessage("0.Quay lại");
        int choice = UI::getUserChoice("vui lòng nhập lựa chọn:");
        if(choice == 0)
            break;
    }
}

void Manager::editRoom() {
    UI::showMessage("Sửa thông tin phòng...");
    // Thêm logic sửa phòng ở đây
   
}

void Manager::deleteRoom() {
    UI::showMessage("Xóa phòng...");
    // Thêm logic xóa phòng ở đây
}

void Manager::listRooms() {
    UI::showMessage("Danh sách phòng");
    /* 
    sắp xếp lại danh sách phòng theo thứ tự -> trả về số lầu
    duyệt qua từng lầu
        in ra các phòng tương ứng với trạng thái
    hiển thị chú thích trạng thái phòngphòng
    */
   
    //Thêm logic liệt kê phòng ở đây
}

// Quản lý dịch vụ
void Manager::manageServices() {
    Menu serviceMenu("Quản lý dịch vụ", {
        {1, "Thêm dịch vụ", [this]() { addService(); }},
        {2, "Sửa thông tin dịch vụ", [this]() { editService(); }},
        {3, "Xóa dịch vụ", [this]() { deleteService(); }},
        {4, "Xem danh sách dịch vụ", [this]() { listServices(); }},
        {0, "Quay lại", []() { UI::showMessage("Quay lại menu quản lý..."); }}
    });

    serviceMenu.showMenu();  // Hiển thị menu quản lý dịch vụ
}

void Manager::addService() {
    UI::showMessage("Thêm dịch vụ...");
    // Thêm logic thêm dịch vụ ở đây
}

void Manager::editService() {
    UI::showMessage("Sửa thông tin dịch vụ...");
    // Thêm logic sửa dịch vụ ở đây
}

void Manager::deleteService() {
    UI::showMessage("Xóa dịch vụ...");
    // Thêm logic xóa dịch vụ ở đây
}

void Manager::listServices() {
    UI::showMessage("Danh sách dịch vụ...");
    // Thêm logic liệt kê dịch vụ ở đây
}
