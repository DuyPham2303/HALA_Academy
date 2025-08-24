#include <iostream>
#include <cstdlib> // Cần cho hàm rand và srand
#include <ctime>   // Cần cho hàm time nếu muốn tạo seed ngẫu nhiên
using namespace std;
void test_create_Random_Number_inRange()
{
    srand(time(0));                      // Khởi tạo seed bằng thời gian thực
    int randomNumber = 1 + rand() % 100; // Tạo số từ 1 đến 100
    std::cout << randomNumber << std::endl;
}
void test_create_RandomNumber_once()
{
    srand(time(0));
    for (int i = 0; i < 7; i++)
    {
        int random = 1 + rand() % 20;
        cout << random << " ";
    }
}
void test_create_Float_Random()
{
    srand(time(0));
    double randomFloat = static_cast<double>(rand()) / 10;
    for (int i = 0; i < 7; i++)
        cout << randomFloat << " ";
}
void test_create_RandomArr()
{
    srand(time(0)); // Seed
    const int SIZE = 10;
    int arr[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = 1 + rand() % 100; // Số ngẫu nhiên từ 1 đến 100
        std::cout << arr[i] << " ";
    }
}
int main()
{
    test_create_RandomArr();
    return 0;
}