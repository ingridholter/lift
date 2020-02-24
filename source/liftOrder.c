#include "liftOrder.h"

static int liftOrders[10] = {0};


void setLiftOrders(){
    //does not take orders when stop signal
    if (hardware_read_stop_signal ())
        return;
    
    //iterates through all the buttons
    for (int floor = 0; floor < 4; floor++) {
        //checks Heispanel
        if (hardware_read_order (floor, HARDWARE_ORDER_INSIDE)) {
            liftOrders[floor*3] = 1;
            hardware_command_order_light (floor, HARDWARE_ORDER_INSIDE, 1);
        }
        //checks orders up
        if (hardware_read_order (floor, HARDWARE_ORDER_UP)) {
            liftOrders[floor*3+1] = 1;
            hardware_command_order_light (floor, HARDWARE_ORDER_UP, 1);
        }
        //checks orders down
        if (hardware_read_order (floor, HARDWARE_ORDER_DOWN)) {
            liftOrders[floor*3-1] = 1;
            hardware_command_order_light (floor, HARDWARE_ORDER_DOWN, 1);
        }
    }
}

void removeOrders(int currentFloor){
    //Removes handled orders from liftOrders array.
    liftOrders[currentFloor*3] = 0;
    liftOrders[currentFloor*3+1] = 0;
    liftOrders[currentFloor*3-1] = 0;
    //Turns off lights for handled orders.
    hardware_command_order_light (currentFloor, HARDWARE_ORDER_INSIDE, 0);
    hardware_command_order_light (currentFloor, HARDWARE_ORDER_UP, 0);
    hardware_command_order_light (currentFloor, HARDWARE_ORDER_DOWN, 0);
}

void removeAllOrders() {
    for (int i = 0; i < 10; i++)
        removeOrders(i);
}


//returnerer 1 hvis den skal stoppe i etasje og 0 hvis ikke
int isCurrentFloorDemanded(int currentFloor, HardwareMovement currDir){
    /*
    //Makes sure lift stays in valid area
    if ((currDir == HARDWARE_MOVEMENT_DOWN && currentFloor == 0) || (currDir == HARDWARE_MOVEMENT_UP && currentFloor == 3)) {
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    }
    */
    //Demanded by Heispanel
    if (liftOrders[currentFloor*3]) {
        return 1;
    }
    //Demanded in current direction, up
    else if (liftOrders[currentFloor*3+1] && (currDir == HARDWARE_MOVEMENT_UP)) {
        return 1;
    }
    //Demanded in current direction, down
    else if (liftOrders[currentFloor*3-1] && (currDir == HARDWARE_MOVEMENT_DOWN)) {
        return 1;
    }
    //Demanded only in opposite direction
    else if ((currDir == HARDWARE_MOVEMENT_UP) && !orderedAbove(currentFloor)) {
        return 1;
    }
    //Demanded only in opposite direction
    else if ((currDir == HARDWARE_MOVEMENT_DOWN) && !orderedBelow(currentFloor)) {
        return 1;
    }
    return 0;
}

//husk å ta høyde for at den kan bestilles der den er - :(
HardwareMovement setDirection(int currentFloor, HardwareMovement currDir) {
    if (!haveOrders()) {
        return HARDWARE_MOVEMENT_STOP;
    }
    int above = orderedAbove(currentFloor);
    int below = orderedBelow(currentFloor);
    
    if (above && !below) {
        return HARDWARE_MOVEMENT_UP;
    }
    else if (!above && below) {
        return HARDWARE_MOVEMENT_DOWN;
    }
    return currDir;
}


//er heisen krev over gjeldende etasje
int orderedAbove(int currentFloor) {
    for (int i = currentFloor*3 + 2; i < 10; i++) {
        if (liftOrders[i]) {
            return 1;
        }
    }
    return 0;
}

//er heisen krev under gjeldende etasje
int orderedBelow(int currentFloor) {
    for (int i = currentFloor*3 - 2; i > -1; i--) {
        if (liftOrders[i]) {
            return 1;
        }
    }
    return 0;
}

//sjekker om det er ordre i køen
int haveOrders() {
    for (int i = 0; i < 10; i++) {
        if (liftOrders[i] == 1){
            return 1;
        }
    }
    return 0;
}

