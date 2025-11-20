# 1. Tổng quan về Stack 
## 1.1 Cơ chế hoạt động của Stack Segment trên Memory layout  
### 1.1.1 Khái niệm Stack Frame 

<table>
  <tr>
    </td>
    <td>
        <img width="500" height="600" alt="Image" src="https://github.com/user-attachments/assets/33fb1955-3215-4920-9028-c6ab6b68b0a4" />
    </td>
</h3>
    <td width="40%">
    <h3>🔹Khi 1 hàm được gọi sẽ được CPU cấp phát 1 vùng nhớ tạm trên RAM để lưu trữ khối dữ liệu của hàm gọi là __Stack frame__
  </tr>
</table>

### 1.1.2 Call Stack là gì 

<table>
  <tr>
    <td width="45%">
      <h3>🔹 Call stack chứa các stack frame của các hàm được gọi, và được quản lý bởi stack pointer (thanh ghi luôn trỏ tới top of stack, chứa khối thông tin của hàm mới nhất được gọi)
</h3>
    </td>
    <td>
      <img width="450" height="650" alt="Image" src="https://github.com/user-attachments/assets/d472abef-b30c-4eb8-a531-fba9ec95f3f6" />
    </td>
  </tr>
</table>

### 1.1.2 Tại sao cần Call Stack 

Khi một hàm được gọi CPU phải nhớ được 
+ Nó sẽ quay về đâu sau khi thực thi hàm xong 
+ Các biến thuộc về hàm này phải được tồn tại cho đến khi hàm kết thúc 
+ Các tham số truyền vào 

__=> Do đó CPU cần 1 nơi để tự động lưu - tự động thu hồi đó là stack__

<table>
  <tr>
    <td width="50%">
      <h3>🔹Khi chương trình chạy, nó sử dụng PC - Program counter để lưu trữ địa chỉ câu lệnh hiện tại mà sẽ được thực thi</h3>
      <ul>
        <li>Thông thường PC sẽ tăng dần theo thứ tự địa chỉ tăng dần của các câu lệnh.   </li>
        <li>Khi 1 hàm được gọi, PC thay đổi đột ngột theo địa chỉ của hàm được call</li>
        <li>Khi thoát khỏi hàm, cần biết chính xác địa chỉ trả về của câu lệnh tiếp theo sau lời gọi hàm.</li>
        <li>Do đó địa chỉ của câu lệnh tiếp theo này cần lưu trữ khi __call function__</li>
      </ul>
    </td>
    <td>
      <img width="500" height="550" alt="Image" src="https://github.com/user-attachments/assets/25d3c1bc-b6ab-4364-8b9d-45412855c23a" />
    </td>
  </tr>
</table>

## 1.2 Stack Pointer / Top Of stack
### 1.2.1 Khái niệm
- Khi phần tử mới nhất được thêm vào stack, vị trí của nó sẽ cần được đánh dấu. Do đó Stack Pointer sẽ chứa thông tin địa chỉ của phần tử cuối cùng được thêm vào stack
### 1.2.2 Nguyên lý hoạt động 

- Stack pointer sẽ luôn thay đổi bằng cách tăng/giảm vùng địa chỉ trên RAM mỗi khi có phần tử mới được thêm vào hay xóa khỏi stack. Nói cách khác stack pointer sẽ có nhiệm vụ quản lý hàm và bộ nhớ trên stack, với các đặc điểm sau 

<table>
  <tr>
    <td width="55%">
      <h3>🔹 Quy trình hoạt động của Stack</h3>
      <ul>
        <li>Luôn trỏ đến top of stack - vùng địa chỉ thấp nhất hiện tại được sử dụng trên Stack </li>
        <li>Mở rộng từ High -> Low address khi cấp phát stack frame mới</li>
        <li>Push: đưa dữ liệu vào ngăn xếp - SP giảm</li>
        <li>Pop: lấy dữ liệu từ đỉnh - SP tăng</li>
      </ul>
    </td>
    <td>
      <img width="400" height="250" alt="Image" src="https://github.com/user-attachments/assets/a1590ba4-286e-47db-b1f8-e5248e80966c" />
    </td>
  </tr>
</table>

=> Tóm lại stack pointer là thanh ghi sẽ được tăng/giảm địa chỉ để quản lý các hàm, biến cục bộ và call stack 

### 1.1.4 Quá trình function call thực hiện như thế nào 
**a) Lưu ý Đối với các thanh ghi tạm thời** 
+ __Trước function call__ : 
    + Lưu trữ những giá trị tính toán, có thể giá trị các biến
    + Sau khi call và thoát khỏi hàm, các register này cần khôi phục lại dữ liệu cũ 
+ __Trong quá trình function call__ :
    + Lưu trữ các Argument, local var 
    + Các register này do đó có thể bị thay đổi 
**b) Quá trình call một hàm**
<table>
  <tr>
    <td width="50%">
      <h3>🔹Giả sử CPU Gọi hàm foo(10) </h3>
      <ul>
        <li>Push tham số lên Stack</li>
        <li>Push return address để xác định câu lệnh tiếp theo cần xử lý sau khi foo() chạy xong</li>
        <li>Tạo stack Frame - CPU giảm dần SP để mở rộng bộ nhớ cấp phát cho iến cục bộ </li>
      </ul>
    <td>
        <pre>
        | Tham số (10)      |
        | Return address    |
        | Biến cục bộ foo() |
        | ...               |
        ↑  
        SP (giảm xuống)
        </pre>>
</td>
  </tr>
</table>

**c) Quá trình return hàm**
<table>
  <tr>
    <td>   
<pre>
    | Tham số (10)      |
    | Return address    |
    | Biến cục bộ foo() |
    | ...               |
            ↑  
        SP (giảm xuống)
</pre>
    </td>
    <td width="50%">
      <h3>🔹Khi hàm foo(10) kết thúc, CPU thực hiẹn</h3>
      <ul>
        <li>Pop vùng biến cục bộ bằng cách nâng SP lên, lúc này biến cục bộ biến mất</li>
        <li>Pop return address, cho phép CPU nhạu về đúng dòng code gọi Foo(10)</li>
        <li>Vùng Stack cũ được khôi phục từ các thanh ghi lưu trữ tạm thời, trả lại trạng thái trước khi gọi hàm foo(10)</li>
      </ul>
  </tr>
</table>


**d) Tóm tắt Quá trình Push/Pop trên Call Stack**

<table>
  <tr>
    <td width="50%">
      <ul>
        <li>Push - SP Giảm xuống : cho phép ghi dữ liệu vào vị trí mới trên stack</li>
        <li>Pop - SP Tăng lên : Tự động bỏ qua dữ liệu mà không cần xóa</li>
      </ul>
    </td>
    <td>
    <pre>
    SP = 0x20001000
    push 4 byte → SP = 0x20000FFC  
    pop 4 byte  → SP = 0x20001000
    </pre> 
    </td>
  </tr>
</table>


## 1.2 Cơ sở ra đời của DSA Stack
### 1.2.1 Tóm tắt Hardware Stack và lý do cần có DSA Stack
- phân vùng stack __ được quản lý tự động bởi Os + CPU__ dựa trên cơ chế LIFO. với các đặc điểm sau  
    + Mỗi lần __gọi hàm__ các local var, thông tin trả về, param được __đẩy vào stack theo thứ tự nào__ thì Khi __hàm kết thúc__ chúng sẽ được thu hồi theo __thứ tự ngược lại__ 
    + Hoạt động dựa trên 2 cơ chế là Push/Pop, và có thể đọc truy cập data thông qua Peek/Top 

=> Dựa trên nguyên lý vận hành này, mà người ta đã xây dựng nên một cấu trúc dữ liệu Stack để ứng dụng vào trong lý thuyết thuật toán để giải quyết các bài toán phức tạp.

## 1.3 Đặc điểm của Stack (DSA)
- Các thao tác trên 1 cấu trúc dữ liệu stack tuân theo các thao tác cơ bản tương tự như vùng ngăn xếp trên RAM
    + Push : Thêm 1 phần tử vào trên cùng
    + Pop : Lấy 1 phần tử khỏi đình
    + Top/Peek : xem phần tử trên cùng mà không pop
    + Empty/full : kiểm tra tình trạng stack
## 1.4 So sánh giữa Stack segment và Stack (DSA)

| Stack trong C (call stack)          | Stack DSA (do lập trình viên tạo) |
| ----------------------------------- | --------------------------------- |
| Do CPU/OS quản lý                   | Do lập trình viên quản lý         |
| Lưu return address, local variables | Lưu dữ liệu tuỳ ý                 |
| Tự động push/pop khi call/return    | push/pop do bạn viết code         |
| Dựa trên thanh ghi SP               | Dựa trên mảng hoặc linked list    |
| Không giới hạn bởi bạn              | Giới hạn bởi array/struct bạn tạo |

# 2. Triển khai Stack (DSA)
## 2.1 Xác định các thành phần
- Để triển khai 1 cấu trúc dữ liệu thì ta cần hiểu rõ về 2 thành phần
      + Organize data : cách thức tổ chức dữ liệu
      + Operation : Các thao tác với Stack (Push/Pop)
## 2.1.1 Tổ chức data cho Stack
- Các phần tử lưu trữ trên stack thông thường sẽ có các đặc điểm
  + có cùng kiểu dữ liệu
  + Có địa chỉ liền kề với nhau

 => Chính vì vậy , ta có thể dùng một array có thể là mảng tĩnh hoặc động để tổ chức và thao tác với các phần tử 
## 2.1.2 Kiến trúc chính của 1 DSA Stack

| **Thành phần**                        | **Mô tả chi tiết**                                                                                                                                                                                                                                                                 |
| ------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Vùng lưu trữ dữ liệu (items)** | • Nơi chứa toàn bộ phần tử của stack. <br>• Có thể được cấp phát **tĩnh** (mảng cố định) hoặc **động** (malloc).                                                                                                                                                                   |
| **Thuộc tính kích thước (size)** | • Xác định số phần tử tối đa stack có thể chứa. <br>• Ở stack động: kích thước có thể mở rộng nếu có cơ chế resize.                                                                                                                                                                |
| **Biến đánh dấu đỉnh (top)**     | • Trạng thái ban đầu: `top = -1` nghĩa là stack rỗng. <br>• Khi push: `top++`. <br>• Khi pop: `top--`.                                                                                                                                                                             |
| **Các thao tác cơ bản**          | • **Push()** – thêm phần tử. <br>• **Pop()** – lấy phần tử trên cùng. <br>• **Top()** – đọc phần tử trên cùng nhưng không xoá. <br>• **IsEmpty()** – kiểm tra rỗng. <br>• **IsFull()** – kiểm tra đầy (đối với stack tĩnh). <br>• **Free()** – giải phóng tài nguyên (stack động). |

## 2.2 Triển khai các thao tác  
### 2.2.1 Tạo các kiểu dữ liệu cần thiết
```c
typedef uint8_t StackStatus;

#define STACK_OVERFLOW  ((StackStatus)0)
#define STACK_EMPTY     ((StackStatus)1)
#define STACK_OK        ((StackStatus)2)

typedef struct{
    int* items;
    int size;
    int top;
}Stack_datastructure;
```
### 2.2.2 Khởi tạo stack
```c
StackStatus Init_Stack(Stack_datastructure* stack,int size){
    stack->items = malloc(size*sizeof(int));
    if(stack->items == NULL){
        printf("không đủ vùng nhớ cấp phát");
        return STACK_OVERFLOW;
    }
    stack->size = size;
    stack->top = -1;
    return STACK_OK;
}
```
### 2.2.3 Thao tác kiểm tra trạng thái stack
```c
StackStatus CheckStatus(const Stack_datastructure* stack){
    if(stack->top == stack->size - 1) return STACK_OVERFLOW;
    else if(stack->top == -1)         return STACK_EMPTY;
    else return STACK_OK;
}
```
### 2.2.4 Thao tác push
```c
StackStatus Push(Stack_datastructure* stack,int indata){
    if(CheckStatus(stack) == STACK_OVERFLOW){
        printf("stack đầy\n");
        return STACK_OVERFLOW;
    }
    stack->items[++stack->top] = indata;
    printf("thêm %d\taddress: %p\n",stack->items[stack->top],&stack->items[stack->top]);
    return STACK_OK;
}
```
### 2.2.5 Thao tác pop
```c
StackStatus Pop(Stack_datastructure* stack,int* outdata){
    if(CheckStatus(stack) == STACK_EMPTY){
        printf("stack rỗng\n");
        return STACK_EMPTY;
    }
    *outdata = stack->items[stack->top--];
    return STACK_OK;
}
```
### 2.2.6 Thao tác top
```c
StackStatus top(const Stack_datastructure* stack,int* topdata){
    if(CheckStatus(stack) == STACK_EMPTY){
        printf("stack rỗng\n");
        *topdata = -1;
        return STACK_EMPTY;
    }
    *topdata = stack->items[stack->top];
    return STACK_OK;
}
```
# 3. So sánh Stack segment và Stack DSA 
## 3.1 Tính giai thừa bằng đệ quy (stack segment)

<table>
  <tr>
    <td width="50%">
      <ul>
        <li>Mỗi lần gọi factorial(n) , sẽ sinh ra một stack frame mới</li>
        <li>Mỗi lần gọi sẽ luu trên stack segment</li>
        <li>Nếu n quá lớn dãn đến tràn stack</li>
      </ul>
    </td>
    <td>
    <pre>
    int factorial(int n){
        if(n == 1) return 1;
        return n * factorial(n - 1);
    }
    -----------------------------------
    factorial(4)
     └─ factorial(3)
         └─ factorial(2)
             └─ factorial(1)
    ------------------------------------
    </pre> 
    </td>
  </tr>
</table>

## 3.2 Tính giai thừa bằng Stack DSA (loại bỏ đệ quy)

<table>
  <tr>
    <td width="50%">
      <h3>🔹 Quy trình hoạt động của Stack</h3>
      <ul>
        <li>Mô phỏng việc stack segment gọi hàm bằng stack DSA</li>
        <li>Thay vì push frame vào call stack, ta push số n vào stack</li>
        <li>Sau đó pop dần để tính kết quả</li>
      </ul>
      <h3>🔹Ưu điểm khi dùng stack DSA</h3>
      <ul>
        <li>Không tạo nhiều stack </li>
        <li>Tránh stack overflow khi n rất lớn</li>
        <li>Dễ kiểm soát kích thước stack</li>
      </ul>  
    </td>
    <td>
    <pre>
     Stack_datastructure stack;
     Init_Stack(&stack,n);
     for(int i = n ; i > 0 ; i--)
        Push(&stack,i); 
     int result = 1;
     for(int i = 0 ; i < n ;i++){
        static int out = 0;
        Pop(&stack,&out);
        result *= out;  
    </pre> 
    </td>
  </tr>
</table>



