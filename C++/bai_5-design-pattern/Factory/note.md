
`ĐẶT VẤN ĐỀ` 
- triển khai 1 hệ thống tích hợp nhiều loại cảm biến, ứng với mỗi cảm biến sẽ cần class tương ứng để quản lý. Nếu vậy khi phát triển ứng dụng cho client sử dụng sẽ trở nên phức tạp 
=>` ko linh hoạt do cần đào sâu mã nguồn` :  Client cần hiểu rõ về class quản lý của từng cảm biến 
`GIẢI PHÁP`
- Cung cấp khởi tạo tổng quát cho phép ẩn đi quá trình khởi tạo các đối tượng của hệ thống
    => không cần quan tâm đến class cụ thể 
    => chỉ cung cấp các tham số khởi tạo gián tiếp.
    => dễ dàng trong việc sử dụng ứng dụng `(ko cần hiểu mã nguồn)`

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
`FACTORY METHOD : `cung cấp class khởi tạo tương ứng cho từng class con muốn quản lý
     __+ Các thành phần__
        **Product (Interface)**
            - Interface đại diện cho đối tượng tổng quát 
            - kế thừa bởi class con
            - chứa hành vi được class con triển khai cụ thể
        **concrete product**
            - class con cụ thể sẽ triển khai hành vi của Porduct
            - được khởi tạo gián tiếp qua Concrete creator
        **Creator (Interface)**
            - Interface chứa method khởi tạo các lớp con thông qua việc gọi Product
            - được kế thừa bởi các concrete creator 
            - method khởi tạo được triển khai cụ thể thông qua concrete creator 
        **concrete creator**
            - triển khai khởi tạo class con tương ứng bằng cách ghi đè method của Creator
            - trả về kiểu Product và tư động xác định class con sẽ trỏ đến 
    __+ Ưu điểm :__ 
        - Khó sử dụng 
        - thích hợp ứng dụng không xác định số lượng thực thể sẽ quản lý 
        - bổ sung thực thể mới thông qua class mới
    __+ nhược điểm :__
        - Tránh cần can thiệp/sửa đổi trực tiếp mã nguồn đã chạy ổn định
        - không thích hợp hệ thống lớn, thay đổi, nâng cấp theo thời gian

