/**
 * @file
 * @brief Uses the library @c time.h to set a timer and check if it has expeired.
 */

#ifndef _TIMER__
#define _TIMER__

#include <time.h>

/**
 * @brief Sets a new timestamp.
 */
void timerReset();

/**
 * @brief Checks if more than 3 seconds have passed since @c timerReset.
 *
 * @return 1 if the time limit has passed; 0 otherwise.
 */
int timerExpired();

#endif
