/**
 * @file
 * @brief The main function of the application
 */

#include "drive.h"

int main() {
    int initialized = driveToDefinedState();
    
    while (initialized) {
        stopSignal = hardware_read_stop_signal();
        hardware_command_stop_light(stopSignal);
        //stateMachine();
    }
    return 0;
}
