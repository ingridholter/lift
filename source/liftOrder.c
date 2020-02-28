#include "liftOrder.h"

#define liftOrdersSize 10
int liftOrders[liftOrdersSize] = {0};
const int lowerFloor = 0;
const int upperFloor = 3;

int ordersDown(int floor) {
    return floor * 3 - 1;
}
int ordersInside(int floor) {
    return floor * 3;
}
int ordersUp(int floor) {
    return floor * 3 + 1;
}

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

void clearOrders(int currFloor) {
    liftOrders[ordersInside(currFloor)] = 0;
    hardware_command_order_light (currFloor, HARDWARE_ORDER_INSIDE, 0);
    
    if (currFloor < upperFloor) {
        liftOrders[ordersUp(currFloor)] = 0;
        hardware_command_order_light (currFloor, HARDWARE_ORDER_UP, 0);
    }
    if (currFloor > lowerFloor) {
        liftOrders[ordersDown(currFloor)] = 0;
        hardware_command_order_light (currFloor, HARDWARE_ORDER_DOWN, 0);
    }
}

void clearAllOrders() {
    for (int i = lowerFloor; i < HARDWARE_NUMBER_OF_FLOORS; i++)
        clearOrders(i);
}

int orderedAbove(int currFloor) {
    if (currFloor == upperFloor) {
        return 0;
    }
    for (int i = ordersUp(currFloor) + 1; i < liftOrdersSize; i++) {
        if (liftOrders[i]) {
            return 1;
        }
    }
    return 0;
}

int orderedBelow(int currFloor) {
    if (currFloor == lowerFloor) {
        return 0;
    }
    for (int i = 0; i < ordersDown(currFloor); i++) {
        if (liftOrders[i]) {
            return 1;
        }
    }
    return 0;
}

int checkIfOrders() {
    for (int i = 0; i < liftOrdersSize; i++) {
        if (liftOrders[i] == 1) {
            return 1;
        }
    }
    return 0;
}

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

int isCurrentFloorDemanded(int currFloor, HardwareMovement currDir) {
    if ((currDir == HARDWARE_MOVEMENT_DOWN && currFloor == lowerFloor) || (currDir == HARDWARE_MOVEMENT_UP && currFloor == upperFloor)) {
        return 1;
    }
    else if (liftOrders[ordersInside(currFloor)]) {
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

int isFloorOrdered(int currFloor) {
    if ((liftOrders[ordersDown(currFloor)] && currFloor > lowerFloor) || liftOrders[ordersInside(currFloor)] || (liftOrders[ordersUp(currFloor)] && currFloor < upperFloor)) {
        return 1;
    }
    return 0;
}

int getFloorNumber() {
    for (int floor = lowerFloor; floor < HARDWARE_NUMBER_OF_FLOORS; floor++) {
        if (hardware_read_floor_sensor(floor) == 1) {
            hardware_command_floor_indicator_on (floor);
            return floor;
        }
    }
    return -1;
}

int updateNextFloor(int currFloor, HardwareMovement currDir) {
    if (currDir == HARDWARE_MOVEMENT_UP) {
        return currFloor + 1;
    }
    else {
        return currFloor - 1;
    }
}

int updateBetweenFloor(int nFloor, int currFloor) {
    if (nFloor > currFloor) {
        return nFloor;
    }
    else {
        return currFloor;
    }
}
