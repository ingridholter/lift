/**
 * @file
 * @brief The main file of the application
 */

#include "hardware.h"
#include "drive.h"

//Initialiserer
bool driveToDefinedState() {
    int hardware_init ();
    // If “ikke i etasje” {kjør ned til etasje}
    //  if “etasje” {sett etasje+lys, åpne for bestillinger}
    return TRUE;
}

void main {
    
    bool initialized = driveToDefinedState();
    
    while (initialized) {
        //Poller hardware
        int stopSignal = hardware_read_stop_signal();
        int obstruction = hardware_read_obstruction_signal();
        
        checkOrderButtons();
        
        stateMachine();
        
    }
}
