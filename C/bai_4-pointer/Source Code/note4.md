# BASIC POINTER
    - Khái niệm 
        + ý nghĩa, thao tác, 
        + so sánh biến thường vs pointer (trên memory)
        + Bản chất 
            -> endian ?
            -> kích thước ?  
            -> kiểu dữ liệu ?  
            => ứng dụng endian ? 
        + tách byte 
            -> tách byte từ 1 số nguyên lưu vào các biến có kiểu nhỏ hơn
            => ứng dụng ? 
        + pointer vs array
            -> mối quan hệ ?
            -> pointer operator ? (cộng/trừ address)
            => Liên hệ embedded system (shortage memory -> optimization required)
        => Tóm tắt bải học
# POINTER VARIATION
__VOID POINTER__ 
    => khái niệm + ví dụ code 
        -> ép kiểu để đọc nhiều kiểu giá trị
        -> chốt lại sử dụng 1 mãng để truy cập dễ dàng hơn
__FUNCTION POINTER__
    => khái niệm + ví dụ code 
        -> cách định nghĩa ? cách sủ dụng ? (gán và gọi)
    => ví dụ tính tổng 
        -> cách 1 -> trỏ từng hàm 
        -> cách 2 -> dùng 1 hàm (truyền vào phép toán muốn thực hiện)
        -> cách 3:-> dùng mảng lưu trữ địa chỉ các hàm  
-__POINTER TO CONSTANT__
    =>  khái niệm + ví dụ code 
    <!-- 
        - con trỏ chỉ đọc , ko thay đổi giá trị
     -->
    => ứng dụng : bảo vệ vùng nhớ ko bị thay đổi 
__CONSTANT POINTER__
    =>  khái niệm + ví dụ code 
    <!-- 
        - Chỉ trỏ đến 1 địa chỉ , ko được thay đổi địa chỉ khác , có thế thay đổi giá trị 
     -->
    => ứng dụng : thiết kế thư viện MCU , lưu địa chỉ thanh ghi -> show tài liệu giải thích
__POINTER TO POINTER__

__NULL POINTER__
    => Khái niệm + code 
__DOUBLE POINTER__
    => khái niệm + code 
    => lái sang ứng dụng học ở các bài sau : json, danh sách liên kết linkest list
__CHỐT KIẾN THỨC__
    => Tổng kết nội dung
__BUBBLE SORT__