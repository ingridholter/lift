/**
* @file
* @brief Sets the lift's direction and motorpower in order to get desired behavior.
*
*/

#ifndef _DRIVE__
#define _DRIVE__


#include "liftOrder.h"
#include "timer.h"
#include <stdio.h>

/*
#include "hardware.h" //Finnes i liftOrder
#include <stdio.h>
#include <stdlib.h>
*/

typedef enum{
  levelOpen,
  levelClosed,
  moving,
  stationaryBetweenFloors 
}liftState;

//Drive variables
int preFloor;
int currFloor;
int nextFloor;
HardwareMovement currentDir;
liftState currentState;
//må ha en neste tilstand varibabel



// må bestemme returverdier
/**
* @brief Initializes lift.
*/
int driveToDefinedState();



/**
 * @brief State Machine, decides the elevator state.
 *
 */
void stateMachine();

#endif
