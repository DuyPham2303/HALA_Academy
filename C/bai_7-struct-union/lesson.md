# 1 Các khải niệm cơ bản 
- Kiểu dữ liệu do người dùng định nghĩa, cho phép nhóm nhiều biến thuộc nhiều kiểu khác nhau lại thành 1 kiểu dữ liêu mới để đại diện cho 1 thực thể (đối tượng cụ thể)

## 1.1 Tại sao cần có struct ? 
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
## 1.2 Khai báo và sử dụng 

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

**d) Tag name - tên tham chiếu**

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


# 2. Bản chất của struct so với biến thông thường 
## 2.1 Điểm giống 
- Biến struct cũng tương tự như 1 biến thông thường, nó chứa các đặc điểm
    + Identifier
    + chiếm bộ nhớ (có địa chỉ)
    + Có thể tạo mảng các struct
    + Có thể truyền truyền / trả về từ hàm 
## 2.2 Điểm khác 
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
    - Ví dụ sau đây sẽ chỉ rõ kết quả là 8 thay vì 5. Điều này do ảnh hưởng của khái niệm __Alignment - Padding__ sẽ được đề cập ở phần tiếp theo
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
## 2.3 Truyền struct vào hàm 
- Do ảnh hưởng của khái niệm Alignment nên
    + Struct Size >= total size struct member 
    + chính vì vậy nếu truyền kiểu `pass by value` sẽ chiếm bộ nhớ khá lớn trên Stack segment của RAM
    + Do vậy việc truyền kiểu `pass by reference` thường được thay thế để giảm thiểu tiêu tốn bộ nhớ stack

# 3 Struct Alignment Padding
## 3.1 Tối ưu bộ nhớ trong struct 
Cần biết rằng hệ thống nhúng thường có tài nguyên hạn chế, vì vậy nên việc sắp xếp và thiết kế struct hợp lý là cần thiết để đảm bảo __tăng hiệu suất__ truy xuất của CPU và __tránh lãng phí tài nguyên__ Để làm được điều đó cần hiểu rõ 2 thứ

 **a) Cách CPU truy xuất memory**
- CPU không truy xuất từng byte mà thường theo đơn vị truy cập tự nhiên là __natural unit__ 
- Mỗi vi xử lý có __độ rộng bus__ và __đơn vị truy cập tự nhiên__ (word) khác nhau. Khi truy cập dữ liệu không được căn chỉnh (misaligned access). CPU có thể cần nhiều __memory cycle__ để đọc đủ dữ liệu hoặc sinh lỗi.
- Do đó, việc sắp xếp dữ liệu sao cho phù hợp với __quy luật truy cập của CPU__ là rất quan trọng.

**b) Cách compiler sắp xếp phần tử trong struct**
- Compiler tự động chèn các khoảng đệm - padding, nhằm đảm bảo từng phần tử được căn chỉnh đúng theo yêu cầu của CPU.
- Cần hiểu được nguyên lý trên để tránh lãng phí bộ nhớ.

=> Tóm lại từ 2 khái niệm trên ta rút ra nguyên tắc khi làm việc với struct ta rút ra nguyên tắc : __Thứ tự và kiểu dữ liệu__ của các phần tử trong struct ảnh hưởng trực tiếp đến bộ nhớ, tốc độ truy cập của CPU

## 3.2 Các khái niệm liên quan đến cách thức CPU truy xuất bộ nhớ vật lý 
**Memory access cycle - chu kỳ truy cập bộ nhớ**
- Mô tả việc CPU thực hiện truy cập dữ liệu (load/store) trong 1 lần
- Trên stm32 ví dụ:
    + Mỗi lần load/store CPU sẽ lấy hoặc ghi tối đa 4 byte qua bus dữ liệu
    + Nếu dữ liệu lớn hơn 32-bit ví dụ uint64_t , CPU sẽ cần phải tốn 2 lần truy cập 4 byte 
**b) Bus width - độ rộng đường dữ liệu**
- Số bit mà CPU có thể truyền/nhận trong 1 chu kỳ bus 
- Là đơn vị dữ liệu mà CPU truy xuất vật lý (qua đường truyền)
- Các đặc điểm vật lý của CPU và Hệ thống bus
  
| Kiến trúc           | Bus width       | Ý nghĩa                    |
| ------------------- | --------------- | -------------------------- |
| 8-bit MCU (8051)    | 8 bit (1 byte)  | CPU đọc/ghi 1 byte mỗi lần |
| 16-bit MCU          | 16 bit (2 byte) | CPU đọc/ghi 2 byte mỗi lần |
| 32-bit ARM Cortex-M | 32 bit (4 byte) | CPU đọc/ghi 4 byte mỗi lần |
| 64-bit x86_64       | 64 bit (8 byte) | CPU đọc/ghi 8 byte mỗi lần |

=> Tóm lại Bus width = __độ rông ống nước__ giữa CPU và RAM, Ống cảng to, mỗi lần PU có thể __múc__ được nhiều dữ liệu 

**b) Natural Unit - đơn vị dữ liệu tự nhiên**
- Kích thước dữ liệu cơ bản mà CPU xử lý trong 1 lần thao tác ALU
- Là đơn vị dữ liệu mà CPU xử lý logic (qua thanh ghi)

| Kiểu dữ liệu | Lệnh CPU ví dụ     | Mô tả thao tác |
| ------------ | ------------------ | -------------- |
| `a`          | `MOVB AL, [addr]`  | đọc 1 byte     |
| `b`          | `MOVW AX, [addr]`  | đọc 2 byte     |
| `c`          | `MOVL EAX, [addr]` | đọc 4 byte     |
| `d`          | `MOVQ RAX, [addr]` | đọc 8 byte     |

__=> Tóm lại CPU có thể xử lý __bus 64-bit__, nhưng vẫn có thể thao tác trên nhiều kích thước khác nhau trong phạm vi độ rộng của bus__ 

**c) Natural alignment - Căn chỉnh tự nhiên**
- Quy tắc đặt dữ liệu trong bộ nhớ sao cho địa chỉ bắt đầu của nó chia hết cho kích thước của chính nó __(hoặc theo yêu cầu của CPU)__
- Mục tiêu là giúp CPU đọc __word__ của 1 dữ liệu hoàn chỉnh chỉ trong 1 chu kỳ
  
| Kiểu dữ liệu | Kích thước | Natural alignment | Hợp lệ khi địa chỉ chia hết cho… |
| ------------ | ---------- | ----------------- | -------------------------------- |
| `uint8_t`    | 1 byte     | 1 byte            | bất kỳ địa chỉ nào               |
| `uint16_t`   | 2 byte     | 2 byte            | 0x00, 0x02, 0x04, …              |
| `uint32_t`   | 4 byte     | 4 byte            | 0x00, 0x04, 0x08, …              |
| `uint64_t`   | 8 byte     | 8 byte            | 0x00, 0x08, 0x10, …              |

**d) Yêu cầu của CPU tác động lên alignment như thế nào ?**
- Alignment phụ thuộc vào kiến trúc của bộ vi xử lý 
    + __trên MCU__ : quyết định CPU xử lý bao nhiêu byte từ bộ nhớ phụ thuộc vào bus width (ví dụ trên ARM-CORTEX M4 xử lý được tối đa là 1 word = 4 byte) 
    + __trên PC__ : bus width tối đa truy cập được dựa trên 
        - x86 - 64 : 8-byte 
        - x86 - 32 : 4 byte
          
__=> Tóm lại trên MCU-32 bit, CPU chỉ đọc được 4 byte/lần khi truy xuất bus vật lý. Nhưng compiler vẫn cần căn chỉnh 8 byte cho kiểu 64-bit để tuân thủ quy tắc ABI, và tránh lỗi alignment. Khi truy xuất, CPU tốn 2 chu kỳ lệnh - memory cycle để đọc 4 byte. Nhưng địa chỉ bắt đầu của biến vẫn phải chia hết cho 8 để đảm bảo đúng chuẩn và tốc độ__

## 3.3 Minh họa thao tác của CPU trên bộ nhớ vật lý thực tế 

<p align = "center">
<img width="600" height="480" alt="Image" src="https://github.com/user-attachments/assets/1a6717a4-15a7-4fde-b8bf-88e534dcbc97" />

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

**a) Alignment diễn ra như thế nào ?**
- Các biến có kích thước n byte sẽ được đặt vào các ô nhớ ó địa chỉ chia hết cho n
    + Các số 4 byte được đặt vào Bank 0,1,2,3
    + Các số 2 byte được đật vào Bank 0,1 hoặc 2,3
    + Các số 1 byte được đặt ở bất kỳ Bank nào
    + Các số 8 byte (uint64_t,double) được đặt vào 2 Word

**b) Struct padding** 
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

# 4. Các vấn đề khi sắp xếp phần tử theo quy tắc alignment - padding và cách loại bỏ padding 
## 4.1 Bối cảnh 
- Việc săp xếp các phần tử như trên sẽ dẫn đến __Tốn bộ nhớ__ mặc dù tốc độ truy cập được tối ưu, nhưng gây phát sinh các byte dư thừa, gây tốn bộ nhớ
- 
## 4.2 Khái niệm struct packing 
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
**b)Trường hợp áp dụng việc loại bỏ padding**

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

## 5. Struct bit field 



