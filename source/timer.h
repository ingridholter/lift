/**
 * @file
 * @brief The Timer module. A library containing functions regarding the timer
 */

#ifndef _TIMER__
#define _TIMER__

#include <time.h>

/**
 * @brief Checks if the lift is ordered and sets the liftOrders array. Lights the order lights accordingly
 */
const int timeLimit = 3;

/**
 * @brief Checks if the lift is ordered and sets the liftOrders array. Lights the order lights accordingly
 */
clock_t clockVar;

/**
 * @brief Sets a new timestamp
 */
void timerReset();

/**
 * @brief Checks if more than timeLimit seconds have passed since last time timer was reset
 * @return 1 if the time limit has passed, 0 otherwise.
  */
int timerExpired();

#endif
