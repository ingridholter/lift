#include "drive.h"

int driveToDefinedState() {
    int error = hardware_init();
    if (error != 0) {
        printf("Unable to initialize hardware\n");
        return 0;
    }
    currentFloor = -1;
    while (currentFloor < 0) {
        currentFloor = getFloorNumber();
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    currentState = levelClosed;
    return 1;
}

void stateMachine() {
    stopSignal = hardware_read_stop_signal();
    hardware_command_stop_light(stopSignal);
    if (stopSignal) {
        clearAllOrders();
    }
    else {
        setOrders(); //Checks order buttons
    }
    
    switch (currentState) {
        case levelClosed:
            //-> levelOpen
            if (stopSignal) {
                hardware_command_door_open(1);
                currentState = levelOpen;
                break;
            }
            else {
                currentDir = setDirection(currentFloor, currentDir, 0);
            }
            //-> moving
            if (currentDir != HARDWARE_MOVEMENT_STOP) {
                //Fjern denne dersom koden fungerer uten:
                //currentDir = newDir;
                hardware_command_movement(currentDir);
                betweenFloor = updateBetweenFloor(currentDir, currentFloor);
                currentState = moving;
            }
            break;
            
        case moving:
            if (getFloorNumber() >= 0) {
                currentFloor = getFloorNumber();
            }
            else {
                betweenFloor = updateBetweenFloor(currentDir, currentFloor);
            }
            //-> stationaryBetweenFloors
            if (stopSignal) {
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                currentState = stationaryBetweenFloors;
                break;
            }
            //-> levelOpen
            if (isCurrentFloorDemanded(currentFloor, currentDir) && getFloorNumber() >= 0) {
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                hardware_command_door_open(1);
                currentState = levelOpen;
            }
            break;
        
        case levelOpen:
            if (stopSignal) {
                timerReset();
                break;
            }
            if (isFloorOrdered(currentFloor)) {
                timerReset();
                clearOrders(currentFloor);
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

        case stationaryBetweenFloors:
            if (!stopSignal) {
                currentDir = setDirection(currentFloor, currentDir, betweenFloor);
                //-> moving
                if (currentDir != HARDWARE_MOVEMENT_STOP) {
                    //Fjern denne dersom koden fungerer uten:
                    //currentDir = newDir;
                    hardware_command_movement(currentDir);
                    currentState = moving;
                }
            }
            break;

        default:
            break;
    }
}
