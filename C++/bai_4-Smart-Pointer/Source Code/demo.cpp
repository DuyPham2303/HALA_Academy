#include <iostream>
#include <memory>
using namespace std;
template<typename T>
class Uniqueptr{
    private:
        T *raw; //point to managed object
    public:
        Uniqueptr(T *p = nullptr){ // : raw(p){}
            raw = p;
        }
        ~Uniqueptr(){
            if(raw)
                delete raw;
        }
        //ngăn chặn việc sao chép hoặc trỏ đến đối tượng Uniqueptr
        Uniqueptr(const Uniqueptr&) = delete; //without delete -> other object to copy

        // trả về tham chiếu đến đối tượng Uniqueptr 
        /*
            -> không cho phép gán 2 object bằng nhau
            -> nghĩa là sẽ không có cùng lúc 2 raw pointer cùng trỏ đến 1 object

        */
        Uniqueptr& operator = (const Uniqueptr&) = delete; // nếu không gán delete vẫn cho phép gán 2 object bằng nhau
        /** 
            * @brief truy xuất giá trị của đối tượng mà raw trỏ đến
            * @return giá trị mà raw lưu trũ (địa chỉ của đối tượng)
         */
        T& operator *() const{ //từ khóa const ngăn chặn việc thay đổi giá trị
            return *raw; 
        }
        /** 
            * @brief truy cập thành viên của object
            * @return giá trị của thành viên
        */
        T* operator ->() const{
            return raw;
        }
        /** 
            * @brief con trỏ đến object 
            * @return trả về giá trị của raw (địa chỉ của đối tượng mà raw trỏ đến)
        */
        T* get() const{
            return raw; 
        }
        /** 
            * @brief chuyển quyền sở hữu 
            * @return trả về con trỏ raw trước khi giải phóng
         */
        T* release() const{
            T* temp = raw;
            raw = nullptr;
            return temp;
        }
        /** 
            * @brief giải phóng đối tượng hiện tại và quản lý đối tượng mới
            * @return trả về con trỏ raw đến đối tượng mới 
         */
        void reset(T* new_raw = nullptr){
            if(raw){
                delete raw;
            }
            raw = new_raw;
        }

};

int main(){ 
  Uniqueptr<int> uptr(new int(10)); // gọi tự động Uniqueptr(const Uniqueptr&) 
  

  //ngăn chặn gán uptr cho uptr1
  //Uniqueptr<int> uptr1 = uptr; 
  
  // nếu viết như này ->  Uniqueptr(const Uniqueptr&) sẽ không được gọi 
  // mà sẽ gọi  Uniqueptr& operator = (const Uniqueptr&) 
  //uptr1 = uptr; 

  //truy cập và in giá trị raw trỏ đến thông qua hàm  T& operator *() const
  //là hàm định nghĩa lại toán tử * để object có thể hiểu được 

  //value of object pointed by raw
  cout << *uptr << endl;
  int* raw_value = uptr.get();  
  cout << raw_value << endl; //address of object pointed by raw 
  cout << *raw_value << endl;
  cout << uptr.get() << endl; 

  //int* uptr1 = uptr.release();
  //cout << *uptr1 << endl;
  //cout << uptr.get();

  uptr.reset(new int(40));
  cout << "value: " << *uptr << endl;
}