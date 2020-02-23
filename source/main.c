/**
 * @file
 * @brief The main file of the application
 */

// #include "hardware.h"
#include "drive.h"


void main {
    
    bool initialized = driveToDefinedState();
    
    while (initialized) {
        //Poller hardware
        int stopSignal = hardware_read_stop_signal();
        int obstruction = hardware_read_obstruction_signal();
        
        setLiftOrders(); // Checks order buttons
        
        stateMachine();
        
    }
}
