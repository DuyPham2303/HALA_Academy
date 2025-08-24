# Giới thiệu compiler : là gì ? tại sao phải dùng ? dùng như thế nào ? => xử lý qua các bước (ví dụ)  
   ## bối cảnh 
        => cầu nối giữa máy và người (mã nguồn -> thực thi)
        => hỗ trợ tối ưu và phát hiện lỗi (logic,cú pháp,khai báo)
   ## demo run program
        -> sinh ra file .exe (kết quả của việc chạy chương trình)
        -> quá trình xử lý qua nhiều step bên trong máy tính
        -> các bước ?
# Preprocessing
   ## QUÁ TRÌNH XỬ LÝ
        - Triển khai code sẵn 
        - chạy lệnh tiền xử lý -> mô tả kết quả 
   ## TRIỂN KHAI CHI TIẾT 
         - Giới thiệu sơ lược 3 loại macro **(chỉ thị)**
   ` #include (Bao hàm tệp) ` 
        - phân biệt  “ ”  và  <> 
   ` #define và #undef (thay thế/định nghĩa)`
        - Show ví dụ trên slide
   `#,##,variadic`
	    - # và ## là gì ? -> demo code 
        - variadic ?
          + tính sum thông thường ? -> cách tổng quát hơn ? -> nhận vào n đối số -> variadic 
          + chú thích … và __VA_ARGS__ ? 
          + ví dụ tính sum -> sử dụng điều kiệu dừng (giá tri 0) và tính Size 
   `(biên dịch có điều kiện)`
    **#if / #elif / #else / #error**
       - so sánh (if,else) 
           + kiểm tra biến ? -> logic if else
           + kiểm tra điều kiện macro ? -> #if #else
           => ví dụ MCU :  cấu hình phần cứng cho nhiều loại MCU khác nhau (tốc độ,mode,vv..) 
    **#ifndef / #ifdef / #endif / #error** 
       - Ví dụ về define SIZE cho array
       - Thiết kế lib
            + demo include .c multiple time -> issue ?
            + show standard lib 
            + tạo .h với include guard với .c tương ứng
# Compiler 
    + tạo mã assembly
    + thao tác trên thanh ghi và phần cứng
    + quản lý việc lưu trữ các biến,dòng lệnh sẽ được lưu ở phân vùng nào trên bộ nhớ khi chương trình chạy 
    => phát hiện các lỗi về gọi hàm chưa khai báo,lỗi logic
# Assembler : 
    + tạo mã nhị phân cho phép máy tính hiểu và xử lý
    => các dòng lệnh chuyển thành các giá trị bin 
# Linker :
    + liên kết các tệp .o thảnh .exe
    => phát hiện lỗi linker (gọi hàm chưa định nghĩa)
# CHẠY CHƯƠNG TRÌNH
    + chạy các lệnh 
    + tóm tắt nội dung bài học
