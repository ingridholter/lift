#include "liftOrder.h"


const int liftOrder_size = 10;

//2??
static int liftOrders[2][liftOrder_size] = {0};


//legge til i liftOrders hvilke knapper som er trykket? checkButtons
void setLiftOrders(){
    checkButtons();
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
int setDirection();

//er heisen krevd over gjeldene etasje
int ordered_above(int CurrentFloor);

//er heisen krev under gjeldende etasje
int ordered_below(int CurrentFloor);

//sjekker om det er ordre i køen
int have_orders();

