#ifndef LIFTORDER_H__
#define LIFTORDER_H__

#include "hardware.h"

//functions

void setLiftOrders();

void removeOrders(int CurrentFloor);

void removeAllOrders();

void getLiftOrders(); //returnere array?


//returnerer 1 hvis den skal stoppe i etasje og 0 hvis ikke
int isCurrentFloorDemanded(int CurrentFloor);

//setter heisens retning 1:ned og 0:opp
//går gjennom array og sjekker
int setDirection();

//er heisen krevd over gjeldene etasje
int ordered_above(int CurrentFloor);

//er heisen krev under gjeldende etasje
int ordered_below(int CurrentFloor);


