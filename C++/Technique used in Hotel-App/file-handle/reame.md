# Các chế độ mở file
Khi làm việc với file, bạn cần chỉ định chế độ mở file:
+ ios::in: Mở file để đọc.
+ ios::out: Mở file để ghi (xóa nội dung cũ).
+ ios::app: Mở file để ghi và thêm nội dung vào cuối file.
+ ios::binary: Mở file ở chế độ nhị phân.
+ ios::ate: Mở file và đưa con trỏ file đến cuối.
+ ios::trunc: Mở file và xóa nội dung cũ.
Bạn có thể kết hợp các chế độ với toán tử |.

ifstream::is_open(): Kiểm tra file đã mở chưa.
ifstream::eof(): Kiểm tra đã đọc đến cuối file chưa.