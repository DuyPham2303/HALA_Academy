# HTTP là gì

<p align = "center">
<img width="463" height="485" alt="Image" src="https://github.com/user-attachments/assets/4cd4c37b-0a47-45a9-835b-2c753ffd596d" />

+ HTTP là một giao thức tầng ứng dụng (Application Layer) nằm trong bộ giao thức TCP/IP.
+ HTTP hoạt động dựa trên kết nối TCP (thường trên port 80 hoặc 8080).
+ Socket chỉ là API của hệ điều hành dùng để tạo, quản lý kết nối TCP giữa client – server.
+ HTTP tuân theo mô hình client–server với cơ chế request–response (client gửi request, server trả response).
    - HTTP quy định:
        + Cấu trúc của message
        + Phương thức (method) gửi/nhận dữ liệu
        + Cách trình duyệt và server trao đổi tài nguyên
        + cách trao đổi dữ liệu siêu văn bản : text, HTML, CSS, hình ảnh, âm thanh, video.
=> Từ đó mã hóa thành giao diện hiển thị trên web


# Mô hình HTTP

<p align = "center">
<img width="644" height="375" alt="Image" src="https://github.com/user-attachments/assets/1424f66e-8863-468f-b1c3-fb449916fc19" />

## a. Khởi tạo phiên đăng nhập 
- user truy cập website thông qua trình duyệt. 1 phiên đăng nhập là __session__ được tạo ra với 
    - client : user's computer
    - server : máy chủ website
    - port 80 : cổng mặc định kết nối 
## b. Các bước thiết lập trên mã nguồn C
- client Khởi động TCP connection đến server
- Socket interface (kết nối được thiết lập) bao gồm:    
    + IP address
    + protocol type 
    + port number
- Sau khi kết nối thành công 
    + client request server với request message : chứa path 
- server nhận và xử lý request qua socket và gửi client response 
    + data return là file HTML
    + Server đóng TCP connection
    + Client nhận response từ server -> đóng TCP connection
## c. Tóm tắt quy trình truy cập website

<p align = "center">
<img width="614" height="466" alt="Image" src="https://github.com/user-attachments/assets/2e65fd8f-be4c-47dc-9ccc-e1e9f4e68044" />

- Trình duyệt mở kết nối TCP đến server qua port 80 hoặc 8080
- Khi TCP xử lý xong, client gửi __HTTP Request__
- Server xử lý request và trả về __HTTP Response__
- Client nhận repsonse và hiển thị nội dung HTML
- Hai bên đóng kết nối khi cần
- Thông tin kết nối chứa:
    + IP Address
    + TCP protocol
    + Port client và Port server 
    + Socket ID dùng đọc/ghi dữ liệu 
## a. Request message 
+ Cấu trúc được chia làm 3 phần

    **Request Line**

- __method__           : GET , POST, HEAD, PUT , DELETE
- __URL path__         : /index.html 
- __protocol version__ : HTTP/1.1 hoặc 1.0
    
    ```c
    GET /index.html HTTP/1.1
    ```
    
    **Header** 
    
    ```c
    Header-Name: Value
    ```
    
    **Body**

- __GET__ : thường không có body
- __POST/PUT__ : chứa dữ liệu (JSON, text, form) gửi lên server 
    ```c
    Request Line:
        GET /index.html HTTP/1.1
    ```
## b. Response message
   __Status line__
        - __protocol version__ : HTTP/1.1
        - __Status code__: 200,404,302
        - __Status text__: 200 OK, 404 Not Found, 403 Forbidden
     ```c
    Response Status Line:
        HTTP/1.1 200 OK
    ```

   __Header line__
    ```c
    Content-Type: text/html
    Content-Length: 1024
    ```
   
   __Body__
        - data return ở dạng 1 trang HTML. Chính là giao diện web hiển thị 
        - dữ liệu được tạo thành từ : HTML page , JSON, CSS Ảnh , file 

# Các bước xây dựng HTTP server 
## Bước 1 – Tạo HTTP đơn giản
- nếu client gửi __GET /__, server sẽ trả về HTML như sau
```c
HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: ...
<html>...</html>
```
## Bước 2 - Trả về file HTML thật từ ổ đĩa
+ Server cần:
    - Mở file index.html
    - đọc toàn bộ nội dung của file 
    - Gửi nội dung file cho client 
+ Tiến hành Đọc file văn bản bằng C sử dụng
    - `fseek` + `ftell` để lấy độ dài chính xác thay vì strlen __(Chỉ dùng cho chuỗi két thúc bằng null)__
```c
char* read_file(char* pf){
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);
    html = malloc(size + 1);
    fread(html, 1, size, fp);
    html[size] = '\0';
    return html
}
```
- `fopen()`, `fread()`, `fclose()`
- con trỏ Đọc toàn bộ nội dung vào char *html
- Gửi __Content-Length__ 
```c
char* html = read_file("index.html");
send(socket, html, length);
```

## Bước 3 - Phân tích URT và trả file tương ứng 
+ Server cần tách method & path từ request:
+ Gửi nội dung file tương ứng với từng đường dẫn:

| **Path**         | **File trả về**                |
|------------------|--------------------------------|
| `/`              | `index.html`                   |
| `/styles.css`    | `styles.css`                   |
| `/data`          | `data.json` hoặc `data.csv`    |
| *(không tồn tại)*| `404 Not Found`                |


## Bước 4 - Xử lý POST Request và lưu dữ liệu
- Đối với phía client cụ thể là trình duyệt (hoặc app) gửi POST /save-data, ví dụ
```c
POST /save-data
Content-Type: application/json
Content-Length: 35
{"temp":27.5,"voltage":3.3}
```
- Server sẽ phải 
    - Đọc header để lấy `content-Length`
    - Đọc đúng số byte của body
    - Lưu vào file : data.json 
    - Phản hồi với nội dung 
```c
HTTP/1.1 200 OK
Content-Type: text/plain
Data saved successfully
```

**Test bằng curl**
- chạy chương trình 
- chạy lệnh trên cmd để gửi dữ liệu 
```c
bash : curl -X POST http://localhost:8080/save-data -H "Content-Type: application/json" -d "{\"temp\":27.5,\"voltage\":3.3}"
```
## Bước 5 - Chạy song song nhiều client (đa luồng)
+ Tạo mỗi client một thread riêng.
+ Giúp server có thể phục vụ nhiều trình duyệt hoặc máy cùng lúc.

```c
while(1) {
    client = accept(...);
    pthread_create(&tid, NULL, client_handler, client);
}
```
## Bước 6 - Tạo form nhập dữ liệu
+ Tạo một trang HTML có form

```c
<form method="POST" action="/save-data">
    <input name="username" />
    <button type="submit">Send</button>
</form>
``` 
+ form mặc định gửi theo MIME

```c
application/x-www-form-urlencoded
```

+ Gửi dữ liệu từ form bằng POST
+ Server nhận, xử lý và lưu lại vào file như ở bước 4 và 5
+ Hiển thị thông báo Đã gửi thành công nếu mọi thứ ổn


# Bước 7 - Hiển thị dữ liệu đã lưu trong khi vẫn chạy song song nhiều client
- Hiển thị dữ liệu đã lưu ra trình duyệt bằng cách xử lý HTTP GET /data.
- Khi truy cập http://localhost:8080/data, server sẽ:
    + mở và đọc file __saved_data.json__
    + Gửi nội dung đó về trình duyệt dưới dạng JSON hoặc HTML
    + Trình duyệt hiển thị dữ liệu người dùng đã gửi
- Ví dụ __response JSON__ có định dạng
```c
HTTP/1.1 200 OK
Content-Type: application/json

{"temp":27.5,"voltage":3.3}
```
