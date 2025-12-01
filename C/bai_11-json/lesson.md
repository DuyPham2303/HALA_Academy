# 1. Giới thiệu về JSON
## 1.1 Bối cảnh thực tế - hệ thống IoT

<p align = "center">
<img width="750" height="400" alt="Image" src="https://github.com/user-attachments/assets/b8935b96-c4b8-4bb7-b6cd-8306ac83794e" />

### 1.1.1 Quy trình xử lý dữ liệu 
- Trong ngữ cảnh hệ thống điều khiển __Smart Home__ , ta có thể dễ dàng giám sát, tương tác, điều khiển trạng thái các thiết bị từ xa thông qua kết nối wifi trên 1 chiếc điện thoại chẳng hạn. Để làm được điều này 
  + Điện thoại cần phải đăng nhập vào 1 App và kết nối đến __web server__. Chính là máy chủ trung gian để truyền/nhận dữ liệu với các ngoại vi. 
  + Các thiết bị ngoại vi cũng cần dược kết nối đến 1 MCU có khả năng kết nối mạng như __esp8266__ để có đẩy dữ liệu lên __web server__.
  + Nói cách khác __web server__ chính là cầu nối trung gian để nhận dữ liệu từ MCU để __App__ trên điển thoại có thể hiển thi lên giao diện web 

### 1.1.2 Các thiết bị xử lý dữ liệu thế nào 
- Các thiết bị trong luồng xử lý dữ liệu qua mạng sẽ khác nhau
  
  + __MCU__ : Xử lý data truyền/nhận ở dạng binary
  
  + __Server__ : dùng kiểu Object, struct để xử lý data ở backend 
  
  + __App(web)__ : dùng javascript để xây dựng giao diện front end 

- Tóm lại MCU sẽ thường truyền từng byte dử liệu thô như sau `0x01 0x00 0x1F` . Chính vì vậy giao diện front end sẽ không thể hiểu được. Lúc này đây ta cần có 1 cơ chế để mã hóa dữ liệu thành 1 định dạng chung, dễ đọc, phân tách cho phép tất cả hệ thống có thể hiểu và xử lý được đó chính là json.

## 1.2 Tổng quan về Json

### 1.2.1 Json là gì 

- Đây là một định dạng lưu trữ dữ liệu dưới dạng một văn bản __text-based__ chứa các đặc điểm chính sau:
  + dữ liệu được tổ chức ở định là cặp __key-value__
  + Có định dạng, cấu trúc rõ ràng, dễ dàng nhận biết thậm chí với con người
  + dễ dàng parse - phân tách với ngôn ngữ C 

<p align = "center">
<img width="517" height="301" alt="Image" src="https://github.com/user-attachments/assets/eaf9e76a-647d-497d-87e7-035d930500cc" />

### 1.2.2 Tóm tắt các đặc điểm 

| Đặc điểm                 | Ý nghĩa                                     |
| ------------------------ | ------------------------------------------- |
| **Text-based**           | Là văn bản thuần túy → dễ debug, dễ ghi log |
| **Language-independent** | Không phụ thuộc ngôn ngữ lập trình          |
| **Lightweight**          | Nhẹ, nhỏ, phù hợp truyền qua network        |
| **Human-readable**       | Con người đọc dễ hơn XML                    |
| **Machine-friendly**     | JS parse JSON cực nhanh (`JSON.parse`)      |
| **Working Operation**    | Không có hành vi xử lý, chỉ lưu trữ         |
| **datatype**             | Lưu nhiều kiểu khác nhau cùng 1 lúc         |

### 1.2.3 Ứng dụng tổng quát 

<p align = "center">
<img width="706" height="407" alt="Image" src="https://github.com/user-attachments/assets/b533acf2-d3dd-4e60-b410-7c020b964181" />

- Giao tiếp trong hệ thống ioT (MCU -> cloud -> App)
- Lưu trữ cấu hình ứng dụng 
- Truyền dữ liệu qua mạng (MQTT,WebSocket)
- Lưu trữ cơ sở dữ liệu NoSQL (MongoDB)


## 1.2 Các định dạng JSON

## 1.2.1 đối tượng JSON
Json là 1 chuỗi chứa các dữ liệu được chuẩn hóa như sau :

__+ Object__ : tập hợp của các cặp key - value được ngăn cách bởi dấu phẩy

+ key: là 1 chuỗi
+ value: bất kỳ loại dữ liệu nào

__Ví dụ:__ : 1 định dạng json được viết dưới dạng 1 object là tập hợp các cặp key-value đặt trong dấu ngoặc nhọn {}

```bash
{ 
  "name": "John Doe",
  "age": 30,
  "city": "New York",
  "isStudent": false,
  "grades": [85, 90, 78]
}"
```

### 1.2.2 Mảng JSON

__+ array__: bên trong array có thể là bất kỳ dữ liệu nào
+ Định dạng: thường được đặt trong 2 dấu ngoặc [ ]

```bash
  [23,"hello world",[64,35,true"]]
```
+ 1 array cùng có thể chức các thành phần là Object với các object cũng được ngăn cách bởi dấu phẩy ,
```bash
[
  {
    "name": "John Doe",
    "age": 30,
    "city": "New York",
    "occupation": "Software Engineer",
    "isStudent": false
  },
  {
    "name": "Jane Smith",
    "age": null,
    "city": "Los Angeles",
    "contact": {
      "email": "jane.smith@example.com",
      "phone": "555-1234"
    }
  },
  {
    "name": "Bob Johnson",
    "age": 35,
    "city": "Chicago"
  }
]
```

### 1.2.3 So sánh với các cấu trúc dữ liệu

| Loại            | Bản chất          | Dùng khi                 |
| --------------- | ----------------- | ------------------------ |
| **Stack**       | Cấu trúc LIFO     | Undo, backtracking       |
| **Queue**       | Cấu trúc FIFO     | Task scheduling, buffer  |
| **Linked List** | Node liên kết     | Chèn/xóa nhanh           |
| **JSON**        | Định dạng văn bản | Truyền dữ liệu, cấu hình |

**Tóm lại** : Json là định dạng dùng để lưu trữ dữ liệu, và dữ liệu đó được xử lý như thế nào để đảm bảo các yếu tố về việc truyền/nhận hợp lý giữa các thiết bị sẽ do __stack / queue / linked list__ quyết định tùy vào các mục đích khác nhau


# 2. Thiết kế cấu trúc lưu trữ dữ liệu JSON

## 2.2 Liệt kê các kiểu dữ liệu có thể có 
- Ta cần biết rằng C compiler chỉ hiểu và phân tích được từng ký tự trong 1 chuỗi mà không tự hiểu được kiểu dữ liệu cụ thể của từng thành phần. Do đó ta cần tạo ta 1 enum để gán thủ công datatype tương ứng cho từng thành phần sau khi phân tích 
```c
  typedef enum {
    JSON_NULL,
    JSON_BOOLEAN,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT
} JsonType;
```
## 2.1 Cấu trúc tổng quát xử lý cho từng loại dữ liệu
- Dựa vào enum đã triẻn khai, ta xác định được datatype cho từng thành phần. Lúc này ta cần chỉ định rõ vị trí cụ thể sẽ lưu trữ chúng thông qua cấu trúc sau đây
  + __JsonType type__   : xác định kiểu json cụ thể 
  + __union Value__     : chỉ định rõ vị trí mà từng phần tử lưu trữ `(Mỗi thời điểm chỉ có 1 member của union được sử dụng)` 

```c
//cấu trúc lưu trữ dữ liệu sau khi phân tích từ json
typedef struct JsonValue {
    JsonType type;

    //tổ hợp chia sẻ vùng nhớ chung cho các member(biến) lưu trữ Json value (do value chỉ gán cho 1 member)
    union { 
        bool boolean;                   
        double number;
        char *string; 

        //cấu trúc lưu trữ cho mảng json
        struct {
            struct JsonValue *values; //con trỏ đệ quy trở lại JsonValue để xác định kiểu (type) và biến tương ứng để lưu trữ value 
            size_t count;             //đếm số lượng phần tử trong mảng
        } array;

        //cấu trúc lưu trữ cho đối tượng json
        struct {
            char **keys;              //mảng con trỏ lưu trữ các chuỗi key
            struct JsonValue *values; //con trỏ đệ quy trở lại JsonValue để xác định kiểu (type) và biến tương ứng để lưu trữ value 
            size_t count;             //đếm số lượng cặp key-value
        } object;
    } value;
}JsonValue;
```
### 2.1.1 Lưu ý về kiểu size_t

**Theo chuẩn C**

- Đây là kiểu chuẩn để biểu diễn kích thước và số lượng phần tử 
- Các hàm như `malloc`, `strlen` , `sizeof` , `memcpy`, `strncpy` đều làm việc với kích thước bộ nhớ, và dùng kiểu size_t làm chuẩn 

**Đây là kiểu unsigned - không âm**
- Phù hợp khi biểu diễn số lượng - luôn là số lớn hơn 0
- Tự động phù hợp với kiển trúc (32/64 - bit)


# 3. Ứng dụng trong lĩnh vực embedded
## 3.1 Truyền nhận dữ liệu cảm biến trong lĩnh vực IoT
<p align = "center">
<img src = "https://github.com/user-attachments/assets/603c06ae-5bb6-462a-bb4f-8735051bf7c6" width = "700" height = "300">

+ __Gửi dữ liệu__ : ta có thể sử dụng chuỗi json để lưu các thông tin về nhiệt độ và độ ẩm và gửi lên server để xử lý

+ __Cấu hình điều khiển__: chuỗi json có thể được gửi từ server về thiết bị chứa các thông tin về cấu hình cài đặt như nhiệt độ,thời gian tương ứng để bật tắt các thiết bị ngoại vi

## 3.2 So sánh với Struct 
__Quản lý memory__ :

+ struct sẽ cấp phát vùng nhớ cho tất cả các thành viên được định nghĩa 1 khi khai báo. vì vậy sẽ có 1 số trường hợp người dùng không muốn 1 số thành viên của struct, điều này sẽ gây lãng phí memory
+ Json hiệu quả hơn so với struct do chỉ chứa các trường định nghĩa chung về loại dữ liệu mà người dùng muốn cấu hình,chính vì vậy người dùng có thể nhập các dữ liệu cấu hình mong muốn mà không gây dư thừa memory 

| Tiêu chí                    | Struct                                               | JSON                                   |
| --------------------------- | ---------------------------------------------------- | -------------------------------------- |
| **Bản chất**                | Nhị phân (binary)                                    | Văn bản (text)                         |
| **Kích thước dữ liệu**      | Rất nhỏ, cố định                                     | Lớn hơn nhiều                          |
| **Tốc độ xử lý**            | Rất nhanh                                            | Chậm hơn vì cần parse/stringify        |
| **Tính linh hoạt**          | Cứng, phải rebuild khi thêm field                    | Linh hoạt, thêm trường không ảnh hưởng |
| **Tương thích đa ngôn ngữ** | Kém (chỉ dùng được trong C/C++/nhị phân cùng format) | Rất cao (JS, Python, Java, Go…)        |
| **Dễ debug**                | Khó (dạng byte)                                      | Rất dễ (đọc như văn bản)               |
| **Dùng cho truyền mạng**    | Thường dùng khi cần hiệu năng cực cao                | Thường dùng trong API, IoT, cloud      |
| **An toàn**                 | Dễ sai nếu lệch packing/alignment                    | Dữ liệu mô tả rõ ràng, ổn định         |


__Ứng dụng thực tế__:

+ struct sẽ phù hợp cho các ứng dụng có memory thấp, tốc độ xử lý nhanh chủ yếu là giữa thiết bị và ngoại vi và không yêu cầu về kết nối hay trao đổi dữ liệu qua mạng
+ json sẽ linh hoạt đối với ứng dụng yêu cầu trao đổi dữ liệu qua mạng

| Nên dùng Struct khi…        | Nên dùng JSON khi…           |
| --------------------------- | ---------------------------- |
| Cần tốc độ cao              | Cần đọc được dễ dàng         |
| Buffer nhỏ, RAM ít          | Làm Web / App / API          |
| Truyền qua UART / SPI / CAN | Truyền qua mạng (HTTP, MQTT) |
| Giao tiếp MCU ↔ MCU         | Giao tiếp MCU ↔ Cloud        |
| Dữ liệu cố định             | Dữ liệu thay đổi linh hoạt   |


    

    
