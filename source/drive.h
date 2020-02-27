/**
* @file
* @brief Sets the lift's direction and motorpower in order to get desired behavior.
*
*/
#ifndef _DRIVE__
#define _DRIVE__

#include "liftOrder.h"
#include "timer.h"

//Fjern denne dersom koden fungerer uten:
//HardwareMovement newDir;

/**
* @brief Order type used in @c hardware_read_order
* and in @c hardware_command_order_light.
*/
typedef enum{
  levelOpen,
  levelClosed,
  moving,
  stationaryBetweenFloors 
}liftState;

/**
 * @brief A 0-3 integer value for the current floor the lift is at. 
  */
int currentFloor;

/**
 * @brief A 1-3 integer value for the areas between floors. 
  */
int betweenFloor;

/**
 * @brief A 0 or 1 integer value. 1 if stopSignal is high, 0 if not.
  */
int stopSignal;

/**
 * @brief A HardwareMovement type. The current direction of the lift. 
  */
HardwareMovement currentDir;

/**
 * @brief Holds the current state of the lift
  */
liftState currentState;

/**
* @brief Initializes lift.
* @return 0 if not able to initialize. 1 if inizialized. 
*/
int driveToDefinedState();

/**
 * @brief State Machine, decides the lift state.
 *
 */
void stateMachine();

#endif
