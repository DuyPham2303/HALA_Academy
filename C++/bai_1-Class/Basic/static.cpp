#include <iostream>

class UART {
private:
    static int baudRate; // Shared property for baud rate
    int instanceId;      // Each UART has a unique ID
public:
    UART(int id) : instanceId(id) {}

    // Static method to set baud rate
    static void setBaudRate(int rate) {
        baudRate = rate;
    }

    // Static method to get baud rate
    static int getBaudRate() {
        return baudRate;
    }

    // Non-static method to display UART details
    void displayDetails() {
        std::cout << "UART Instance ID: " << instanceId
                  << ", Baud Rate: " << baudRate << std::endl;
    }
};

// Define static member outside the class
int UART::baudRate = 9600; // Default baud rate

int main() {
    UART uart1(1); // UART instance 1
    UART uart2(2); // UART instance 2

    // Set shared baud rate using static method
    UART::setBaudRate(115200);

    // Each instance will use the same baud rate
    uart1.displayDetails();
    uart2.displayDetails();

    // Retrieve shared baud rate
    std::cout << "Shared Baud Rate: " << UART::getBaudRate() << std::endl;

    return 0;
}
