#include "liftOrder.h"

static int liftOrders[10] = {0};

void setLiftOrders(){
    /*
    //Does not take orders when stop signal
    if (hardware_read_stop_signal ())
        return;
    */
    //Iterates through all the buttons
    for (int floor = 0; floor < 4; floor++) {
        //Checks Heispanel
        if (hardware_read_order (floor, HARDWARE_ORDER_INSIDE)) {
            liftOrders[floor*3] = 1;
            hardware_command_order_light (floor, HARDWARE_ORDER_INSIDE, 1);
        }
        //Checks orders up
        if (hardware_read_order (floor, HARDWARE_ORDER_UP)) {
            liftOrders[floor*3+1] = 1;
            hardware_command_order_light (floor, HARDWARE_ORDER_UP, 1);
        }
        //Checks orders down
        if (hardware_read_order (floor, HARDWARE_ORDER_DOWN)) {
            liftOrders[floor*3-1] = 1;
            hardware_command_order_light (floor, HARDWARE_ORDER_DOWN, 1);
        }
    }
}

void removeOrders(int currFloor){
    //Removes handled orders from liftOrders[]
    liftOrders[currFloor*3] = 0;
    liftOrders[currFloor*3+1] = 0;
    liftOrders[currFloor*3-1] = 0;
    //Turns off lights for handled orders
    hardware_command_order_light (currFloor, HARDWARE_ORDER_INSIDE, 0);
    hardware_command_order_light (currFloor, HARDWARE_ORDER_UP, 0);
    hardware_command_order_light (currFloor, HARDWARE_ORDER_DOWN, 0);
}

void removeAllOrders() {
    for (int i = 0; i < 10; i++)
        removeOrders(i);
}

//Returns 1 if lift should stop at floor
int isCurrentFloorDemanded(int currFloor, HardwareMovement currDir){
    //Makes sure lift stays in valid area
    if ((currDir == HARDWARE_MOVEMENT_DOWN && currFloor == 0) || (currDir == HARDWARE_MOVEMENT_UP && currFloor == 3)) {
        return 1;
    }
    //Demanded by Heispanel
    if (liftOrders[currFloor*3]) {
        return 1;
    }
    //Demanded in current direction, up
    else if (liftOrders[currFloor*3+1] && (currDir == HARDWARE_MOVEMENT_UP)) {
        return 1;
    }
    //Demanded in current direction, down
    else if (liftOrders[currFloor*3-1] && (currDir == HARDWARE_MOVEMENT_DOWN)) {
        return 1;
    }
    //Demanded only in opposite direction
    else if ((currDir == HARDWARE_MOVEMENT_UP) && !orderedAbove(currFloor)) {
        return 1;
    }
    //Demanded only in opposite direction
    else if ((currDir == HARDWARE_MOVEMENT_DOWN) && !orderedBelow(currFloor)) {
        return 1;
    }
    return 0;
}

//husk å ta høyde for at den kan bestilles der den er - :(
HardwareMovement setDirection(int currFloor, HardwareMovement currDir) {
    if (!haveOrders()) {
        return HARDWARE_MOVEMENT_STOP;
    }
    // Må kanskje snu retning her når i 0 og 3
    
    int above = orderedAbove(currFloor);
    int below = orderedBelow(currFloor);
    
    if (above && !below) {
        return HARDWARE_MOVEMENT_UP;
    }
    else if (!above && below) {
        return HARDWARE_MOVEMENT_DOWN;
    }
    //if bare bestilt i currFloor, snu retning
    if (currDir == HARDWARE_MOVEMENT_STOP) {
        return HARDWARE_MOVEMENT_DOWN;
    }
    return currDir;
}

//er heisen krev over gjeldende etasje
int orderedAbove(int currFloor) {
    if (currFloor == 3) {
        return 0;
    }
    for (int i = currFloor*3 + 2; i < 10; i++) {
        if (liftOrders[i]) {
            return 1;
        }
    }
    return 0;
}

//er heisen krev under gjeldende etasje
int orderedBelow(int currFloor) {
    if (currFloor == 0) {
        return 0;
    }
    for (int i = 0; i < currFloor*3 -1; i++) {
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

int orderedAtFloor(int currFloor) {
    for (int i = currFloor*3 - 1; i < currFloor*3 + 2; i++) {
        if (liftOrders[i] && (-1 < i) && (i < 10)) {
            return 1;
        }
    }
    return 0;
}

int atFloor() {
    for (int floor = 0; floor < 4; floor++) {
        if (hardware_read_floor_sensor(floor) == 1){
            hardware_command_floor_indicator_on (floor);
            return floor; //Returns current floor
        }
    }
    return -1; //Returns invalid floor when between floors
}
