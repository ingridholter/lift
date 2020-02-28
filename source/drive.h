/**
 * @file
 * @brief Drives the lift first by initializing and then by using different states in the @c stateMachine().
 */
#ifndef _DRIVE__
#define _DRIVE__

#include "liftOrder.h"
#include "timer.h"

/**
 * @brief Lift states used to switch between states in @c stateMachine().
 */
typedef enum{
  levelOpen,
  levelClosed,
  moving,
  stationaryBetweenFloors 
}liftState;

/**
 * @brief Initializes lift.
 *
 * @return 1 on success; 0 otherwise.
 */
int driveToDefinedState();

/**
 * @brief Sets the @c currentState. Decides the lift's direction and motorpower in order to get desired behavior.
 */
void stateMachine();

#endif
