#include <iostream>
#include <string>

using namespace std;

typedef enum{
    student,
    teacher
}PersonType;

//Product : mô tả đối tượng tổng quát -> kế thừa bởi lớp con cụ thể
class Person{
    private:
        string name;
        int age;
    public:
        //hàm khởi tạo các thuộc tính chung cho các lớp con 
        Person(string name,int age) : name(name),age(age){}
        virtual void printInfo(){
            cout << "name:" << name << endl;
            cout << "age:" << age << endl;
        }
};

//Concrete Product : lớp con cụ thể
class Student : public Person{
    private:
        float gpa;
        string major;
    public:
        Student(string name,int age,string major,float gpa): Person(name,age) , major(major),gpa(gpa){
           cout << "student created" << endl;
        }

        void printInfo(){
            cout << "student's Info" << endl;
            Person::printInfo();
            cout << "major:" << major << endl
                 << "gpa:" << gpa << endl;
        }
};
//Concrete Product : lớp con cụ thể
class Teacher : public Person{
     private:
        string subject;
        string ID;
    public:
        Teacher(string name,int age,string subject,string ID) : Person(name,age), subject(subject),ID(ID){
           cout << "Teacher created" << endl;
        }

        void printInfo(){
            cout << "Teacher's Info" << endl;
            Person::printInfo();
            cout << "subject:" << subject << endl
                 << "ID:" << ID << endl;
        }
};
//Creational class : lớp khởi tạo tổng quát cho class cụ thể dựa trên tham số đầu vào
class Factory{
    public:
        //truy cập thông qua tên class, mà không cần khởi tạo Instance -
        //-> chỉ dùng với mục đích khởi tạo Instance của class khác (ko cần cấp phát memory để sữ dụng)
        static Person* createPerson(PersonType type){
            if(type == student){
                return new Student("Duy Pham",23,"Co dien tu",3.4);
            }
            else if(type == teacher){
                return new Teacher("Hoang Le",21,"tu dong hoa","ID001");
            }
            else {
                return nullptr;
            }
        }
};


int main(){
    Person* p = Factory::createPerson(PersonType::teacher);

    p->printInfo();

    p = Factory::createPerson(PersonType::student);

    p->printInfo();

    return 0;
}



