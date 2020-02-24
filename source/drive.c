#include "drive.h"


int driveToDefinedState() {
    int error = hardware_init();
    if (error != 0) {
        printf("Unable to initialize hardware\n");
        return 0;
    }
    currFloor = 5;
    while (currFloor > 3) {
    //Checks if lift is at floor
        for (int floor = 0; floor < 4; floor++) {
            if (hardware_read_floor_sensor(floor) == 1){
                currFloor = floor;
            }
        }
        //Drives down until it is at floor
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    currentDir = HARDWARE_MOVEMENT_DOWN;
    //Changes floor light to given floor
    hardware_command_floor_indicator_on(currFloor);
    currentState = levelClosed;
    return 1;
}


void stateMachine() {
    switch (currentState) {
        case levelOpen:
            if (hardware_read_stop_signal()) {
                hardware_command_stop_light(1);
                removeAllOrders();
                break;
            }
            setLiftOrders(); // Checks order buttons
            removeOrders(currFloor);
            /* Fungerer dette uansett?
            if (isCurrentFloorDemanded(currentFloor, currentDir) {
                timerReset();
                removeOrders(currentFloor);
            }
            */
            if (hardware_read_obstruction_signal()) {
                timerReset();
                break;
            }
            
            if (timerExpired() && !hardware_read_stop_signal()) {
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
            if (hardware_read_stop_signal()) {
                hardware_command_door_open(1);
                currentState = levelOpen;
                break;
            }
            setLiftOrders(); // Checks order buttons
            currentDir = setDirection(currFloor, currentDir);
            hardware_command_movement(currentDir);
            
            if (currentDir != HARDWARE_MOVEMENT_STOP) {
                currentState = moving;
                break;
            }
            /*
            if (!haveOrders()) {
                currentDir = HARDWARE_MOVEMENT_STOP;
            }
             */
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
                    preFloor = currFloor;
                    currFloor = floor;
                }
            }
            setLiftOrders(); // Checks order buttons
            //Changes floor light to current floor
            hardware_command_floor_indicator_on (currFloor);
            
            if (isCurrentFloorDemanded(currFloor, currentDir)) {
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                hardware_command_door_open(1);
                timerReset();
                currentState = levelOpen;
            }
            else if (hardware_read_stop_signal()) {
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
            
            if (!hardware_read_stop_signal()) {
                hardware_command_stop_light(0);
                currentDir = setDirection(currFloor, currentDir);
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


