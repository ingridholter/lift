/**
 * @file
 * @brief Handles all orders of the lift.
 * Updates the position of the lift.
 * Finds out where to drive next and where to stop.
 */

#ifndef LIFTORDER_H__
#define LIFTORDER_H__

#include "hardware.h"
#include <stdio.h>

/**
 * @brief Checks down orders.
 *
 * @param floor The floor that is being checked for down orders.
 *
 * @return Index of the down order at @p floor in @c liftOrders[].
 */
int ordersDown(int floor);

/**
 * @brief Checks inside orders.
 *
 * @param floor The floor that is being checked for inside orders.
 *
 * @return Index of the inside order at @p floor in @c liftOrders[].
 */
int ordersInside(int floor);

/**
 * @brief Checks up orders.
 *
 * @param floor The floor that is being checked for up orders.
 *
 * @return Index of the up order at @p floor in @c liftOrders[].
 */
int ordersUp(int floor);

/**
 * @brief Checks all the order buttons.
 * Sets @c liftOrders[] and order lights accordingly.
 */
void setOrders();

/**
 * @brief Removes orders at @p currFloor from @c liftOrders[] and turnes off the order lights.
 *
 * @param currFloor The current floor where orders have been handled.
 */
void clearOrders(int currFloor);

/**
 * @brief Removes all the orders in @c liftOrders[] and turnes off all the order lights.
 */
void clearAllOrders();

/**
 * @brief Checks if the lift is ordered above @p currFloor.
 *
 * @param currFloor The current floor.
 *
 * @return 1 if there is an order above @p currFloor; 0 otherwise.
 */
int orderedAbove(int currFloor);

/**
 * @brief Checks if the lift is ordered below @p currFloor.
 *
 * @param currFloor The current floor.
 *
 * @return 1 if there is an order below @p currFloor; 0 otherwise.
 */
int orderedBelow(int currFloor);

/**
 * @brief Checks for orders in @c liftOrders[].
 *
 * @return 1 if there are any orders; 0 otherwise.
 */
int checkIfOrders();

/**
 * @brief Decides which direction the lift should go next.
 * If there are orders above and below @p currFloor, the lift continues in @p currDir.
 * This is unless @p currDir = HARDWARE_MOVEMENT_STOP; the lift will then choose to go down.
 *
 * @param currFloor The current floor.
 * @param currDir The current direction.
 * @param betwFloor The floor directly above; 0 if the lift is at a floor.
 *
 * @return The new direction.
 */
HardwareMovement setDirection(int currFloor, HardwareMovement currDir, int betwFloor);

/**
 * @brief Decides if the lift should stop.
 * The lift should stop if it has an inside order at @p currFloor, or if it is ordered in @p currDir.
 *
 * @param currFloor The current floor.
 * @param currDir The current direction.
 *
 * @return 1 if the lift should stop at @p currFloor; 0 otherwise.
 */
int isCurrentFloorDemanded(int currFloor, HardwareMovement currDir);

/**
 * @brief Checks if lift is ordered at @p currFloor.
 *
 * @param currFloor The current floor.
 *
 * @return 1 if the lift is ordered at @p currFloor; 0 otherwise.
 */
int isFloorOrdered(int currFloor);

/**
 * @brief Checks which floor the lift is currently on.
 *
 * @return The current floor; -1 if the lift is not at a floor.
 */
int getFloorNumber();

/**
 * @brief Updates @c nextFloor.
 *
 * @param currDir The current direction.
 * @param currFloor The current floor.
 *
 * @return The next floor the lift will reach if @p currDir is not changed.
 */
int updateNextFloor(int currFloor, HardwareMovement currDir);

/**
 * @brief Updates the @c betweenFloor.
 *
 * @param nFloor The next floor the lift will reach.
 * @param currFloor The current floor.
 *
 * @return The floor the lift is directly under.
 */
int updateBetweenFloor(int nFloor, int currFloor);

#endif
