/**
 * @file
 * @brief The timer module. A library containing functions regarding the timer.
 */

#ifndef _TIMER__
#define _TIMER__

#include <time.h>

/**
 * @brief Sets a new timestamp.
 */
void timerReset();

/**
 * @brief Checks if more than 3 seconds have passed since timerReset().
 * @return 1 if the time limit has passed, 0 otherwise.
  */
int timerExpired();

#endif
