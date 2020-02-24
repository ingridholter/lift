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
int currFloor;
//int between;
HardwareMovement currentDir;
HardwareMovement newDir;
liftState currentState;
//må ha en neste tilstand varibabel



// må bestemme returverdier
/**
* @brief Initializes lift.
*/
int driveToDefinedState();

int atFloor();

/**
 * @brief State Machine, decides the elevator state.
 *
 */
void stateMachine();

#endif
