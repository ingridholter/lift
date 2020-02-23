/**
* @file
* @brief A library containing the LiftOrder module
*/


#ifndef LIFTORDER_H__
#define LIFTORDER_H__

#include "hardware.h"

//functions

/**
* @brief
*/
void setLiftOrders();

/**
* @brief
*/
void removeOrders(int CurrentFloor);

/**
* @brief
*/
void removeAllOrders();


//returnerer 1 hvis den skal stoppe i etasje og 0 hvis ikke
/**
* @brief
*/
int isCurrentFloorDemanded(int CurrentFloor);

//setter heisens retning 1:ned og 0:opp
//går gjennom array og sjekker
/**
* @brief
*/
int setDirection();

//er heisen krevd over gjeldene etasje
/**
* @brief
*/
int ordered_above(int CurrentFloor);

//er heisen krev under gjeldende etasje
/**
* @brief
*/
int ordered_below(int CurrentFloor);


