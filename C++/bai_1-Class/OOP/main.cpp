#include"inher.cpp"

int main() {
    // Encapsulation
    Car basicCar("Toyota", "Corolla", 180);
    basicCar.displayInfo();

  /*   // Inheritance
    ElectricCar tesla("Tesla", "Model 3", 200, 75);
    tesla.displayInfo();

    GasCar toyota("Toyota","Model 2",180);
    toyota.displayInfo();

    // Abstract và Polymorphism
    Car* type[2];
    type[0] = new ElectricCar("Tesla", "Model S", 250, 100);
    type[1] = new GasCar("Toyota","model A",180);
   
    for(auto& car : type)
        car->displayInfo(); */

    return 0;
}
