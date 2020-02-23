#include "liftOrder.h"


const int liftOrderSize = 10;

static int liftOrders[liftOrderSize] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


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
        // liftOrders[i] = 0;
}


//returnerer 1 hvis den skal stoppe i etasje og 0 hvis ikke
int isCurrentFloorDemanded(int currentFloor, HardwareMovement currentDir){
    if (liftOrders[currentFloor])
        return 1;
    if (currentDir = HARDWARE_MOVEMENT_UP && liftOrders[currentFloor+4])
        

}
Stopper heisen dersom
-nåværende etasje er ønsket
-nåværende etasje er bestilt i nåværende retning,
sjekker om nåværende retning tilsvarer UP eller DOWN.


//setter heisens retning 1:ned og 0:opp
//går gjennom array og sjekker
int setDirection() {
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

//er heisen krevd over gjeldene etasje
int orderedAbove(int CurrentFloor);

//er heisen krev under gjeldende etasje
int orderedBelow(int CurrentFloor);

//sjekker om det er ordre i køen
int haveOrders();

