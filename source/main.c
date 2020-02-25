/**
 * @file
 * @brief The main function of the application
 */

#include "drive.h"

/*
 IKKE NØDVENDIG: ?
#include "hardware.h"
#include <stdio.h>
#include <stdlib.h>
*/

int main() {
    
    int initialized = driveToDefinedState();
    
    while (initialized) {
        /*
        //Poller hardware
        int stopSignal = hardware_read_stop_signal();
        int obstruction = hardware_read_obstruction_signal();
        
        setLiftOrders(); // Checks order buttons
        */
        
        stateMachine();
        
    }
    return 0;
}
