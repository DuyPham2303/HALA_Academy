# Bối cảnh ra đời của Storage class
<p align = "center">
<img width="549" height="423" alt="Image" src="https://github.com/user-attachments/assets/80399234-bc18-4bd3-af3c-e0432a28a3ef" />

- Storage class là tập các từ khóa được sử dụng kèm với việc khai báo biến, nhằm quản lý vòng đời, phạm vi sử dụng của biến để đáp ứng các yêu cầu thực tế khi triển khai lập trình C trên hệ thống nhúng thực tế. Bao gồm 
    + Tối ưu hóa code, bộ nhớ 
    + Tăng tính module hóa và tái sử dụng code
# 1. Từ khóa extern 

## 1.1 Định nghĩa
- Từ khóa nhắc cho compiler biết 1 biến đã được khai báo rồi và có thể được tái sử dụng và chia sẻ cho nhiều module trong cùng thư mục gốc của dự án mà không cần phải khai báo lại
## 1.2 Bản chất

<p align = "center">
<img width="939" height="524" alt="Image" src="https://github.com/user-attachments/assets/e4c73ecb-1475-4c42-8e8f-d7a3ab7d9eb4" />

- Khi file nguồn chứa khai báo `extern` được biên dịch thành file object nó sẽ chứa 1 tham chiếu __(symbol reference)__ được ký hiệu là __U (Undefined Symbol)__
```c
// file driver.c
int adc_value = 0;   // global symbol: adc_value

// file app.c
extern int adc_value; // compiler tạo ra symbol kiểu U adc_value
```
- Khi compile với 
    + `nm driver.c` sẽ cho
```c
00000000 D adc_value
```
    + `nm app.c` sẽ cho
```c
U adc_value;
```

- Compiler không thực sự biết biến gốc nằm ở đâu
- Nhưng nó tin rằng ở 1 file nguồn khác sẽ chứa biến đó 
- Do đó ở bước linker. Nó sẽ tìm symbol 'adc_value' trong driver.o và nối vào app.o tạo ra 1 symbol là T __(Global symbol in text/data segment)__ . Chính là liên kết tham chiếu hoàn chỉnh.

```c
T adc_value
```
## 1.3 Extern và function declaration 
- Đối với hàm, extern là mặc định 

```c
void foo();        // = extern void foo();
extern void foo(); // same
```
- Tức là mọi function đều có 1 liên kết ra ngoài __(external linkage)__ trừ khi ta dùng static 

```c
static void foo(); //internal , private 
```

## 1.4 So sánh cách cập nhật giá trị thông qua extern,truyền con trỏ, và return

### 1.4.1 Ngữ cảnh áp dụng extern

- chia sẻ dữ liệu giữa nhiều file nguồn cùng chức năng
- ví dụ module read 
    + dùng để cập nhật ghi dữ liệu cảm biến, và extern cho các module khác để đọc và xử lý. 
    + Có thể dùng gettter/setter để bảo vệ quyền đọc/ghi trực tiếp tránh việc biến bị thay đổi ngoài mong muốn
- Phù hợp 
    + ứng dụng nhỏ, ít chức năng
    + dũ liệu nhỏ, ít thay đổi
    + dữ liệu có thể chấp nhận chia sẻ trực tiếp

**Ưu điểm**

+ đơn giản, dễ code
+ chia sẻ giữa nhiều module dẽ dàng

**Nhược điểm**

+ dữ liệu dễ bị ghi đè ngoài ý muốn
+ dễ bị xung đột khi nhiều module thực hiện ghi giá trị

### 1.4.2 Ngữ cảnh áp dụng truyền con trỏ vào hàm
- Cần đọc/ghi dữ liệu gián tiếp trong 1 hệ thống lớn thông qua các API trung gian, mà không cần quan tâm đển quá trình xử lý chi tiết. Phù hợp với các dự án lớn, phân chi các lớp cụ thể. __(yêu cầu tính trừu tượng)__
- Phù hợp cập nhật dữ liệu dạng struct, kết hợp return trạng thái xử lý kiểu bool

**+ Ưu điểm** : Không cần hiểu sâu về quy trình xử lý dữ liệu 

**+ Nhược điểm** : Cần xác định param truyền vào hàm để xử lý,

### 1.4.3 Ngữ cảnh áp dụng return giá trị trực tiếp
- Cần xử lý và trả về giá trị đơn giản, đọc lẻ tẻ

**+ Ưu điểm** : APi dễ đọc, đọc nhanh trong ứng dụng xử lý theo thời gian thực

**+ Nhược điểm**: Không phù hợp cho dữ liệu phúc tạp kiểu struct nhiều field

`VÍ DỤ PHÂN LOẠI`


```bash
// Dành cho dữ liệu nhỏ
int16_t Temp_ReadNow(void); 

// Dành cho dữ liệu phức tạp
Std_ReturnType Sensor_Read(SensorId id, SensorData* out);

// Hằng số dùng cho quá trình tính toán
extern const double pi;  // ok
```

## 1.5 Áp dụng trong thiết kế Autosar Module  
- Trong kiến trúc Autosar, chứa nhiều module nhằm tách biệt các phần triển khai riêng biệt để dễ quản lý bao gồm 
    + Cfg.c / h (chứa cấu hình)
    + Types.h (Chứa các datatypes được định nghĩa chuẩn Autosar)
    + Module.c (chứa triển khai logic chức năng cụ thể)
    + Module.h (Chứa API để sử dụng)
- Bối cảnh cần chia sẻ thông tin cấu hình cho 1 số module cụ thể ta bắt buộc phải dùng extern. Ví dụ

**AUTOSAR Configuration Structure**
```c
// Can_Cfg.h
extern const Can_ConfigType CanConfigData;

//Can_cfg.c
const Can_ConfigType CanConfigData = {
    // danh sách controller
};
```
**Note** : 
- Nếu không extern các module như CanIf không đọc được cấu hình 
- Từ khóa const ngăn chặn các module khác truy cập ghi vào vùng dữ liệu chia sẻ này 

## 1.6 Tóm tắt những lỗi sai và lưu ý 

| Lỗi sai                                     | Giải thích         |
| ------------------------------------------- | ------------------ |
| Khai báo extern nhưng quên định nghĩa       | lỗi linker         |
| extern xuất hiện trong file .c nhiều lần    | không tối ưu       |
| Dùng extern để chia sẻ state trong embedded | gây race condition |
| Extern biến static                          | không thể đúng     |
| extern const nhưng lại thay đổi dữ liệu     | undefined behavior |


# 2. Từ khóa static 
- Đặc điểm
    + `Static Lifetime` : Địa chỉ cố định khi chương trình chạy
    + `Internal Linkage` : Phạm vi sử dụng cục bộ 
    + `Preserve State` : Vùng nhớ không bị thu hồi khi thoát khỏi phạm vi 
## 2.1 Static & Storage Duration (Lifetime)
- 1 biến khi được khai báo static ở phạm vi local hay global thì lifetime của nó luôn luôn tồn tại xuyên suốt thời gian chương trình chạy. Ví dụ 
```c
void counter() {
    static int count = 0;  // sống suốt runtime
    count++;
}
```

## 2.2 Static variable & Memory section
- Static variable sẽ được đặt vào các section tương ứng trong memory layout trước khi được load lên RAM khi chương trình chạy

| Trường hợp                                | Section |
| ----------------------------------------- | ------- |
| static có khởi tạo → `static int x = 10;` | `.data` |
| static không khởi tạo → `static int y;`   | `.bss`  |

- Ta có thể kiểm tra bằng câu lệnh sau đây 

```c
readelf -S main.o
nm main.o

//kết quả dự kiến 
00000000 b y
00000004 d x
```
## 2.3 Các kỹ thuật thiết kế với static 
### 2.3.1 Preserve state - Static local 
- Trong 1 số trường hợp, ta cần lưu trữ lại kết quả xử lý nhiều lần trong runtime, và kết quả này chỉ nên giữ trong phạm vi xử lý của 1 hàm cụ thể. - Ví dụ : Lưu trạng thái tín hiệu nhiễu `debounce signal` khi nhấn phím 
```c
uint8_t DebounceButton() {
    static uint8_t stable = 0;
    static uint8_t last_sample = 0;

    uint8_t sample = ReadPin();
    if(sample == last_sample) stable++;
    else stable = 0;

    last_sample = sample;

    return (stable > 5);
}
```

**Một số ứng dụng khác trong Embedded**
- Counter timer cục bộ 
- ADC Oversampling
- Bộ lọc debouncing 
- State machine cục bộ 

### 2.3.2 Internal Linkage - static global 
- Khi ta khai báo 1 biến / hàm static ở phạm vi __scope file__ Ví dụ:
```c
static int adc_buffer[16];  // chỉ driver này nhìn thấy
static void ADC_Start();     // private function

static void Spi_PrivateHelper() {
    // xử lý logic thấp, không để lộ ra API
}

```
- Biến / hàm staic này sẽ không xuất hiện trong __symbol table global__ 
    + file khác không thể extern nó 
    + Tương tự như Encapsulation module trong c++ OOP 
**Đây là chuẩn kiến trúc thiết kế firmware & AUTOSAR module**
- Public API : khai báo trong .h
- Private API : dùng static trong .c 
- 
### 2.3.3 Thiết kế Hardware driver 
- Driver thường được thiết kế theo pattern ví dụ __[Driver_X].c  +  [Driver_X].h__
    - Trong `Driver_X.c`, các thành phần được khai báo static 
        + state nội bộ 
        + buffer 
        + private function 
        + peripheral flag
    - Ví dụ 
```c
static uint8_t txBuffer[32];
static uint8_t rxBuffer[32];
static volatile uint8_t rxCompleted = 0;

static void UART_StartTx();
```
- Nếu không khai báo static có thể vô tình extern cho các file khác không theo thiết kế pattern truy cập sai 

### 2.3.4 bảo vệ tài nguyên RTOS 
- Bên trong 1 kernel RTOS có thể phải khai báo static cho các thành phần sau để đảm bảo
    + giữ an toàn cho state hệ thống không bị tác động bởi các module khác
    + Không lộ API ra ngoài 
```c
static TCB_t tcbArray[MAX_TASK];
static uint32_t SystemTick;
```

### 2.3.5 Tối ưu hóa Compiler 
- từ khóa static còn giúp compiler 
    - giữ biến trong RAM cố định 
    - tránh cấp phát trên stakc (MCU có stack RAM ít)
    - khai báo static const được lưu ở flash giảm RAM 
### 2.3.6 Thiết kế Lookup table, Calibration Table 
- Lưu trong flash
```
static const uint16_t ADC_LUT[32] = {
    100, 200, 300, ...
};
```
- Trong Autosar 
```c
static const Can_ControllerConfigType ControllerDefaults[2] = {...};
```
## 2.4 Các lỗi sai và lưu ý với static 

| Lỗi                                                           | Giải thích                 |
| ------------------------------------------------------------- | -------------------------- |
| quên static, biến trở thành global symbol                     | gây xung đột, linker error |
| dùng static quá nhiều → memory bloat                          | static chiếm RAM cố định   |
| dùng static để share state giữa ISR/main nhưng thiếu volatile | lỗi logic                  |
| static trong header file                                      | SAI 100%                   |

# 3. Từ khóa register
sử dụng khi ta muốn lưu trữ 1 biến nào đó trong thanh ghi của CPU thay vì trên RAM, mục đích là để tăng tốc độ tính toán xử lý. 
```bash
#include<stdio.h>
#include<time.h>
int main(){
    //gán thời gian bắt đầu
    clock_t start = clock();

    //khai báo biến để kiểm tra
    register int data = 0;

    //thực hiện công việc nào đó
    for( ;data < 5000000;data++);

    //gán thời gian kết thúc
    clock_t end = clock();
    
    //in ra thời gian xử lý 
    double time_differece = ((double)(end - start)/CLOCKS_PER_SEC);
    printf("time : %f",time_differece);

    return 0;
}
```
hàm trên sẽ đo thời gian thực thi của vòng lặp đối với biến i khi khai báo là register. Nếu ta không khai báo biến i là register thì khi in ra kết quả sẽ có sự chênh lệch thời gian. Trong trường hợp khai báo là register thì khi ra kết quả thời gian sẽ nhỏ hơn khi không khai báo là register
# 4. Từ khóa volatile 
## 4.1 Định nghĩa
được sử dụng trên những biến thay đổi ngoài ý muốn của chương trình . Mục đích là để tránh việc compiler hiểu nhầm những biến này không Được cập nhật trong khoảng thời gian nhất định và thực hiện xóa nó đi để tối ưu hóa chương trình chẳng hạn như trong trong các trường hợp xử lý sau đây

+ __Phần cứng__: thanh ghi của thiết bị ngoại vi

+ __Ngắt__: bién được cập nhật khi có tín hiệu tác động đến từ trong/ngoài vi điều khiển

+ __Đa luồng:__ biến được truy cập hoặc thay đổi bời 1 luòng khác

## 4.2 Bản chất
- Từ khóa volatile đảm bảo rằng mỗi lần truy cập, giá trị mới nhất của biến được lấy trực tiếp từ RAM, thay vì dùng giá trị lưu trên thahh ghi. Tóm lại volatile làm 2 việc sau
- **1. Ngăn compiler cache giá trị biến trong thanh ghi**
    + Compiler không được phép 
        - Lưu biến vào register và không đọc lại 
        - Bỏ qua các lệnh đọc/ghi không cần thiết 
        - Gộp các lần đọc liên tiếp 
        - Xóa vòng lặp rỗng 
- **2. Buộc Compiler luôn đọc / ghi giá trị từ bộ nhớ thật 
    + Đảm bảo rằng CPU luôn thấy giá trị cập nhật mới nhất 
## 4.3 Tối ưu hóa chương trình là gì ? cách ngăn chặn ?
### a) Định Nghĩa
- Cơ chế giảm tải hoạt động cho chương trình khi nó giả định 1 biến sẽ không thay đổi giá trị trừ khi nó được sửa đổi bởi logic trong chương trình chính.
- Nếu compiler thấy biến không thay đổi trong logic của chương trình, nó có thể bỏ qua việc đọc giá trị biến từ bộ nhớ chính. 
### b) Tác động của volatile
Khi từ khóa này được khai báo , nó sẽ báo cho compiler biết rằng giá trị cũa biến có thể thay đổi bất kỳ luc nào và yêu cầu
+ __không tối ưu hóa:__ Bắt buốc đọc lại giá trị biến từ bộ nhớ chính

+ __Luôn đọc giá trị trực tiếp từ bộ nhớ chính:__ compiler phải đọc giá trị mới nhất từ bộ nhớ thay vì dùng giá trị đã lưu trong thanh ghi

## 4.3 Ứng dụng xử lý tín hiệu nút nhấn 

Giả sử ta có 1 hệ thống nhúng điều khiển bởi 1 nút nhấn được cấu hình ngắt ngoài. Mỗi khi nhấn nút, thì sẽ có tín hiệu ngắt phát biến bởi vi điều khiển, và 1 biến trạng thái sẽ được dùng để lưu sự kiện ngắt này. Trong chương trình chính sẽ xử lý những công việc dựa trên giá trĩ của biến này.

### a) Định nghĩa và khai báo biến cần thiết

```bash
#include <stdio.h>
#include <stdbool.h>

// Biến cờ được cập nhật bởi ngắt
volatile bool button_pressed = false; // Khai báo volatile vì biến này thay đổi ngoài vòng lặp chính
```

### b) Định nghĩa 1 hàm ngắt giả lập 

```bash
void button_interrupt_handler() {
    button_pressed = true; // thay đổi giá trị khi có tín hiệu ngắt
}
```

### c) Chương trình chính

```bash
int main() {
    while (1) {
        // Kiểm tra trạng thái nut nhấn
        if (button_pressed) {
            // Reset cờ
            button_pressed = false;
            
            // Xử lý sự kiện nhấn nút
            printf("Button was pressed!\n");
        }
        for (volatile int i = 0; i < 100000; i++); // Chờ giả lập
    }
    return 0;
}
```
__LƯU Ý__ lý do phải thêm volatile khi khai báo biến i trong vòng lặp for là vì 

+ Nếu không có volatile: compiler sẽ nhận ra rằng vòng for chỉ chạy 1 số lần nhất định và không làm gì bên trong vòng lặp, do đó nó có thể loại bỏ for
+ Nếu có volatile: compiler sẽ bị buộc phải luôn luôn thực hiện thực thi for. Volatile sẽ yêu cầu compiler đọc.ghi giá trị của i từ RAM trong mỗi lần lặp

## 4.4 Một số ứng dụng khác 
### 4.4.1 Shared variable giữa ISR và main 
```c
volatile uint8_t g_flag = 0;

void EXTI_IRQHandler(void) {
    g_flag = 1;
}

int main() {
    while (!g_flag) { } // phải volatile
}

```
Nếu không có volatile, compiler sẽ optimize. Dẫn đến ứng dụng bị treo 
```c
while(1) { }   // vì nghĩ rằng g_flag “không bao giờ thay đổi”
```

### 4.4.2 Đoc thanh ghi thiết bị ngoại vi
- Đối với các tín hiệu đến từ phần cứng không kiểm soát bởi chương trình, ta cần khai báo là volatile để bảo vệ vùng dữ liệu đọc về 
```c
#define UART_SR   (*(volatile uint32_t*)0x40011000)
```
- Nếu không volatile, 
    + compiler đọc 1 lần 
    + lưu vào register 
    + Những lân sau dùng lại giá trị cũ 

=> driver hoạt động sai
# 5. So sánh các từ khóa








