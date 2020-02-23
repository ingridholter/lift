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
void removeOrders(int currentFloor);

/**
* @brief
*/
void removeAllOrders();


//returnerer 1 hvis den skal stoppe i etasje og 0 hvis ikke
/**
* @brief Stops the lift when it arrives at a floor where it is demanded
*in the same direction that it is driving as well as at the floors where someone wants to get out of the elevator.
*/
int isCurrentFloorDemanded(int currentFloor, int currentDir);

//setter heisens retning 1:ned og 0:opp
//går gjennom array og sjekker
/**
* @brief Decides where the lift should go next and sets the motor direction.
*/
int setDirection();


//er heisen krevd over gjeldene etasje
/**
* @brief
*/
int orderedAbove(int CurrentFloor);

//er heisen krev under gjeldende etasje
/**
* @brief
*/
int orderedBelow(int CurrentFloor);

/**
* @brief
*/
int haveOrders();
