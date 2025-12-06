# 1. Tổng quan về Pointer
## 1.1 Khái niệm
- Biến dùng để lưu trữ giá trị là địa chỉ của 1 đối tượng (biến thông thường, con trỏ, hàm, mảng)
- Sử dụng khi cần thao truy cập đọc/ghi, thao tác trên nhiều vùng nhớ một cách linh hoạt, nhanh chóng, tối ưu

<p align = "center">
<img width="550" height="350" alt="Image" src="https://github.com/user-attachments/assets/58b43943-3851-4847-a917-70c7e60703c7" />


## 1.2 Bản chất lưu trữ (RAM, Address, giá trị)

<p align = "center">
<img width="7550" height="350" alt="Image" src="https://github.com/user-attachments/assets/531425a3-7514-479d-95eb-6ba981f58b9b" />

### 1.2.1 Địa chỉ và giá trị trong bộ nhớ
- Biến lưu trên RAM có đặc điểm
  + Lưu trong một vùng nhớ chứa địa chỉ cấp phát liền kề
  + biến int chiếm 4 byte cần 4 ô địa chỉ kế tiếp nhau
  + Máy tính chỉ làm việc với byte, nên dù bất kỳ kiểu nào (int,float,double), đều được chia nhỏ thành từng byte để lưu ở 1 giá trị địa chỉ
  + Giá trị ở dạng decimal được chuyển đổi thành hệ binary hoặc Hex khi lưu trữ (ví dụ : decimal (10) -> 0b1010 hoặc 0x0A)

### 1.2.2 MSB & LSB
- Quy định vị trí byte cao/thấp nhất của 1 dữ liệu nhiều byte
  + `MSB` : Byte có trọng số cao nhất  (bên trái ngoài cùng)
  + `LSB` : Byte có trọng số thấp nhất (bên phải ngoài cùng)
  + Ví dụ : int a = 10 thì LSB biểu diễn 0x0A. Tùy theo cách sắp xếp byte trên RAM 0x0A có thể nằm ở low/high address __(Khái niệm về endian)__

### 1.2.3 Con trỏ luu trên RAM
- Đặc điểm
  + có địa chỉ của riêng nó
  + mỗi ô địa chỉ chứa 1 byte địa chỉ của đối tượng mà nó trỏ đến
  + được cấp phát 4 hoặc 8 byte __(tùy theo kiến trúc máy tính / MCU)__

## 1.3 Endianess
### 1.3.1 Khái niệm
Khái niệm để mô tả thứ tự sắp xếp các byte của 1 dữ liệu nhiều byte ở các vùng địa chỉ được cấp phát trên bộ RAM. Được chia làm 2 loại là big và little endian 

<p align = "center">
<img width="550" height="350" alt="Image" src="https://github.com/user-attachments/assets/440efc8a-3f00-487a-abd7-5ff8ab67f989" />

`Ví dụ` : kiểm tra kiến trúc máy tính chạy kiểu endian nào dựa trên đoạn code sau 

```c
int main() { 
  //khai báo số nguyên 4 byte -> gán giá trị hex -> chiếm 4 byte liên tiếp
  unsigned int x = 0x12345678; 
  //ép kiểu để đồng bộ với kiểu con trỏ 
  //cho phép con trỏ đọc từng byte -> đọc lần lượt từng byte
  unsigned char *p = (unsigned char *)&x; 
  printf("Byte[0] = %02X\n", p[0]); 
  printf("Byte[1] = %02X\n", p[1]); 
  printf("Byte[2] = %02X\n", p[2]);
  printf("Byte[3] = %02X\n", p[3]); 
  return 0; }
```

__Lưu ý__ : Ép kiểu con trỏ không thay đổi kiểu dữ liệu của biến ban đầu, nó chỉ thay đổi cách nhìn để truy cập đọc/ghi dữ liệu thông qua con trỏ 

__Tóm tắt__: Kiểu endian phụ thuộc vào kiến trúc CPU và ảnh hưởng đến cách ta thao tác với dữ liệu khi giao tiếp các hệ thống khác nhau như (MCU - Sensor) hay truyền thông mạng (Networking)

### 1.3.2 Ứng dụng 
Trong thực tế, Endianess sẽ ảnh hưởng trực tiếp đến cách dữ liệu được truyền giữa các thiết bị có nền tảng CPU khác nhau.


**a) GIAO TIẾP SENSOR - MC - PC**

<p align = "center">
<img width="450" height="200" alt="Image" src="https://github.com/user-attachments/assets/f7644535-9d44-4351-8d53-2d4723cd3550" />

Trong hệ thống nhúng, dữ liệu được truyền dựa trên sơ đồ như trên và mỗi thành phần có thể sử dụng các kiến trúc CPU khác nhau. Ví dụ
  + Sensor có thể dùng chip ARM (little endian)
  + PC dùng intel x86 (little endian)
  + Các thiết bị điều khiển / gateway (big endian)

=> Chính vì vậy nếu bên gửi __(big endian)__ là "12 45 56 78" , thì bên nhận ___(little endian)__ có thể đọc ngược thứ tự byte __(nếu không chuyển đổi)__ . Dẫn đến sai dữ liệu nhận về

```c
uint16_t swap_endian(uint16_t val) {
    return (val << 8) | (val >> 8);
}
```

**GIAO TIẾP MẠNGg**

<p align = "center">
<img width="450" eight="200" alt="Image" src="https://github.com/user-attachments/assets/ce1bc092-957b-41a1-913c-2756940e3ed9" />


Trong mạng máy tính (TCP/IP) có đặc điểm
  + các dữ liệu truyền thông luôn tuân theo chuẩn Networking Byte Order - Big Endian 
  + đảm bảo mọi hệ thống đều chia sẻ chung 1 ngôn ngữ, dù bên gửi / nhận dùng little/big 

```c
uint32_t sensorData = 0x12345678;
uint32_t netData = htonl(sensorData);  // chuyển sang Network Byte Order
send(socket, &netData, sizeof(netData), 0);


```
## 1.4 Kích thước và kiểu dữ liệu 

### 1.4.1 Kích thước con trỏ
- Có các đặc điểm
  + Không phụ thuộc vào datatype của nó
  + phụ thuộc vào kiến trúc CPU (32 / 64 - bit) hoặc bộ vi xử lý 
    + trên x86-64 : 8 byte 
    + trên x86-32 : 4 byte
    + trên ARM cortex-M (32 bit) : 4 byte
  + phụ thuộc vào compiler : dù hệ thống chạy x86-64, nhưng compiler được cấu hình là 32-bit (msys32 hoặc gcc -m32) thì kích thước vẫn là 4 byte 

`Ví dụ` : kiểm tra kích thước con trỏ 

```c
#include <stdio.h>
#include <stdbool.h>
int main(){
    printf("%d bytes\n",sizeof(char*));
    printf("%d bytes\n",sizeof(int*));
    printf("%d bytes\n",sizeof(short*));
    printf("%d bytes\n",sizeof(float*));
    printf("%d bytes\n",sizeof(double*));
    printf("%d bytes\n",sizeof(long*));
    printf("%d bytes\n",sizeof(long long*));
    printf("%d bytes\n",sizeof(bool*));
    return 0;
}
```

__Tóm tắt__ : kích thước của con trỏ trên PC trên thực tế phụ thuộc vào mô hình biên dịch chứ không chỉ CPU

### 1.4.2 Kiểu dữ liệu và Pointer Arithmetic
- Kiểu dữ liệu con trỏ quy định 
  + số lượng byte mà nó được phép truy xuất đọc/ghi
  + Bước nhảy của con trỏ khi thao tác ++/-- 
  + ví dụ : p1 += 3 tương ứng với bước nhảy là 3 đơn vị * sizeof(int)
```c
int *p1;   // đọc/ghi 4 byte tại địa chỉ p1
char *p2;  // đọc/ghi 1 byte tại địa chỉ p2
double *p3;// đọc/ghi 8 byte tại địa chỉ p3
```
- Pointer Arithmetic 
  + là các phép toán tăng/giảm địa chỉ (p++,p--)
  + dùng để thay đổi giá trị của con trỏ
  + con trỏ dịch chuyển qua vùng nhớ với bước nhảy tương ứng với datatype mà nó trỏ tới



**Tách byte sử dụng con trỏ**

```bash
#include<stdio.h>
#include<stdint.h>
void tach_byte(){
    uint16_t sum = 0xabcd;
    uint8_t* px = (uint8_t*)&sum; 
    uint8_t bit_low = *px;
    uint8_t bit_high = *(px + 1);
    printf("2 bit cao: 0x%x\n 2 bit thap: 0x%x",bit_high,bit_low);
}
int main(){
    tach_byte();
    return 0;
}
```

## 1.5 Con trỏ và mảng

<p align = "center">
<img width="400" height="350" alt="Image" src="https://github.com/user-attachments/assets/c6d0ae3b-d2ba-4ded-a74c-8014323ba2f3" />

### 1.4.1 Bối cảnh
Khi làm việc với dữ liệu lớn ví dụ như buffer chứa nhiều phần tử 
  + giao tiếp buffer trong truyền/nhận UART
  + Mảng ký tự chuỗi

=> Cần cơ chế để duyệt qua hay nói cách khác là truy cập đọc/ghi từng phần tử nhanh chóng và hiệu quả, chứ không cần khai báo nhiều biến (tốn memory) đó chính là con trỏ

| Thành phần                        | Vai trò                                    | Lưu ý                                               |
| --------------------------------- | ------------------------------------------ | --------------------------------------------------- |
| `int arr[3] = {10, 20, 30};`      | Mảng gồm 3 phần tử `int`                   | `arr` là tên mảng, không phải biến con trỏ thực thụ |
| `int *ptr = arr;`                 | Con trỏ trỏ đến phần tử đầu tiên của `arr` | `ptr` có thể di chuyển (`ptr++`)                    |
| `arr[i]` tương đương `*(arr + i)` | Truy xuất giá trị tại chỉ số `i`           | Dựa vào **pointer arithmetic**                      |

**ý khi thao tác với con trỏ trên mảng**
  + khi truyền tên mảng vào hàm chính là truyền địa chỉ của phần tử đầu mảng
  + dữ liệu trong hàm có thể thay đổi mảng gốc thông qua tham số con trỏ trỏ đến địa chỉ của mảng truyền vào

## 1.5.2 Ứng dụng và ưu điểm 

| Ứng dụng                   | Giải thích                                                          |
| -------------------------- | ------------------------------------------------------------------- |
| **Buffer UART / ADC**      | Mảng chứa dữ liệu, con trỏ duyệt từng byte nhận được                |
| **Truyền dữ liệu qua hàm** | Truyền con trỏ mảng thay vì toàn bộ mảng giúp tiết kiệm RAM         |
| **DMA hoặc ISR**           | DMA cần địa chỉ bắt đầu của vùng dữ liệu → con trỏ trỏ đến `arr[0]` |


# 2. Các loại con trỏ 
## 2.1 Con trỏ vô định - Void Pointer
### 2.1.1 Khái niệm và sử dụng
- Con trỏ không có kiểu xác định
  + có thể trỏ đến địa chỉ bất kỳ biến nào
  + Nếu muốn truy cập biến đang trỏ tới cần ép về kiểu dữ liệu gốc
  + Ứng dụng thao tác trên nhiều loại dữ liệu khác nhau mà không muốn tạo nhiều con trỏ riêng biệt
  + `(datatype*)ptr` : thao tác ép kiểu để biết cần đọc bao nhiêu byte __(vì compiler không biết kích thước dữ liệu gốc)__

```c
//thay vì làm như sau 
int *pInt;
double *pDouble;
char *pChar;

//ta chỉ cần
void* ptr; //thao tác trên bất kỳ biến nào 
``` 

### 2.1.2 Các ví dụ
**a) Truy cập nhiều biến** 
```c
void *ptr;
int a = 10;
double b = 3.14;
char c = 'X';

ptr = &a;
printf("%d\n", *(int*)ptr);    // Ép kiểu sang int*

ptr = &b;
printf("%.2f\n", *(double*)ptr); // Ép kiểu sang double*

ptr = &c;
printf("%c\n", *(char*)ptr);   // Ép kiểu sang char*

```

**b) Truy cập thông qua mảng con trỏ void**
```c
int a = 12;
char b = 's';
float c = 12.32;
double d = 122333.12;
char* str = "hello  world"; //'\0'

void* ptr[] = {&a,&b,&c,&d,str};

printf("a = %d\n", *(int *)ptr[0]);
printf("b = %c\n", *(char *)ptr[1]);
printf("c = %.2f\n", *(float *)ptr[2]);
printf("a = %lf\n", *(double *)ptr[3]);
printf("str = %s\n",(char*)ptr[4]); //in toàn bộ chuỗi

//in từng ký tự của phần tử chuội 
for(int i = 0 ; i < sizeof(str) ; i++){
      printf("str[%d] = %c\n",i,*((char*)ptr[4] + i));
}
```

**c) Truy cập mảng con trỏ đến các chuỗi ký tự bằng con trỏ void**

```c
char* pstr[] = {"hello","world","my name","is Duy"};

//số lượng phần tử của pstr
printf("size of pstr : %d\n",sizeof(pstr));

//in ra rừng phần tử của pstr
for(int i = 0 ; i < sizeof(pstr) / sizeof(pstr[0]); i++){
    printf("str[%d] : %s\n",i,pstr[i]);
}

//độ dài của phần tử chuỗi ở index = 2
int len = strlen(pstr[2]); 

//in ra từng ký tự của phần tử chuỗi
for(int i = 0 ; i < len  ; i++){
    printf("%c",*(pstr[2] + i));
}
```

### 2.1.3 Tóm tắt chức năng và ứng dụng thực tế

**a) Ưu điểm**

- Tái sử dụng con trỏ cho nhiều kiểu 
- Tổng quát hóa và rút gọn mã nguồn
- Đơn giản hóa thiết kế (ví dụ : hàm xử lý đa kiểu dữ liệu - `Generic function`)

**b) Nhược điểm**

- Cần ép kiểu thủ công để truy cập đọc/ghi chính xác
- Không thể áp dụng phép toán tăng/giảm hoặc dereference nếu chưa ép kiểu
- Gây lỗi nếu ép sai kiểu

**c) Ứng dụng thực tế**

Trong hệ thống nhúng thực tế sử dụng nhiều cấu trúc dữ liệu khác nhau như (Linked list,Stack,Queue) - Tổng quát. Do đó void* giúp lưu trữ đĩa chỉ của mọi loại dữ liệu trong cùng 1 container 

```c
void printValue(void *ptr, int type) {
    switch(type) {
        case 0: printf("int: %d\n", *(int*)ptr); break;
        case 1: printf("double: %.2f\n", *(double*)ptr); break;
        case 2: printf("char: %c\n", *(char*)ptr); break;
    }
}
```

## 2.2 Con trỏ Null - Null Pointer

### 2.2.1 Khái niệm & bối cảnh
- Là con trò không trỏ đến bất kỳ vùng nhớ hợp lệ nào
- Khi khai báo pointer mà chưa gán address cụ thể thì
  + có thể chứa giá trị rác
  + hoặc trỏ vùng nhớ random
  + nếu cố tình truy cập đọc/ghi, dẫn đến
    + gây lỗi segmentation fault (trên PC sẽ tự kích hoạt cảnh báo)
    + hoặc ghi đè dữ liệu ngẫu nhiên trên MCU (Không có cơ chế bảo vệ memory)

- Giải pháp gán NULL ngay khi khởi tạo nếu chưa sử dụng ngay giúp
  + dễ kiểm tra có hợp lệ không trước khi dùng
  + tránh lỗi `trỏ rác` khi chương trình chạy runtime

```c
int* ptr = NULL;
```

### 2.2.2 Ví dụ minh họa

**a) Trường hợp truy cập con trỏ chưa khởi tạo**
- Trong hệ thống nhúng, 
    + nếu thực hiện dereference *ptr , có thể tro MCU hoặc reset watchdog
    + do không có Os bảo vệ mem, lỗi Null pointer có thể gây hỏng dữ liệu toàn bộ hệ thống
```c
#include <stdio.h>


void sensor_read()
{
    int *data;          // chưa khởi tạo
    *data = 50;         // ❌ lỗi nghiêm trọng: ghi vào vùng nhớ ngẫu nhiên
}
```

**b) Gán Null và kiểm tra trước khi dùng**

```c
#include <stdio.h>

void sensor_read()
{
    int *data = NULL;

    if (data == NULL)
    {
        // chưa có vùng nhớ -> cấp phát hoặc báo lỗi
        static int sensor_cache = 0;
        data = &sensor_cache;
    }

    *data = 50;  // an toàn, có địa chỉ hợp lệ
}
```

### 2.2.3 Tóm tắt chức năng và ứng dụng thực tế

**a) Vấn đề - giải pháp**
- `Uninitialized pointer` 
   + trỏ ngẫu nhiên gây lỗi bộ nhớ 
   + Khắc phục ? gán NULL khi khai báo
- `Truy xuất NULL `
  + gây crash / reset hệ thống 
  + khắc phục ? kiểm tra if(ptr != NULL) trước khi dùng
- `Embedded không bảo vệ RAM`
 + hỏng dữ liệu -> reset watchdog
 + khắc phục ? luôn khởi tạo và kiểm tra con trỏ hợp lệ 

**b) Ứng dụng thực tế**

- `Driver layer` : khi trỏ tới DMA buffer / hardware reg cần được kiệm tra trước khi truy xuất
- `RTOS task` : nếu NULL truyền nhầm vào hàm , nên có logic kiểm tra để tránh crash task

## 2.3 Con trỏ đến hằng - Pointer to Const  

### 2.3.1 Khái niệm 
Con trỏ đến dữ liệu hằng có các đặc điểm
- Không được phép thay đổi giá trị 
- Có thể đổi hướng con trỏ đến vùng nhớ khác 

```c
int a = 10, b = 20;
const int *ptr = &a; // ptr trỏ đến a (giá trị 10)
*ptr = 15;   // ❌ Lỗi – không được phép thay đổi dữ liệu qua ptr
ptr = &b;    // ✅ Hợp lệ – ptr có thể trỏ sang b
```
**Note** : Không phải con trỏ là hằng mà giá trị mà nó trỏ tới là hằng 

### 2.3.2 Ứng dụng
Áp dụng
- Đọc dữ liệu an toàn - ko cho phép ghi
- Ví dụ : đọc giá trị từ thanh ghi IDR - Input Data Register 

```c
const uint32_t *pIDR = (uint32_t *)0x48000010; // Địa chỉ thanh ghi chỉ đọc GPIO
uint32_t value = *pIDR; // chỉ đọc, không ghi
```

| Tình huống                | Khai báo                              | Mục đích                                   |
| ------------------------- | ------------------------------------- | ------------------------------------------ |
| Đọc giá trị cảm biến      | `const volatile uint32_t *pSensor`    | Giá trị thay đổi do cảm biến, code chỉ đọc |
| Ghi điều khiển actuator   | `volatile uint32_t * const pActuator` | Ghi giá trị ra thanh ghi cố định           |
| Cấu hình tham số hệ thống | `const uint8_t *pConfig`              | Chỉ đọc dữ liệu cấu hình trong Flash       |


### 2.3.2 Kết hợp (const + volatile)
Áp dụng khi 
- không muốn thay đổi dữ liệu dựa trên logic code
- Dữ liệu có thể được cập nhật bởi phần cứng 

```c
const volatile uint32_t *pSTATUS = (uint32_t *)0x40001000;
```


## 2.4 Hằng con trỏ - Constant Pointer 
### 2.4.1 Khái niệm 
Con trỏ đến vùng địa chỉ cố định
- Không được đổi hướng con trỏ một khi đã gán địa chỉ
- Có thể thay đổi giá trĩ tại địa chỉ đó (trừ khi dữ liệu là hằng)

### 2.4.2 Ứng dụng
- Dùng khi khai báo con trỏ đại diện cho thanh ghi có địa chỉ cố định
- Ví dụ : thanh ghi điều khiển CR - Control Register

```c
volatile uint32_t * const pODR = (uint32_t *)0x48000014;  // Thanh ghi Output Data Register
*pODR = 1; // ghi dữ liệu ra GPIO
```
## 2.6 Con trỏ hàm - Function Pointer

## 2.6.1 Khái niệm 
Con trỏ đến địa chỉ của hàm
- Khi cần thao tác trên các hàm có định dạng giống nhau
- Cho phép gọi nhiều hàm khác nhau có cùng prototype mà không cần viết if/else hoặc switch-case
- Cú pháp : <return_type> (*func_ptr)(<data_type_1>,<data_type_2>);

```c
func_ptr = func;
(*func_ptr)();   // hoặc func_ptr();
```
Ví dụ : 
```c
int add(int a, int b) { return a + b; }
int (*op)(int, int) = add;
printf("%d", op(2,3)); // Kết quả: 5
```

## 2.6.2 Ví dụ sử dụng nâng cao
- Triển khai các hàm tính toán và thao tác qua con trỏ hàm bằng 3 cách

```c
void Tong(int a, int b)
{
    printf("%d + %d = %d\n", a, b, a + b);
}
void Hieu(int a, int b)
{
    printf("%d - %d = %d\n", a, b, a - b);
}
void Tich(int a, int b)
{
    printf("%d x %d = %d\n", a, b, a * b);
}
void Thuong(int a, int b)
{
    if (b != 0)
        printf("%d / %d = %.2f\n", a, b, (float)a / b);
    else
        printf("value of b is invalid\n");
}
```

### a) Trỏ tửng hàm
```c
int a = 12, b = 2;
/* cach 1 */
void (*func_ptr)(int,int) = NULL;
func_ptr = Tong;
func_ptr(a,b);

func_ptr = Hieu;
func_ptr(a,b);

func_ptr = Tich;
func_ptr(a,b);

func_ptr = Hieu;
func_ptr(a,b);
```
### b) Mảng con trỏ hàm
```c
int a = 12, b = 2;
void (*funcArr[])(int,int) = {Tong,Hieu,Tich,Thuong};
funcArr[0](a,b);
funcArr[1](a,b);
funcArr[2](a,b);
funcArr[3](a,b);
```
### c) Truyền địa chỉ vào hàm tổng quát
```c
void Operator(void (*op)(int, int), int a, int b)
{
    op(a, b);
}
void main(){
  int a = 12 , b = 3;
  Operator(Tong, a, b);
  Operator(Hieu, a, b);
  Operator(Tich, a, b);
  Operator(Thuong, a, b);
}
```
## 2.6.3 Ứng dụng

**Xử lý Ngắt** : CPU gọi ra hàm xử lý thủ tục ngắt __ISR__ tương ứng dựa trên địa chỉ trong __vector table__

<p align = "center">
<img width="500" height="250" alt="Image" src="https://github.com/user-attachments/assets/5a4a45bd-09c2-4bd6-8aa5-99efb92f0978" />

**Task Scheduler - RTOS** : Mỗi task có con trỏ trỏ tới hàm thưc thi 

## 2.7 Con trỏ đến con trỏ - Pointer to Pointer

### 2.7.1 Khái niệm 

Con trỏ đến địa chỉ của con trỏ khác, mà không trực tiếp trỏ tới dữ liệu. Khi ta cần thay đổi địa chỉ trỏ đến của 1 con trỏ thông qua con trỏ khác. 

Ví dụ : khi thay đổi địa chỉ của con trỏ cấp 1, cần thông qua cấp 2.
```c
int **pp;  
```
=> Khi truyền vào hàm để thao tác, cần truyền địa chỉ của con trỏ cấp 1, Cho phép thao tác thông qua 1 con trỏ cấp cao hơn

| Trường hợp                                                                                 | Mô tả                                                                  |
| ------------------------------------------------------------------------------------------ | ---------------------------------------------------------------------- |
| 1️⃣ Muốn **thay đổi giá trị của con trỏ khác** từ trong hàm                                | Giúp “hàm con” có thể gán địa chỉ mới cho con trỏ “bên ngoài”          |
| 2️⃣ Làm việc với **mảng con trỏ (pointer array)**                                          | Mỗi phần tử của mảng là 1 con trỏ, ví dụ `char *argv[]` trong `main()` |
| 3️⃣ Khi cần **quản lý cấu trúc động phức tạp**, như danh sách, buffer 2D, hoặc bảng string |                                                                        |
| 4️⃣ Trong **embedded**, dùng cho việc **phân tích buffer, frame hoặc chuỗi dữ liệu động**  |                                                                        |


### 2.7.2 Ứng dụng và ví dụ thực tê

Trong hệ thống nhúng khi làm việc với dữ liệu truyền qua các giao thức mạng, truyền thông - UART / CAN / Ethernet. Chuỗi nhận về có định dạng như JSON / UART string. Ví dụ như : "TEMP:28;HUM:65;" Do đó cần phân tách ra từng thành phần. Cụ thể bằng cách 
- Viết các hàm xử lý chuỗi như strtok() hoặc parse JSON để trả về con trỏ tới từng token
- Dùng double pointer để truyền/nhận các con trỏ đó 1 cách an toàn

**Ví dụ - con trỏ đến vùng nhớ cấp phát động thông qua việc gọi hàm để xử lý**

```c
#include <stdio.h>
#include <stdlib.h>

void allocateBuffer(char **p)
{
    *p = (char *)malloc(20);  // gán địa chỉ vùng nhớ mới cho con trỏ bên ngoài
    if (*p)
        sprintf(*p, "Sensor OK");
}

int main(void)
{
    char *msg = NULL;
    allocateBuffer(&msg);  // truyền địa chỉ của con trỏ -> double pointer nhận

    printf("%s\n", msg);   // In ra: Sensor OK

    free(msg);
    return 0;
}
```

**Ví dụ - Phân tích chuỗi dữ liệu UART**

```c
#include <stdio.h>
#include <string.h>

void parseUART(char *rx, char **temp, char **hum)
{
    *temp = strtok(rx, ";");  // con trỏ tới "TEMP=27"
    *hum  = strtok(NULL, ";"); // con trỏ tới "HUM=63"
}

int main(void)
{
    char buffer[] = "TEMP=27;HUM=63;";
    char *t, *h;

    parseUART(buffer, &t, &h);

    printf("%s | %s\n", t, h);  // In ra: TEMP=27 | HUM=63
}
```
