/* #include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <future>
#include <thread>
#include <chrono>
#include <ctime>
#define FILENAME "database.csv"
using namespace std;

// Struct lưu dữ liệu cảm biến
struct SensorData {
    double speed;
    double fuel;
    double distance;
    SensorData(double speed,double fuel,double distance) : speed(speed) , fuel(fuel) , distance(distance){}
};
// Hàm đọc dữ liệu từ file CSV (bất đồng bộ)
vector<SensorData> readCSVData(const string& filename) {
    vector<SensorData> data;
    ifstream file(filename);    //khởi tạo đối tượng để quản lý file csv -> truyền vào đường dẫn đến file nguồn
    string line;
    
    //kiểm tra đối tượng trỏ đến file có hợp lệ
    if (!file.is_open()) {
        cerr << "Khong the mo file csv!\n";
        return data;
    }

    //tiến hành đọc từng dòng của file
    getline(file,line); 

    //kiểm tra từng dòng có hợp lệ 
    while (getline(file, line)) {
        stringstream ss(line);  //khởi tạo đối tượng để lưu dữ liệu từng dòng
        string speed, fuel, distance;
        
        //đọc dòng hiện tại thông qua đối tượng trung gian và lưu vào biến tương ứng
        getline(ss, speed, ',');
        getline(ss, fuel, ',');
        getline(ss, distance, ',');

        //lưu dữ liệu vào bộ nhớ
        data.push_back({stod(speed), stod(fuel), stod(distance)});
    }

    file.close();
    return data;
}
void WriteCsvdata(const string& filename,const vector<SensorData> writedata){
    fstream outfile(filename);  //tạo đối tượng cho phép ghi file -> truyền vào file cần ghi
    
    //kiểm tra file có hợp lệ
    if(!outfile.is_open()){
        cout << "can't open file";
        return;
    }

    //ghi từng dòng 1
    outfile << "toc do,nhien lieu,khoang cach" << endl;
    for(const auto& value : writedata){
        outfile << value.speed << "," << value.fuel << "," << value.distance << endl;
    }

    
    outfile.close();
    cout << "saved file successfully" << endl;
}

// Hàm xử lý dữ liệu cảm biến (bất đồng bộ)
vector<SensorData> processSensorData(vector<SensorData> rawData) {
    for (auto& data : rawData) {
        data.speed *= 1.1; // Giả lập xử lý: tăng tốc độ 10%
        data.fuel -= 0.05; // Giả lập xử lý: giảm nhiên liệu nhẹ
        data.distance *= 0.98; // Giả lập xử lý: hiệu chỉnh khoảng cách
    }
    return rawData;
}

// Hàm hiển thị dữ liệu lên giao diện
void displayData(const vector<SensorData>& data) {
    cout << "=== Hien thi du lieu len giao dien ===\n";
    for (const auto& entry : data) {
        cout << "Toc do: " << entry.speed << " km/h, "
                  << "Nhien lieu: " << entry.fuel << " L, "
                  << "Khoang cach: " << entry.distance << " m\n";
    }
    cout << "--------------------------------" << endl;
}

// Hàm gửi dữ liệu mạng nền (dùng `detach()`)
void sendDataToServer(const vector<SensorData>& data) {
    thread([](vector<SensorData> data) {
        cout << "[Nen] dang gui du lieu len  server...\n";
        this_thread::sleep_for(chrono::seconds(3)); // Giả lập quá trình gửi dữ liệu
        cout << "[Nen] Gui du lieu thanh cong\n";
    }, data).detach(); // Tách luồng, không quan tâm phản hồi
}

int main() {

    auto database = [](){
        vector<SensorData> list_data;
        srand(time(0));
        for(int i = 0 ; i < 10 ; i++){
            double speed = 10 + rand() % 200;
            double fuel = rand() % 101;
            double distance = rand() % 1000;
            list_data.emplace_back(speed,fuel,distance);
        }
        return list_data;
    };
    vector<SensorData> data = database();
    WriteCsvdata(FILENAME,data);
    return 0;
    cout << "bat dau chuong trinh dieu khien xe hoi...\n";

    // Khởi chạy luồng bất đồng bộ để đọc file CSV
    future<vector<SensorData>> futureData = async(launch::async, readCSVData,FILENAME);
    
    // Trong khi chờ dữ liệu, thực hiện công việc khác
    cout << "dang tai giao dien dieu khien...\n";
    this_thread::sleep_for(chrono::seconds(2));

    // Lấy dữ liệu cảm biến từ future
    vector<SensorData> rawData = futureData.get();

    // Xử lý dữ liệu cảm biến bất đồng bộ
    future<vector<SensorData>> futureProcessedData = async(launch::async, processSensorData, rawData);
    
    // Lấy dữ liệu đã xử lý
    vector<SensorData> processedData = futureProcessedData.get();

    // Hiển thị dữ liệu lên giao diện
    displayData(processedData);

    // Gửi dữ liệu lên server trong nền (không cần phản hồi)
    sendDataToServer(processedData);

    cout << "Chuong trinh ket thuc!\n";
    this_thread::sleep_for(chrono::seconds(5)); // Đợi luồng detach chạy xong trước khi kết thúc

    return 0;
}
 */