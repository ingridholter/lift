/**
* @file
* @brief A library containing the LiftOrder module
*/

#ifndef LIFTORDER_H__
#define LIFTORDER_H__

#include "hardware.h"
#include <stdlib.h>
//#include <stdio.h>


/**
 * @brief Array of where the lift has been ordered, 0-3: inside orders, 4-6 up orders, 7-9 down orders. 
 */
//static int liftOrders[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//static int liftOrders[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static int liftOrders[10] = {0};
/**
* @brief Checks if the lift is ordered and sets the liftOrders array. Lights the order lights accordingly
*/
void setLiftOrders();

/**
* @brief removes handled orders from liftOrders array. Turnes of lights accordingly
* @param[in] currentFloor The floor the lift is currently on. Must be an integer in range 0-3.
*/
void removeOrders(int currentFloor);

/**
* @brief removes all orders in liftOrder array. Turnes off all order lights
*/
void removeAllOrders();

/**
* @brief Stops the lift when it arrives at a floor where it is demanded
*in the same direction that it is driving as well as at the floors where someone wants to get out of the elevator.
* @param[in] currentFloor The floor the lift is currently on. Must be an integer in range 0-3.
* @param[in] currentDir The direction of the lift. Must be of enum type HardwareMovement 
* @return 1 if the lift should stop at currentFloor, 0 otherwise
*/
int isCurrentFloorDemanded(int currentFloor, HardwareMovement currentDir);


/**
* @brief Decides where the lift should go next and sets the motor direction.
* @param[in] currentFloor The floor the lift is currently on. Must be an integer in range 0-3.
* @param[in] currentDir The direction of the lift. Must be of enum type HardwareMovement.
* @return HardwareMovement enum type.
*/
HardwareMovement setDirection(int currentFloor, HardwareMovement currentDir);


/**
* @brief  Checks if lift is ordered above currentFloor
* @param[in] currentFloor The floor the lift is currently on. Must be an integer in range 0-3.
*/
int orderedAbove(int currentFloor);

/**
* @brief Checks if lift is ordered below currentFloor.
* @param[in] currentFloor The floor the lift is currently on. Must be an integer in range 0-3.
*/
int orderedBelow(int currentFloor);

/**
* @brief checks if there is any orders in the liftOrders array.
*/
int haveOrders();


#endif
