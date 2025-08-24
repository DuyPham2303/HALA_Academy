# ỨNG DỤNG
cho phép tạo trực tiếp đối tượng trong container
# So sánh với push_back
## Cách hoạt động của push_back
+ Tạo 1 object trước
+ đưa object này vào vector
Ví dụ:
std::vector<Employee> employees;
Employee emp("123", "John Doe", "0123456789", "Manager"); // Tạo đốitượng
employees.push_back(emp); // Sao chép hoặc di chuyển vào vector

## Cách hoạt động của emplace_back

+ Cung cấp các tham số truyền vào emplace_back -> object sẽ được khởi tạo tự động 
+ Không yêu cầu bước sao chép -> tối ưu

Ví dụ:

std::vector<Employee> employees;
employees.emplace_back("123", "John Doe", "0123456789", "Manager"); // Khởi tạo trực tiếp trong vector
