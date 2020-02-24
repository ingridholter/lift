/**
 * @file
 * @brief The main function of the application
 */

//hei
//#include "hardware.h"
#include "drive.h"
//#include <stdio.h>
//#include <stdlib.h>


int main() {
    
    int initialized = driveToDefinedState();
    
    while (initialized) {
        /*
        //Poller hardware
        int stopSignal = hardware_read_stop_signal();
        int obstruction = hardware_read_obstruction_signal();
        
        setLiftOrders(); // Checks order buttons
        */
        stopSignal = hardware_read_stop_signal();
        hardware_command_stop_light(stopSignal);
        stateMachine();
        
    }
    return 0;
}
