# 1 Các loại biến, chỉ thị, và rules trong makefile
## 1.1 Biến tự động (Automatic Variables)

### 1.1.1 Các loại cơ bản
-   **\$@**: Tên target hiện tại.
-   **\$\<**: Prerequisite đầu tiên (thường dùng cho quy tắc compile
    `.c → .o`).
-   **\$\^**: Danh sách tất cả prerequisites (loại trừ trùng lặp).
-   **\$?**: Các prerequisites mới hơn target.
-   **\$(@D)**: Thư mục chứa target.
-   **\$(@F)**: Tên file target (không kèm đường dẫn).
### 1.1.2 Biến `vpath` 
- Cho phép Make tìm file `.c` trong nhiều thư mục.

**Ví dụ**
```c
vpath %.c src utils drivers
```
## 1.2 Ký tự `%` trong Makefile (Pattern Matching)

-`%` đại diện cho *bất kỳ chuỗi ký tự nào*, dùng trong pattern rule.

**Ví dụ**
```c
$(SOURCE_DIR)/%.o: $(SOURCE_DIR)/%.c
```
__→ `.o` và `.c` phải có cùng tên gốc.__

## 1.3 Sự khác nhau giữa `$<` và `$^`

| Biến | Ý nghĩa                                          | Dùng khi              | Ví dụ |
|------|--------------------------------------------------|------------------------|--------|
| `$<` | Chỉ lấy **một file prerequisite đầu tiên**       | Compile `.c → .o`     | `$(CC) -c -o $@ $<` |
| `$^` | Lấy **toàn bộ danh sách prerequisites**          | Linking               | `a.out: a.o b.o c.o`<br>`$(CC) $^ -o $@` |

> **Lưu ý:**  
> Không được dùng `$^` thay `$<` trong quy tắc compile, vì compile chỉ nhận **một file input duy nhất**.


## 1.4 Pattern Rule 

- Dùng để viết quy tắc tổng quát:
- Cú pháp tổng quát 
```c
%.o: %.c
    $(CC) -c -o $@ $<
```

**% nghĩa là gì ?**
-`%` đại diện cho một mẫu `stem`
- Make sẽ so khớp để tìm phần chung giữa `target` và `dependencies` 

**Ví dụ**
```c
$(SOURCE_DIR)/%.o: $(SOURCE_DIR)/%.c
    $(CC) $(CFLAGS) -c -o $@ $<
```
- Giả sử `$(SOURCE_DIR)` chứa src/main.c
- target lúc này `$(SOURCE_DIR)` chứa src/main.o 
- So khớp với rule `sr/%.o -> stem = main`
- make tự suy ra dependencies src/main.c 

=> `%` tự suy luận tên file__
------------------------------------------------------------------------

# 2. Các hàm xử lý tự động trong makefile
## 2.1 Các hàm cơ bản
### 2.1.1 Hàm `wildcard`

- Lấy danh sách file trong thư mục chỉ định tùy theo pattern quy định __(đặc trưng của file)__ 

**Ví dụ:**
```c
SOURCES = $(wildcard src/*.c)
```

------------------------------------------------------------------------

**Ý Nghĩa**
- `*.c` chỉ là pattern __(đặc trưng)__ , lệnh make phải mở rộng nó thành danh sách file dùng `wildcard function`
- Không tự đông như shell, nền phải dùng wildcard

### 2.1.2 Substitution reference (`:.c=.o`)

- Cách viết ngắn gọn, thay `.c` → `.o`.
- Cú pháp tổng quát `$(VAR:from=to)`
**Ví dụ**
```c
OBJECTS = $(SOURCES:.c=.o)
// Tương đương
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))
```
**Ý Nghĩa**
- Lấy từng phần tử trong `$(...)`
- Nếu phần tử khớp với mẫu `from` thì thay bằng `to`
- Đây là cách tạo danh sách file mục tiêu từ danh sách nguồn 
------------------------------------------------------------------------

### 2.1.3 Hàm `subst` -- thay thế chuỗi đơn giản

- Cú pháp : `$(subst FROM,TO,TEXT)`
- **TEXT** là phần cần thay thế nội dung.\
Make sẽ tìm chuỗi FROM và thay bằng TO.

**Ví dụ**
```c
A := a/b/c
B := $(subst /,\,${A})
# → B = a\b\c
```
__Note__ : đây là thay thế chuỗi thuần, không hiểu pattern

**Ý Nghĩa**
- from : chuỗi cần tìm
- to : chuỗi thay thế
- text : đoạn văn bản hoặc chuỗi đầu vào để thực hiện thay thế

------------------------------------------------------------------------

### 2.1.4 Hàm `patsubst` -- thay thế theo pattern

- Cú pháp : `$(patsubst pattern,replacement,text)`
- `patsubst` hiểu và xử lý được pattern (%)
- `subst`chỉ thay chuỗi thô 

**Ví dụ**
```c 
SRCS = src/a.c src/b.c src/c.c
OBJS = $(patsubst src/%.c,build/%.o,$(SRCS))
# → build/a.o build/b.o build/c.o
```
__Note__ : 
- pattern được match theo từng "token"
- Cho phép dùng wildcard `%`.\ Mạnh hơn `subst`.

------------------------------------------------------------------------


### 2.1.5 Tóm tắt các hàm, biến, rule thông dụng trong makefile

| Hàm           | Công dụng                               |
| ------------- | --------------------------------------- |
| `wildcard`    | Lấy danh sách file thật                 |
| `subst`       | Thay chuỗi thuần (không pattern)        |
| `patsubst`    | Thay chuỗi theo pattern `%`             |
| `filter`      | Lọc *giữ lại* các phần tử match pattern |
| `filter-out`  | Lọc *loại bỏ* phần tử match pattern     |
| `VAR:%.c=%.o` | Viết tắt của `patsubst`                 |
| `%`           | Placeholder trong pattern rule          |
| `$<`          | Prerequisite đầu tiên                   |
| `$^`          | Tất cả prerequisites                    |

### 2.1.6 Một số thao tác nâng cao

```c
SOURCES = $(foreach dir,$(SOURCE_DIR),$(wildcard $(dir)/*.c))
// Kết quả
SOURCES chứa src/app/main.c src/log/logger.c src/math/add.c
```
**Mô tả**
- `foreach` lặp qua từng folder trong SOURCE_DIR
- Ở mỗi lần lặp, wildcard lấy tất cả file `.c` trong folder đó
- Kết quả `SOURCES` chứa toàn bộ đường dẫn file `.c` từ nhiều folder khác nhau


```c
SOURCE_NAMES = $(notdir $(SOURCES))
OBJECTS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SOURCE_NAMES))
```

`SOURCE_NAMES = $(notdir $(SOURCES))`
- _notdir_ loại bỏ phần chỉ thư mục, chỉ giữ lại tên file
- từ src/app/main.c -> chỉ còn main.c

`OBJECTS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SOURCE_NAMES))`
- __patsubst__ đổi `.c` -> `.o` và thêm tiền tố thư mục build
- Tạo ra danh sách object đầy đủ đường dẫn


## 2.2 Vấn ấn đề thường gặp với makefile và template chuẩn

## 2.2.1 Order-only prerequisites (`|`)

Make đảm bảo thư mục tồn tại trước khi build file:

    $(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)

------------------------------------------------------------------------

### 2.2.2 Wildcard sai dấu ngoặc

Sai:

    $(wildcard $(SOURCE_DIR/*.c))

Đúng:

    $(wildcard $(SOURCE_DIR)/*.c)

### 2.2.3 Không tạo thư mục_OUTPUT

Fix:

    $(BINARY_DIR):
        mkdir -p $(BINARY_DIR)

### 2.2.4❗ Circular dependency

Do sử dụng sai đường dẫn hoặc object file bị trùng tên.

------------------------------------------------------------------------

### 2.2.5 Best Practices

-   Tách rõ SOURCE_DIR, BUILD_DIR, HEADER_DIR.
-   Luôn dùng pattern rule thay vì viết từng rule thủ công.
-   Dùng `vpath` nếu có nhiều thư mục nguồn.
-   Luôn tạo thư mục output bằng order-only prerequisite.
-   Tránh object file trùng tên → dùng đầy đủ đường dẫn hoặc giữ cấu
    trúc thư mục.

------------------------------------------------------------------------

## 2.5.6. Template Makefile chuẩn

    TARGET = app
    SRC_DIR = src
    INC_DIR = include
    BUILD = build

    SOURCES = $(wildcard $(SRC_DIR)/*.c)
    OBJECTS = $(patsubst %.c,$(BUILD)/%.o,$(notdir $(SOURCES)))

    vpath %.c $(SRC_DIR)

    CC = gcc
    CFLAGS = -I$(INC_DIR) -Wall -Werror -g

    all: $(BUILD)/$(TARGET)

    $(BUILD):
        mkdir -p $(BUILD)

    $(BUILD)/$(TARGET): $(OBJECTS)
        $(CC) -o $@ $^

    $(BUILD)/%.o: %.c | $(BUILD)
        $(CC) $(CFLAGS) -c -o $@ $<

    clean:
        rm -rf $(BUILD)

    .PHONY: all clean

------------------------------------------------------------------------

