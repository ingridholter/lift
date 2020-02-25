/**
* @file
* @brief A library containing the LiftOrder module
*/

#ifndef LIFTORDER_H__
#define LIFTORDER_H__

#include "hardware.h"
#include <stdlib.h>
#include <stdio.h>


/**
 * @brief Array of where the lift has been ordered, 0-3: inside orders, 4-6 up orders, 7-9 down orders. 
 */

/**
* @brief Checks if the lift is ordered and sets the liftOrders array. Lights the order lights accordingly
*/
void setLiftOrders();

/**
* @brief removes handled orders from liftOrders array. Turnes of lights accordingly
* @param[in] currFloor The floor the lift is currently on. Must be an integer in range 0-3.
*/
void removeOrders(int currFloor);

/**
* @brief removes all orders in liftOrder array. Turnes off all order lights
*/
void removeAllOrders();

/**
* @brief Stops the lift when it arrives at a floor where it is demanded
*in the same direction that it is driving as well as at the floors where someone wants to get out of the elevator.
* @param[in] currFloor The floor the lift is currently on. Must be an integer in range 0-3.
* @param[in] currDir The direction of the lift. Must be of enum type HardwareMovement
* @return 1 if the lift should stop at currFloor, 0 otherwise
*/
int isCurrentFloorDemanded(int currFloor, HardwareMovement currDir);


/**
* @brief Decides where the lift should go next and sets the motor direction.
* @param[in] currFloor The floor the lift is currently on. Must be an integer in range 0-3.
* @param[in] currDir The direction of the lift. Must be of enum type HardwareMovement.
* @return HardwareMovement enum type.
*/
HardwareMovement setDirection(int currFloor, HardwareMovement currDir);

/**
* @brief  Checks if lift is ordered above currFloor
* @param[in] currFloor The floor the lift is currently on. Must be an integer in range 0-3.
*/
int orderedAbove(int currFloor);

/**
* @brief Checks if lift is ordered below currFloor.
* @param[in] currFloor The floor the lift is currently on. Must be an integer in range 0-3.
*/
int orderedBelow(int currFloor);

/**
* @brief checks if there is any orders in the liftOrders array.
*/
int haveOrders();

int orderedAtFloor(int currFloor);


#endif
