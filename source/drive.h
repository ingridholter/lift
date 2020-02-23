/**
* @file
* @brief Sets the lift's direction and motorpower in order to get desired behavior.
*
*/

#ifndef _DRIVE__
#define _DRIVE__

//#include "hardware.h" Finnes i liftOrder
#include "liftOrder.h"

typedef enum{
  levelOpen
  levelClosed
  moving
  stationaryBetweenFloors 
}liftState;



// må bestemme returverdier
/**
* @brief Initializes lift.
*/
int driveToDefinedState();



/**
* @brief Finner ut hva denne skal gjøre senere
*/
manageDoor();

/**
 * @brief State Machine, decides the elevator state.
 *
 */
stateMachine();
