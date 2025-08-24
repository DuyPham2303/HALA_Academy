#include"..//inc//os.hpp"
void delay_ms(uint32_t ms){
     // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    clock_t desired_time = start_time + ms;
    while (clock() < desired_time);
}
void simulation(EngineControlUnit *ECU, uint32_t ms, uint32_t limit)
{
    cout << "CAR STARTS MOVING" << endl;
    while (limit--)
    {   cout<<"-------------"<<endl;
        ECU->readsensor_ECU();
        ECU->display_ECU();
        cout<<"-------------"<<endl;
        delay_ms(ms);
    }
    ECU->DataRecord_ECU();
    cout << "CAR HAS STOPPED" << endl;
}
