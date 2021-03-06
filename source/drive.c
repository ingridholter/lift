#include "drive.h"

int currentFloor;
int nextFloor;
int betweenFloor;
int stopSignal;
HardwareMovement currentDir;
liftState currentState;

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
        setOrders();
    }
    
    switch (currentState) {
        case levelClosed:
            if (stopSignal) {
                hardware_command_door_open(1);
                currentState = levelOpen;
                break;
            }
            else {
                currentDir = setDirection(currentFloor, currentDir, 0);
            }
            if (currentDir != HARDWARE_MOVEMENT_STOP) {
                hardware_command_movement(currentDir);
                currentState = moving;
            }
            break;
            
        case moving:
            if (getFloorNumber() >= 0) {
                currentFloor = getFloorNumber();
                nextFloor = updateNextFloor(currentFloor, currentDir);
                betweenFloor = updateBetweenFloor(nextFloor, currentFloor);
            }
            if (stopSignal) {
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                currentState = stationaryBetweenFloors;
                break;
            }
            if (isCurrentFloorDemanded(currentFloor, currentDir) && getFloorNumber() >= 0) {
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                hardware_command_door_open(1);
                currentState = levelOpen;
            }
            else
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
            if (hardware_read_obstruction_signal()) {
                timerReset();
                break;
            }
            if (timerExpired()) {
                hardware_command_door_open(0);
                currentState = levelClosed;
            }
            break;

        case stationaryBetweenFloors:
            if (!stopSignal) {
                currentDir = setDirection(currentFloor, currentDir, betweenFloor);
                if (currentDir != HARDWARE_MOVEMENT_STOP) {
                    hardware_command_movement(currentDir);
                    currentState = moving;
                }
            }
            break;

        default:
            break;
    }
}
