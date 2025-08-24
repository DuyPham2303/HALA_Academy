# Tên chương trình
TARGET = run

# Thư mục chứa các file .h và .c
SOURCE_DIRS = src UI
HEADER_DIRS = include
BINARY_DIR = bin

# Tìm tất cả file .c trong các thư mục SOURCE_DIRS
SRCS := $(wildcard $(addsuffix /*.c, $(SOURCE_DIRS)))

# Chuyển đổi file .c -> file .o trong bin
OBJECTS := $(patsubst %.c,$(BINARY_DIR)/%.o,$(notdir $(SRCS)))

# Compiler & flags
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -std=c17 \
         $(addprefix -I,$(HEADER_DIRS) $(SOURCE_DIRS))

# Thiết lập đường dẫn tìm kiếm .c
vpath %.c $(SOURCE_DIRS)

# Quy tắc mặc định (biên dịch ra file thực thi)
all: $(BINARY_DIR)/$(TARGET)

# Tạo thư mục bin nếu chưa có
$(BINARY_DIR):
	mkdir -p $(BINARY_DIR)

# Link các object thành chương trình
$(BINARY_DIR)/$(TARGET): $(OBJECTS) | $(BINARY_DIR)
	@echo "Linking..."
	$(CC) $(CFLAGS) -o $@ $^

# Build từng .c thành .o
$(BINARY_DIR)/%.o: %.c | $(BINARY_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c -o $@ $<

# Chạy chương trình
run: all
	./$(BINARY_DIR)/$(TARGET)

# Dọn sạch
clean:
	rm -rf $(BINARY_DIR)/*.o $(BINARY_DIR)/$(TARGET)

.PHONY: all clean run
