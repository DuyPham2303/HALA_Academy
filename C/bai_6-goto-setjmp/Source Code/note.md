# GOTO
## Ví dụ dẫn dắt
- Cách kiểm soát luồng chạy chương trình 
    + từ tuần tự -> ko tuần tự (dùng 1 biến)
        => vấn đề : tốn RAM (ví dụ: embedded system có tài nguyên giới hàn)
    + dùng goto -> tối ưu hơn
## Giới thiệu cú pháp
- mô tả cách thao tác 
- ví dụ cơ bản (dùng lại ví dụ dẫ dắt) 
    => Lưu ý: label chỉ được đặt trong 1 phạm vi

## Ứng dụng điều khiển led ma trận
- Giới thiệu led ma trận
**Note**
<!-- 
    - tập hợp các led nhỏ kết hợp lại
    - làm sao điều khiển ? -> mỗi chân gấn 1 led ? -> ko đủ chân
    - sử dụng kỹ thuật quét led 
        => quét từng hàng , cột
        => hiển th5i hình ? => diễn ra rất nhanh => tần số cao mắt ko nhận biết được 
        => chỉ cần dùng 1 vài chân kết nối với 1 chân MCU (cho phép điều khển 1 lúc nhiều led)
 -->
- triển khai mô phỏng 
    + conio : cơ chế kiểm tra phím đang nhấn
    + unistd : cơ chế delay chính xác theo s,ms 
        => sleep() và usleep()
    + mảng đon định nghĩa thông tin hiễn thị
    + mảng 2 chiều định nghĩa cách thức hiển thị từng chữ của thông tin 
    + 1 biến lưu trữ trạng thái phím 
    + 2 vòng for xác định hàng/cột tương ứng với vị trí trên ma trận
        => in ra ký tự tương ứng với việc bật/tắt led mong muốn 
    + hàm lấy phím : 
        => dùng kbhit() : kiểm tra có nhấn phím ?
        => getch() : xác định phím nhấn ?
- So sánh goto và break 
    - khó quản lý (cần gọi nhiều để escape multi-loop)
# Setjmp 
## Bối cảnh dẫn dắt
    - là gì ? 
    - So sánh với goto 
        + phiên bãn nâng cấp (nhảy giữa nhiều hàm)
## cách dùng 
    - set_jmp(jmp_buff env) : lưu trữ vị trí thực thi hiện tại -> liên hệ PC (thực thi dòng lệnh hiện tại bằng cách đọc ra địa chỉ)
        + env chứa địa chỉ của dòng hiện tại 
    - long_jmp(jmp_buf env,int value) : cho phép nhảy về ví trị set_jmp dựa trên jmp_buf
        + value : giá trị sẽ trả về cho set_jmp
## Ví dụ cơ bản
    - mô tả cách chạy (minh họa ưu điểm so với goto)
## Ứng dụng xử lý exception handling
    - Mô tả từng lỗi exception 
    - giới thiệu co chế xử lý ngoại lệ 
        + try : định nghĩa 1 lỗi
        + catch : bắt lỗi
        + throw : ném ra lỗi 
        =>C++ tích hợp sẵn -> C không hỗ trợ (tự định nghĩa thông qua setjmp,longjmp)
    - Viết hàm xử lý lỗi chia 0 (dùng if - else)
        + viết lại bằng try,catch,throw

