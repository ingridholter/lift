/**
* @file
* @brief Sets the lift's direction and motorpower in order to get desired behavior.
*
*/

#ifndef _DRIVE__
#define _DRIVE__

//#include "hardware.h" Finnes i liftOrder
#include "liftOrder.h"
#include "timer.h"

typedef enum{
  levelOpen,
  levelClosed,
  moving,
  stationaryBetweenFloors 
}liftState;

//Drive variables
int prevFloor = -1;
int currentFLoor = 5;
HardwareMovement currentDir;
liftState currentState;
//må ha en neste tilstand varibabel
static int liftOrders[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


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
