
`ĐẶT VẤN ĐỀ` 
- triển khai 1 hệ thống tích hợp nhiều loại cảm biến, ứng với mỗi cảm biến sẽ cần 
1 class để quản lý. Nếu vậy khi phát triển ứng dụng cho client sử dụng sẽ trở nên 
phức tạp 
=> cần nắm được class tương ứng với cảm biến cần khởi tạo (không linh hoạt do client chỉ cần sử dụng mà không cần hiểu về mã nguồn)
- Factory design : cơ chế giúp ẩn đi quá trình khởi tạo các đối tượng (thực thể) của hệ thống mà không cần quan tâm đến class cụ thể, chỉ cung cấp các tham số khởi tạo gián tiếp. Từ đó giúp client dễ dàng trong việc sử dụng ứng dụng (ko cần hiểu mã nguồn)
- Chia làm 2 loại 
--------------------------------------------------------------------------------------------------------------
`SIMPLE FACTORY :` cung cấp lớp trung gian để ẩn đi quá trình gọi class chi tiết để khởi tạo đối tượng
    __+ Các thành phần__
        **Product(Interface class)** 
            - Lớp đại diện cho thực thể tổng quát 
            - chứa hành vi tổng quát (pure virtual) sẽ được triển khai cụ thể dựa trên các đối tượng lớp con 
            - cần được kế thừa bởi các class muốn khởi tạo gián tiếp
        **Factory(creational class)**
            - chứa hàm khởi tạo gián tiếp bằng cách trả về con trỏ tới interface class
            - hàm này khởi tạo đối tượng từ class tương ứng dựa trên logic xử lý và tham số truyền vào (chuỗi,biến enum)
            - class này không cần tạo object, chỉ cần gọi static method để khởi tạo các đối tượng class khác 
        **Concrete Product**
            - Các lớp con cụ thể được tạo ra từ Product (thông qua kế thừa)
    __+ Ưu điểm :__ 
        - dễ sử dụng 
        - thích hợp ứng dụng xác định số lượng thực thể cố định sẽ quản lý
        - bổ sung thực thể mới qua if-else
    __+ nhược điểm :__
        - cần can thiệp/sửa đổi trực tiếp mã nguồn ban đầu để thay đổi -> dễ gây lỗi
        - không thích hợp hệ thống lớn, thay đổi, nâng cấp theo thời gian
--------------------------------------------------------------------------------------------------------------
+ FACTORY METHOD : cung cấp class khởi tạo tương ứng cho từng class con muốn quản lý

