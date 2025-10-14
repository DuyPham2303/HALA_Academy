# PROCESS (tiến trình)
+ Chương trình đang chạy trên hệ thống
+ Có địa chỉ riêng 
+ Tương tác được với ngoại vi khác phần cứng bên ngoài
+ chứa nhiều thread
+ các process giáo tiếp với nhau thông qua IPC
    1.signal
    2.semaphore
    3.pipe
# THREAD 
+ Đơn vị nhỏ hơn process
+ Các luồng trong cùng process chia sẻ tài nguyên chung
+ Có thể hiểu là 1 task chia thành nhiều câu lệnh -> các task sẽ được phân chía thời gian thực hiện xen kẽ nhau

## ĐẶC ĐIỂM 
+ Mỗi lường chỉ thực thi 1 hàm
+ Luồng chính kết thúc thì các luồng khác cùng kết thúc

# BASIC THREAD

## KHỞI TẠO LUỒNG

__Cú pháp__

std::thread thread_id(function,args...)
__thread_id__ : khởi tạo việc thực thi luồng (không kiểm tra trạng thái)
__args...__ : macro variadic (nhận số lượng tham số không xác định)
__function:__: hàm thực thi hoặc lambda

=> mỗi luồng chỉ thực thi 1 hàm duy nhất

## QUẢN LÝ LUỒNG
+ Đảm bảo luồng phụ kết thúc trước luồng chính sẽ tối ưu nhất 

### join()
+ Chờ cho đến khi 1 luồng thực thi xong thì luồng khác mới được thực thi
+ Khi 1 luồng phụ được khai báo nó sẽ phụ thuộc vào luồng chính  khi luồng chính không gọi ra __join()__ thì nó sẽ kết thúc và không chờ luồng phụ thực hiện -> lúc này chương trình sẽ bị xung đột (lỗi)

__=> Luôn đảm bảo luồng phụ kết thúc trước luồng chính__

nếu gọi method join() 
     __+ AFTER__ code của luồng chính : cả luồng chính và phụ đèu chạy song
     __+ BEFORE__ code của luồng chính : luồng phụ chạy xong mới đến luồng chính
### detach()
+ cho phép luồng phụ tách khỏi luồng chính và chạy độc lập
+ Luồng chính không cần chờ hàm phụ kết thúc
+ Chương trình sẽ kết thúc nếu luồng chính kết thúc trước luồng phụ (xóa kết quả luồng phụ -> không bị xung đột)
+ Nếu gọi join trước detach và luồng chính kết thúc trước luồng gọi detach -> báo lỗi do gọi ra luồng đã kết thúc

__=> Đảm bảo luồng chính luôn kết thúc sau những luồng phụ mà gọi detach__


__=> tránh việc gọi join() và detach() đồng thòi trong chương trình trên 1 luồng__ 

## Khi nào dùng join() hay detach()
### dùng join() khi
+ Khi kết quả task cần được xử lý bởi luồng chính (tài nguyên của luồng chính và phụ chia sẽ với nhau)
-> khi đọc dữ liệu từ cảm biến (luồng phụ) và cần lấy dữ liệu để xử lý (luồng chính)
### dùng detach() khi
+ Khi đọc dữ liệu từ nhiều cảm biến khác nhau (công việc của luồng phụ không ảnh hưởng đến luồng chính)

### joinable()

+ kiểm tra 1 luồng đã kết thúc hoặc join() chưa
+ return true -> khi luồng chưa kết thúc/chưa gọi join()
+ return false -> khi luồng đã kết thúcthúc

# ADVANCE THREAD

# ĐỒNG BỘ LUỒNG

## Atomic 
+ là 1 struct template
+ chỉ sử dụng đối với dữ liệu
+ thao tác với biến global
+ cho phép nhiều luồng cùng truy cập vào tài nguyên nhưng không bị gián đoạn việc thao tác trên dữ liệu được chia sẻ chung giữa các luồng 
=> có nghĩa là khi 1 luồng đang sử dụng biến atomic những luồng khác không được cho phép truy cập 

__+ LƯU Ý:__ atomic chỉ phù hợp với các thao tác đơn giản, chẳng hạn tăng/giảm hoặc hoán đổi giá trị. Đối với các logic phức tạp (như cập nhật nhiều biến hoặc thao tác trên cấu trúc dữ liệu lớn), bạn cần sử dụng mutex.


ví dụ: 
int cnt = 0;
for(int i = 0 ; i < 5 ; i++){
    cout << ++cnt;
}
câu lệnh trên thực hiện các công việc sau
+ đọc 
+ thay đổi
+ ghi
Tuy nhiên khi 2 luồng cùng sử dụng biến cnt thì lúc này các luồng sẽ gián đoạn việc xử lý dữ liệu của biến cnt. 
=> ví dụ: Khi 1 luồng chưa xử lý trong 3 công việc trên và chỉ mới __đọc__ mà luồng khác đã
nhảy vào đề __thay đổi__ thì khi luồng trước đó lại quay lại để thực tiêp __ghi__ dữ liêu đã đọc chứ không phải dữ liệu mới sau thay đổi

## Lưu ý
+ chỉ sử dụng cho biến toàn cục
+ áp dụng trong việc chia sẻ dữ liệu cảm biến giữa các luồng
+ Chưa đảm bảo tuyệt đối việc cho phép 1 luồng truy cập vào tài nguyên chung ở 1 thời điểm -> sử dụng mutex sẽ tối ưu hơn


## Mutex
+ đảm bảo chỉ có 1 luồng duy nhất truy cập vào tài nguyên tại 1 thời điểm -> tối ưu phần Atomic
+ Sử dụng cơ chế khóa mutex để lock/unlock tài nguyên 


## lock guard (cơ chế của Mutex)
+ hoạt động như mutex
+ cơ chế tự động lock/unlock 

## Unique lock(cơ chế của Mutex)

+ Tối ưu lock_guard
+ Cho phép lock/unlock 1 cách thủ công hoặc tự động 
+ Ứng dụng trong việc chọn khối lệnh sẽ thực hiện để xử lý tài nguyên chung nào đó chia sẻ giữa nhiều luồng


## So sánh lock guard và unique lock

+ lock guard sẽ khóa cả đoạn code trong phạm vi định nghĩa
+ unique lock sẽ khóa đoạn code mà người dùng mong muốn

## condition variable
+ là 1 class template 
+ cơ chế giao tiếp và đồng bộ cho phép 1 luồng chờ cho đến khi 1 điều kiện cụ thể được đáp ứng, và có thể gửi thông báo khi điều kiện được thực hiện 

-> Áp dụng khi 1 luồng cần chờ dữ liệu từ 1 luồng khác để xử lý
METHOD
+ wait(): Cho phép 1 luồng chờ cho đến khi 1 điều kiện được thực hiện xong 
-> liên tục kiểm tra điều kiện xử lý từ luồng khác bằng cách unlock tạm thời shared resource -> nếu true thì sẽ dừng wait -> xử lý data 
+ notify_one(): gửi thông báo xử lý đến 1 luồng
+ notify_all(): gửi thông báo xử lý đến tất cả các luồng

# LUỒNG BẤT ĐỒNG BỘ
+ Độc lập so với luồng chính

## So sánh với detach()

__Giống nhau__
+ đều chạy độc lập/song song với luông chính

__Khác nhau__

=> khi luồng chính kết thúc

+ detach() cũng sẽ kết thúc theo -> không lấy được kết quả từ luồng chạy detach()

+ Luồng Async vẫn chạy và trả về kết quả  

+ shared_future và future
-> lưu trữ kết quả của luồng bất đồng bộ __nằm ở heap__
-> future: đảm bảo không có luông nào truy cập đến kết quả này __(tương tự unique smart pointer)__
-> shared_future: cho phép kết quả trả về được truy cập bởi nhiều luồngluồng
-> đọc về kết quả thông qua method __get()__ lúc này heap cũng được release luôn
__Cú pháp__

__future<T> async(launch_policy,callable&& func,Args&&... args);__

__+ launch_policy__ chế độ chạy (2 mode)
- async: tạo xong chạy luôn
- deferred: tạo xong đợi khi nào gọi mới chạy

__+ func__ hàm thực thi local/global 

__+ Args__ 

