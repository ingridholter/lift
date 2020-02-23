#include "drive.h"

//Drive variables
// I h-filen?
int prevFloor = -1;
int currentFLoor = 5;
HardwareMovement currentDir;
//må ha en neste tilstand varibabel

/*

for (i=0; i<4;i++){
    if(hardware_floor_sensor(i)==1)
        int prevFloor = currentFloor;
        int currentFloor = hardware_floor_sensor(i);
        return currentFloor;
} //skal vi gjøre med prevFloor
*/

int driveToDefinedState() {
    int error = hardware_init();
    if (error != 0) {
        printf("Unable to initialize hardware\n");
        return 0;
    }
    
    while (currentFloor > 3) {
    //Checks if lift is at floor
        for (int floor = 0; floor < 4; floor++) {
            if (hardware_read_floor_sensor(floor) == 1){
                currentFloor = floor;
            }
        }
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    //Changes floor light to given floor
    hardware_command_floor_indicator_on(currentFloor);
    return 1;
}


//Implementer denne
manageDoor();

stateMachine() {
    switch (liftState) {
            case levelOpen
            
            levelClosed
            moving
            stationaryBetweenFloors
    }
}

