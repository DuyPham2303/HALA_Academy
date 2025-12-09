# 1. Tổng quan về Memory lauout
## 1.1 Bối cảnh 
- Khi triển khai trên 1 hệ thống nhúng, ngoài việc đảm bảo code chạy đúng như yêu cầu, ta cần phải quan tâm đến các khía cạnh khác như
	+ Hiệu suất và tốc độ xử lý có tối ưu chưa
	+ Dung lượng lưu trữ có đủ để hệ thống có thể sử dụng

=> Để quản lý tốt được bộ nhớ hạn chế của hệ thống nhúng , ta cần hiểu rõ được đặc điểm của các phân vùng lưu trữ trên RAM, từ đó có thể lựa chọn và sử dụng cho hợp lý nhằm tránh lãng phí tài nguyên và sử dụng bộ nhớ 1 cách tối ưu. Do đó cần nắm rõ kiến thức về memory layout - sơ đồ tổ chức bộ nhớ

## 1.2 Khái niệm và bản chất 
- Sơ đồ tổ chức bộ nhớ, mô tả 
  	+ các vùng bộ nhớ mà mã máy __(machine code)__ và biến sẽ được đặt ở đâu khi chương trình chạy
  	+ cách mà file thực thi tổ chức thành các section như `.text` , `.data` , `.bss` , `.rdata`
- file thực thi có định dạng tùy hệ thống
  	+ window : .exe (lưu ở SSD)
  	+ Linux/MCU ARM : .elf 
  	+ MCU 8-bit/32-bit : .hex   
## 1.3 Quy trình xử lý sau khi load FILE thực thi lên RAM 
### 1.3.1 Trên PC (Window/Linux)

<p align = "center">
<img width="650" height="300" alt="Image" src="https://github.com/user-attachments/assets/6e05a11a-d607-4fb4-8537-5115582d970a" />

+ Os loader đọc file thực thi và map các segment vào RAM
+ Os ánh xạ virtual address thông qua MMU sang physic address  
+ Program counter bắt đầu thực thi từ main()
### 1.3.2 Trên MCU 
+ CPU truy cập trực tiếp .text và .rdata từ Flash __(ko copy xuống RAM)__
+ StartUp code tiến hành copy .data từ flash xuống RAM và zero hóa .bss

  => ko có MMU như trên PC, vì vậy MCU thường sử dụng địa chỉ tuyệt đối 
+ Gọi main() để bắt đầu program 

<p align = "center">
<img src = "https://github.com/user-attachments/assets/71fc9574-93e0-4cf0-a661-1d776b60a516" width = "500" height = "400">

# 2. Triển khai các segment trên RAM
## 2.1 Code segment
### 2.1.1 Bản chất 
- Đây là nơi chứa mã nguồn thực thi của chương trình
- Dữ liệu chỉ được đọc và thực thi, mà không được phép ghi (thay đổi)
- chứa các section cụ thể như
  	+ `.text` : chứa mã lệnh
  	+ `.rdata`: chứa chuỗi hằng (string literal), các biến (const)
### 2.1.2 Ví dụ 
**a) char* str = "hello"**
+ "hello" là chuỗi hằng , đặt vào .rdata (read-only data section)
+ str được lưu tùy vào vị trí khai báo
  	+ global (toàn cục) : đặt trong .dara (hoặc .rdata tùy compiler)
  	+ local  (cục bộ)   : đặt trong stack  
**b) const char* str1 = "hello"**
+ "hello" vẫn là chuỗi hằng trong .rdata
+ str1 là __pointer to const__ , nhưng bản thân nó vẫn trỏ tới địa chỉ khác được nên nằm trong .data 

**c) char str2[] = "hello"**
+ mảng str2[] được khởi tạo bằng chuỗi hằng => compiler copy chuỗi vào .data
+ Vì là mảng, nó không trỏ vào vùng dữ liệu hằng - literal, dữ liệu đã được copy

**d) const char str3[] = "hello"**
+ mảng nhưng là const => compiler đặt nó vào .rdata
+ str3 nằm trong .rdata

**e) char* str4[] = {"hello", "my name", "is duy"}**
+ str4[] là mảng con trỏ nằm trong .data
+ mỗi chuỗi nằm trong .rdata 

## 2.2 DATA segment 
### 2.2.1 Initialized data 
+ Lưu trữ biến global khởi tạo khác 0
+ Lưu trữ biến static (local + global) cũng khởi tạo khác 0
+ Quyền truy cập đọc/ghi
+ Địa chỉ cấp phát 1 lần cố định khi chương trình chạy 
+ vùng nhớ được thu hồi khi chương trình kết thúc
```bash
int a = 23;        
static int b = 21; 
  int main(){
     static int c = 12; 
     return 0;
  }
```

### 2.2.2 Uninitialized data - BSS  
+ Lưu trữ biến global chưa khởi tạo hoặc bằng 0
+ Lưu trữ biến static (local + global) chưa khởi tạo hoằc bằng 0
+ Quyền truy cập đọc/ghi
+ Địa chỉ cấp phát 1 lần cố định khi chương trình chạy 
+ vùng nhớ được thu hồi khi chương trình kết thúc

```bash
 int a;        // global -> uninitialized  
 static int b; // static global -> uninitialized
 int c = 0;    // global -> intialized 0
 int main(){
  static int e; //local static -> uninitialized
  return 0;
 }
```

## 2.3 STACK
### 2.3.1 Bản chất 
+ Vùng nhớ được cấp phát tại thời điểm biên dịch và được giải phóng khi ra khỏi phạm vi được cấp phát. Dùng lưu trữ 
	+ các biến khai báo cục bộ (local)
	+ tham số hàm 
	+ địa chỉ trả về của hàm 
+ Hoạt động theo cơ chế LIFO
+ Khi 1 hàm được gọi thì toàn bộ thông tin của hàm đó bao gồm các giá trị trên sẽ được push lên stack và cấp phát cho 1 vùng nhớ để lưu trữ và sẽ được giải phóng khi hàm thực thi xong. 

```bash
  void swap(int a,int b){
    int temp = a;
    a = b;
    b = temp; 
  }
  int main(){
     int a = 23,b = 78;
     swap(a,b);
  }
```
+ Khi ta truyền giá trị a,b vào trong hàm swap, thực chất ta chỉ đang truyền bản copy của chúng
+ Khi hàm swap được gọi, địa chỉ của nó sẽ được đẩy lên stack, và các giá trị copy của tham số truyền vào cũng như các biến cục bộ bên trong swap sẽ được cấp phát vùng nhớ riêng biệt
+ Chính vì vậy quá trình tính toán xử lý bên trong swap sẽ không ảnh hưởng đến giá trị bên ngoài phạm vi của nó

### 2.3.2 Stack trỏ đến code segment
Khi ta khai báo như sau 
```bash
  int main(){
  char* str = "hello world"; // stack trỏ đến code segment
  char pstr[] = "hello world"; //cấp phát toàn bộ trên stack
  str[0] = 'g'; //wrong -> can't modify read-only memory
    return 0;
  }
```
+ con trỏ str sẽ được lưu trên stack
+ chuỗi "hello world" mà str trỏ đến sẽ được lưu ở code segment
### 2.3.3 Thay đổi local const thông qua con trỏ 

khi ta khai báo 1 biến const ở phạm vi local, nó sẽ được lưu trên stack và không thể thay đổi được giá trị. Tuy nhiên dùng 1 con trỏ để truy cập vào địa chỉ của nó thì vẫn thay đổi được

```bash
 const int b = 12;
 int main(){
 const int a = 23;
 a = 34; //wrong -> can't modify value
 int* p = &a;
 *p = 16; //true
 p = &b;
 *p = 15; //wrong -> can't modify value
 }
```
+ Việc chỉnh sửa giá trị của 1 biến const cục bộ thông qua con trỏ sẽ khiến compiler đưa ra cảnh báo nhưng vẫn thực hiện được
+ Đối với biến const toàn cục, thì ta không thể thay đổi giá trị của nó như làm với biến local. 
## 2.4. HEAP
### 2.4.1 Bản chất
+ Vùng nhớ cấp phát tại thời điểm run-time 
+ Kích thước thay đổi được trong khi chương trình chạy 
+ được quản lý bởi người dùng thông qua các từ khóa malloc, calloc,realloc, free (sử dụng thư viện stdlib.h)
+ vùng nhớ được giải phóng bằng cách sử dụng từ khóa free

### 2.4.2 Sử dụng 
Ví dụ ta có chương trình sau để cấp phát vùng nhớ heap ở thời điểm chương trình đang chạy.
```bash
 #include <stdio.h>
 #include <stdlib.h>

int main(){
  int size;
  printf("nhap so phan tu:");
  scanf("%d",&size);
  //khai báo 1 con trỏ để quản lý vùng nhớ heap được cấp phát 
  int* ptr = (int*)malloc(size * sizeof(int));

  //kiểm tra vùng nhớ được cấp phát thành công hay chưa
  if(ptr == NULL){
    printf("cap phat vung nho that bai");
    return 0;
  }

  //gán giá trị cho mỗi phần tử của vùng nhớ
  for(int i = 0 ; i < size ; i++){
    printf("input %d:",i);
    scanf("%d",&ptr[i]);
  }
  printf("\n");

  //in ra giá trị vừa nhập
  for(int i = 0 ; i < size ; i++){
    printf("output %d:%d\n",i,ptr[i]);
  }
  
  //giải phóng vùng nhớ sau khi sử dụng để tránh lỗi memory leak
  free(ptr);
  return 0;
 }
```
Khi ta chạy chương trình trên, sẽ yêu cầu ta nhập vào số lượng phần tử ví dụ size = 5, thì sau đó hàm sau đây sẽ cấp phát cho ta 1 vùng nhớ trên heap với 
+ tổng cộng là size * (kiểu dữ liệu của size) = 20 byte
+  malloc(mặc định là void*) được ép lại thành kiểu (int*) để nó biết phải lấy ra 4 byte đối với mỗi ô địa chỉ được cấp phát vùng nhớ 
+ con trỏ ptr (được khởi tạo trên stack) được trỏ tới heap để quản lý vùng nhớ vừa được khởi tạo
```bash
  int* ptr = (int*)malloc(size * sizeof(int));
```
+ Sau đó ta phải kiểm tra liệu địa chỉ trỏ tới vùng nhớ hiện tại có hợp lệ hay không để tránh việc cấp phát vùng nhớ thất bại
```bash
 if(ptr == NULL){
    printf("cap phat vung nho that bai");
    return 0;
  }
```
+ Tiếp theo ta sử dụng chỉ số để truy xuất vào giá trị của các phần tử được cấp phát trên heap để gán giá trị
```bash
  for(int i = 0 ; i < size ; i++){
    printf("input %d:",i);
    scanf("%d",&ptr[i]);
  }
```
+ Cuối cùng ta sẽ in ra giá trị, và thu hồi vùng nhớ sau khi đã sử dụng xong bằng từ khóa free
```bash
  for(int i = 0 ; i < size ; i++){
    printf("output %d:%d\n",i,ptr[i]);
  }
  
  //giải phóng vùng nhớ sau khi sử dụng để tránh lỗi memory leak
  free(ptr);
```

# 3. Phân biệt STACK và HEAP
![Capture](https://github.com/user-attachments/assets/b729ce20-051e-48f9-987c-e21d43eb7002)
## 3.1 Khai báo các biến trên STACK để đọc dữ liệu thông qua cảm biến dht11 và đưa ra cảnh báo

```bash
typedef struct{
  float temp;
  float humi;
}dht11;
void read_dht11(dht11* mydht){
	float temp,humi; // khai báo 2 biến để lưu kết quả xủ lý
      /*
	 	 giả sử khung truyền data của dht11 được xử lý ở đây
	  */
	//lưu data đọc về vào struct
	mydht->temp = temp;
	mydht->humi = humi;
}
void control_Alarm(dht11* mydht){
//khai báo 2 biến local để đọc giá trị từ struct
    float read_temp = mydht->temp;
    float read_humi = mydht->humi;
    if(read_temp > 50 && read_humi < 60){
      // bật còi cảnh báo
    }
    else if(read_temp > 20 && read_temo <= 50){
      // do something
    }
}
int main(){
  dht11 mydht;
  read_dht11(&mydht);
  control_Alarm(&mydht);
  return 0;
}
```
## 3.2 Sử dụng HEAP để đọc về 1 buffer trên server online nào đó và thực hiện hành đông cụ thể
Ta sẽ có 1 hàm để thực hiện việc đọc 1 buffer nào đó và trả về con trỏ tới vùng nhớ được cấp phát trên heap để lưu trữ chuỗi đọc về

```bash
char* get_data_online(char* online_buffer){
    uint8_t size = 0;
    char* ptr = online_buffer; //trỏ tới chuỗi cần đọc 
    for(int i = 0 ; ptr[i] != '\0'; i++){
        size += 1; //tính toán kích thước chuỗi
    }
	
	//cấp phát động trên heap
    char* read_buff = (char*)malloc((size + 1) * sizeof(char));

	//sao chép vào vùng nhớ heap
    for(int i = 0 ; i < size ; i++){
      read_buff[i] = ptr[i];
    }
    
	read_buff[size] = '\0'; 	//thêm ký tự kết thúc chuỗi
    return read_buff;
}
```
sau đó ta sẽ gọi hàm trên và lưu vào 1 chuỗi và thực hiện so sánh nếu giống như cmd thì sẽ thực hiện 1 công việc nào đó 
```bash
int main(){
  char* buff = "turn on led 1";
  int num = 231;
  char* read_buff = get_data_online(buff);
  if (strcmp(read_buff,"turn on led 1") == 0){
      //thực hiện bật led 
      printf("led 1 has been turned on\n"); // in ra thông báo
  }
  else printf("other commands\n");
  free(read_buff);
  return 0;
```




    
    



    
