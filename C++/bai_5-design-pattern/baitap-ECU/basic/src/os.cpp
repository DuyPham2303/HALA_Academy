#include"..//inc//os.hpp"
void delay_ms(size_t ms){
     // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    clock_t desired_time = start_time + ms;
    while (clock() < desired_time);
}
void simulation(Engine& subject,size_t time_ms,uint8_t limit){
    cout << "Begin communication between OBSERVER and SUBJECT" << endl;
    while(limit-- > 0){
        cout << "-----------" << endl;
        subject.setEngineState();
        cout << "-----------" << endl;
        delay_ms(time_ms);
    }
    cout << "Communication has ended" << endl;
}
