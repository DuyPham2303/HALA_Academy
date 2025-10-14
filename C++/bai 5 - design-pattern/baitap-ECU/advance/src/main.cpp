#include "..//inc//ecu.hpp"
#include "..//inc//record.hpp"
#include "..//inc//os.hpp"
int main()
{
    EngineControlUnit *ECU1 = EngineControlUnit::ECUInit();
    simulation(ECU1, 250, 100);
    ECU1->diagnostics_ECU();
    
}