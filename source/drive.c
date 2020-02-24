#include "drive.h"


int driveToDefinedState() {
    int error = hardware_init();
    if (error != 0) {
        printf("Unable to initialize hardware\n");
        return 0;
    }
    currFloor = -1;
    while (currFloor < 0) {
        //Checks if lift is at floor
        currFloor = atFloor();
        //Drives down until it is at floor
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    currentDir = HARDWARE_MOVEMENT_DOWN;
    currentState = levelClosed;
    return 1;
}

int atFloor() {
    for (int floor = 0; floor < 4; floor++) {
        if (hardware_read_floor_sensor(floor) == 1){
            //Changes floor light to current floor
            hardware_command_floor_indicator_on (floor);
            return floor;
        }
    }
    return -1;
}

void stateMachine() {
    setLiftOrders(); // Checks order buttons
    stopSignal = hardware_read_stop_signal();
    /*
    //Makes sure lift stays in valid area
    if ((currentDir == HARDWARE_MOVEMENT_DOWN && currFloor == 0) || (currentDir == HARDWARE_MOVEMENT_UP && currFloor == 3)) {
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    }
    */
    switch (currentState) {
        case levelOpen:
            //stop signal
            if (stopSignal) {
                hardware_command_stop_light(1); //turn on stop light
                removeAllOrders(); //remove orders
                break;
            }
            //remove Orders
            else {
                removeOrders(currFloor);
                hardware_command_stop_light(0);
            }
            //obstruction
            if (hardware_read_obstruction_signal()) {
                timerReset();
                break;
            }
            //-> levelClosed
            if (timerExpired()) {
                hardware_command_door_open(0);
                hardware_command_stop_light(0);
                currentState = levelClosed;
            }
            break;
            
            
        case levelClosed:
            //stop signal -> levelOpen
            if (hardware_read_stop_signal()) {
                hardware_command_door_open(1);
                currentState = levelOpen;
                break;
            }
            //direction
            else {
                newDir = setDirection(currFloor, currentDir);
            }
            //-> moving
            if (newDir != HARDWARE_MOVEMENT_STOP) {
                between = 1;
                currentDir = newDir;
                hardware_command_movement(currentDir);
                currentState = moving;
            }
            break;
            
            
        case moving:
            //current floor
            if (atFloor() >= 0 && atFloor() != currFloor) {
                currFloor = atFloor();
                between = 0;
            }
            
            //-> stop signal
            if (hardware_read_stop_signal()) {
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                currentState = stationaryBetweenFloors;
                break;
            }
            
            //-> levelOpen
            if (isCurrentFloorDemanded(currFloor, currentDir)) {
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                timerReset();
                hardware_command_door_open(1);
                currentState = levelOpen;
            }
            break;
            
            
        case stationaryBetweenFloors:
            //stop light, remove orders
            hardware_command_stop_light(1);
            removeAllOrders();
            //not stop signal -> moving
            if (!hardware_read_stop_signal()) {
                hardware_command_stop_light(0);
                currentDir = setDirection(currFloor, currentDir);
                hardware_command_movement(currentDir);
                           
                if (currentDir != HARDWARE_MOVEMENT_STOP) {
                    between = 1;
                    currentState = moving;
                }
            }
            break;
            
        default:
            break;
    }
}
