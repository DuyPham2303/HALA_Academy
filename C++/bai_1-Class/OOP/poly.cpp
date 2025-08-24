/*
Polymorphism thể hiện qua việc sử dụng lớp cơ sở để trỏ đến đối tượng lớp con, cho phép xử lý linh hoạt.
myCar là con trỏ kiểu Vehicle nhưng trỏ đến đối tượng kiểu GasCar.
Khi gọi startEngine và stopEngine, chương trình sử dụng phương thức ghi đè của GasCar.
 */
/* #include "inher.cpp"
int main()
{
    Car *myCar = new GasCar();
    myCar->startEngine(); // Gọi phương thức của GasCar thông qua con trỏ Vehicle
    myCar->stopEngine();
    delete myCar; // Giải phóng bộ nhớ
    return 0;
} */
