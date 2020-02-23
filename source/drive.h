/**
* @file
* @brief Sets the lift's direction and motorpower in order to get desired behavior.
*
*/

#ifndef _DRIVE__
#define _DRIVE__

#include "hardware.h"
#include "liftOrder.h"


// må bestemme returverdier

/**
* @brief State Machine, decides the elevator state.
*
*/
stateMachine();

/**
* @brief Stops the lift when it arrives at a floor where it is demanded in the same direction that it is driving as well as at the floors where someone wants to get out of the elevator.
*/
isCurrentFloorDemanded();

/**
* @brief Decides where the lift should go next and sets the motor direction.
*/
setDirection();


/**
* @brief Finner ut hva denne skal gjøre senere
*/
manageDoor();

