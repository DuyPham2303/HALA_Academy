# 1. Bối cảnh và khái niệm Union

- Ta cần biết rằng, việc quản lý bộ nhớ tốt luôn là ưu tiên trong phát triển hệ thống nhúng để đảm bảo tránh lãng phí tài nguyên do đặc điểm về giới hạn dung lượng lưu trữ của phần cứng, do vậy Union là 1 trong các cấu trúc dữ liệu có thể hỗ trợ ta thao tác với dữ liệu 1 cách tối ưu và tiết kiệm bộ nhớ nhất có thể.

## 1.1 Bản chất Union ?

<p align = "center">
<img width="550" height="450" alt="Image" src="https://github.com/user-attachments/assets/9c64b4a2-5e29-4d54-bf04-79ba50eaf6f4" />

**a) Union là gì ?**
- Là 1 kiểu user-define datatype, cũng cho phép các member có kiểu khác nhau chia sẻ chung 1 vị trí bộ nhớ, với các đặc điểm
    + tại 1 thời điểm chỉ có 1 member có giá trị hợp lệ
    + Kích thước union chính là của member lớn nhất 

- Union như 1 chiếc hộp đa năng
    + có thể chứa 1 quyển sách, hoặc điện thoại 
    + Tuy nhiên chiếc hộp này chỉ được thiết kế để đặt vừa quyển sách __(vật lớn nhất)__

**b) Lý do cần có Union ?**
- Giả sử ta cần thu thập dữ liệu cảm biến từ MCU1 và truyền sang MCU2 thông qua UART. Với dữ liệu cần truyền là các số thực __(float)__ làm tròn đến 3 con số. 
    + `Phương án thông thường :` 
        + MCU1 converts __(float)__ sang __(string)__ (ví dụ : 123.456 -> "123.456") 
        + MCU1 sends từng byte sang MCU2 
        + MCU2 receives __(string)__ và convert về __(float)__ 
    
    => Cách này tốn tài nguyên và thời gian xử lý cho việc chuyển đổi giữa số thực và chuỗi

    + `Phương án tối ưu :`
        + MCU1 Truyền từng byte mà không cần xử lý gì cả
        + MCU2 nhận từng byte và tự sắp xếp các byte để tạo thành số __(float)__ mà không cần thao tác gì khác 

    => Đó chính là cách mà Union sẽ xử lý, cho phép dữ liệu mà ta thao tác có thể được biểu diễn và nhìn nhận ở nhiều kiểu dữ liệu khác nhau trên cùng 1 vị trí bộ nhớ 

## 1.3 Thao tác với Union

**a) Khai báo và sử dụng**

```c
union Union_Name {
    datatype element1;
    datatype element2;
    // ...
    datatype elementN;
};
```

__Ví dụ__ : Union dưới đây sẽ có kích thước là 5 byte, do nó phụ thuộc vào member lớn nhất 

```c
union Data {
    int A;
    float B;
    char str[5];
};

union Data dt;

dt.A = 34;
dt.float = 21.3;
dt.str[0] = 21;

```

__Note__ : Khi printf các member trên thì sẽ trả về giá trị của member cuối cùng được ghi dữ liệu, lý do chính là vì đặc điểm chia sẻ chung bộ nhớ. Vì vậy tại 1 thời điểm chỉ có 1 member được đọc/ghi dữ liệu hợp lệ

# 2. Ứng dụng thực tế
## 2.1 Chuyển đổi giữa byte array và cấu trúc dữ liệu cụ thể khi truyền/nhận gói tin qua UART/SPI/I2C

```c
// Example: Read 10-bit ADC value (2 bytes) and store it in a 16-bit variableư
union AdcValue {
    uint16_t fullValue;
    struct {
        uint8_t lowByte;
        uint8_t highByte;
    } bytes;
};

void readADC(void) {
    union AdcValue adc;
    // Suppose low byte is read first, high byte is read later
    adc.bytes.lowByte = read_adc_low_byte_register();
    adc.bytes.highByte = read_adc_high_byte_register();

    // Now 16-bit values ​​can be accessed
    printf("ADC Value: %u\n", adc.fullValue);
}
```
## 2.2 Tạo các biến cờ (flags) bitwise
- Khi ta cần quản lý tập hợp các cờ trạng thái mà mỗi flag chỉ cần sử dụng 1 bit trong 1 byte hoặc word. Ta dùng Union để gộp chúng lại để tạo ra 1 cách __truy cập rõ ràng và hiệu quả__

```c
union DeviceStatus {
    uint8_t allFlags; 		// Access all flags as 1 byte
    struct {
	unsigned int isReady : 1; // Flag 0: Device ready
		unsigned int isError : 1; // Flag 1: Error occurred
		unsigned int isTransmitting : 1; // Flag 2: Data is being transmitted
		unsigned int reserved : 5; // Reserved bits
    } individualFlags; 		// Access each flag individually
};

// Usage
union DeviceStatus status;
status.allFlags = 0x01;   // Set isReady bit = 1
if (status.individualFlags.isReady) {
    // Device ready
}
```
## 2.3 Thao tác với thanh ghi MCU 
- Việc sử dụng bitfield + Union cho phép ta thao tác trên 1 bộ nhớ thông qua việc chỉ định truy cập duói dạng các bit riêng lẻ  
- Giả sử ta muốn thao tác với thanh ghi điều khiển UART 8-bit có cấu trúc 

| Bit(s) | Tên trường   | Mô tả                              |
|:-------:|---------------|------------------------------------|
| 0       | TX_EN         | Bật truyền (1: Enable)             |
| 1       | RX_EN         | Bật nhận (1: Enable)               |
| 2–3     | BAUD_PRESC    | Hệ số chia tần số baud (0–3)       |
| 4       | PARITY_EN     | Bật kiểm tra chẵn lẻ (1: Enable)   |
| 5       | PARITY_TYPE   | Loại chẵn lẻ (0: Even, 1: Odd)     |
| 6–7     | RSVD          | Dự trữ                             |


```c
#include <stdint.h>

//cấu trúc chứa các trường bit tương ứng với chức năng cần thao tác trên thanh ghi 
typedef volatile struct {
    uint8_t TX_EN       : 1; // Bit 0: Transmit Enable
    uint8_t RX_EN       : 1; // Bit 1: Receive Enable
    uint8_t BAUD_PRESC  : 2; // Bit 2-3: Baud Prescaler
    uint8_t PARITY_EN   : 1; // Bit 4: Parity Enable
    uint8_t PARITY_TYPE : 1; // Bit 5: Parity Type
    uint8_t RSVD        : 2; // Bit 6-7: Reserved
} UART_CR_BITS_t;   

typedef union {
    uint8_t           byte_access; // Truy cập toàn bộ byte
    UART_CR_BITS_t    bits;       // Truy cập từng bit
} UART_CR_REG_t;

#define UART_CR (*((volatile UART_CR_REG_t *) 0x40001000)) // Địa chỉ thanh ghi

void init_uart(void) {
    // Cấu hình bitfield
    UART_CR.bits.TX_EN = 1;       // Bật truyền
    UART_CR.bits.RX_EN = 1;       // Bật nhận
    UART_CR.bits.BAUD_PRESC = 0;  // Hệ số baud 0
    UART_CR.bits.PARITY_EN = 0;   // Tắt parity

    // Đọc trạng thái
    if (UART_CR.bits.RX_EN) {
        // UART nhận đang bật
    }

    // Truy cập toàn bộ byte
    uint8_t cr_value = UART_CR.byte_access;
}

int main() {
    init_uart();
    return 0;
}
```

__Giải thích cụ thể__
    
+ `UART_CR_BITS_t` : định nghĩa cấu trúc Bitfield cho từng trường bit

+ `UART_CR_REG_t` : cho phép truy cập thanh ghi dưới dạng byte hoặc bitfield

+ `volatile` : ngăn compiler tối ưu hóa các thao tác trên thanh ghi phần cứng


__=> Bằng cách trên ta không cần phải định nghĩa các macro mặt nạ bit và áp dụng các phép toán bitwise phức tạp để thao tác trên các bit của thanh ghi__


# 3. Ưu và nhược điểm
| **Khía cạnh**                               | **Ưu điểm (Advantages)**                                                                                                                                                                     | **Nhược điểm (Disadvantages)**                                                                                                                                        |
| ------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Bộ nhớ (Memory)**                         | **Tiết kiệm bộ nhớ:** các member share chung vùng nhớ → tổng kích thước là của member lớn nhất. Rất hữu ích trong hệ thống nhúng có RAM/ROM hạn chế.           | —                                                                                                                                                                     |
| **Truy cập dữ liệu (Data Access)**          | **Linh hoạt:** access cùng một vùng dữ liệu dưới nhiều kiểu khác nhau (ví dụ: xem 1 biến `int` dưới dạng mảng byte). Hữu ích khi xử lý dữ liệu nhị phân hoặc giao tiếp phần cứng. | **Rủi ro dữ liệu:** Yêu cầu người lập trình phải tự quản lý và hiểu các member nào đang hợp lệ, tránh đọc sai dữ liệu nếu không biết thành viên nào đang “hợp lệ”; dẫn đến hành vi không xác định (undefined behavior).                              |
| **Hiệu suất (Performance)**                 | **Cải thiện hiệu suất (trong vài trường hợp):** Truy cập dữ liệu theo “word” có thể nhanh hơn so với truy cập từng byte riêng lẻ.                                                            | —                                                                                                                                                                     |
| **Độ rõ ràng của mã (Code Clarity)**        | —                                                                                                                                                                                            | **Khó đọc và bảo trì:** Người khác (hoặc chính lập trình viên sau này) có thể khó hiểu được dữ liệu nào đang được sử dụng, đặc biệt khi code phức tạp.                |
| **Tính tương thích hệ thống (Portability)** | —                                                                                                                                                                                            | **Vấn đề Endianness:** Khi chuyển đổi giữa byte array và kiểu dữ liệu lớn hơn (int, short, float...), kết quả có thể sai lệch nếu không tính đến thứ tự byte của CPU. |


# 4. Struct vs Union  

<p align = "center">
<img width="650" height="500" alt="Image" src="https://github.com/user-attachments/assets/d9e1041c-73c7-4255-9961-be5e0b9889bf" />

## 4.1 So sánh tổng quát theo các tiêu chí 

+ **Bộ nhớ cấp phát**
    - `Struct` : từng member có vị trí bộ nhớ riêng
    - `Union`  : tất cả member chia sẻ chung vị trí bộ nhớ 
+ **Kích thước** 
    - `Struct` : total size of members + padding 
    - `Union`  : size of largest member 
+ **Truy cập**
    - `Struct` : có thể truy cập độc lập từng member 
    - `Union`  : chỉ truy cập được 1 member tai 1 thời điểm 
+ **Mục đích** 
    - `Struct` : gộp nhiều kiểu khác nhau để truy cập đồng thời 
    - `Union`  : Khi cần
        + optimize memory
        + access từng member tại các thời điểm khác nhau
        + access dữ liệu ở các định dạng khác nhau 

## 4.2 Trường hợp cụ thể dùng struct 
- Truy cập nhiều thông tin một lúc của các đối tương như
    + Sinh viên (mssv,name,age,major,gpa)
    + tọa độ (x,y,z)
    + Giá trị cảm biến (timestamp,temperature,humidity,sensorId)
```c
struct SensorReading {
	uint32_t timestamp;	// Reading time
	float temperature; 	// Temperature
	float humidity; 	// Humidity
	uint8_t sensorId; 	// Sensor ID
};
// All of this information is needed and accessed at the same time for each reading.
```

    + __Rõ ràng và an toàn__ : do mỗi member là độc lập, hạn chế rủi ro về lỗi __undefined behaviour__ do access sai dữ liệu. Do đó code trở nên

=> Dễ hiểu, dể đọc, dễ bảo trì

    + __Yêu cầu về truyền dữ liệu dưới dạng block__ : định dạng tiêu chuẩn cho  
        + các gói tin truyền thông `UART` , `SPI` , `I2C`
        + các bản ghi trong FLASH
        + Cấu trúc dữ liệu phức tạp

## 4.3 Trường hợp cụ thể dùng Union
- __Khi cần tiết kiệm bộ nhớ__ : 
    + Lưu nhiều loại datatype khác nhau
    + Tại 1 thời điểm chỉ cần lưu 1 trong số chúng
    + Union giúp giảm đáng kể số lượng bộ nhớ sử dụng 

```c
// For example, a message can be either sensor data or a control command,
// but not both.
enum MessageType {
	SENSOR_DATA_MSG,
	CONTROL_CMD_MSG
};

struct Message {
	enum MessageType type;
	union {
		struct {
			float temperature;
			float humidity;
		} sensorData;
		struct {
			uint8_t commandId;
			uint16_t value;
		} controlCmd;
	} payload; // payload
};
// The size of the 'payload' will be the size of the larger structure (sensorData or controlCmd),
// rather than the sum of both if using a struct.
```
- __Truy cập 1 vùng bộ nhớ với nhiều kiểu khác nhau__   
    + Union cho phép chuyển đổi linh hoạt giữa nhiều kiểu khác nhau
    + Hữu ích khi áp dụng thao tác với dữ liệu truyền thông ở cấp độ bit (packing/unpacking) 
    + Tránh việc tốn thời gian xử lý ép kiểu

```c
// Example: Convert a 32-bit integer to 4 separate bytes
union U32Bytes {
	uint32_t value;
	uint8_t bytes[4];
};

void send32BitValue(uint32_t data) {
	union U32Bytes packet;
	packet.value = data; // Assign a 32-bit value
	// Now we can send each byte to the serial port
	send_byte(packet.bytes[0]);
	send_byte(packet.bytes[1]);
	send_byte(packet.bytes[2]);
	send_byte(packet.bytes[3]);
	// Note: Byte order depends on the Endianness of the system
}
```

- __Tổ chức thanh ghi MCU__ :
    + Thao tác với các trường bit khác nhau trên thanh ghi tương tự như các bitmask 
    + Thuận tiện hơn trong việc truy cập đọc/ghi theo từng bit hoặc word khi kết hợp với bitfield 

```c
/**
  \brief  Union type to access the Application Program Status Register (APSR).
 */
typedef union
{
  struct
  {
    uint32_t _reserved0:27;              /*!< bit:  0..26  Reserved */
    uint32_t Q:1;                        /*!< bit:     27  Saturation condition flag */
    uint32_t V:1;                        /*!< bit:     28  Overflow condition code flag */
    uint32_t C:1;                        /*!< bit:     29  Carry condition code flag */
    uint32_t Z:1;                        /*!< bit:     30  Zero condition code flag */
    uint32_t N:1;                        /*!< bit:     31  Negative condition code flag */
  } b;                                   /*!< Structure used for bit  access */
  uint32_t w;                            /*!< Type      used for word access */
} APSR_Type;
```
