/**
 * @file
 * @brief The main function of the application
 */

//#include "drive.h"

#include "liftOrder.h"
#include "timer.h"


int driveToDefinedState() {
    int error = hardware_init();
    if (error != 0) {
        printf("Unable to initialize hardware\n");
        return 0;
    }
    currentFloor = -1;
    while (currentFloor < 0) {
        currentFloor = atFloor();
        //Drives down until it is at floor
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    currentState = levelClosed;
    return 1;
}

int main() {
    int initialized = driveToDefinedState();
    
    while (initialized) {
        //stateMachine();
    }
    return 0;
}
