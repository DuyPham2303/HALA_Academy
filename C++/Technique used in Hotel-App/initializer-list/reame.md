ĐỊNH NGHĨA
- là 1 template Hỗ trợ khởi tạo 1 tập hợp giá trị trong 1 đối tượng mà không cần phải sử dụng mảng hoặc danh sách cụ thể
- Dễ dàng khởi tạo các đối tượng của các lớp hoặc cấu trúc với 1 tập hợp giá trị theo cách dễ hiểu
CẤU TRÚC

template <class T>
class initializer_list {
public:
    // Trả về con trỏ tới mảng đầu tiên của danh sách.
    const T* begin() const;
    
    // Trả về con trỏ tới phần tử sau cùng (hết danh sách).
    const T* end() const;
    
    // Trả về số lượng phần tử trong danh sách.
    size_t size() const;
};

ỨNG DỤNG
- Khởi tạo mảng hoặc vector mà không cần khởi tạo mảng hay danh sách theo cách thủ công 

ƯU ĐIỂM

+ Cú pháp đơn giản
=> sữ dụng {} khởi tạo object / container với tập giá trị -> không cần khởi tạo mảng/container tạm
=> Tương thích với container khác: hữu ích khi làm vịệc với vector
=> không cần xác định kích thước: tự động tính 