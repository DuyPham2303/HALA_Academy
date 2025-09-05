#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
    char* name;
    uint8_t id;
    uint16_t value; 
}SensorData;

// Dành cho dữ liệu nhỏ
int16_t Temp_ReadNow(void); 

// Dành cho dữ liệu phức tạp
bool Sensor_Read(SensorData* out);

// Hằng số dùng cho quá trình tính toán
extern const double pi;  // ok

char* handleString(char* str){
    char buf[30];
    strcpy(buf,str);
    buf[strlen(str)]= '\0';
    printf("%s\n",buf);
    return buf;     // trả về địa chỉ của vùng nhớ đã bị thu hồi
}
// void handleString(char* buf,char* str){
//     strcpy(buf,str);
//     buf[strlen(str)]= '\0';
// }   
int main(){
    char* str = "hello world";

    
    char* rcvBuf = handleString(str);

    //char buf[30];
    //handleString(buf,str);
    printf("%s",rcvBuf);

}
