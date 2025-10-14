#include <iostream>
#include <cstdint>
using namespace std;
class Point
{
private:
    int x, y;

public:
    inline void setX(int xVal) { x = xVal; }
    inline int getX() const { return x; }
    inline void setY(int yVal) { y = yVal; }
    inline int getY() const { return y; }
};
inline int multiply(int a, int b)
{
    return a * b;
}
inline void setRegister(volatile uint32_t *reg, uint32_t value)
{
    *reg = value;
}
inline void toggleLED(volatile uint32_t *port, uint32_t pin)
{
    *port ^= (1 << pin); // Đảo trạng thái pin
}
int main()
{
    /* BASIC EXAMPLE */
     int result = multiply(4, 5);
     cout << "Result: " << result << endl; // Output: Result: 20
     Point p;
     p.setX(10);
     p.setY(20);

     cout << "Point: (" << p.getX() << ", " << p.getY() << ")" << endl; // Output: Point: (10, 20)

    /* EMBEDDED EXAMPLE */

    // Access register
    volatile uint32_t PORTA = 0;
    setRegister(&PORTA, 0xFF); // Ghi giá trị 0xFF vào thanh ghi PORTA

    volatile uint32_t GPIO_PORT = 0;
    toggleLED(&GPIO_PORT, 5); // Toggle LED trên pin 5
    return 0;
}
