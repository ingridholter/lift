#include "liftOrder.h"
//Prøv å flytte dette til headerfil
const int liftOrdersSize = 10;
static int liftOrders[liftOrdersSize] = {0};
const int lowerFloor = 0;
const int upperFloor = 3;

int ordersDown(int floor) {
    return floor * 3 - 1;
}
int ordersInside(int floor){
    return floor * 3;
}
int ordersUp(int floor){
    return floor * 3 + 1;
}

//brukes i drive, 1 gang
void setOrders() {
     for (int floor = lowerFloor; floor < HARDWARE_NUMBER_OF_FLOORS; floor++) {
        if (hardware_read_order (floor, HARDWARE_ORDER_INSIDE)) {
            liftOrders[ordersInside(floor)] = 1;
            hardware_command_order_light (floor, HARDWARE_ORDER_INSIDE, 1);
        }
        if (hardware_read_order (floor, HARDWARE_ORDER_UP) && floor < upperFloor) {
            liftOrders[ordersUp(floor)] = 1;
            hardware_command_order_light (floor, HARDWARE_ORDER_UP, 1);
        }
        if (hardware_read_order (floor, HARDWARE_ORDER_DOWN) && floor > lowerFloor) {
            liftOrders[ordersDown(floor)] = 1;
            hardware_command_order_light (floor, HARDWARE_ORDER_DOWN, 1);
        }
    }
}
//brukes i liftOrder, 1 gang
//brukes i drive, 1 gang
void clearOrders(int currFloor){
    liftOrders[ordersInside(currFloor)] = 0;
    hardware_command_order_light (currFloor, HARDWARE_ORDER_INSIDE, 0);
    
    if (currFloor < upperFloor) {
        liftOrders[ordersDown(currFloor)] = 0;
        hardware_command_order_light (currFloor, HARDWARE_ORDER_UP, 0);
    }
    if (currFloor > lowerFloor) {
        liftOrders[ordersUp(currFloor)] = 0;
        hardware_command_order_light (currFloor, HARDWARE_ORDER_DOWN, 0);
    }
}

//brukes i drive, 1 gang
void clearAllOrders() {
    for (int i = lowerFloor; i < HARDWARE_NUMBER_OF_FLOORS; i++)
        clearOrders(i);
}

//brukes i liftOrder
int orderedAbove(int currFloor) {
    if (currFloor == upperFloor) {
        return 0;
    }
    //for (int i = currFloor * 3 + 2; i < 10; i++) {
    for (int i = ordersDown(currFloor + 1); i < liftOrdersSize; i++) {
        if (liftOrders[i]) {
            return 1;
        }
    }
    return 0;
}

//brukes i liftOrder
int orderedBelow(int currFloor) {
    if (currFloor == lowerFloor) {
        return 0;
    }
    //for (int i = 0; i < currFloor*3 -1; i++) {
    for (int i = 0; i < ordersUp(currFloor - 1); i++) {
        if (liftOrders[i]) {
            return 1;
        }
    }
    return 0;
}

//Brukes kun i liftOrder, 1 gang
int checkIfOrders() {
    for (int i = 0; i < liftOrdersSize; i++) {
        if (liftOrders[i] == 1){
            return 1;
        }
    }
    return 0;
}

//brukes i drive, 2 ganger
HardwareMovement setDirection(int currFloor, HardwareMovement currDir, int betwFloor) {
    int above;
    int below;
    
    if (!checkIfOrders()) {
        return HARDWARE_MOVEMENT_STOP;
    }
    if (betwFloor) {
        above = orderedAbove(betwFloor - 1);
        below = orderedBelow(betwFloor);
    }
    else {
        above = orderedAbove(currFloor);
        below = orderedBelow(currFloor);
    }
    if (above && !below) {
        return HARDWARE_MOVEMENT_UP;
    }
    else if (!above && below) {
        return HARDWARE_MOVEMENT_DOWN;
    }
    if (currDir == HARDWARE_MOVEMENT_STOP) {
        return HARDWARE_MOVEMENT_DOWN;
    }
    return currDir;
}

//Brukes i drive, 1 gang
int isCurrentFloorDemanded(int currFloor, HardwareMovement currDir) {
    if ((currDir == HARDWARE_MOVEMENT_DOWN && currFloor == lowerFloor) || (currDir == HARDWARE_MOVEMENT_UP && currFloor == upperFloor)) {
        return 1;
    }
    if (liftOrders[ordersInside(currFloor)]) {
        return 1;
    }
    else if (liftOrders[ordersUp(currFloor)] && (currDir == HARDWARE_MOVEMENT_UP)) {
        return 1;
    }
    else if (liftOrders[ordersDown(currFloor)] && (currDir == HARDWARE_MOVEMENT_DOWN)) {
        return 1;
    }
    else if ((currDir == HARDWARE_MOVEMENT_UP) && !orderedAbove(currFloor)) {
        return 1;
    }
    else if ((currDir == HARDWARE_MOVEMENT_DOWN) && !orderedBelow(currFloor)) {
        return 1;
    }
    return 0;
}

//brukes kun i drive, 1 gang
int isFloorOrdered(int currFloor) {
    /*
    switch (currFloor) {
        case 0:
            if (liftOrders[floor0Inside] || liftOrders[floor0Up]) {
                return 1;
            }
            break;
        case 1:
            if (liftOrders[floor1Down] || liftOrders[floor1Inside] || liftOrders[floor1Up]) {
                return 1;
            }
            break;
        case 2:
            if (liftOrders[floor2Down] || liftOrders[floor2Inside] || liftOrders[floor2Up]) {
                return 1;
            }
            break;
        case 3:
            if (liftOrders[floor3Down] || liftOrders[floor3Inside]) {
                return 1;
            }
            break;
        default:
            break;
    }
    */
    if ((liftOrders[ordersDown(currFloor)] && currFloor > lowerFloor) || liftOrders[ordersInside(currFloor)] || (liftOrders[ordersUp(currFloor)] && currFloor < upperFloor)) {
        return 1;
    }
        
    return 0;
}

//brukes i drive og initialize
int getFloorNumber() {
    for (int floor = lowerFloor; floor < HARDWARE_NUMBER_OF_FLOORS; floor++) {
        if (hardware_read_floor_sensor(floor) == 1) {
            hardware_command_floor_indicator_on (floor);
            return floor;
        }
    }
    return -1;
}

//brukes i drive, 1 gang
int updateBetweenFloor(HardwareMovement currDir, int currFloor) {
    if (currDir == HARDWARE_MOVEMENT_UP) {
        return currFloor + 1;
    }
    else {
        return currFloor;
    }
}
