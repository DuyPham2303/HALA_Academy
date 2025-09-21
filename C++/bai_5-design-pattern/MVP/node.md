`ĐẶT VẤN ĐỀ`
- Các hệ thống tích hợp giao diện tương tác người dùng cần được triển khai theo hướng trừu tượng đi quá trình xử lý dữ liệu bên dưới của hệ thống, thông qua việc
    => cung cơ chế tương tác vả hiển thị dữ liệu phản hồi trên màn hình 
    => tách biệt giữa phần xử lý thuật toán và giao diện người dùng 
`PHƯƠNG PHÁP`
- Cơ chế MVP giúp triển khai luồng xử lý hệ thống 1 cách logic và linh hoạt trong việc vận chuyển và giao tiếp dữ liệu giữa DATABASE và UI
=> đảm bảo hệ thống phản hồi nhanh chóng để hiển thị lên màn hình với những tương tác từ người dùng

__các thành phần__

**Presenter** : cầu nối trung gian giữa UI và database -> cung cấp cơ ché xử lý logic để điều phối luồng giao tiếp dữ liệu 
**Model**     : Database 
**View**      : giao diện hiển thị của người dùng