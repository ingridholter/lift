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
    if (currentDir = HARDWARE_MOVEMENT_UP && liftOrders[currentFloor+4])
        return 1;
    if (currentDir = HARDWARE_MOVEMENT_DOWN && liftOrders[currentFloor+6])
        return 1;
    return 0;
}



//setter heisens retning 1:ned og 0:opp
//går gjennom array og sjekker
HardwareMovement setDirection(int currentFloor, HardwareMovement currentDir) {
    
    for (int i = 0; i < 4; i++) {
        if (liftOrders[i])
    }
    
    switch (currentFloor) {
        case 0:
            
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        default: // code to be executed if n doesn't match any cases
    }
}
    /*
     
     Bestemmer om heisen skal opp, ned eller stoppe.
     Går gjennom arrayet, for å sjekke hva som er neste etasje å dra til.

     Fortsetter i samme retning dersom det er bestillinger eller ønsker i den retningen.
     Retning lagret i lokal variabel.

     Dersom heis er på vei opp betjenes bestillinger i retning opp og alle ønsker.
     Heis på vei opp: Fortsetter opp dersom heis bestilt oppover eller noen skal av over

     Dersom heis er på vei ned betjenes bestillinger i retning ned og alle ønsker.

     Dersom heisen ikke er ønsket i nåværende retning, snu om det finnes andre bestillinger.

     Ellers stå stille.

    for (i=0; i<10, i++) {
        array[i][1]
        if(array[i][1]==inside) //bestilt fra insiden
        {
            if(array[i][0]>currentFloor){
                direction = up;
                return direction;
            }
            if (array[i][0]<currentFloor){
                direction = down;
                return direction;
            }
        }
        //hva mer skal gjøres her;
    }
}

*/
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

