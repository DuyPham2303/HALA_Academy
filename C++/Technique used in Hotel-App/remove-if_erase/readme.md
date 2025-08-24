# remove_if
## Chức năng 
Di chuyển các phần tử không thỏa mãn điều kiện đến đầu container và trả về 1 iterator trỏ đến vị trí sau phần tử cuối cùng cần giữ lại
## Đặc điểm
+ Không thực sự xóa cá phần tử khỏi container mà chỉ thay đổi thứ tự các phần tử và __đánh dấu__ các phần tử không còn cần thiết ở cuối container 
+ Các phần tử sau iterator trả về bởi remove_if vẫn tồn tại nhưng không hợp lệ về logic 


