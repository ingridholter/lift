/**
 * @file
 * @brief A library containing the LiftOrder module
 */

#ifndef LIFTORDER_H__
#define LIFTORDER_H__

#include "hardware.h"
#include <stdio.h>
/*
/**
 * @brief int
 */

const int liftOrdersSize = 10;
/*
/**
 * @brief int
 */

static int liftOrders[liftOrdersSize] = {0};
/*
/**
 * @brief int
 */

const int lowerFloor = 0;
/*
/**
 * @brief int
 */

const int upperFloor = 3;

/**
 * @brief Gives the correct value of the down orders in the liftOrders array. 
 * @param[in] floor. 0-3 integer value of where the lift has been ordered. 
 */
int ordersDown(int floor);

/**
 * @brief Gives the correct value of the inside orders in the liftOrders array.
 * @param[in] floor. 0-3 integer value of where the lift has been ordered.
 */
int ordersInside(int floor);

/**
 * @brief Gives the correct value of the up orders in the liftOrders array.
 * @param[in] floor. 0-3 integer value of where the lift has been ordered.
 */
int ordersUp(int floor);

/**
 * @brief Checks if the lift is ordered and sets the liftOrders array. Lights the order lights accordingly
 */
void setOrders();

/**
 * @brief removes handled orders from liftOrders array. Turnes of lights accordingly
 * @param[in] currFloor The floor the lift is currently on. Must be an integer in range 0-3.
 */
void clearOrders(int currFloor);

/**
 * @brief removes all orders in liftOrder array. Turnes off all order lights
 */
void clearAllOrders();

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
 * @brief Checks if there is any orders in the liftOrders array.
 */
int checkIfOrders();

/**
 * @brief Decides where the lift should go next and sets the motor direction.
 * @param[in] currFloor The floor the lift is currently on. Must be an integer in range 0-3.
 * @param[in] currDir The direction of the lift. Must be of enum type HardwareMovement.
 * @param[in] betwFloor A value for the areas between floors. Must be an integer in range 1-3.
 * @return HardwareMovement enum type, the new direction for the lift.
 */
HardwareMovement setDirection(int currFloor, HardwareMovement currDir, int betwFloor);

/**
 * @brief Stops the lift when it arrives at a floor where it is demanded in the same direction that it is driving as well as at the floors where someone wants to get out of the lift.
 * @param[in] currFloor The floor the lift is currently on. Must be an integer in range 0-3.
 * @param[in] currDir The direction of the lift. Must be of enum type HardwareMovement
 * @return 1 if the lift should stop at currFloor, 0 otherwise
 */
int isCurrentFloorDemanded(int currFloor, HardwareMovement currDir);

/**
 * @brief Checks if lift is ordered at floor.
 * @param[in] currFloor The floor the lift is currently on. Must be an integer in range 0-3.
 * @return 1 if the lift is ordered at floor, 0 if not.
 */
int isFloorOrdered(int currFloor);

/**
 * @brief Gives the value of the lifts floor.
 * @return 0-3 integer of the floor the lift is currently at.
 */
int getFloorNumber();

/**
 * @brief Updates the nextFloor variable.
 * @param[in] currDir The direction of the lift. Must be of enum type HardwareMovement
 * @return 1-3 integer value. Gives the next floor the lift will reach, given the current direction.
 */
int updateNextFloor(int currFloor, HardwareMovement currDir);

/**
 * @brief Updates the betweenfloor variable.
 * @param[in] currDir The direction of the lift. Must be of enum type HardwareMovement
 * @param[in] currFloor The floor the lift is currently on. Must be an integer in range 0-3.
 * @return 1-3 integer value. Gives which floor the lift is directly under.
 */
int updateBetweenFloor(int nFloor, int currFloor);

#endif
