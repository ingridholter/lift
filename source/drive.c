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
    setLiftOrders(); //Checks order buttons
    hardware_command_stop_light(hardware_read_stop_signal());
    
    switch (currentState) {
        case levelOpen:
            if (hardware_read_stop_signal()) {
                removeAllOrders();
                timerReset();
                //hardware_command_stop_light(hardware_read_stop_signal());
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
            if (hardware_read_stop_signal()) {
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
            if (hardware_read_stop_signal()) {
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                currentState = stationaryBetweenFloors;
                break;
            }
            //-> levelOpen
            if (isCurrentFloorDemanded(currentFloor, currentDir)) {
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                hardware_command_door_open(1);
                timerReset();
                currentState = levelOpen;
            }
            break;
            
        case stationaryBetweenFloors:
            if (hardware_read_stop_signal()) {
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
