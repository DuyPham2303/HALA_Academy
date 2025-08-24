# EXTERN
## Đặt vấn đề
- sử dụng nội dung trong 1 file -> include cả file (cách cơ bản)
    => không nền, không an toàn do copy toàn bộ source 
    => nhược điểm:
        + tăng kích thước mã nguồn, không tối ưu
        + lỗi khai báo nhiều lần (include nhiều lần)
## Triển khai
- dùng extern thay include cho biến/hàm
    + chỉ sử dụng lại các biến/hàm mong muốn 
    + cần liên kết bằng lệnh , do bấm Run code chỉ chạy 1 file
    + tổng kết 3 đặc diểm 
    **Note**
    <!-- 

        - thông báo chương trình biết biến này đã được khai báo (tài nguyên đã tồn tại)
        - chỉ được khai báo ko được phép định nghĩa lại
        - sử dụng cho biến/hàm toàn cục
     -->
    => Ứng dụng tổng kết : 
- khai báo extern trong .h
    + extern các biến sử dụng lại
    + so sánh hàm có/không extern 
        => hàm toàn cục mặc định (ko cần extern)

# STATIC 
## Local
    - Giải thích cách gọi hàm xử lý biến cục bộ (outline minh họa cấp phát địa chỉ)
        + cấp phát -> thao tác -> thu hồi 
        + cách giữa lại ? -> static local
        + đặc điệm : giữ lại tài nguyên cấp phát trước đó
        => thay đồi static local ngoài phạm vi ? -> dùng con trỏ toàn ccu5
## Global
    -  
## Ứng dụng thiết hàm giải ptb2
    - ví dụ nếu ko khai báo static 
        => hiển thị hết toàn bộ quá trình tính toán,xử lý chi tiết
        => show ví dụ App calculator
        => khai báo extern thử -> gọi ra -> lỗi
        => ví dụ liên hệ các app nhập thông tìn (password,account) 
# Volatile
## Đặt vấn đề 
    - ví dụ về nút nhấn, ngắt -> minh họa về khái niệm
    - ví dụ KeilC
        => đọc data sensor
        => cập nhật phím nhấn -> IRQ_Hnadle 
        => ví dụ dọc giá trị trên thanh ADC 
**Note**
<!-- 

    - cấu hình
    - bắt đầu chuyển đổi
    - đợi quá trình chuyển đổi kết thúc 
    - đọc về từ thanh ghi
-->

# Register 

## Bối cảnh 
    - cách thức biến lưu trữ,xử lý trên máy tính 
        => ALU -> register -> RAM
    - khai báo lưu trực tiếp trên Register ? -> xử lý nhanh chóng
    => Register chỉ định biến lưu trên Register thay vì RAM -> tăng tốc độ truy cập 
## ví dụ 
    - giải thích hàm clock()
    Nhược điểm
    - in ra địa chỉ biến register -> ko có do lưu trên register 
    - chỉ khai báo cục bộ -> lý do ? -> số lượng thanh ghi hạn chế -> sử dụng xong cần trả về

