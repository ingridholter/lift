/**
* @file
* @brief The Timer module. A library containing functions regarding the timer
*/

#ifndef _TIMER__
#define _TIMER__

#include <time.h>

/**
* @brief Sets a new timestamp
*/
void timerReset();

//Checks if more than timeLimit seconds since last ?timestamp?

/**
* @brief Checks if more than timeLimit seconds have passed since last time timer was reset
* @return 1 if the time limit has passed, 0 otherwise.
*/
int timerExpired();

#endif
