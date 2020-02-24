#include "drive.h"



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


stateMachine() {
    switch (currentState) {
        case levelOpen:
            if (stopSignal) {
                hardware_command_stop_light(1);
                removeAllOrders();
                break;
            }
            
            timerReset();
            removeOrders(currentFloor);
            /* Fungerer dette uansett?
            if (isCurrentFloorDemanded(currentFloor, currentDir) {
                timerReset();
                removeOrders(currentFloor);
            }
            */
            if (obstruction) {
                timerReset();
                break;
            }
            
            if (timerExpired() && !stopSignal) {
                hardware_command_door_open(0);
                hardware_command_stop_light(0);
                currentState = levelClosed;
            }
            
            /*
           √  slette ordre
           √  med timer -> endre state til levelClosed
           √  resette dørtimer dersom current Floor bestilles
           √  sjekke stoppknapp -> resette timer, holde dører åpne, ordne stoppknapplys
           √  Husk obstruction
             */
            break;
            
        case levelClosed:
            if (stopSignal) {
                hardware_command_door_open(1);
                currentState = levelOpen;
                break;
            }
            currentDir = setDirection(currentFloor, currentDir);
            hardware_command_movement(currentDir);
            
            if (currentDir != HARDWARE_MOVEMENT_STOP) {
                currentState = moving;
            }
            /*
           √  Bestemme ny retning -> kjøre heis, endre state til moving
             husk å ta høyde for at den kan bestilles der den er
           √  Sjekke stoppknapp -> åpne dør, endre state til level Open
             
             Oppdatere:
           √   HardwareMovement currentDir;
            */
            break;
            
        case moving:
            //Updating currentFloor
            for (int floor = 0; floor < 4; floor++) {
                if (hardware_read_floor_sensor(floor) == 1){
                    prevFloor = currentFloor;
                    currentFloor = floor;
                }
            }
            //Changes floor light to current floor
            hardware_command_floor_indicator_on (currentFloor);
            
            if (isCurrentFloorDemanded(currentFloor, currentDir)) {
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                hardware_command_door_open(1);
                currentState = levelOpen;
            }
            else if (stopSignal) {
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                currentState = stationaryBetweenFloors;
            }
            
            /*
           √  Endre etasjelys
           √  Sjekke om currentFLoor er ønsket -> stopp, åpne dører, endre state til levelOpen
           √  Sjekke stoppknapp -> stopp, endre state til stationaryBetweenFloors:
             
             Oppdatere:
           √  int prevFloor = -1;
           √  int currentFLoor = 5;
            */
            break;
            
        case stationaryBetweenFloors:
            hardware_command_stop_light(1);
            removeAllOrders();
            
            if (!stopSignal) {
                currentDir = setDirection(currentFloor, currentDir);
                hardware_command_movement(currentDir);
                           
                if (currentDir != HARDWARE_MOVEMENT_STOP) {
                    currentState = moving;
                }
            }
            /*
           √  Slette ordre og lys
           √  Ordne stoppknapplys
           √  Sjekke stoppknapp
           √  setDirection når stoppknapp slippes
            */
            break;
            
        default:
            break;
    }
}

