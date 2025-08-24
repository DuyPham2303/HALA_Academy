
## Khái niệm 
    - dùng làm gì ?
    <!-- 
        - định nghĩa kiểu dữ liệu user 
        - gói nhiều kiểu dữ liệu nguyên thủy lại thành 1 kiểu chung
        - Định nghĩa 1 đối tượng cụ thể
     -->
## Bối cãnh
    - Khai báo 1 kiểu tự định nghĩa -> sinhvien -> ko thể dùng kiểu nguyên thủy 
# Giới thiệu các nội dung nhỏ
    - Data Alignment
    - Data Padding 
    - size
    - bit field
# STRUCT
## Sử dụng
    - khai báo thông thường
    - kết hợp typedef (dùng như nào ? ->)
    - cách truy cập (đọc/ghi data)
        => dùng con trỏ (->)
        => dùng biến thường (.)
+ Kích thước
    - đặt vấn đề tại sao cần tính size 
        => ảnh hưởng ntn ?
        => ví dụ embedded system có tài nguyên limited -> cần phải quản lý memory tốt
         <!-- 
        - Đảm bảo quản lý tốt và tránh gây lảng phí memory
        - triển khai các hệ thống nhúng (yêu cầu về tài nguyên hạn chế)
        - cần nắm được cách thức cấp phát memory của struct -> tối ưu tài nguyên
     -->
    - triển khai nhìn ví dụ đoán size -> lái sang các yếu tố ảnh hưởng
        => data alignment ? 
            - minh họa cách địa chỉ được cấp phát
            - tại sao cần ? -> truy xuất nhanh hơn
            - cách thức CPU cấp phát dựa trên ?
                => theo thứ tự
                => kích thước biến có size lớn nhất 
        <!-- 
            - Quy định việc các thành viên được cấp phát memory tại các địa chỉ cụ thể theo yêu cầu của 
            + CPU
            + kiến trúc hệ thống   
                -> đảm bảo việc truy cập nhanh chóng 
                -> việc căn chỉnh đảm bảo các thành viên có giá trị địa chỉ chia hết cho datatype của nó
                -> tổng kích thước của struct phải chia hết cho thành viên có kiểu lớn nhất
         -->
        => padding byte ? 
            - byte địa chỉ trống dược thêm vào để đảm bảo yêu cầu căn chỉnh của cpu
            - có thế có/không khi thay đổi thứ tự byte cấp phát
        <!-- 
            - byte thêm vào sau mỗi thành viên,đảm bảo đúng yêu cầu căn chỉnh 
         -->
    Lưu ý : khai báo struct cần cân nhắc
        - datatype khai báo
        - thứ tự sắp xếp datatype
        => tối ưu size (tránh padding)
        
+ Bit field
    - Dùng làm gì ?
    <!-- 
        - cơ chế cho phép chỉ định số lượng bit mong muốn để quản lý 1 biến
        - cho phép giới hạn số bit tối đa mà 1 biến có thể được truy cập 
        - tối ưu memory do chỉ sử dụng đúng số bit mong muốn
     -->
    - Ví dụ cơ bản : Quản lý các chân GPIO
    - Ví dụ nâng cao: Quản lý các tính năng xe hơi
+ Ứng dụng 
    - cấu hình thông số ngoại vi MCU, định nghĩa thanh ghi -> mở keilC giảng giải
    - xây dựng các cấu trúc dữ liệu
# UNION
## So sánh với struct : 
   **Điểm giống**
        - data alignment,padding,truy xuất bằng . và ->
   **Điểm khác**
        - shared memory
        - size = member (max size) + padding (member max size) 
## Phân tích Union
   **cấp phát memory** 
        - outline các vùng địa chỉ để mô tả
        - cơ chế : theo thứ tự và member (max datatype)
            `Lưu ý về padding` : so sánh với struct
            => size ? 
## Demo 2 ví dụ (có/không padding)
    + liên hệ cách mà các byte được bố trí (little endian)
    + diễn giải cách mà dữ liệu (bin) thao tác trên các vùng địa chỉ
## Trình bày padding trên slide (ví dụ có padding)

## Ửng dụng truyền data giữa 2 MCU

