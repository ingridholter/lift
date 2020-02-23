#include "liftOrder.h"


const int liftOrderSize = 10;

static int liftOrders[liftOrderSize] = {0};


//legge til i liftOrders hvilke knapper som er trykket? checkButtons
// Begge funksjonene checkOrderButtons og setLiftOrders?
void setLiftOrders(){
    int hardware_read_order (int floor, HardwareOrder order_type)
}

void removeOrders(int CurrentFloor){
    for (i in liftOrders[][]){
        
    }
}

void removeAllOrders();

void getLiftOrders(); //returnere array?


//returnerer 1 hvis den skal stoppe i etasje og 0 hvis ikke
int isCurrentFloorDemanded(int CurrentFloor){
    
}


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

