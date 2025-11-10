# 1 Struct - User Define Datatype 
## 1 Các khải niệm cơ bản 
- Kiểu dữ liệu do người dùng định nghĩa, cho phép nhóm nhiều biến thuộc nhiều kiểu khác nhau lại thành 1 kiểu dữ liêu mới để đại diện cho 1 thực thể (đối tượng cụ thể)


### 1.1 Tại sao cần có struct ? 
- Tưởng tượng ta cần quản lý các thông tin để mô tả của sinh viên như sau
```c
char name[30];
char phone[12];
int  mssv;
float gpa;
char major[20];
```
- Nếu giữ nguyên cách triển khai như trên thì việc quản lý thong tin của nhiều sinh viên sẽ khiến chương trình 
    + Phức tạp, khó quản lý, do nhiều biến rời rạc được tạo ra
    + thao tác truyền/nhận dữ liệu giữa hàm trở nên khó khăn (truyền từng biến)

__Giải pháp tối ưu là gộp tất cả các thông tin trên vào vị trí duy nhất để dễ dàng quản lý bằng cách sử dụng struct keyword__

### 1.2 Liên hệ thực tế trong hệ thống nhúng 
- Thông thường cần quản lý nhiều loại dữ liệu, tín hiệu từ các thực thể, đối tượng khác nhau ví dụ 

| Nhóm đối tượng | Ví dụ               | Đặc điểm                                                                      |
| -------------- | ------------------- | ----------------------------------------------------------------------------- |
| Sensor         | DHT11, HC-SR04, RTC | mỗi sensor có nhiều thông tin: giá trị đo, đơn vị, trạng thái kết nối...      |
| Protocol       | UART, SPI, I2C      | mỗi giao thức có thông tin: tốc độ baud, trạng thái truyền, buffer dữ liệu... |
| Actuator       | DC Motor, Servo     | mỗi thiết bị có thông tin: tốc độ, góc, trạng thái on/off...                  |

- Nếu chỉ dùng biến riêng lẻ, thì
    + mã nguồn trở nên rối rắm, khó mở rộng
    + Khó quản ý từng thiết bị độc lập 
- Chính vì vậy bằng cách dùng struct, ta có thể đóng gói và tổ chức nhiều thông tin riêng lẻ thành các đơn vị dữ liệu tổng quát tương ứng với từng thực thể

```c
typedef struct {
    float temperature;
    float humidity;
    uint8_t status;
} DHT11_t;
DHT11_t sensor1 ,sensor2;
```
DHT11_t sensor1, sensor2;
```
### 1.2 Khai báo và sử dụng 

**a) Tạo 1 kiểu struct** 

```c
struct structureName {
  dataType member1;
  dataType member2;

};
```
- Các thành phần bên trong struct có thể là 
    + biến thông thường, con trỏ 
    + mảng
    + một struct con,...(hoặc bất kỳ datatype nào khác)

**b) Sử dụng Struct**
- Khi tạo ra kiểu struct như dưới đây chỉ là 1 template, chưa phải là các biến (chưa được cấp phát địa chỉ thực tế để sử dụng)
```c
struct Sensor{
    int time;
    float temp;
    int humidity;
}
```
- Để sử dụng được cần phải thực hiện khai báo ra biến với kiểu struct được tạo ra như dưới đây

```c
struct Sensor data1;    //uninitialized data 
struct Sensor data2 = {.time = 12,.temp = 44,.humidity = 14}; //initialized data 
struct Sensor data3 = {12,35,21}; //initialized data 
struct Sensor data4 = {.time = 21,.humidity = 21} //temp = 0 (default)
```
**c) typedef keyword**
- Ở cách khai báo trên, có thể thấy nó khiến cho code trở nên dài dòng, và mất thời gian viết code. Do đó ta có thể rút gọn cách khai báo bằng cách sau 

```c
typedef struct {
  int time;
  float temp;
  int humidity;
} Sensor_t;    // Create Data Type

// Create Variable
Sensor_t Data = { .time = 1, .temp = 30.5, .humidity = 40 };
```
`Note:` các kiểu struct được tạo ra nên được thêm đuôi `_t` hoặc `Type` để đánh dấu đây là 1 kiểu dữ liệu (ví dụ thư viên __stdint.h__)

**d) *Tag name - tên tham chiếu**

__Ý NGHĨA__

- Khi khai báo 1 struct, ta có thể đặt __tag name__ tức là tên định danh, mà ta có thể dùng lại sau này để tham chiều đến kiểu struct đó.

```c
struct Student{
    char name[20];
    int id;
}
```
Với: 
    + Student là `tag name`
    + kiểu struct đầy đủ `struct Student`

- Nếu không có `tag name`, nên để sử dụng được cần thông qua alias  `Student` được tạo bởi typedef 
```c
typedef struct {
    char name[30];
    int id;
} Student;
```

__DÙNG KHI NÀO ?__

+ Trường hợp trong struct có chứa member trỏ đến chính kiểu của nó - ví dụ linked list

```c
struct Node {
    int data;
    struct Node *next;
};
```
+ Struct Node ở trong ? : vì ở dòng khai báo `next` , kiểu `struct Node` chưa hoàn chỉnh, nên cần khai báo con trỏ tới chính nó - chứ không thể khai báo kiểu `Struct Node`
+ Khi compiler đọc đến dòng đầu -> tạo ra tên định danh là `Node` chưa đầy đủ 
+ Khi compiler đọc đến dòng (struct Node *next;),  biết rằng có một kiểu tên Node tồn tại, nên cho phép khai báo con trỏ tới kiểu này, dù struct chưa hoàn chỉnh 


## 2. Bản chất của struct so với biến thông thường 
### 2.1 Điểm giống 
- Biến struct cũng tương tự như 1 biến thông thường, nó chứa các đặc điểm
    + Identifier
    + chiếm bộ nhớ (có địa chỉ)
    + Có thể tạo mảng các struct
    + Có thể truyền truyền / trả về từ hàm 
### 2.2 Điểm khác 
- Truy xuất member struct với 
    - toán từ `.` đối với member là biến thường 
    - toán tử `->` đối với member là con trỏ 
```c
Sensor_t data1;
Sensor data_2;

data1.time = 21;
data2->time = 32; //hoặc (*data2).time = 32
```
- Kích thước của struct  
    - Đối với logic thông thường sẽ là total size của toàn bộ struct member. Tuy nhiên thực tế thì khác 
    - Ví dụ sau đây sẽ chỉ rõ kết quả là 8 thay vì 5. Điều này do ảnh hưởng của khái niệm __Alignmwnt - Padding__ sẽ được đề cập ở phần tiếp theo

```c
typedef struct {
    uint8_t   A;
    uint32_t  B;
} TestType;

int main() {
  printf("Size of TestType: %d", sizeof(TestType));     // 8
  return 0;
}
```

### 2.3 Truyền struct vào hàm 
- Do ảnh hưởng của khái niệm Alignment nên
    + Struct Size >= total size struct member 
    + chính vì vậy nếu truyền kiểu `pass by value` sẽ chiếm bộ nhớ khá lớn trên Stack segment của RAM
    + Do vậy việc truyền kiểu `pass by reference` thường được thay thế để giảm thiểu tiêu tốn bộ nhớ stack

## 3 Struct Alignment Padding

### 3.1 Vấn đề khi làm việc với struct 
- Ta cần quan tâm đến việc tối ưu bộ nhớ khi quản lý các member được khai báo bên trong struct để tránh lãng phí tài nguyên hệ thống __(có hạn đối với embedded system)__ , 
- Điều này liên quan đến cách sắp xếp các phần tử của struct 

### 3.2 Cách thức truy cập bộ nhớ của CPU 
- Khi làm việc với struct, CPU không đọc từng biến một, mà đọc theo đơn vị truy cập tự nhiên `natural unit`
    + __Natural unit__ : là kích thước dữ liệu mà CPU xử lý hiệu quả nhất trong một lần đọc hoặc ghi.
- Cách CPU truy cập bộ nhớ vật lý phụ thuộc vào memory cycle và bus width 
    + __memory cycle__ - chu kỳ máy `: số lần CPU / bus phải đọc từ RAM để lấy đủ dữ liệu 
    + __Bus width - độ rộng bus__ : số bit dữ liệu mà nó thể đọc/ghi trong 1 lần truy xuất (ví dụ 32-bit => 4 byte/cycle)

### 2.3 Khái niệm Data Alignment trên Memory

**a) Alignment là gì ?**
- Khái niệm liên quan đến yêu cầu căn chỉnh đối với tất cả kiểu dữ liệu, bằng cách cấp phát vùng nhớ lưu trữ các member tại các giá trị địa chỉ chia hết cho datatype của chính nó. Nhằm đảm bảo tối ưu tốc dộ truy cập. Để hiểu được điều này cần xem xét phần triển khai hinh họa bên dưới 

**b) Tại sao cần có Alignment ?**
- Alignment phụ thuộc vào kiến trúc của bộ vi xử lý 
    + __trên MCU__ : quyết định CPU xử lý được độ rộng của 1 hay nhiều word phụ thuộc vào kích thước của bus dữ liệu (ví dụ trên ARM-CORTEX M4 xử lý được tối đa là 1 word - 4 byte) 
    + __trên PC__ : bus width tối đa truy cập được dựa trên 
        - x86 - 64 : 8-byte 
        - x86 - 32 : 4 byte
<p align = "center">
<img width="550" height="450" alt="Image" src="https://github.com/user-attachments/assets/1a6717a4-15a7-4fde-b8bf-88e534dcbc97" />

**Banked Memory** Bộ nhớ được chia thành các vùng lưu trữ dữ liệu riêng biệt, và song song với nhau  

- Ảnh hưởng của việc đặt 1 word = 4 byte có thể thấy đó là 
    + truy xuất đến bộ nhớ nhanh hơn
    + 1 memory cycle lấy được 4 thay vì 1 byte

__=> Do đó CPU sẽ lấy dữ liệu 4 byte/ chu kỳ__ 

- Ví dụ ta có 1 struct như dưới đây, và khi các member được cấp phát địa chỉ để lưu trữ thì theo logic thông thường 
    + biến a có thể được đặt tại bank 0 
    + biến b có thể được đặt liền kề ở các bank kế tiếp

```c
typedef struct{
    uint8_t a;
    uint32_t b;
}data;
```
__=> Dẫn đến việc truy xuất đến b có thể tốn 2 memory cycle, vì vậy yêu cầu các member cần được căn chỉnh để đảm bảo CPU có thể tối ưu tốc độ truy xuất__

<p align = "center">
<img width="700" height="400" alt="Image" src="https://github.com/user-attachments/assets/10840370-2d74-4709-8373-d807375bf931" />

**c) Alignment diễn ra như thế nào ?**
- Các biến có kích thước n byte sẽ được đặt vào các ô nhớ ó địa chỉ chia hết cho n
    + Các số 4 byte được đặt vào Bank 0,1,2,3
    + Các số 2 byte được đật vào Bank 0,1 hoặc 2,3
    + Các số 1 byte được đặt ở bất kỳ Bank nào
    + Các số 8 byte (uint64_t,double) được đặt vào 2 Word

**d) Struct padding** 
- Khái niệm này đề cập đến việc bổ sung các byte đệm (trống) để đảm bảo cấu trúc alignment

```c
typedef struct{
    uint8_t a;
    uint32_t b;
}data;
```

- Nếu không tuân theo alignment Việc truy xuất B tốn 2 cycle, khiến tốc độ thực thi chương trình bị chậm 

<p align = "center">
<img width="700" height="400" alt="Image" src="https://github.com/user-attachments/assets/260d6398-580c-40c4-8ec9-88bc9180d276" />

- Vì vậy theo alignment tự nhiên thì bộ nhớ sẽ được sắp xếp như sau

<p align = "center">
<img width="700" height="400" alt="Image" src="https://github.com/user-attachments/assets/59ee3542-05a1-49db-8c34-f1bf2ddda993" />

- Do đó padding byte có đặc điểm
    + là các byte trống được thêm vào để căn chỉnh các phần tử 
    + giúp giảm thiểu số chu kỳ đọc của CPU khi truy cập struct member

### 2.4 Vấn đề với padding byte
- Việc săp xếp các phần tử nhu trên sẽ có 1 vài rủi ro
    + __Tốn bộ nhớ :__ mặc dù tốc độ truy cập được tối ưu, nhưng gây phát sinh các byte dư thừa, gây tốn bộ nhớ

    + __Sai lệch khi truyền/nhận dữ liệu :__ Khi cần truyền qua chuẩn truyền thông, dữ liệu sẽ truyền theo từng byte, Nếu 2 bên không thống nhất về Alignment có thể dẫn đến dữ liệu bị nhận sai
    
__Ví dụ STM32F4 và PC giao tiếp qua UART, cần truyền struct data__

    + STM32F4 : có Alignment tự nhiên là 4 byte -> sizeof(Sensor) = 12 bytes
    + PC (x86): có Alignment tự nhiên là 8 byte -> sizeof(Sensor) -> 16 bytes
```c
typedef struct {
    uint8_t   A;
    uint64_t  B;
}data;
```

__=> Dẫn đến nếu truyền dữ liệu từ STM32F4 sang PC hoặc ngược lại thì số byte sẽ bị lệch (thiếu byte)__

### 2.5 Khái niệm struct packing 
- Trong một số trường hợp ta sẽ cần tránh Alignment - padding như kể trên. Chính vì vậy hầu hết các compiler đều hỗ trợ tiện ích để tắt phần padding măc định 

- Các chỉ thiện biên dịch sau đây dùng để kiểm soát việc căn chỉnh và bỏ byte padding trong struct 

**a) Pragma pack**

- Dùng để điều chỉnh alignment tối đa cho struct 
- Yêu cầu compiler giới hạn alignment tối đa của tất cả struct sau dòng này là n byte __(với n là kết quả giá trị số mũ của 2)__

```c
#pragma pack(n)
```

vÍ dụ : n = 1 thì các struct được khai báo sẽ chỉ căn chỉnh theo từng byte - không có padding 

- cách khác tương tự việc loại bỏ hoàn toàn padding, dẫn đến các member được cấp phát địa chỉ liền kể nhau mà không có padding byte 
```c
struct name {
    ...
} __attribute__((packed));
```

**b) Cú pháp nâng cao puch/pop**
....

**c) Trường hợp áp dụng việc loại bỏ padding**

`Lưu ý sử dụng thưc tế`

| Ưu điểm                                                                       | Nhược điểm                                                                                  |
| ----------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------- |
| Giảm kích thước struct                                                        | CPU có thể truy cập chậm hơn do không đúng alignment tự nhiên                               |
| Hữu ích khi đóng gói dữ liệu gửi/nhận qua UART, CAN, SPI, file nhị phân, v.v. | Một số vi điều khiển (như ARM Cortex-M0) có thể **lỗi bus** nếu truy cập dữ liệu misaligned |
| Đồng bộ định dạng giữa các hệ thống (ví dụ giữa MCU và PC)                    | Không nên dùng cho dữ liệu xử lý thường xuyên trong CPU                                     |

`Trường hợp ứng dụng`

| Trường hợp                                                        | Nên dùng | Không nên dùng |
| ----------------------------------------------------------------- | -------- | -------------- |
| Truyền dữ liệu nhị phân giữa 2 thiết bị (ví dụ UART, CAN, Modbus) | ✅        |                |
| Lưu trữ cấu trúc vào file nhị phân (firmware, EEPROM, flash)      | ✅        |                |
| Xử lý nội bộ trong RAM (các biến tính toán thường xuyên)          |          | ❌              |





## 3. Struct bit field 

# 2. Union 
## 1 Khái niệm 
## 2 Thao tác với struct 
## 3 Vấn đề trong struct 
## 4 Ứng dụng thực tế 

# 4 So sánh struct và union

