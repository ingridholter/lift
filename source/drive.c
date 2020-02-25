#include "drive.h"

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

void stateMachine() {
    stopSignal = hardware_read_stop_signal();
    hardware_command_stop_light(stopSignal);
    if(!hardware_read_stop_signal()){
        setLiftOrders(); //Checks order buttons
    }
 
    
    switch (currentState) {
        case levelOpen:
            if (stopSignal) {
                removeAllOrders();
                timerReset();
                break;
            }
            if (orderedAtFloor(currentFloor)) {
                timerReset();
                removeOrders(currentFloor);
                break;
            }
            else {
                removeOrders(currentFloor);
            }
            //obstruction
            if (hardware_read_obstruction_signal()) {
                timerReset();
                break;
            }
            //-> levelClosed
            if (timerExpired()) {
                hardware_command_door_open(0);
                currentState = levelClosed;
            }
            break;
            
        case levelClosed:
            //-> levelOpen
            if (stopSignal) {
                hardware_command_door_open(1);
                currentState = levelOpen;
                break;
            }
            else {
                newDir = setDirection(currentFloor, currentDir);
            }
            //-> moving
            if (newDir != HARDWARE_MOVEMENT_STOP) {
                currentDir = newDir;
                hardware_command_movement(currentDir);
                currentState = moving;
            }
            break;
            
        case moving:
            if (atFloor() >= 0) {
                currentFloor = atFloor();
            }
            //-> stationaryBetweenFloors
            if (stopSignal) {
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                currentState = stationaryBetweenFloors;
                break;
            }
            //-> levelOpen
<<<<<<< HEAD
            if (isCurrentFloorDemanded(currentFloor, currentDir) && atFloor() >= 0) {
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                hardware_command_door_open(1);
=======
            if (isCurrentFloorDemanded(currentFloor, currentDir)&& atFloor()>=0) {
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                hardware_command_door_open(1);
                //timerReset();
>>>>>>> b9118d151dee9a27ca6773f558241d59abc15b28
                currentState = levelOpen;
            }
            break;
            
        case stationaryBetweenFloors:
            if (stopSignal) {
                removeAllOrders();
            }
            else {
                newDir = setDirection(currentFloor, currentDir);
                //-> moving
                if (newDir != HARDWARE_MOVEMENT_STOP) {
                    currentDir = newDir;
                    hardware_command_movement(currentDir);
                    currentState = moving;
                }
            }
            break;
            
        default:
            break;
    }
}
