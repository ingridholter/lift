#include "liftOrder.h"

static int liftOrders[10] = {0};

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
int isCurrentFloorDemanded(int currentFloor, HardwareMovement currDir){
    if (liftOrders[currentFloor]) {
        return 1;
    }
    /*
    if (currentFloor == 3) {
        currDir = HARDWARE_MOVEMENT_DOWN;
    }
    else if (currentFloor == 0) {
        currDir = HARDWARE_MOVEMENT_UP;
    }
    */
    if (liftOrders[currentFloor+4] && (currDir == HARDWARE_MOVEMENT_UP)) {
        return 1;
    }
    if (liftOrders[currentFloor+6] && (currDir == HARDWARE_MOVEMENT_DOWN)) {
        return 1;
    }
    if ((currDir == HARDWARE_MOVEMENT_UP) && !orderedAboveUp(currentFloor) && liftOrders[currentFloor+6]) {
        return 1;
    }
    if ((currDir == HARDWARE_MOVEMENT_DOWN) && !orderedBelowDown(currentFloor) && liftOrders[currentFloor+4]) {
        return 1;
    }
    return 0;
}


//setter heisens retning 1:ned og 0:opp
//går gjennom array og sjekker
//husk å ta høyde for at den kan bestilles der den er - :(
HardwareMovement setDirection(int currentFloor, HardwareMovement currDir) {
    if (!haveOrders()) {
        return HARDWARE_MOVEMENT_STOP;
    }
    
    int above = orderedAboveUp(currentFloor) || orderedAboveDown(currentFloor);
    
    int below = orderedBelowUp(currentFloor) || orderedBelowUp(currentFloor);
    
    if (above && !below) {
        return HARDWARE_MOVEMENT_UP;
    }
    else if (!above && below) {
        return HARDWARE_MOVEMENT_DOWN;
    }
    else {
        switch (currDir) {
            case HARDWARE_MOVEMENT_UP:
                //Lift continues up if ordered above currentFloor on Heispanel
                for (int i = currentFloor; i < 4; i++) {
                    if (liftOrders[i]) {
                        return HARDWARE_MOVEMENT_UP;
                    }
                }
                //Lift changes direction if ordered below currentFloor on Heispanel
                for (int i = 0; i < currentFloor+1; i++) {
                    if (liftOrders[i]) {
                        return HARDWARE_MOVEMENT_DOWN;
                    }
                }
                //If not ordered on Heispanel, lift continues up
                return HARDWARE_MOVEMENT_UP;
                break;
                
            case HARDWARE_MOVEMENT_DOWN:
                //Lift continues down if ordered below currentFloor on Heispanel
                for (int i = 0; i < currentFloor+1; i++) {
                    if (liftOrders[i]) {
                        return HARDWARE_MOVEMENT_DOWN;
                    }
                }
                //Lift changes direction if ordered above currentFloor on Heispanel
                for (int i = currentFloor; i < 4; i++) {
                    if (liftOrders[i]) {
                        return HARDWARE_MOVEMENT_UP;
                    }
                }
                //If not ordered on Heispanel, lift continues down
                return HARDWARE_MOVEMENT_DOWN;
                break;
                
            default:
                break;
        }
    }
    return HARDWARE_MOVEMENT_STOP;
}

int orderedAboveUp(int currentFloor) {
    if (currentFloor == 3) {
        return 0;
    }
    for (int i = currentFloor + 4; i < 7; i++) {
        if (liftOrders[i] == 1) {
            return 1;
        }
    }
    return 0;
}

int orderedAboveDown(int currentFloor) {
    if (currentFloor == 3) {
        return 0;
    }
    for (int i = currentFloor + 7; i < 10; i++) {
        if (liftOrders[i] == 1) {
            return 1;
        }
    }
    return 0;
}
/*
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
*/
int orderedBelowUp(int currentFloor) {
    if (currentFloor == 0) {
        return 0;
    }
    for (int i = 4; i < 7 - currentFloor; i++) {
        if (liftOrders[i] == 1) {
            return 1;
        }
    }
    return 0;
}

int orderedBelowDown(int currentFloor) {
    if (currentFloor == 0) {
           return 0;
       }
       for (int i = 7; i < 10 - currentFloor; i++) {
           if (liftOrders[i] == 1) {
               return 1;
           }
       }
    return 0;
}

/*
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
*/

//sjekker om det er ordre i køen
int haveOrders() {
    for (int i = 0; i < 10; i++) {
        if (liftOrders[i] == 1){
            return 1;
        }
    }
    return 0;
}

