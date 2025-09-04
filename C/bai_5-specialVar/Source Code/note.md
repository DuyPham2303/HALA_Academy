# BỐI CẢNH 
- Các từ khóa dùng kèm với việc khai báo biến, để thực thi 1 chức năng nhất định 
# EXTERN
## Đặt vấn đề
- sử dụng nội dung trong 1 file -> include cả file (cách cơ bản)
    => không an toàn do copy toàn bộ source (ko có cơ chế bảo vệ nào)
    => nhược điểm:
        + tăng kích thước mã nguồn, không tối ưu (compiler biên dịch những đoạn mã ko cần thiết)
        + lỗi khai báo nhiều lần (include nhiều lần)
## Sử dụng
- dùng extern thay vì include cho biến/hàm
    + tổng kết 3 đặc diểm 
    - thông báo chương trình biết biến này đã được định nghĩa (tài nguyên đã tồn tại)
    - chỉ được khai báo ko được phép định nghĩa lại
    - sử dụng cho biến/hàm toàn cục
- share cho nhiều file -> khai báo extern trong .h
-  so sánh hàm có/không extern => hàm toàn cục mặc định (ko cần extern)

# STATIC 
## Local
    + cấp phát -> thao tác -> thu hồi 
    + cách giữa lại ? -> static local
    + đặc điệm : giữ lại tài nguyên cấp phát trước đó
    => thay đồi static local ngoài phạm vi ? -> dùng con trỏ global 
## Global
    -  demo gọi extern với biến/hàm static -> ko hoạt động kể cả khai báo trong .h 
    - tóm lược
        + biến/hàm chia sẻ khai báo extern trong .h
        + biến/hàm cục bộ file khai báo static trong .c hiện tại
## Ứng dụng thiết hàm giải ptb2
    - ví dụ nếu ko khai báo static 
        => hiển thị hết toàn bộ quá trình tính toán,xử lý chi tiết
        => show ví dụ App calculator
        => khai báo extern thử -> gọi ra -> lỗi
        => ví dụ liên hệ các app nhập thông tin (password,account) 
# Volatile
## Đặt vấn đề 
    - ví dụ về nút nhấn, ngắt -> minh họa về khái niệm
    - ví dụ KeilC
        => đọc data sensor
        => cập nhật ngắt nút nhấn gọi -> ISR_Handler
        => ví dụ dọc giá trị trên thanh ADC

# Register 

## Bối cảnh 
    - cách thức biến lưu trữ,xử lý trên máy tính 
        => ALU -> register -> RAM
    - khai báo Register ? 
        -> xử lý nhanh chóng đối với biến cần xử lý tính toán phức tạp
    => Register chỉ định biến lưu trên Register thay vì RAM -> tăng tốc độ truy cập 
    - Ứng dụng tính toán tốc độ động co 
## ví dụ 
    - giải thích hàm clock()
   `Nhược điểm`
    - ko có địa chỉ do ko lưu trên RAM
    - chỉ khai báo cục bộ -> số lượng thanh ghi hạn chế -> sử dụng xong cần trả về
    `Liên hệ MCU`
    - stm32 chỉ có 32 thanh ghi 
    - trên f103 -> clock 72MHZ -> 72,000,000 lệnh / s  

