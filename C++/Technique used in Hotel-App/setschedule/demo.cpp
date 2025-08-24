#include <iostream>
#include <map>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>

using namespace std;

enum session
{
    none,
    morning,  // Sáng
    afternoon, // Chiều
    evening    // Tối
};

enum dayinWeek
{
    Mon, // Thứ 2
    Tue, // Thứ 3
    Wed, // Thứ 4
    Thu, // Thứ 5
    Fri, // Thứ 6
    totalday
};

class WorkShiftManager
{
private:
    map<dayinWeek, vector<session>> schedule;

    // Hàm ánh xạ ký tự sang ca làm
    session parseSession(char s)
    {
        switch (toupper(s))
        {
        case 'S': return morning;   // Sáng
        case 'C': return afternoon; // Chiều
        case 'T': return evening;   // Tối
        default: return none;       // Không hợp lệ
        }
    }

    // Hàm ánh xạ số sang ngày trong tuần
    dayinWeek parseDay(char d)
    {
        switch (d)
        {
        case '2': return Mon; // Thứ 2
        case '3': return Tue; // Thứ 3
        case '4': return Wed; // Thứ 4
        case '5': return Thu; // Thứ 5
        case '6': return Fri; // Thứ 6
        default: return totalday; // Không hợp lệ
        }
    }
    void setSchedule(const dayinWeek& day,const session& sess) 
    {
            schedule[day].push_back(sess); 
    }
public:
    WorkShiftManager()
    {
        // Khởi tạo lịch làm việc với các ngày và giá trị mặc định
        for (int day = Mon; day < totalday; ++day)
        {
            schedule[static_cast<dayinWeek>(day)] = {}; // Danh sách rỗng cho mỗi ngày
        }
    }

    // Hàm thiết lập ca làm việc từ chuỗi định dạng "2-C"
    void setWorkShiftFromString(const string& shift)
    {
        if (shift.size() != 3 || shift[1] != '-') // Định dạng phải là "2-C"
        {
            cout << "Sai định dạng: " << shift << endl;
            return;
        }

        // Parse ngày và ca làm từ chuỗi
        dayinWeek day = parseDay(shift[0]);
        session sess = parseSession(shift[2]);

        // Kiểm tra giá trị hợp lệ
        if (day == totalday || sess == none)
        {
            cout << "Không hợp lệ: " << shift << endl;
            return;
        }

        // Thêm ca làm vào lịch trình (tránh trùng lặp)
       /*  if (find(schedule[day].begin(), schedule[day].end(), sess) == schedule[day].end())
        {
            schedule[day].push_back(sess);
        } */
        setSchedule(day,sess);
    }

    // Hàm in lịch làm việc theo định dạng
    void printSchedule(const string &employeeName)
    {
        vector<string> list_day = {"T2", "T3", "T4", "T5", "T6"};
        vector<string> list_session = {"X", "Sáng", "Chiều", "Tối"};

        // In tiêu đề
        cout << "Xem ca làm\n";
        cout << "Thời gian làm việc:\n";
        cout << "Tên nhân viên     | ";
        for (size_t i = 0; i < list_day.size(); ++i)
        {
            cout << list_day[i] << "        | ";
        }
        cout << endl;

        // In dữ liệu của từng nhân viên và căn lề
        cout << setw(17) << left << employeeName;
        cout << " | ";

        // Lặp qua từng ca làm và lần lượt in ra dựa trên ngày tương ứng
        bool new_line = false;
        for (int shift = morning; shift <= evening; ++shift)
        {
            if (new_line)
            {
                cout << setw(17) << left << "  ";
                cout << " |";
                new_line = false;
            }

            // Lặp qua từng ngày để in ra tất cả ca làm hiện tại
            for (int day = Mon; day < totalday; ++day)
            {
                // Tìm ngày tương ứng
                auto it = schedule.find(static_cast<dayinWeek>(day));

                // Nếu có ca làm và ca làm trùng với ca hiện tại, in ra
                if (it != schedule.end() &&
                    find(it->second.begin(), it->second.end(), static_cast<session>(shift)) != it->second.end())
                {
                    cout << list_session[shift] << "      | ";
                }
                else
                {
                    cout << " X         | "; // Không có ca làm
                }
            }
            new_line = true;
            cout << endl;
        }
    }
};

int main()
{
    WorkShiftManager manager;

    // Thiết lập ca làm việc cho nhân viên từ chuỗi định dạng
    manager.setWorkShiftFromString("5-C"); // Chiều thứ 2
    manager.setWorkShiftFromString("3-T"); // Tối thứ 4
    manager.setWorkShiftFromString("5-S"); // Sáng thứ 5
    manager.setWorkShiftFromString("3-C"); // Chiều thứ 2
    manager.setWorkShiftFromString("2-T"); // Tối thứ 4
    manager.setWorkShiftFromString("2-S"); // Sáng thứ 5
    // Không nhập tất cả ca làm, chỉ nhập một vài ca


    // In lịch làm việc
    manager.printSchedule("Duy");

    return 0;
}
