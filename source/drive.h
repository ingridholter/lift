/**
* @file
* @brief Sets the lift's direction and motorpower in order to get desired behavior.
*
*/
#ifndef _DRIVE__
#define _DRIVE__

#include "liftOrder.h"
#include "timer.h"

typedef enum{
  levelOpen,
  levelClosed,
  moving,
  stationaryBetweenFloors 
}liftState;

//Drive variables
int currentFloor;
//int 1-3 for between floors
int betweenFloor;
int stopSignal;
HardwareMovement currentDir;
HardwareMovement newDir;
liftState currentState;

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
