# 1. Các biến và rule trong makefile  
## 1.1 Biến tự động (Automatic Variables)

-   \*\*\$@*\*: Tên target hiện tại.
-   **\$\<**: Prerequisite đầu tiên (thường dùng cho quy tắc compile
    `.c → .o`).
-   **\$\^**: Danh sách tất cả prerequisites (loại trừ trùng lặp).
-   **\$?**: Các prerequisites mới hơn target.
-   **\$(@D)**: Thư mục chứa target.
-   **\$(@F)**: Tên file target (không kèm đường dẫn).

## 1.2 Ký tự `%` trong Makefile (Pattern Matching)

-   `%` đại diện cho *bất kỳ chuỗi ký tự nào*, dùng trong pattern rule.

Ví dụ:

    $(SOURCE_DIR)/%.o: $(SOURCE_DIR)/%.c

→ `.o` và `.c` phải có cùng tên gốc.

## 1.3 Sự khác nhau giữa `$<` và `$^`

  Biến   Ý nghĩa                                     Dùng khi
  ------ ------------------------------------------- -------------------
  `$<`   chỉ lấy *một file prerequisites đầu tiên*   compile `.c → .o`
  `$^`   lấy *toàn bộ danh sách prerequisites*       linking

Nếu dùng `$^` thay `$<` trong quy tắc compile thì sai vì compile chỉ
nhận 1 file input.

## 1.4 Biến `vpath`

Cho phép Make tìm file `.c` trong nhiều thư mục.

    vpath %.c src utils drivers

------------------------------------------------------------------------

## 1.5 Pattern Rule

Dùng để viết quy tắc tổng quát:

    %.o: %.c
        $(CC) -c -o $@ $<

------------------------------------------------------------------------


------------------------------------------------------------------------

# 2. Các hàm trong makefile
## 2.1 Hàm `wildcard`

-   Lấy danh sách file thỏa mãn pattern.

Ví dụ:

    SOURCES = $(wildcard src/*.c)

------------------------------------------------------------------------

## 2.2 Substitution reference (`:.c=.o`)

Cách viết ngắn gọn, thay `.c` → `.o`.

    OBJECTS = $(SOURCES:.c=.o)

Tương đương:

    OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

------------------------------------------------------------------------

## 2.3 Hàm `subst` -- thay thế chuỗi đơn giản

Cú pháp:

    $(subst FROM,TO,TEXT)

**TEXT** là phần cần thay thế nội dung.\
Make sẽ tìm chuỗi FROM và thay bằng TO.

Ví dụ:

    $(subst src,build,$(SOURCES))

------------------------------------------------------------------------

## 2.4 Hàm `patsubst` -- thay thế theo pattern

    $(patsubst %.c,%.o,$(SOURCES))

Cho phép dùng wildcard `%`.\
Mạnh hơn `subst`.

------------------------------------------------------------------------

## 2.5 Hàm `filter` và `filter-out`

### a. filter

Giữ lại các phần tử trùng với pattern.

    $(filter %.c, $(FILES))

### b. filter-out

Loại bỏ phần tử trùng với pattern.

    $(filter-out test%.c, $(FILES))

------------------------------------------------------------------------

# 3. Lỗi thường gặp và lưu ý trong makefile  

## 3.1 ❗ Wildcard sai dấu ngoặc

Sai:

    $(wildcard $(SOURCE_DIR/*.c))

Đúng:

    $(wildcard $(SOURCE_DIR)/*.c)

## 3.2 ❗ Không tạo thư mục_OUTPUT

Fix:

    $(BINARY_DIR):
        mkdir -p $(BINARY_DIR)

## 3.3 ❗ Circular dependency

Do sử dụng sai đường dẫn hoặc object file bị trùng tên.

------------------------------------------------------------------------

## 3.4 Order-only prerequisites (`|`)

Make đảm bảo thư mục tồn tại trước khi build file:

    $(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)

------------------------------------------------------------------------


## 3.5 Best Practices

-   Tách rõ SOURCE_DIR, BUILD_DIR, HEADER_DIR.
-   Luôn dùng pattern rule thay vì viết từng rule thủ công.
-   Dùng `vpath` nếu có nhiều thư mục nguồn.
-   Luôn tạo thư mục output bằng order-only prerequisite.
-   Tránh object file trùng tên → dùng đầy đủ đường dẫn hoặc giữ cấu

------------------------------------------------------------------------

## 4. Tổ chức cấu trúc của makefile chuyên nghiệp
### 4.1 Bối cảnh 
- Đối với các dự án nhỏ, chỉ chứa vài tệp nguồn `.c` nằm trong 1 thư mục thì có thể chỉ cần viết vài dòng makefile là xong
- Tuy nhiên khi dự án trở nên phức tạp, cần tổ chức theo kiểu module ví dụ
    + module header có thể chỉ chứa tệp `.h`
    + module source chứa các tệp `.c`, và có thể chia thành các module nhỏ hơn 
    + Cần tách biệt kết quả makefile với các module dự án

=> Việc triển khai makefile theo cách viết liệt kê từng file sẽ không còn phù hợp

- Do đó khi này ta sẽ sử dụng 1 template tổng quát để dễ dàng tạo 1 makefile có thể build bất kỳ dự án với án nào mà không cần quan tâm số tệp `.c` và `.h`, hay cách thức tổ chức module như thế nào. Từ đó có thể đảm bảo các yếu tố
    + dễ bảo trì
    + thêm tệp mới mà không cần chỉnh sửa makefile
    + tiết kiệm thời gian build project
    + dễ dàng chuyển đổi hệ thống đa nền tảng 
### 4.2 Template makefile chuyên nghiệp 
**A . Configuration Variable**
- Quy định nơi triển khai phần khai báo đường dẫn, các biến thay thế cần thiết. Hay nói 1 cách đơn giản là nơi __cấu hình các thông số build__ của dự án

```c
# Compiler & flags
CC      := gcc
CFLAGS  := -Wall -Wextra -O2 -Iinclude

# Directories
SRC_DIR := src
OBJ_DIR := build
BIN_DIR := bin

# Output binary
TARGET  := $(BIN_DIR)/app
```

__ƯU ĐIỂM__

- Khi muốn đổi sang compiler khác. Ví dụ `arm-none-eabi-gcc` cho vi điều khiển. chỉ cần chỉnh 1 dòng
- Khi muốn cập nhật thư mục, chỉ chỉnh trên 1 dòng

**B. Liệt kê tệp nguồn và tự động tạo tệp object**
- Thay vì viết thủ công
```c
main.o: main.c
    gcc -c main.c -o main.o
```
- Tự động scan toàn bộ tệp nguồn
```c
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
```
__Ý nghĩa các thành phần__

| Biến                 | Ý nghĩa                                        |
| -------------------- | ---------------------------------------------- |
| `wildcard`           | tự quét tất cả file `.c`                       |
| pattern substitution | tự convert `a.c → a.o` và đưa vào folder build |

**C. Định nghĩa target chính để build project**

```c
# quy tác để tạo ra tệp .exe -> tự động chạy rule bên dưới
all: $(TARGET)

# tự đông tạo build folder -> link các tệp .o thành tệp .exe
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $@
```

__Ý nghĩa các thành phần__

- `$@` : tên target (file thực thi) chính là `bin/app`
- `4^` : toàn bộ dependency chính là các `.o`

**D. Rules biên dịch từ .c sang .o**
- Tự động tạo ra các `.o` tương ứng với danh sách các `.c` đã quét được từ `wilcard`

```c
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
```
__Ý nghĩa các thành phần__

| Symbol | Nghĩa                        |
| ------ | ---------------------------- |
| `$<`   | file nguồn (source)          |
| `$@`   | file đích (object)           |
| `%`    | wildcard cho bất kỳ tên file |

**E. Các tiện ích (Utility Targets)**

```c
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: $(TARGET)
	./$(TARGET)

debug:
	make CFLAGS="$(CFLAGS) -g"

.PHONY: all clean run debug

```

**D. Sample Template**

```c
# ================== CONFIG ==================
CC      := gcc
CFLAGS  := -Wall -Wextra -O2 -Iinclude

SRC_DIR := src
OBJ_DIR := build
BIN_DIR := bin

TARGET  := $(BIN_DIR)/app

# ================== FILE SCAN ==================
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ================== MAIN TARGET ==================
all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) -o $@

# ================== COMPILE RULE ==================
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ================== UTILITIES ==================
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
```