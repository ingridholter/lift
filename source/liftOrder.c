#include "liftOrder.h"


//legge til i liftOrders hvilke knapper som er trykket? checkButtons
// Eventuelt ikke sjekke 1, NED og 4, OPP
void setLiftOrders(){
    if (hardware_read_stop_signal ())
        return;
    
    for (int floor = 0; floor < 4; floor++) {
        
        if (hardware_read_order (floor, HARDWARE_ORDER_INSIDE)) {
            liftOrders[floor] = 1;
            hardware_command_order_light (floor, HARDWARE_ORDER_INSIDE, 1);
        }
            
        if (hardware_read_order (floor, HARDWARE_ORDER_UP)) {
            liftOrders[floor+4] = 1;
            hardware_command_order_light (floor, HARDWARE_ORDER_UP, 1);
        }
        
        if (hardware_read_order (floor, HARDWARE_ORDER_DOWN)) {
            liftOrders[floor+6] = 1;
            hardware_command_order_light (floor, HARDWARE_ORDER_DOWN, 1);
        }
    }
}

void removeOrders(int currentFloor){
    //Removes handled orders from liftOrders array.
    liftOrders[currentFloor] = 0;
    liftOrders[currentFloor+4] = 0;
    liftOrders[currentFloor+6] = 0;
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
int isCurrentFloorDemanded(int currentFloor, HardwareMovement currentDir){
    if (liftOrders[currentFloor])
        return 1;
    if ((currentDir == HARDWARE_MOVEMENT_UP) && liftOrders[currentFloor+4])
        return 1;
    if ((currentDir == HARDWARE_MOVEMENT_DOWN) && liftOrders[currentFloor+6])
        return 1;
    return 0;
}


//setter heisens retning 1:ned og 0:opp
//går gjennom array og sjekker
HardwareMovement setDirection(int currentFloor, HardwareMovement currentDir) {
    if (!= haveOrders()) {
        return HARDWARE_MOVEMENT_STOP;
    }
    
    int above = orderedAbove(currentFloor);
    int below = orderedBelow(currentFloor);
    
    if (above && != below) {
        return HARDWARE_MOVEMENT_UP;
    }
    else if (!= above && below) {
        return HARDWARE_MOVEMENT_DOWN;
    }
    else {
        switch (currentDir) {
            case HARDWARE_MOVEMENT_UP:
                for (int i = currentFloor; i < 4; i++) {
                    if (liftOrder[i]) {
                        return HARDWARE_MOVEMENT_UP;
                    }
                }
                return HARDWARE_MOVEMENT_DOWN
                break;
                
            case HARDWARE_MOVEMENT_DOWN:
                    for (int i = 0; i < currentFloor+1; i++) {
                        if (liftOrder[i]) {
                            return HARDWARE_MOVEMENT_DOWN;
                        }
                    }
                    return HARDWARE_MOVEMENT_UP
                break;
                
            default:
                break;
        }
    }
    return HARDWARE_MOVEMENT_STOP;
}

//er heisen krevd over gjeldene etasje
int orderedAbove(int currentFloor) {
    switch (currentFloor) {
        case 0:
            for (int i = 0; i < 10; i++) {
                if (liftOrders[i] == 1){
                    return 1;
                }
            }
            break;
            
        case 1:
            for (int i = 2; i < 10; i++) {
                if ((i != 4 || i != 5 || i != 7) && liftOrders[i] == 1) {
                    return 1;
                }
            }
            break;
            
        case 2:
            if (liftOrders[3] == 1 || liftOrders[9] == 1) {
                    return 1;
                }
            break;
            
        case 3:
            return 0;
            break;
            
        default:
            break;
    }
    return 0;
}

//er heisen krev under gjeldende etasje
int orderedBelow(int currentFloor) {
    switch (currentFloor) {
        case 0:
            return 0;
            break;
            
        case 1:
            if (liftOrders[0] == 1 || liftOrders[4] == 1) {
                    return 1;
                }
            break;
            
        case 2:
            for (int i = 0; i < 8; i++) {
                if ((i != 2 || i%3 != 0) && liftOrders[i] == 1) {
                    return 1;
                }
            }
            break;
            
        case 3:
            for (int i = 0; i < 10; i++) {
                if (liftOrders[i] == 1){
                    return 1;
                }
            }
            break;
            
        default:
            break;
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

