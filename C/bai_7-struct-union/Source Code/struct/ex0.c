#include <stdio.h>
#include <stdint.h> //cung cấp các kiểu số nguyên với kích thước biến đổi khác nhau

/* 
    giả sử muốn định nghĩa ra 1 đối tượng là sinh viên -> yêu cầu cần có datatype kiểu sinh viên
    -> dùng kiểu nguyên thủy int,float,char,double ? (ko hợp lệ)
    Sinh viên là 1 đối tượng được xác định dựa trên 
        - tên       : char[30] (ví dụ lưu trữ mảng ký tự cho tên)
        - tuổi      : int (luu trữ số tuổi)
        - mssv      : char[10] (ví dụ lưu trữ mãng chứa các ký tự số : 17146011) -> dùng kiểu int,double -> chiếm nhiều tài nguyên ko hợp lý
        - ngành học : char[20] (lưu trữ mảng ký tự chứa tên ngành)
        - GPA       : float (lưu điểm số)
    => struct : kiểu cấu trúc tạo ta kiểu mới bằng cách gộp nhiều biến có kiểu khác nhau
        + biến : thành viên
        + định nghĩa kèm từ khóa struct
*/
/* 
    - data alignment 
    - padding byte
    - Size -> cần thiết trong quản lý việc khởi tạo struct, cần lưu ý
        + kiểu dữ liệu khai báo
        + thứ tự sắp xếp 
        =? ảnh hưởng đến memory cấp phát trên RAM nhiều/ít (cần optimize trên embedded system)
*/
/* cách 1 : cơ bản -> dùm kèm typedef để compiler nhậ biết struct data sẽ được thay thế bởi 1 tên định danh mới*/
typedef struct data{
    /* 
        các yếu tố cần quan tâm
            - thứ tự sắp xếp
            - member có size max
    */
    int a;      //1 byte + 3 padding
    double b;   //8 byte
}data;  //bổ sung thêm tên dịnh danh ở đây khi định nghĩa lại struct bằng typedef

//khai báo cách 1 
//struct data dt; //kèm từ khóa struct để compiler biết data là kiểu tự định nghĩa

//khai báo cách 2

data dt1;   //biến -> các member đã được cấp phát mem
data* pdt1;  //con trỏ -> các member chứa có mem


typedef struct dataField{
     //kỹ thuật bitfield
    /* 
        - chỉ định số lượng bit muốn sử dụng
        - ko áp dụng cho biến thường
        - member khai báo ko thể truy cập địa chỉ -> do bộ nhớ bị chia nhỏ (chỉ đọc được địa chỉ với biến có kiểu nhỏ nhất là 1 byte)
        - tối ưu memory
        - những member cùng kiễu share chung 1 vùng địa chỉ, nếu số bit chỉ định không vượt quá kiểu được khai báo
    */
   //cấp phát 0x10 - 0x17 (1 byte)-> lưu a,b 
   uint8_t a : 3; 
   uint8_t b : 4;
   //cấp phát 1 padding byte -> căn chỉnh cho c
   //cấp phát 0x18 - 28 (2 byte) -> lưu c
   uint16_t c : 10; //0x18 -> 0x22 (10 bit) , 0x23 - 0x28 (6 bit thừa)
}dataField; //size = 4

int main(){
    //truy cập biến
    dt1.a = 23;
    dt1.b = 31;
    //truy cập con trỏ
    //pdt1->a = 21;   //lỗi ghi vào vùng nhớ chưa có địa chỉ
    //printf("a = %d",pdt1->a);   //Lỗi segmentation fault

    //gán địa chỉ cụ thể 
    pdt1 = &dt1;
    printf("a = %d",pdt1->a); //truy cập vùng nhớ hợp lệ

    //size ?
    sizeof(dt1); //

    //data alignment ? 
    //-> yêu cầu căn chỉnh của hệ thống : quy định các member có address được cập phát cần chia hết cho datatype của chính nó
    //-> đảm bảo CPU truy cập nhanh chóng đến các vùng nhớ 
    /* 
        -  char,uint8_t (unsigned char) : 1 byte -> 0x01,0x02,0x03,...0xf1,0xf2,0xf3 -> bất cứ vị trí nào
        -  short, uint16_t : 2 byte -> 0x02,0x04,0x06,0x08
        - int,uint32_t,float : 4 byte -> 0x04,0x08,0x0c (12)
        - double,uint64_t : 8 byte -> 0x08,0x10 (16),0x18 (24), 0x20 (32)
    */

    //ví dụ cần lưu trữ giá trị từ 0 - 100 -> dùng 1 byte ? 
    uint8_t data; //2^n - 1 = 0 - 255 (vẫn tốn dung lượng ) -> chỉ cần 2^7 - 1 : 0 - 127
   
    sizeof(dataField);
    return 0;
}